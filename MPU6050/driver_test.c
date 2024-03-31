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
#include "math.h"

/* Just a character buffer to print the angle rates */
char roll_buffer[10], pitch_buffer[10], yaw_buffer[10];

int main(void)
{
    mpu6050_packet obj;
    USART_Printf_Init(57600);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();

    mpu6050_init();

    while(1){
      mpu6050_read(&obj);

      gcvt(obj.kalman_angles[ROLL], 6, roll_buffer);
      gcvt(obj.kalman_angles[PITCH], 6, pitch_buffer);
//      gcvt(obj.kalman_angles[YAW], 6, yaw_buffer);

      printf("%s, %s\r\n", roll_buffer, pitch_buffer);

      Delay_Ms(50);
    }

}
