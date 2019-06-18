/********************************Copyright (c)******************************\
**
**                    (c) Copyright 2018, WangYu, China, SZ.
**                            All Rights Reserved
**
**                               By(MR.Richard)
**
**----------------------------------File Information------------------------
** FileName:      led.c
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
/*PA5  --   LED*/

#include "led.h"
#include "sys.h"
#include "user_config.h"
#include "PUBLIC.h"
#include "timer.h"

#define  REG_MODE		0
#define  LIB_MODE		1
#define  CURRENT_MODE	REG_MODE

bool led1_on_flag = false;
bool led2_on_flag = false;
bool led3_on_flag = false;

#ifdef	LED_ENABLE
void Led_Init(void)
{
    
	#if (CURRENT_MODE == REG_MODE)
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;		//初始化GPIOB时钟
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIODEN;		//初始化GPIOB时钟
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;		//初始化GPIOB时钟
	
	/*00: Input mode
	  01: General purpose output mode
	  10: Alternate function mode
	  11: Analog mode (reset state)*/
	LED1_GPIO->MODER &= GPIO_MODER_MODER6_1;
	LED1_GPIO->MODER |= GPIO_MODER_MODER6_0;		/*01: General purpose output mode*/
			
	
	/*0: Output push-pull(PP) (reset state)
	  1: Output open-drain(OD)*/
	LED1_GPIO->OTYPER &= GPIO_OTYPER_OT_6;			/*0--Output push-pull(PP)*/
	/*00: Low speed
	  01: Medium speed
	  10: High speed
	  11: Very high speed*/
	LED1_GPIO->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6_1;
	LED1_GPIO->OSPEEDR &= GPIO_OSPEEDER_OSPEEDR6_0;	/*10 High speed*/
	/*00: No pull-up, pull-down
	  01: Pull-up
	  10: Pull-down
	  11: Reserved*/
	LED1_GPIO->PUPDR &= GPIO_PUPDR_PUPDR6_1;		/*01: Pull-up*/
	LED1_GPIO->PUPDR |= GPIO_PUPDR_PUPDR6_0;
	
	
	
	
	#elif(CURRENT_MODE == LIB_MODE)
	GPIO_InitTypeDef GPIO_Initure;
	
	LED1_RCC_GPIO_CLK_ENABLE();
	LED2_RCC_GPIO_CLK_ENABLE();	
	LED3_RCC_GPIO_CLK_ENABLE();
	
    GPIO_Initure.Pin = LED1_PIN;				//LED引脚
    GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;	//推挽输出
    GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;	//高速率
    GPIO_Initure.Pull = GPIO_PULLUP;			//上拉
    HAL_GPIO_Init(LED1_GPIO, &GPIO_Initure);
	
	GPIO_Initure.Pin = LED2_PIN;				//LED引脚
	HAL_GPIO_Init(LED2_GPIO, &GPIO_Initure);
	
	GPIO_Initure.Pin = LED3_PIN;				//LED引脚
	HAL_GPIO_Init(LED3_GPIO, &GPIO_Initure);

    HAL_GPIO_WritePin(LED1_GPIO, LED1_PIN, LED_OFF);
	HAL_GPIO_WritePin(LED2_GPIO, LED2_PIN, LED_OFF);
	HAL_GPIO_WritePin(LED3_GPIO, LED3_PIN, LED_OFF);
	#endif
}

void Led1_On(void)
{
    led1_on_flag = true;
    HAL_GPIO_WritePin(LED1_GPIO, LED1_PIN, LED_ON);
}

void Led1_Off(void)
{
    led1_on_flag = false;
    HAL_GPIO_WritePin(LED1_GPIO, LED1_PIN, LED_OFF);//初始为灭灯
}

void Led2_On(void)
{
    led2_on_flag = true;
    HAL_GPIO_WritePin(LED2_GPIO, LED2_PIN, LED_ON);
}

void Led2_Off(void)
{
    led2_on_flag = false;
    HAL_GPIO_WritePin(LED2_GPIO, LED2_PIN, LED_OFF);//初始为灭灯
}

void Led3_On(void)
{
    led3_on_flag = true;
    HAL_GPIO_WritePin(LED3_GPIO, LED3_PIN, LED_ON);
}

void Led3_Off(void)
{
    led3_on_flag = false;
    HAL_GPIO_WritePin(LED3_GPIO, LED3_PIN, LED_OFF);//初始为灭灯
}

void Led_Status_Reversal(unsigned char num)
{
	if(num == LED1)
	{
		if(!led1_on_flag)
			Led1_On();
		else
			Led1_Off();
	}
	else if(num == LED2)
	{
		if(!led2_on_flag)
			Led2_On();
		else
			Led2_Off();
	}
	else if(num == LED3)
	{
		if(!led3_on_flag)
			Led3_On();
		else
			Led3_Off();
	}
	else
	{
		return;
	}
    
}

unsigned int loop_delay = 0;
void led_water_loop(void)
{
	static unsigned char led_status = 0;
	static unsigned int softimersec=0xffffffff;
    if(softimersec==Get_SysmilliTick())return;
    softimersec=Get_SysmilliTick();
	
	if(loop_delay)
	{
		loop_delay--;
		return;
	}
	led_status++;
	loop_delay = 500;
	#if 0
	if(led_status == 1)
	{
		Led1_On();
		Led2_Off();
		Led3_Off();
	}
	else if(led_status == 2)
	{
		Led1_Off();
		Led2_On();
		Led3_Off();
	}
	else if(led_status == 3)
	{
		Led1_On();
		Led2_On();
		Led3_Off();
	}
	else if(led_status == 4)
	{
		Led1_Off();
		Led2_Off();
		Led3_On();
	}
	else if(led_status == 5)
	{
		Led1_Off();
		Led2_On();
		Led3_Off();
	}
	else if(led_status == 6)
	{
		Led1_Off();
		Led2_On();
		Led3_On();
	}
	else if(led_status == 7)
	{
		Led1_On();
		Led2_On();
		Led3_On();
	}
	else
	{
		Led1_Off();
		Led2_Off();
		Led3_Off();
		led_status = 0;
	}
	#else
	if(led_status == 1)
	{
		Led1_On();
		Led2_Off();
		Led3_Off();
	}
	else if(led_status == 2)
	{
		Led1_On();
		Led2_On();
		Led3_Off();
	}
	else if(led_status == 3)
	{
		Led1_On();
		Led2_On();
		Led3_On();
	}
	else if(led_status == 4)
	{
		Led1_On();
		Led2_On();
		Led3_Off();
	}
	else if(led_status == 5)
	{
		Led1_On();
		Led2_Off();
		Led3_Off();
	}
	else if(led_status == 6)
	{
		Led1_Off();
		Led2_On();
		Led3_Off();
	}
	else if(led_status == 7)
	{
		Led1_Off();
		Led2_Off();
		Led3_On();
	}
	else if(led_status == 8)
	{
		Led1_Off();
		Led2_On();
		Led3_Off();
	}
	else if(led_status == 9)
	{
		Led1_On();
		Led2_Off();
		Led3_Off();
	}
	else if(led_status == 10)
	{
		Led1_Off();
		Led2_Off();
		Led3_Off();
	}
	else
	{
		Led1_Off();
		Led2_Off();
		Led3_Off();
		led_status = 0;
	}
	#endif
}

#if 0
static void led_loop(void)
{
    static unsigned int softimersec=0xffffffff;
    if(softimersec==Get_SysTick())return;
    softimersec=Get_SysTick();

    Led_Status_Reversal(LED1);
	Led_Status_Reversal(LED2);
	Led_Status_Reversal(LED3);
}
#endif

void led_task(void)
{
    //led_loop();
	led_water_loop();
}



#endif

