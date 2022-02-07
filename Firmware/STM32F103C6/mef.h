#ifndef MEF_H
#define MEF_H

#include <stm32f103x6.h>
#include <stdio.h>
#include <stdlib.h>
#include "dht22.h"
#include "ds1307.h"
#include "glcd.h"

#define SELECTION_NONE 0
#define SELECTION_DAY 1
#define SELECTION_DATE 2
#define SELECTION_MONTH 3
#define SELECTION_YEAR 4
#define SELECTION_HOUR 5
#define SELECTION_MINUTE 6
#define SELECTION_SECOND 7
#define SELECTION_START 1
#define SELECTION_END 7
#define SELECTION_START_ALARM 5
#define SELECTION_END_ALARM 7

typedef enum {IDLE,IDLE_ACTIVE, SETTING_DATE,SETTING_ALARM} MEF_state;


void MEF_Init(void);
void MEF_Update(void);


#endif
