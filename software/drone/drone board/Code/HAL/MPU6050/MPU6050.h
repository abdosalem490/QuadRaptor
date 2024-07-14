/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   header file for MPU 6050                                                                                    |
 * |    @file           :   MPU6050.h                                                                                                   |
 * |    @author         :   Mohab Zaghloul                                                                                              |
 * |    @origin_date    :   12/06/2024                                                                                                  |
 * |    @version        :   1.0.0                                                                                                       |
 * |    @tool_chain     :   RISC-V Cross GCC                                                                                            |
 * |    @compiler       :   GCC                                                                                                         |
 * |    @C_standard     :   ISO C99 (-std=c99)                                                                                          |
 * |    @target         :   CH32V203C8T6                                                                                                |
 * |    @notes          :   None                                                                                                        |
 * |    @license        :   MIT License                                                                                                 |
 * |    @brief          :   this file is the header file for MPU6050 Sensor                                                             |
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    MIT License                                                                                                                     |
 * |                                                                                                                                    |
 * |    Copyright (c) - 2024 - Abdelrahman Mohamed Salem - All Rights Reserved                                                          |
 * |                                                                                                                                    |
 * |    Permission is hereby granted, free of charge, to any person obtaining a copy                                                    |
 * |    of this software and associated documentation files (the "Software"), to deal                                                   |
 * |    in the Software without restriction, including without limitation the rights                                                    |
 * |    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell                                                       |
 * |    copies of the Software, and to permit persons to whom the Software is                                                           |
 * |    furnished to do so, subject to the following conditions:                                                                        |
 * |                                                                                                                                    |
 * |    The above copyright notice and this permission notice shall be included in all                                                  |
 * |    copies or substantial portions of the Software.                                                                                 |
 * |                                                                                                                                    |
 * |    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR                                                      |
 * |    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,                                                        |
 * |    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE                                                     |
 * |    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER                                                          |
 * |    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,                                                   |
 * |    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE                                                   |
 * |    SOFTWARE.                                                                                                                       |
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @history_change_list                                                                                                            |
 * |    ====================                                                                                                            |
 * |    Date            Version         Author                          Description                                                     |
 * |    12/06/2023      1.0.0           Mohab Zaghloul                  file Created.                                                   |
 * --------------------------------------------------------------------------------------------------------------------------------------
 */


#ifndef HAL_MPU6050_H_
#define HAL_MPU6050_H_

/******************************************************************************
 * Includes
 *******************************************************************************/

#include "stdint.h"

/******************************************************************************
 * Preprocessor Constants
 *******************************************************************************/

/* Receiver buffer size */
#define I2C_Rx_BUFFER_SIZE   6

/******************************************************************************
 * Configuration Constants
 *******************************************************************************/

/* I2C master mode flag */
#define MASTER_TRANSMIT_MODE 0
#define MASTER_RECEIVER_MODE 1

/* MPU6050 Constants */
#define MPU6050_SLAVE_ADDRESS    (0x68)
#define MPU6050_REG_PWR_MGMT_1   (0x6B)
#define MPU6050_REG_CONFIG       (0x1A)
#define MPU6050_REG_GYRO_CONFIG  (0x1B)
#define MPU6050_REG_GYRO_OUT     (0x43)
#define MPU6050_LSB_DPS          (65.5)
#define MPU6050_REG_ACCEL_CONFIG (0x1C)
#define MPU6050_REG_ACCEL_OUT    (0x3B)
#define MPU6050_LSB_G            (4096)

/******************************************************************************
 * Macros
 *******************************************************************************/

/******************************************************************************
 * Typedefs
 *******************************************************************************/

typedef struct
{
    float x;
    float y;
    float z;
} mpu6050_acc_t;

typedef struct
{
    float roll;
    float pitch;
    float yaw;
} mpu6050_gyro_t;


/******************************************************************************
 * Variables
 *******************************************************************************/

/* Receiver buffer */
extern uint8_t RxData[I2C_Rx_BUFFER_SIZE];

/******************************************************************************
 * Function Prototypes
 *******************************************************************************/

/**
 * Initializes the MPU6050 gyroscope and accelerometer sensor. This function configures the sensor with default
 * settings for measurement. It must be called before any other operations are performed on the sensor.
 *
 * @note This function should be called only once at the start of the program.
 *
 * @return void.
 */
void mpu6050_init();

/**
 * Reads the gyroscope measurements from the MPU6050 sensor and stores them in the provided variables.
 * This function should be called after initializing the sensor with mpu6050_init().
 *
 * @param roll_rate [OUT] Pointer to a float where the roll rate will be stored.
 * @param pitch_rate [OUT] Pointer to a float where the pitch rate will be stored.
 * @param yaw_rate [OUT] Pointer to a float where the yaw rate will be stored.
 *
 * @note mpu6050_init must be called once in the program before using this function.
 *
 * @return void.
 */
void mpu6050_gyro_read(float* roll_rate, float* pitch_rate, float* yaw_rate);

/**
 * Reads the accelerometer measurements from the MPU6050 sensor and stores them in the provided variables.
 * This function should be called after initializing the sensor with mpu6050_init().
 *
 * @param x_acc [OUT] Pointer to a float where the acceleration on the X-axis will be stored.
 * @param y_acc [OUT] Pointer to a float where the acceleration on the Y-axis will be stored.
 * @param z_acc [OUT] Pointer to a float where the acceleration on the Z-axis will be stored.
 *
 * @note mpu6050_init must be called once in the program before using this function.
 *
 * @return void.
 */
void mpu6050_accel_read(float* x_acc, float* y_acc, float* z_acc);


/*** End of File **************************************************************/
#endif /*HAL_MPU6050_H_*/
