#include "dht22.h"

//Macros for GPIO

#define DHT22_data_set() {DHT22_DR |= (1 << DHT22_DATA_PIN);}
#define DHT22_data_clear() {DHT22_DR &= ~(1 << DHT22_DATA_PIN);}
#define DHT22_data_get() (DHT22_DR_IN>>DHT22_DATA_PIN & 1)

//Private Functions Prototypes
uint8_t DHT22_SendStart(void);
uint8_t ReadByte(void);
uint8_t data[5]={0};
uint8_t datar=0;
uint32_t aux=0;

uint8_t VAR = 0;

void DHT22_Init(void){
    //We use PA15 as the DHT22 data pin, output open drain
    DHT22_DATA_PORT->CRH |= 0x70000000; //PA15 is GPO open drain -> setting it means pin gets pulled up
    DHT22_data_set(); //PA15 set to high
    delay_ms(1000);
}


uint8_t DHT22_GetTemp_Humidity(float *temp, float *humidity){
    uint8_t i;
    if(temp==0 || humidity==0)
        return 0;
    if(DHT22_SendStart()){
        for(i=0; i<5; i++){
            data[i] = ReadByte();
        }
        //Checksum check
        if(data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)){
            *temp = (float)((data[2] & 0x7F) << 8 | data[3]) / 10; //TODO check this
            *humidity = (float)(data[0] << 8 | data[1]) / 10; //TODO check this
            return 1;
        }
    }
    return 0;
}

//This function will send start signal to DHT22
//Return 1 if success, 0 if fail
//Returns when DHT22 is about to start data transmission
uint8_t DHT22_SendStart(){
    aux=1;
    //Set data pin to low
    DHT22_data_clear(); //PA15 set to low
    //Wait for 1ms
    delay_ms(18);
    //Set data pin to high and wait DHT22 response
    DHT22_data_set(); //PA15 set -> high impedance
    VAR  = DHT22_data_get();
    //Wait for DHT22 response
    while(DHT22_data_get()!=0 && ++aux!=DHT22_RESPONSE_TOLERANCE); //Wait sensor response
    VAR = DHT22_data_get();
    if(aux==DHT22_RESPONSE_TOLERANCE)
        return 0;
    //Wait for DHT22 to release data pin
    aux=1;
    VAR = DHT22_data_get();
    delay_us(40);
    VAR = DHT22_data_get()==0;
    while(DHT22_data_get()==0 && ++aux!=DHT22_RESPONSE_TOLERANCE); //Wait sensor to set voltage in high (~80us)
    VAR = DHT22_data_get()==0;
    delay_us(40);
    VAR = DHT22_data_get();
    while(DHT22_data_get()!=0 && ++aux!=DHT22_RESPONSE_TOLERANCE); //Wait sensor to set voltage in low (~80us)
    VAR = DHT22_data_get();
    //DHT is ready to send data
    return aux!=DHT22_RESPONSE_TOLERANCE;
}

//This function is supposed to be called AFTER a data start transmission has been sent
//It will read one byte from DHT22 assuming single-bus signal is being sent
//Return the byte read
uint8_t ReadByte(){
    uint8_t i=0;
    datar=0;
    while(i<8){
        //Wait for DHT22 response
        while(DHT22_data_get()==0); //Wait until PA15 gets high (~50us)
        //PA15 is high, if it stills high after more than 28us it means DHT22 is sending a 1
        //We wait for 29us just in case
        delay_us(29);
        if(DHT22_data_get() !=0)
            datar |= (1<<(7-i)); //We get PA15 state and set data bit accordingly
        //Wait for DHT22 to set pin to low before reading next bit
        while(DHT22_data_get()!=0); //PA15 is low
        i++;
    }
    return datar;
}
