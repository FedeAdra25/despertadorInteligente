#ifndef GPIO_H
#define GPIO_H

#include <stm32f103x6.h>



//This on port A
#define GPIOA_BUTTON_OK_PIN 8
#define GPIOA_BUTTON_CANCEL_PIN 9

//This on port B
#define GPIOB_BUTTON_BUZZER_PIN 9
#define GPIOB_BUTTON_UP_PIN 12
#define GPIOB_BUTTON_DOWN_PIN 13
#define GPIOB_BUTTON_LEFT_PIN 14
#define GPIOB_BUTTON_RIGHT_PIN 15


#define getOk() (GPIOA->IDR & (1 << GPIOA_BUTTON_OK_PIN))
#define getCancel() (GPIOA->IDR & (1 << GPIOA_BUTTON_CANCEL_PIN))
#define getUp() (GPIOB->IDR & (1 << GPIOB_BUTTON_UP_PIN))
#define getDown() (GPIOB->IDR & (1 << GPIOB_BUTTON_DOWN_PIN))
#define getLeft() (GPIOB->IDR & (1 << GPIOB_BUTTON_LEFT_PIN))
#define getRight() (GPIOB->IDR & (1 << GPIOB_BUTTON_RIGHT_PIN))

#define setBuzzer() {GPIOB->ODR |= 1 << GPIOB_BUTTON_BUZZER_PIN;}
#define resetBuzzer() {GPIOB->ODR &= ~(1 << GPIOB_BUTTON_BUZZER_PIN);}


#define BUTTON_NONE 0
#define BUTTON_OK 1
#define BUTTON_CANCEL 2
#define BUTTON_UP 3
#define BUTTON_DOWN 4
#define BUTTON_LEFT 5
#define BUTTON_RIGHT 6






//---

//TODO: ver de mover esto a una librería
void GPIO_Init(void);
void GPIOS_getButtonPressed(uint8_t* buttonPressed);

#endif
