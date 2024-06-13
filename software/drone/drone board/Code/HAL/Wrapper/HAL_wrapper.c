/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   wrapper file for the HAL layer functions                                                                    |
 * |    @file           :   HAL_wrapper.c                                                                                               |
 * |    @author         :   Abdelrahman Mohamed Salem                                                                                   |
 * |    @origin_date    :   12/06/2024                                                                                                  |
 * |    @version        :   1.0.0                                                                                                       |
 * |    @tool_chain     :   RISC-V Cross GCC                                                                                            |
 * |    @compiler       :   GCC                                                                                                         |
 * |    @C_standard     :   ISO C99 (-std=c99)                                                                                          |
 * |    @target         :   CH32V203C8T6                                                                                                |
 * |    @notes          :   None                                                                                                        |
 * |    @license        :   MIT License                                                                                                 |
 * |    @brief          :   this file is a wrapper file for the HAL layer so that when we change HAL, the code could be portable.       |
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
 * |    12/06/2023      1.0.0           Abdelrahman Mohamed Salem       file Created.                                                   |
 * --------------------------------------------------------------------------------------------------------------------------------------
 */
 

/******************************************************************************
 * Includes
 *******************************************************************************/

/**
 * @reason: contains definition for HAL wrapper
 */
#include "HAL_wrapper.h"

/**
 * @reason: contains definitions and decelerations for functions/variables for MCAL wrapper
*/
#include "MCAL_wrapper.h"

/**
 * @reason: contains common definitions
 */
#include "common.h"

/**
 * @reason: contains definitions from ADXL345 interface
 */
#include "ADXL345_header.h"

/**
 * @reason: contains definitions for MPU6050
 */
#include "MPU6050.h"

/******************************************************************************
 * Module Preprocessor Constants
 *******************************************************************************/

/******************************************************************************
 * Module Preprocessor Macros
 *******************************************************************************/

/******************************************************************************
 * Module Typedefs
 *******************************************************************************/

/******************************************************************************
 * Module Variable Definitions
 *******************************************************************************/
HAL_ADXL345_Acc_t global_ADXL345ACC_t = {0};
mpu6050_acc_t global_MPU6050ACC_t = {0};
mpu6050_gyro_t global_MPU6050GYRO_t = {0};

/******************************************************************************
 * Function Prototypes
 *******************************************************************************/

/******************************************************************************
 * Function Definitions
 *******************************************************************************/

/**
 * 
 */
HAL_WRAPPER_ErrStat_t HAL_WRAPEPR_ReadAcc(HAL_WRAPPER_Acc_t *arg_pAcc)
{
    if(NULL == arg_pAcc)
        return HAL_WRAPPER_STAT_INVALID_PARAMS;

    // TODO: try reading from ADXL345 around 30 times and see what happens

    float avg_x = 0.0;
    float avg_y = 0.0;
    float avg_z = 0.0;

    // read the accelerometer data from ADXL345
    for(int i = 0; i < 30; i++)
    {
    	HAL_ADXL345_ReadAcc(&MCAL_CFG_adxlSPI, &global_ADXL345ACC_t);
    	avg_x += (global_ADXL345ACC_t.x / 30.0);
    	avg_y += (global_ADXL345ACC_t.y / 30.0);
    	avg_z += (global_ADXL345ACC_t.z / 30.0);
    }

    avg_x = (avg_x * 4) / 1000;
    avg_y = (avg_y * 4) / 1000;
    avg_z = (avg_z * 4) / 1000;

    // read acceleration from MPU6050
    // mpu6050_accel_read(&global_MPU6050ACC_t.x, &global_MPU6050ACC_t.y, &global_MPU6050ACC_t.z);

    arg_pAcc->x = global_ADXL345ACC_t.x;
    arg_pAcc->y = global_ADXL345ACC_t.y;
    arg_pAcc->z = global_ADXL345ACC_t.z;

    return MCAL_WRAPPER_STAT_OK;
}



/*************** END OF FUNCTIONS ***************************************************************************/


// to be the IdleTask (called when no other tasks are running)
// void vApplicationIdleHook( void );
