#include "i2c.h"

#define I2C_set_scl() { I2C_DR |= (1 << I2C_SCL_PIN); } //Poner SCL en alto
#define I2C_clear_scl() { I2C_DR &= ~(1 << I2C_SCL_PIN); } //Poner SCL en bajo
#define I2C_set_sda() { I2C_DR |= (1 << I2C_SDA_PIN); } //Poner SDA en alto
#define I2C_clear_sda() { I2C_DR &= ~(1 << I2C_SDA_PIN); } //Poner SDA en bajo
#define I2C_bus_init() { I2C_DR |= ((1 << I2C_SDA_PIN) | (1 <<I2C_SCL_PIN)); } //Poner ambos pines en alto
#define I2C_get_sda I2C_DR_IN &  (1 << I2C_SDA_PIN) //Obtener valor de SDA


//Half a bit delay
#define HALF_BIT_DELAY delay_us(5);


//I2C doesn't work on STM32. We implement it by software. It's super ADHOC.
void I2C_Init(){
    //Config GPIO pins
    RCC->APB2ENR |= (0xFC); /* enable clocks for GPIOs */
    RCC->APB1ENR |= (1<<21); /* enable clock for I2C1 */
    GPIOB->CRL |= 0x77000000; /* configure PA6 and PA7 as GPO. open drain */
    I2C_set_scl();
    I2C_set_sda();
}


void i2c_waitForReady(){
    while((I2C1->SR2&(1<<1)) != 0); /* check bus busy (FLAG) via pooling */
}

//Send start signal
void I2C_SendStart(){
    I2C_bus_init(); //put both pins on high

    //Wait half bit, put SDA low
	HALF_BIT_DELAY
    I2C_clear_sda(); //SDA goes low

    //Wait half bit, put SCL LOW
    HALF_BIT_DELAY
    I2C_clear_scl(); //SCL goes low
    HALF_BIT_DELAY

}

//Send stop signal
void I2C_SendStop(){
    I2C_clear_sda(); //SDA goes low
    I2C_clear_scl(); //SCL goes low
    HALF_BIT_DELAY

    //Wait half bit, put SCL HIGH
    I2C_set_scl(); //SCL goes high
    HALF_BIT_DELAY

    //Wait half bit, put SDA HIGH
    I2C_set_sda(); //SDA goes high
    HALF_BIT_DELAY

}

//This function will send Address for read
uint8_t I2C_SendAddrForRead(uint8_t addr){
    return I2C_SendData((addr<<1) | 1); //addr + Read(1)
}

//This function will send Address for write
uint8_t I2C_SendAddrForWrite(uint8_t addr){
    return I2C_SendData(addr<<1); //addr+Write(0)
}

//This function will send data to the slave
//Return 1 if ACK received, 0 if NACK received
uint8_t I2C_SendData(uint8_t data){
    unsigned char msk = 0x80;	//Mask, starts in 1000 0000
    unsigned char ack;		//Acknowledge received from slave
   
    //We transmit the 7+1 bits of data
    do
    {
        //We use the mask to check if the bit is 1 or 0
        if (data & msk)  {I2C_set_sda();} 
        else {I2C_clear_sda();}
        
        //Set SCL, then wait half bit and clear SCL, in order for slave to read SDA.
        I2C_set_scl();
        HALF_BIT_DELAY
        I2C_clear_scl();
    }
    while ((msk>>=1) != 0); //Shift mask to the right 1 bit and check if it's 0

    //After sending 8 bits, we set both SDA and SCL, and wait half a bit
    I2C_set_sda();
    I2C_set_scl();
    HALF_BIT_DELAY

    //Here, if ACK is sent by slave, SDA will be drained to low, otherwise it will be high
    //So we read it.
    ack =(I2C_get_sda);

    //Finally, we clear SCL before leaving function
    I2C_clear_scl();
    HALF_BIT_DELAY

    //We return true if sending data was successful. False otherwise.
    return (!ack);
}

//This function will read data from the slave
//It receives ack which is used in burst reading to know when to stop
//Data read is returned
uint8_t I2C_ReadData(uint8_t send_nack){
    unsigned char msk = 0x80;	//Mask, starts in 1000 0000
    unsigned char b = 0;		//Buffer for the received data

    //Receive bit by bit
    do
    {
        //Set SCL and wait half bit
        I2C_set_scl();
        HALF_BIT_DELAY
        
        //We read SDA, if it is 1 we set the bit in the buffer (using mask to know which bit)
        if(I2C_get_sda)  b|=msk;
        
        //Clear SCL and wait half bit for next bit
        I2C_clear_scl();
        HALF_BIT_DELAY
    }
    while ((msk>>=1) != 0); //We shift mask to the right 1 bit and check if it's 0 in order to read every bit.
        
    //We check ack parameter to know if we need to send ACK or NACK
    if(send_nack == 0) //We send ACK (still not finished reading)
    {
        I2C_clear_sda();
    }
    else //send_nack = 1, We send NACK (notify slave we end read )
    {
        I2C_set_sda();
    }

    //Set SCL to send ACK/NACK (then wait half bit)
    I2C_set_scl();
    HALF_BIT_DELAY
    //Clear SCL to finish sending ACK/NACK
    I2C_clear_scl();
    //Free SDA line. Then wait half bit we are ready for next operation
    I2C_set_sda();
    HALF_BIT_DELAY

    //Return read data
    return (b);
}
