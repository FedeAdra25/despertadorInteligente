#include "gpio.h"

void GPIO_Init(){
    //---
    GPIOA->CRH = 0x44444488; //PA8 and PA9 as input with pull-up 
    GPIOB->CRH = 0x88884434; //PB8,9,10,11,12,13 as input with pull-up
    //---                   PB9 as output with push-pull (0011)
}

//RETURNS BUTTON_MENU or BUTTON_SELECT
void GPIOS_getButtonPressed(uint8_t* buttonPressed)
{
    //TODO: ver de mover esto a una librería
    //Also, order of this ifs matters. CANCEL has priority
    if (getCancel() != 0)
    {
        *buttonPressed = BUTTON_CANCEL;
        return;
        //return BUTTON_CANCEL;
    }
    if (getOk() != 0)
    {
        *buttonPressed = BUTTON_OK;
        return;
        //return BUTTON_OK;
    }
    if (getUp() != 0)
    {
        *buttonPressed = BUTTON_UP;
        return;
        //return BUTTON_UP;
    }
    if (getDown() != 0)
    {
        *buttonPressed = BUTTON_DOWN;
        return;
        //return BUTTON_DOWN;
    }
    if (getLeft() != 0)
    {
        *buttonPressed = BUTTON_LEFT;
        return;
        //return BUTTON_LEFT;
    }
    if (getRight() != 0)
    {
        *buttonPressed = BUTTON_RIGHT;
        return;
        //return BUTTON_RIGHT;
    }
    *buttonPressed = BUTTON_NONE;
    return;
    //return BUTTON_NONE;
}
