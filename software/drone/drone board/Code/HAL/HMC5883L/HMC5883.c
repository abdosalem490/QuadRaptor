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

/**
 * 
 */
#include <math.h>


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
void hmc5883l_write(uint8_t reg, uint8_t data);
void hmc5883l_setptr(uint8_t reg);
void mpu6050_write(uint8_t reg, uint8_t data);

/******************************************************************************
 * Function Definitions
 *******************************************************************************/

void hmc5883l_write(uint8_t reg, uint8_t data)
{
    I2C_start_transmission(HMC5883L_SLAVE_ADDRESS, MASTER_TRANSMIT_MODE);
    I2C_write(reg);
    I2C_write(data);
    I2C_stop();
}

void hmc5883l_setptr(uint8_t reg)
{
    I2C_start_transmission(HMC5883L_SLAVE_ADDRESS, MASTER_TRANSMIT_MODE);
    I2C_write(reg);
    I2C_stop();
}

void mpu6050_write(uint8_t reg, uint8_t data)
{
    I2C_start_transmission(MPU6050_SLAVE_ADDRESS, MASTER_TRANSMIT_MODE);
    I2C_write(reg);
    I2C_write(data);
    I2C_stop();
}

/**
 * 
 */
void hmc5883l_init()
{

    #if GY87_AUXILIARY != 0
    /**
    Register: USER_CTRL (0x6A)
    *  Disable the MPU6050 master mode. This is a prerequisite for the next step
    **/
    mpu6050_write(MPU6050_REG_USER_CTRL, MPU6050_DISABLE_MASTER);
    /**
    Register: BYPASS_CTRL (0x37)
    *  Enables bypass mode. This connects the main I2C bus to the auxiliary one.
    **/
    mpu6050_write(MPU6050_REG_BYPASS, MPU6050_ENABLE_BYPASS);
    /**
    Register: PWR_MGMT_1 (0x6B = 107)
    *  Selects the clock source: 8MHz oscillator
    *  Disables the following bits: Reset, Sleep, Cycle
    *  Does not disable Temperature sensor.
    **/
    mpu6050_write(MPU6050_REG_PWR_MGMT_1, 0);
    #endif

    /**
    Register: MODE_REG (0x02)
    *  Sets the measurement mode
    **/
    hmc5883l_write(HMC5883L_REG_MODE, HMC5883L_CONTINUOUS_MODE);
    /**
    Register: CONFIG_A (0x00)
    *  Sets the samples per measurement output to 8
    *  Sets the output data rate to 15Hz
    **/
    hmc5883l_write(HMC5883L_REG_CONFIG_A, HMC5883L_SAMPLES_8 | HMC5883L_OUTPUT_RATE_15);
    /**
    Register: CONFIG_B (0x01)
    *  Sets the sensor field range to 1.3 Ga
    **/
    hmc5883l_write(HMC5883L_REG_CONFIG_B, HMC5883L_RANGE_1_3);
}  

/**
 * 
 */
void hmc5883l_read(hmc5883l_packet* data)
{
    /**
     * Registers: Magnetometer measurements (0x03 to 0x08)
    */
    hmc5883l_setptr(HMC5883L_REG_DATA);

    // Get sensor readings
    I2C_requestFrom(HMC5883L_SLAVE_ADDRESS, I2C_Rx_BUFFER_SIZE);

    data->magnetometer_raw_x = (I2C_read()<<8 | I2C_read());
    data->magnetometer_raw_z = (I2C_read()<<8 | I2C_read());
    data->magnetometer_raw_y = (I2C_read()<<8 | I2C_read());
}



void hmc5883l_normalize(hmc5883l_packet* data)
{
    data->calibrated_x = (data->magnetometer_raw_x - X_OFFSET) / SCALE;
    data->calibrated_y = (data->magnetometer_raw_y - Y_OFFSET) / SCALE;
    data->calibrated_z = (data->magnetometer_raw_z - Z_OFFSET) / SCALE;
}

/*************** END OF FUNCTIONS ***************************************************************************/
