#ifndef MEF_H
#define MEF_H

#include <stm32f103x6.h>
#include <stdio.h>
#include <stdlib.h>
#include "dht22.h"
#include "ds1307.h"
#include "glcd.h"


typedef enum {IDLE,IDLE_ACTIVE, SETTING_DATE,SETTING_ALARM} MEF_state;


void MEF_Init(void);
void MEF_Update(void);


#endif
