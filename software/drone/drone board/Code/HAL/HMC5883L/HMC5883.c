/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   header file for HMC5883L                                                                                    |
 * |    @file           :   HMC5883.c                                                                                                   |
 * |    @author         :   Mohab Zaghloul                                                                                              |
 * |    @origin_date    :   14/06/2024                                                                                                  |
 * |    @version        :   1.0.0                                                                                                       |
 * |    @tool_chain     :   RISC-V Cross GCC                                                                                            |
 * |    @compiler       :   GCC                                                                                                         |
 * |    @C_standard     :   ISO C99 (-std=c99)                                                                                          |
 * |    @target         :   CH32V203C8T6                                                                                                |
 * |    @notes          :   None                                                                                                        |
 * |    @license        :   MIT License                                                                                                 |
 * |    @brief          :   this file is the source file for HMC5883L Sensor                                                            |
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
 * |    14/06/2023      1.0.0           Mohab Zaghloul                  file Created.                                                   |
 * --------------------------------------------------------------------------------------------------------------------------------------
 */

/******************************************************************************
 * Includes
 *******************************************************************************/

/**
 * 
 */
#include "HMC5883.h"

/**
 * 
 */
#include "stdint.h"

/**
 * 
 */
#include "MCAL_wrapper.h"

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

/******************************************************************************
 * Function Prototypes
 *******************************************************************************/

/******************************************************************************
 * Function Definitions
 *******************************************************************************/

/**
 * 
 */
void hmc5883l_init()
{

    #if GY86_AUXILIARY != 0
    /**
    Register: USER_CTRL (0x6A)
    *  Disable the MPU6050 master mode. This is a prerequisite for the next step
    **/
    I2C_start_transmission(MPU6050_SLAVE_ADDRESS, MASTER_TRANSMIT_MODE);
    I2C_write(MPU6050_REG_USER_CTRL);
    I2C_write(MPU6050_DISABLE_MASTER);
    I2C_stop();

    /**
    Register: BYPASS_CTRL (0x37)
    *  Enables bypass mode. This connects the main I2C bus to the auxiliary one.
    **/
    I2C_start_transmission(MPU6050_SLAVE_ADDRESS, MASTER_TRANSMIT_MODE);
    I2C_write(MPU6050_REG_BYPASS);
    I2C_write(MPU6050_ENABLE_BYPASS);
    I2C_stop();

    /**
    Register: PWR_MGMT_1 (0x6B = 107)
    *  Selects the clock source: 8MHz oscillator
    *  Disables the following bits: Reset, Sleep, Cycle
    *  Does not disable Temperature sensor.
    **/
    I2C_start_transmission(MPU6050_SLAVE_ADDRESS, MASTER_TRANSMIT_MODE);
    I2C_write(MPU6050_REG_PWR_MGMT_1);
    I2C_write(0);
    I2C_stop();

    // printf("BYPASS ENABLED\r\n");
    #endif


    /**
    Register: CONFIG_A (0x00)
    *  Sets the samples per measurement output to 8
    *  Sets the output data rate to 30Hz
    **/
    I2C_start_transmission(HMC5883L_SLAVE_ADDRESS, MASTER_TRANSMIT_MODE);
    I2C_write(HMC5883L_REG_CONFIG_A);
    I2C_write(HMC5883L_SAMPLES_8 | HMC5883L_OUTPUT_RATE);
    I2C_stop();

    /**
    Register: CONFIG_B (0x00)
    *  Sets the sensor field range to 1.3 Ga
    **/
    I2C_start_transmission(HMC5883L_SLAVE_ADDRESS, MASTER_TRANSMIT_MODE);
    I2C_write(HMC5883L_REG_CONFIG_B);
    I2C_write(HMC5883L_RANGE_1_3);
    I2C_stop();

    /**
    Register: MODE_REG (0x02)
    *  Sets the measurement mode to continuous measurement mode
    **/
    I2C_start_transmission(HMC5883L_SLAVE_ADDRESS, MASTER_TRANSMIT_MODE);
    I2C_write(HMC5883L_REG_MODE);
    I2C_write(HMC5883L_CONTINUOUS_MODE);
    I2C_stop();

}  



/**
 * 
 */
void hmc5883l_read(hmc5883l_packet* data)
{
    // Get sensor readings
    I2C_requestFrom(HMC5883L_SLAVE_ADDRESS, I2C_Rx_BUFFER_SIZE);

    data->magnetometer_raw_x = (I2C_read()<<8 | I2C_read()) / HMC5883L_GAIN;
    data->magnetometer_raw_y = (I2C_read()<<8 | I2C_read()) / HMC5883L_GAIN;
    data->magnetometer_raw_z = (I2C_read()<<8 | I2C_read()) / HMC5883L_GAIN;

}


/*************** END OF FUNCTIONS ***************************************************************************/