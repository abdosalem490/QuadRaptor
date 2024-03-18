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
 *7-bit addressing mode, master/slave mode, transceiver routine:
 *I2C1_SCL(PB8)\I2C1_SDA(PB9).
 *This routine demonstrates that Master sends and Slave receives.
 *Note: The two boards download the Master and Slave programs respectively,
 *and power on at the same time.
 *    Hardware connection:PB8 -- PB8
 *                        PB9 -- PB9
 *
 */

#include "debug.h"

/* Global define */
#define Size   6

/* Global Variable */
u8 RxData[5][Size];

/*********************************************************************
 * @fn      IIC_Init
 *
 * @brief   Initializes the IIC peripheral.
 *
 * @return  none
 */
void IIC_Init(u32 bound, u16 address)
{
    GPIO_InitTypeDef GPIO_InitStructure={0};
    I2C_InitTypeDef I2C_InitTSturcture={0};

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE );
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_I2C1, ENABLE );

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init( GPIOB, &GPIO_InitStructure );

    I2C_InitTSturcture.I2C_ClockSpeed = bound;
    I2C_InitTSturcture.I2C_Mode = I2C_Mode_I2C;
    I2C_InitTSturcture.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitTSturcture.I2C_OwnAddress1 = address;
    I2C_InitTSturcture.I2C_Ack = I2C_Ack_Enable;
    I2C_InitTSturcture.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Init( I2C1, &I2C_InitTSturcture );

//    I2C_Cmd( I2C1, ENABLE );
}

float RateRoll, RatePitch, RateYaw;
char roll_buffer[10], pitch_buffer[10], yaw_buffer[10];

void gyro_signals(void) {
    int16_t GyroX, GyroY, GyroZ, i = 0;
    while( I2C_GetFlagStatus( I2C2, I2C_FLAG_BUSY ) != RESET );

    I2C_GenerateSTART(I2C2, ENABLE);
    while( !I2C_CheckEvent( I2C2, I2C_EVENT_MASTER_MODE_SELECT ) );

    I2C_Send7bitAddress(I2C2, 0x68 << 1, I2C_Direction_Transmitter);
    while( !I2C_CheckEvent( I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED ) );

    while(I2C_GetFlagStatus(I2C2, I2C_FLAG_TXE)!=SET);
    I2C_SendData(I2C2, 0x1A);
    while(I2C_GetFlagStatus(I2C2, I2C_FLAG_TXE)!=SET);
    I2C_SendData(I2C2, 0x05);
    while(I2C_GetFlagStatus(I2C2, I2C_FLAG_TXE)!=SET);
    I2C_GenerateSTOP(I2C2, ENABLE);

    ////////////////////////////////////////////////////

    while( I2C_GetFlagStatus( I2C2, I2C_FLAG_BUSY ) != RESET );

    I2C_GenerateSTART(I2C2, ENABLE);
    while( !I2C_CheckEvent( I2C2, I2C_EVENT_MASTER_MODE_SELECT ) );

    I2C_Send7bitAddress(I2C2, 0x68 << 1, I2C_Direction_Transmitter);
    while( !I2C_CheckEvent( I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED ) );

    while(I2C_GetFlagStatus(I2C2, I2C_FLAG_TXE)!=SET);
    I2C_SendData(I2C2, 0x1B);
    while(I2C_GetFlagStatus(I2C2, I2C_FLAG_TXE)!=SET);
    I2C_SendData(I2C2, 0x08);
    while(I2C_GetFlagStatus(I2C2, I2C_FLAG_TXE)!=SET);
    I2C_GenerateSTOP(I2C2, ENABLE);

    ///////////////////////////////////////////////////

    while( I2C_GetFlagStatus( I2C2, I2C_FLAG_BUSY ) != RESET );

    I2C_GenerateSTART(I2C2, ENABLE);
    while( !I2C_CheckEvent( I2C2, I2C_EVENT_MASTER_MODE_SELECT ) );

    I2C_Send7bitAddress(I2C2, 0x68 << 1, I2C_Direction_Transmitter);
    while( !I2C_CheckEvent( I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED ) );

    while(I2C_GetFlagStatus(I2C2, I2C_FLAG_TXE)!=SET);
    I2C_SendData(I2C2, 0x43);

    while(I2C_GetFlagStatus(I2C2, I2C_FLAG_TXE)!=SET);
    I2C_GenerateSTOP(I2C2, ENABLE);

    ////////////////////////////////////////////////////

    while( I2C_GetFlagStatus( I2C2, I2C_FLAG_BUSY ) != RESET );

    I2C_GenerateSTART( I2C2, ENABLE );
    while( !I2C_CheckEvent( I2C2, I2C_EVENT_MASTER_MODE_SELECT ) );

    I2C_Send7bitAddress( I2C2, 0x68<<1, I2C_Direction_Receiver );
    while( !I2C_CheckEvent( I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED  ) );


    while(i < 6){
        if( I2C_GetFlagStatus( I2C2, I2C_FLAG_RXNE ) !=  RESET ){
            RxData[0][i] = I2C_ReceiveData( I2C2 );
            i++;
        }
        if(i == 5) I2C_NACKPositionConfig(I2C2, I2C_NACKPosition_Next);
    }
    while(I2C_GetFlagStatus(I2C2, I2C_FLAG_RXNE)!=SET);
    I2C_GenerateSTOP(I2C2, ENABLE);

    GyroX= RxData[0][0]<<8 | RxData[0][1];
    GyroY= RxData[0][2]<<8 | RxData[0][3];
    GyroZ= RxData[0][4]<<8 ;
    RateRoll=(float)GyroX/65.5;
    RatePitch=(float)GyroY/65.5;
    RateYaw=(float)GyroZ/65.5;

    gcvt(RateRoll, 6, roll_buffer);
    gcvt(RatePitch, 6, pitch_buffer);
    gcvt(RateYaw, 6, yaw_buffer);

}

int main(void)
{
    USART_Printf_Init(57600);
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
    I2CConfig.I2C_ClockSpeed = 400000;
    I2CConfig.I2C_Mode = I2C_Mode_I2C;
    I2CConfig.I2C_DutyCycle = I2C_DutyCycle_2;
    I2CConfig.I2C_OwnAddress1 = 0x2F;
    I2CConfig.I2C_Ack = I2C_Ack_Enable;
    I2CConfig.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Init(I2C2, &I2CConfig);


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


    while(1){
      gyro_signals();

      printf("%s, %s, %s\r\n", roll_buffer, pitch_buffer, yaw_buffer);

      Delay_Ms(50);
    }

}
