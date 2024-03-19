/********************************** (C) COPYRIGHT *******************************
 * File Name          : gyro_ch32v203.c
 * Author             : Mohab Zaghloul
 * Version            : V1.0.0
 * Date               : 2021/03/14
 * Description        : One file program to test the gyroscope interface.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

#include "debug.h"

/* I2C master mode flag */
#define MASTER_RECEIVER_MODE 1

/* Receiver buffer size */
#define I2C_Rx_BUFFER_SIZE   6

/* Receiver buffer */
u8 RxData[I2C_Rx_BUFFER_SIZE];

/* Flight angle rates to be computed by gyroscope measurements */
float RateRoll, RatePitch, RateYaw;

/* Just a character buffer to print the angle rates */
char roll_buffer[10], pitch_buffer[10], yaw_buffer[10];

void I2C_init() __attribute__((always_inline));
void I2C_start_transmission(uint8_t receiver_address, uint8_t master_receive) __attribute__((always_inline));
void I2C_write(uint8_t value) __attribute__((always_inline));
void I2C_stop() __attribute__((always_inline));
uint8_t I2C_requestFrom(uint8_t address, uint8_t quantity, uint8_t stop_bool) __attribute__((always_inline));
uint8_t I2C_read() __attribute__((always_inline));

inline void I2C_start_transmission(uint8_t receiver_address, uint8_t master_receive = 0){
    uint8_t i2c_dir = I2C_Direction_Transmitter;
    uint32_t i2c_event = I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED;

    if(master_receive){
        i2c_dir = I2C_Direction_Receiver;
        i2c_event = I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED;
    }

    while( I2C_GetFlagStatus( I2C2, I2C_FLAG_BUSY ) != RESET );

    I2C_GenerateSTART(I2C2, ENABLE);
    while( !I2C_CheckEvent( I2C2, I2C_EVENT_MASTER_MODE_SELECT ) );

    I2C_Send7bitAddress(I2C2, receiver_address << 1, i2c_dir);
    while( !I2C_CheckEvent( I2C2, i2c_event ) );
}

inline void I2C_write(uint8_t value){
    while(I2C_GetFlagStatus(I2C2, I2C_FLAG_TXE)!=SET);
    I2C_SendData(I2C2, value);
}

inline void I2C_stop(){
    while(I2C_GetFlagStatus(I2C2, I2C_FLAG_TXE)!=SET);
    I2C_GenerateSTOP(I2C2, ENABLE);
}

inline uint8_t I2C_read(){
    static uint8_t i = 0;
    uint8_t result = RxData[i];
    i = (i+1) % I2C_Rx_BUFFER_SIZE;
    return result;
}

inline uint8_t I2C_requestFrom(uint8_t address, uint8_t quantity, uint8_t stop_bool = true){
    uint8_t i = 0;

    I2C_start_transmission(address, MASTER_RECEIVER_MODE);

    while(i < I2C_Rx_BUFFER_SIZE){
        if( I2C_GetFlagStatus( I2C2, I2C_FLAG_RXNE ) !=  RESET ){
            RxData[i] = I2C_ReceiveData( I2C2 );
            i++;
        }
        if(i == I2C_Rx_BUFFER_SIZE-1) I2C_NACKPositionConfig(I2C2, I2C_NACKPosition_Next);
    }

    while(I2C_GetFlagStatus(I2C2, I2C_FLAG_RXNE)!=SET);
    I2C_GenerateSTOP(I2C2, ENABLE);
    
    return i;
}

void I2C_init_ch32()
{
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
}

inline void I2C_init(){
    I2C_init_ch32();
}


void gyro_signals(void) {
    int16_t GyroX, GyroY, GyroZ;

    I2C_start_transmission(0x68);
    I2C_write(0x1A);
    I2C_write(0x05);
    I2C_stop();
    ////////////////////////////////////////////////////
    I2C_start_transmission(0x68);
    I2C_write(0x1B);
    I2C_write(0x08);
    I2C_stop();
    ///////////////////////////////////////////////////
    I2C_start_transmission(0x68);
    I2C_write(0x43);
    I2C_stop();
    ////////////////////////////////////////////////////
    I2C_requestFrom(0x68, I2C_Rx_BUFFER_SIZE);

    GyroX= I2C_read()<<8 | I2C_read();
    GyroY= I2C_read()<<8 | I2C_read();
    GyroZ= I2C_read()<<8 | I2C_read();

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
    I2C_init_ch32();


    I2C_start_transmission(0x68);
    I2C_write(0x6B);
    I2C_write(0);
    I2C_stop();


    while(1){
      gyro_signals();

      printf("%s, %s, %s\r\n", roll_buffer, pitch_buffer, yaw_buffer);

      Delay_Ms(50);
    }

}
