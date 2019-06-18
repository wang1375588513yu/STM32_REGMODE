/********************************Copyright (c)******************************\
**
**                   (c) Copyright 2018, WangYu, China, SZ.
**                           All Rights Reserved
**
**                       		By(MR.Richard)
**
**----------------------------------File Information------------------------
** FileName:      led.h
** The Author:    WangYu
** Creation Date: 2018-08-27
** Description:   
**
**--------------------------------Version Information-----------------------
** Version NO: V1.0
** Version Description: Initial Version
**
**--------------------------------------------------------------------------
\********************************End of Head********************************/



#ifndef __LED_H__
#define __LED_H__

#include "user_config.h"

#define LED1_RCC_GPIO_CLK_ENABLE() 		__HAL_RCC_GPIOB_CLK_ENABLE()
#define LED1_GPIO						GPIOB
#define LED1_PIN						GPIO_PIN_6
#define LED1							1

#define LED2_RCC_GPIO_CLK_ENABLE() 		__HAL_RCC_GPIOE_CLK_ENABLE()
#define LED2_GPIO						GPIOE
#define LED2_PIN						GPIO_PIN_3
#define LED2							2

#define LED3_RCC_GPIO_CLK_ENABLE() 		__HAL_RCC_GPIOD_CLK_ENABLE()
#define LED3_GPIO						GPIOD
#define LED3_PIN						GPIO_PIN_15
#define LED3							3

#define LED_OFF							GPIO_PIN_SET		
#define LED_ON							GPIO_PIN_RESET

void Led_Init(void);
void Led_On(void);
void Led_Off(void);
void Led_Status_Reversal(unsigned char num);
void led_task(void);



#endif


