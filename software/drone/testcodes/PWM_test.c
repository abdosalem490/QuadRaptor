/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2021/06/06
 * Description        : Main program body.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/

/*
 *@Note
 USART Print debugging routine:
 USART1_Tx(PA9).
 This example demonstrates using USART1(PA9) as a print debug port output.

*/

#include "debug.h"


/* Global typedef */

/* Global define */

/* Global Variable */

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    // USART_Printf_Init(115200);
    // printf("SystemClk:%d\r\n", SystemCoreClock);
    // printf("This is printf example\r\n");

    GPIO_InitTypeDef gpioConfig;
    gpioConfig.GPIO_Mode = GPIO_Mode_AF_PP;
    gpioConfig.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    gpioConfig.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOB, &gpioConfig);


    TIM_TimeBaseInitTypeDef initConfig;
    initConfig.TIM_CounterMode = TIM_CounterMode_CenterAligned1;
    initConfig.TIM_ClockDivision = TIM_CKD_DIV1;
    initConfig.TIM_Prescaler = 143;
    initConfig.TIM_Period = 10000;
    TIM_TimeBaseInit(TIM4, &initConfig);

    // 9818
    TIM_OCInitTypeDef ocConfig;
    ocConfig.TIM_OCMode = TIM_OCMode_PWM2;
    ocConfig.TIM_OutputState = TIM_OutputState_Enable;
    ocConfig.TIM_Pulse = 750; // 1.5 ms
    ocConfig.TIM_OCPolarity = TIM_OCPolarity_Low;

    TIM_OC1Init(TIM4, &ocConfig);
    TIM_OC2Init(TIM4, &ocConfig);
    TIM_OC3Init(TIM4, &ocConfig);
    TIM_OC4Init(TIM4, &ocConfig);

    TIM_Cmd(TIM4, ENABLE);

    while(1)
    {

    }
}
