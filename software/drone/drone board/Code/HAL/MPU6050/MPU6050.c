/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   source code file for MPU 6050                                                                               |
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
 * |    @brief          :   this file is the source code file for MPU6050 Sensor                                                        |
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

/******************************************************************************
 * Includes
 *******************************************************************************/

/**
 * 
 */
#include "mpu6050.h"

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

#define CALIBRATION_ITERATIONS (2000)   /**<  */

/******************************************************************************
 * Module Preprocessor Macros
 *******************************************************************************/

/******************************************************************************
 * Module Typedefs
 *******************************************************************************/

/******************************************************************************
 * Module Variable Definitions
 *******************************************************************************/

/* Receiver buffer */
uint8_t RxData[I2C_Rx_BUFFER_SIZE];

/* Calibration */
float roll_calibration = 0, pitch_calibration = 0, yaw_calibration = 0;

/******************************************************************************
 * Function Prototypes
 *******************************************************************************/

/******************************************************************************
 * Function Definitions
 *******************************************************************************/

/**
 * 
 */
void mpu6050_gyro_setup()
{
    int16_t calibration_iter = CALIBRATION_ITERATIONS;
    float roll_rate, pitch_rate, yaw_rate;
    float roll_local_calib = 0, pitch_local_calib = 0, yaw_local_calib = 0;

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
    /**
    Register: CONFIG (0x1A = 26)
    * Disables FSYNC
    * Sets the Digital Low Pass filter of BW = 10Hz
    */
    I2C_start_transmission(MPU6050_SLAVE_ADDRESS, MASTER_TRANSMIT_MODE);
    I2C_write(MPU6050_REG_CONFIG);
    I2C_write(0x05);
    I2C_stop();
    /**
    Register: GYRO_CONFIG (0x1B = 27)
    * Doesn't enable gyroscope self test
    * Sets the full scale range to [+-500 deg/s]
    */
    I2C_start_transmission(MPU6050_SLAVE_ADDRESS, MASTER_TRANSMIT_MODE);
    I2C_write(MPU6050_REG_GYRO_CONFIG);
    I2C_write(0x08);
    I2C_stop();

    /**
     * Calibrate the gyroscope
     * Make the sensor aware of its physical reference
    */
    while(calibration_iter--){
        mpu6050_gyro_read(&roll_rate, &pitch_rate, &yaw_rate);
        roll_local_calib += roll_rate;
        pitch_local_calib += pitch_rate;
        yaw_local_calib += yaw_rate;
        Delay_Ms(1);
    }
    roll_calibration = roll_local_calib / CALIBRATION_ITERATIONS;
    pitch_calibration = pitch_local_calib / CALIBRATION_ITERATIONS;
    yaw_calibration = yaw_local_calib / CALIBRATION_ITERATIONS;
}

/**
 * 
 */
void mpu6050_accel_setup()
{
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
    /**
    Register: CONFIG (0x1A = 26)
    * Disables FSYNC
    * Sets the Digital Low Pass filter of BW = 10Hz
    */
    I2C_start_transmission(MPU6050_SLAVE_ADDRESS, MASTER_TRANSMIT_MODE);
    I2C_write(MPU6050_REG_CONFIG);
    I2C_write(0x05);
    I2C_stop();
    /**
    Register: ACCEL_CONFIG (0x1C = 28)
    * Doesn't enable accelerometer self test
    * Sets the full scale range to [+- 8g]
    */
    I2C_start_transmission(MPU6050_SLAVE_ADDRESS, MASTER_TRANSMIT_MODE);
    I2C_write(MPU6050_REG_ACCEL_CONFIG);
    I2C_write(0x10);
    I2C_stop();
}

/**
 * 
 */
void mpu6050_init()
{
    mpu6050_gyro_setup();
    mpu6050_accel_setup();
}

/**
 * 
 */
void mpu6050_accel_read(float* x_acc, float* y_acc, float* z_acc)
{
    int16_t x_reg, y_reg, z_reg;

    /**
    * Registers: Accelerometer measurements (0x3B to 0x40 = 59 to 64)
    */
    I2C_start_transmission(MPU6050_SLAVE_ADDRESS, MASTER_TRANSMIT_MODE);
    I2C_write(MPU6050_REG_ACCEL_OUT);
    I2C_stop();

    // Get sensor readings
    I2C_requestFrom(MPU6050_SLAVE_ADDRESS, I2C_Rx_BUFFER_SIZE);

    x_reg= I2C_read()<<8 | I2C_read();
    y_reg= I2C_read()<<8 | I2C_read();
    z_reg= I2C_read()<<8 | I2C_read();

    *x_acc=(float)x_reg/MPU6050_LSB_G;
    *y_acc=(float)y_reg/MPU6050_LSB_G;
    *z_acc=(float)z_reg/MPU6050_LSB_G;
}

/**
 * 
 */
void mpu6050_gyro_read(float* roll_rate, float* pitch_rate, float* yaw_rate) {
    int16_t GyroX, GyroY, GyroZ;

    /**
    * Registers: Gyroscope measurements (0x43 to 0x48 = 67 to 72)
    */
    I2C_start_transmission(MPU6050_SLAVE_ADDRESS, MASTER_TRANSMIT_MODE);
    I2C_write(MPU6050_REG_GYRO_OUT);
    I2C_stop();

    // Get sensor readings
    I2C_requestFrom(MPU6050_SLAVE_ADDRESS, I2C_Rx_BUFFER_SIZE);

    GyroX= I2C_read()<<8 | I2C_read();
    GyroY= I2C_read()<<8 | I2C_read();
    GyroZ= I2C_read()<<8 | I2C_read();

    *roll_rate=(float)GyroX/MPU6050_LSB_DPS - roll_calibration;
    *pitch_rate=(float)GyroY/MPU6050_LSB_DPS - pitch_calibration;
    *yaw_rate=(float)GyroZ/MPU6050_LSB_DPS - yaw_calibration;

}

/*************** END OF FUNCTIONS ***************************************************************************/
