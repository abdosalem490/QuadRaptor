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

/* Packet Constants */
#define ROLL        (0)
#define PITCH       (1)
#define YAW         (2)
#define X_AXIS      (0)
#define Y_AXIS      (1)
#define Z_AXIS      (2)

/* Kalman Filter constants */
#define STD_DEV_GYR (4.0)   // Standard Deviation of the gyroscope
#define STD_DEV_ACC (3.0)   // Standard Deviation of the accelerometer

/******************************************************************************
 * Macros
 *******************************************************************************/

/******************************************************************************
 * Typedefs
 *******************************************************************************/

struct packet{
    float angle_rates[3];
    float accel[3];
    float kalman_angles[3];
    float kalman_uncertainty[3];
};
typedef struct packet mpu6050_packet;


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
 *  \b function                                 :       None
 *  \b Description                              :       Initialize gyroscope and accelerometer.
 *  @param  arg_pFuncTaskFunction [IN]          :       None
 *  @param  arg_pu8TaskName [IN]                :       None
 *  @param  arg_pTaskHandle [OUT]               :       None
 *  @note                                       :       Only called once.
 *  \b PRE-CONDITION                            :       None
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       None
 *  @see                                        :       None
 *
 *  \b Example:
 * @code
 * 
 *          None
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 19/05/2024 </td><td> 1.0.0            </td><td> MZ      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
void mpu6050_init();


/**
 *  \b function                                 :       None
 *  \b Description                              :       Get gyroscope and accelerometer measurements.
 *  @param  arg_pFuncTaskFunction [IN]          :       None
 *  @param  arg_pu8TaskName [IN]                :       None
 *  @param  arg_pTaskHandle [OUT]               :       None
 *  @note                                       :       mpu6050_init must be called once in the program before using this function.
 *  \b PRE-CONDITION                            :       None
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       None
 *  @see                                        :       None
 *
 *  \b Example:
 * @code
 * 
 *          None
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 12/06/2024 </td><td> 1.0.0            </td><td> MZ      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
void mpu6050_gyro_read(float* roll_rate, float* pitch_rate, float* yaw_rate);


/**
 *  \b function                                 :       None
 *  \b Description                              :       Get gyroscope and accelerometer measurements.
 *  @param  arg_pFuncTaskFunction [IN]          :       None
 *  @param  arg_pu8TaskName [IN]                :       None
 *  @param  arg_pTaskHandle [OUT]               :       None
 *  @note                                       :       mpu6050_init must be called once in the program before using this function.
 *  \b PRE-CONDITION                            :       None
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       None
 *  @see                                        :       None
 *
 *  \b Example:
 * @code
 * 
 *          None
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 12/06/2024 </td><td> 1.0.0            </td><td> MZ      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
void mpu6050_accel_read(float* x_acc, float* y_acc, float* z_acc);


/*** End of File **************************************************************/
#endif /*HAL_MPU6050_H_*/
