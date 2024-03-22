/********************************** (C) COPYRIGHT *******************************
 * File Name          : gyro_driver_test.c
 * Author             : Mohab Zaghloul
 * Version            : V1.0.0
 * Date               : 2021/03/14
 * Description        : Testing the first version of the mpu6050 driver.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

#include "debug.h"
#include "mpu6050.h"

/* Just a character buffer to print the angle rates */
char roll_buffer[10], pitch_buffer[10], yaw_buffer[10];

int main(void)
{
    float roll_rate = 0, pitch_rate = 0, yaw_rate = 0;
    USART_Printf_Init(57600);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();

    mpu6050_gyro_setup();

    while(1){
      mpu6050_gyro_read(&roll_rate, &pitch_rate, &yaw_rate);

      gcvt(roll_rate, 6, roll_buffer);
      gcvt(pitch_rate, 6, pitch_buffer);
      gcvt(yaw_rate, 6, yaw_buffer);

      printf("%s, %s, %s\r\n", roll_buffer, pitch_buffer, yaw_buffer);

      Delay_Ms(50);
    }

}
