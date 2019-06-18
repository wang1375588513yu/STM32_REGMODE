/********************************Copyright (c)******************************\
**
**                    (c) Copyright 2018, WangYu, China, SZ.
**                            All Rights Reserved
**
**                               By(MR.Richard)
**
**----------------------------------File Information------------------------
** FileName:      usart.h
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

#ifndef ___USART_H___
#define ___USART_H___
#include "sys.h"
#include "PUBLIC.H"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>

/*******************************************************************************************	
 ***THE_FIRST_CASE = 1	����1 PA9,PA10 	����2 PA2,PA3  ����3 PC4 PC5	����4 PC10,PC11*****
 ***THE_FIRST_CASE = 0	����1 PB6,PB7	����2 PA2,PA3  ����3 PB10,PB11	����4 PC10,PC11*****
 *******************************************************************************************/
#define THE_FIRST_CASE		0	//���ڵ�Ӳ�����÷���			

#define UART1_ENABLE		1			//���ڿ�or��
#define UART2_ENABLE		1
#define UART3_ENABLE		0
#define UART4_ENABLE		0

/************************************************************
 ** ��USARTx_USE_PIPE = 1  ʹ��public.h����� pipe_t�ṹ��***  
 ** ��USARTx_USE_PIPE = 0  ʹ��public.h����� pipe1_t�ṹ��**
 ************************************************************/
#define USART1_USE_PIPE		1			
#define USART2_USE_PIPE		0
#define USART3_USE_PIPE		1
#define USART4_USE_PIPE		0


/******************************************************************************************	
 ***���¶��崮�ڵ�GPIO�˿ں����ţ����¶���˿�ʱ�ӣ�����Ժ���ֲ����ֱ�Ӹ�������Ӳ���˿�***
 ******************************************************************************************/
#if UART1_ENABLE
#if THE_FIRST_CASE
#define   UART1_GPIO						GPIOA
#define   UART1_TX_PIN						GPIO_PIN_9
#define   UART1_RX_PIN						GPIO_PIN_10
#define   __HAL_RCC_UART1_GPIO_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE();
#else
#define   UART1_GPIO						GPIOB
#define   UART1_TX_PIN						GPIO_PIN_6
#define   UART1_RX_PIN						GPIO_PIN_7
#define   __HAL_RCC_UART1_GPIO_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE();
#endif
#endif

#if UART2_ENABLE
#define   UART2_GPIO						GPIOA
#define   UART2_TX_PIN						GPIO_PIN_2
#define   UART2_RX_PIN						GPIO_PIN_3
#define   __HAL_RCC_UART2_GPIO_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE();
#endif

#if UART3_ENABLE
#if THE_FIRST_CASE
#define   UART3_GPIO						GPIOC
#define   UART3_TX_PIN						GPIO_PIN_4
#define   UART3_RX_PIN						GPIO_PIN_5
#define   __HAL_RCC_UART3_GPIO_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE();
#else
#define   UART3_GPIO						GPIOB
#define   UART3_TX_PIN						GPIO_PIN_10
#define   UART3_RX_PIN						GPIO_PIN_11
#define   __HAL_RCC_UART3_GPIO_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE();
#endif
#endif

#if UART4_ENABLE
#define   UART4_GPIO						GPIOC
#define   UART4_TX_PIN						GPIO_PIN_10
#define   UART4_RX_PIN						GPIO_PIN_11
#define   __HAL_RCC_UART4_GPIO_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE();
#endif


#if USART1_USE_PIPE
extern Pipe_t uart_pipe1;
#else
extern Pipe1_t uart_pipe1;
#endif

#if USART2_USE_PIPE
extern Pipe_t uart_pipe2;
#else
extern Pipe1_t uart_pipe2;
extern Pipe1_t uart_pipe2_log;
#endif

#if USART3_USE_PIPE
extern Pipe_t uart_pipe3;
#else
extern Pipe1_t uart_pipe3;
#endif

#if USART4_USE_PIPE
extern Pipe_t uart_pipe4;
#else
extern Pipe1_t uart_pipe4;
#endif

void usart_initconfig(void);
#if UART1_ENABLE
void UART1_init(u32 bound);
void uart1_output(const unsigned char * buf,int len);
void uart1_printf(char * string, ...);
#endif
#if UART2_ENABLE
void UART2_init(u32 bound);
void uart2_output(const unsigned char * buf,int len);
void uart2_printf(char * string, ...);
#endif
#if UART3_ENABLE
void UART3_init(u32 bound);
void uart3_output(const unsigned char * buf,int len);
void uart3_printf(char * string, ...);
#endif
#if UART4_ENABLE
void UART4_init(u32 bound);
void uart4_output(const unsigned char * buf,int len);
void uart4_printf(char * string, ...);
#endif
 
#endif
