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
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);

    GPIO_InitTypeDef gpioConfig;
    gpioConfig.GPIO_Mode = GPIO_Mode_AF_OD;
    gpioConfig.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    gpioConfig.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOB, &gpioConfig);


    // I2C code
    I2C_InitTypeDef I2CConfig;
    I2CConfig.I2C_ClockSpeed = 100000;
    I2CConfig.I2C_Mode = I2C_Mode_I2C;
    I2CConfig.I2C_DutyCycle = I2C_DutyCycle_2;
    I2CConfig.I2C_OwnAddress1 = 0x2F;
    I2CConfig.I2C_Ack = I2C_Ack_Disable;
    I2CConfig.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Init(I2C2, &I2CConfig);

    // I2C_Cmd(I2C2, ENABLE);
    while( I2C_GetFlagStatus( I2C2, I2C_FLAG_BUSY ) != RESET );

    I2C_GenerateSTART(I2C2, ENABLE);
    while( !I2C_CheckEvent( I2C2, I2C_EVENT_MASTER_MODE_SELECT ) );

    I2C_Send7bitAddress(I2C2, 0x68 << 1, I2C_Direction_Transmitter);
    while( !I2C_CheckEvent( I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED ) );

    while(I2C_GetFlagStatus(I2C2, I2C_FLAG_TXE)!=SET);
    I2C_SendData(I2C2, 0x6B);
    while(I2C_GetFlagStatus(I2C2, I2C_FLAG_TXE)!=SET);
    I2C_SendData(I2C2, 0);
    while(I2C_GetFlagStatus(I2C2, I2C_FLAG_TXE)!=SET);
    I2C_GenerateSTOP(I2C2, ENABLE);


    while(1)
    {

    }
}
