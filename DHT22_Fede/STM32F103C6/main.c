/* Main.c file generated by New Project wizard
 *
 * Created:   dom. ene. 23 2022
 * Processor: STM32F103C6
 * Compiler:  Keil for ARM
 */

#include "main.h"

/* Private function prototypes -----------------------------------------------*/
/*
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
*/
float temp, humidity;

char str[34];

int main(void)
{
  RCC->APB2ENR |= 0xFC | (1<<14); //enable clock for GPIO

  usart1_init();
  DHT22_Init();

  while (1)
  {
    DHT22_GetTemp_Humidity(&temp, &humidity);
    sprintf(str, "Temp: %.2f C, Humidity: %.2f %%\r\n", temp, humidity);
    usart1_sendStr(str);
    delay_ms(100);
  }
   
  
  return 0;
}
