/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   Wrapper File for RTOS function                                                                              |
 * |    @file           :   Service_RTOS_wrapper.h                                                                                      |
 * |    @author         :   Abdelrahman Mohamed Salem                                                                                   |
 * |    @origin_date    :   18/05/2024                                                                                                  |
 * |    @version        :   1.0.0                                                                                                       |
 * |    @tool_chain     :   RISC-V Cross GCC                                                                                            |
 * |    @compiler       :   GCC                                                                                                         |
 * |    @C_standard     :   ISO C99 (-std=c99)                                                                                          |
 * |    @target         :   CH32V203C8T6                                                                                                |
 * |    @notes          :   None                                                                                                        |
 * |    @license        :   MIT License                                                                                                 |
 * |    @brief          :   this header file contains useful functions to easily change RTOS without changing much in code              |
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
 * |    18/05/2023      1.0.0           Abdelrahman Mohamed Salem       Interface Created.                                              |
 * |    24/05/2023      1.0.0           Abdelrahman Mohamed Salem       added the function 'HAL_Config_ConfigAllHW'.                    |
 * --------------------------------------------------------------------------------------------------------------------------------------
 */
 

/******************************************************************************
 * Includes
 *******************************************************************************/

/**
 * @reason: contains the function declarations
*/
#include "HAL_config.h"

/**
 * @reason: contains definitions for ENABLE and DISABLE
*/
#include "constants.h"

/**
 * @reason: contains definitions for ADXL345 functions and structs
*/
#include "ADXL345_config.h"

/**
 * @reason: contains initialization function for ADXL345
*/
#include "ADXL345_header.h"

/**
 * @reason: contains initialization function for MPU6050
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

/**
 * @brief: a variable through which we will deal with ADXL345
 */
HAL_ADXL345_config_t global_adxl345Config_t;

/******************************************************************************
 * Function Prototypes
 *******************************************************************************/

/******************************************************************************
 * Function Definitions
 *******************************************************************************/


/**
 * 
*/
HAL_Config_ErrStat_t HAL_Config_ConfigAllHW(void)
{
    // configure ADXL345
    global_adxl345Config_t.bandwidth_rate = HAL_ADXL345_BW_RATE_800HZ;
    global_adxl345Config_t.enableFullRange = LIB_CONSTANTS_ENABLED;
    global_adxl345Config_t.g_range = HAL_ADXL345_G_RANGE_8;
    global_adxl345Config_t.int_pol = HAL_ADXL345_INT_POL_ACT_LOW;
    global_adxl345Config_t.int0_src = HAL_ADXL345_INT_SRC_DATA_READY;
    global_adxl345Config_t.int1_src = HAL_ADXL345_INT_SRC_FREE_FALL;
    HAL_ADXL345_Init(&global_adxl345Config_t, &MCAL_CFG_adxlSPI);


    // configure MPU6050 accelerometer and gyroscope
    // mpu6050_init();

    // configure HMC5883L

    // configure BMP280

    return HAL_Config_STAT_OK;
}




/*************** END OF FUNCTIONS ***************************************************************************/


// to be the IdleTask (called when no other tasks are running)
// void vApplicationIdleHook( void );