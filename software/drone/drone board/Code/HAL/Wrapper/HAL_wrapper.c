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

/**
 * @reason: contains definition for HMC5883L
 */
#include "HMC5883.h"

/**
 * @reason: contains functions for ESCs driver
 */
#include "ESC.h" 

/**
 * @reason: contains BMP280 interface
 */
#include "bmp.h"

/**
 * @reason: contains HC SR04 interface
 */
#include "HC_SR04.h"

/******************************************************************************
 * Module Preprocessor Constants
 *******************************************************************************/

/**
 *
 */
#define LIPO_3S_MIN_V	10

/**
 *
 */
#define LIPO_3S_MAX_V	11.3

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
hmc5883l_packet global_HMC5883MAGNET_t = {0};

/******************************************************************************
 * Function Prototypes
 *******************************************************************************/

/******************************************************************************
 * Function Definitions
 *******************************************************************************/

/**
 * NOTE: ADXL345 isn't working. tried many methods to debug but either the routing of pcb track isn't good or the IC is fake
 */
HAL_WRAPPER_ErrStat_t HAL_WRAPPER_ReadAcc(HAL_WRAPPER_Acc_t *arg_pAcc)
{
    if(NULL == arg_pAcc)
        return HAL_WRAPPER_STAT_INVALID_PARAMS;

    // TODO: try reading from ADXL345 around 30 times and see what happens

    // float avg_x = 0.0;
    // float avg_y = 0.0;
    // float avg_z = 0.0;

    // read the accelerometer data from ADXL345
    // for(int i = 0; i < 30; i++)
    // {
    // 	HAL_ADXL345_ReadAcc(&MCAL_CFG_adxlSPI, &global_ADXL345ACC_t);
    // 	avg_x += (global_ADXL345ACC_t.x / 30.0);
    // 	avg_y += (global_ADXL345ACC_t.y / 30.0);
    // 	avg_z += (global_ADXL345ACC_t.z / 30.0);
    // }

    // avg_x = (avg_x * 4) / 1000;
    // avg_y = (avg_y * 4) / 1000;
    // avg_z = (avg_z * 4) / 1000;

    // read acceleration from MPU6050
    mpu6050_accel_read(&global_MPU6050ACC_t.x, &global_MPU6050ACC_t.y, &global_MPU6050ACC_t.z);

    // account for the placement of the IC on the PCB
   global_MPU6050ACC_t.x = -global_MPU6050ACC_t.x;
    global_MPU6050ACC_t.y = -global_MPU6050ACC_t.y;
//    global_MPU6050ACC_t.z = global_MPU6050ACC_t.z;

    arg_pAcc->x = global_MPU6050ACC_t.x;
    arg_pAcc->y = global_MPU6050ACC_t.y;
    arg_pAcc->z = global_MPU6050ACC_t.z;

    return MCAL_WRAPPER_STAT_OK;
}


/**
 * 
 */
HAL_WRAPPER_ErrStat_t HAL_WRAPPER_ReadGyro(HAL_WRAPPER_Gyro_t *arg_pGyro)
{
    // read gyroscope from mpu6050
    mpu6050_gyro_read(&global_MPU6050GYRO_t.roll, &global_MPU6050GYRO_t.pitch, &global_MPU6050GYRO_t.yaw);

    // account for the placement of the IC on the PCB
    global_MPU6050GYRO_t.roll = -global_MPU6050GYRO_t.roll;
    global_MPU6050GYRO_t.pitch = -global_MPU6050GYRO_t.pitch;
//    global_MPU6050GYRO_t.yaw = global_MPU6050GYRO_t.yaw;

    arg_pGyro->pitch = global_MPU6050GYRO_t.pitch;
    arg_pGyro->roll = global_MPU6050GYRO_t.roll;
    arg_pGyro->yaw = global_MPU6050GYRO_t.yaw;

    return HAL_WRAPPER_STAT_OK;
}

/**
 * 
 */
HAL_WRAPPER_ErrStat_t HAL_WRAPPER_ReadMagnet(HAL_WRAPPER_Magnet_t *arg_pMagnet)
{
    int16_t temp = 0;
    // read gyroscope from hmc5883l
    hmc5883l_read(&global_HMC5883MAGNET_t);

    // account for the placement of the IC on the PCB
    temp = -global_HMC5883MAGNET_t.magnetometer_raw_x;
    global_HMC5883MAGNET_t.magnetometer_raw_x = -global_HMC5883MAGNET_t.magnetometer_raw_y;
    global_HMC5883MAGNET_t.magnetometer_raw_y = temp;

    hmc5883l_normalize(&global_HMC5883MAGNET_t);


    arg_pMagnet->x = global_HMC5883MAGNET_t.calibrated_x;
    arg_pMagnet->y = global_HMC5883MAGNET_t.calibrated_y;
    arg_pMagnet->z = global_HMC5883MAGNET_t.calibrated_z;

    return HAL_WRAPPER_STAT_OK;

}

/**
 * 
 */
HAL_WRAPPER_ErrStat_t HAL_WRAPPER_SetESCSpeeds(HAL_WRAPPER_MotorSpeeds_t *arg_pMotorsSpeed)
{
    if(arg_pMotorsSpeed->topLeftSpeed > 100 || arg_pMotorsSpeed->topRightSpeed > 100 || arg_pMotorsSpeed->bottomLeftSpeed > 100 || arg_pMotorsSpeed->bottomRightSpeed > 100)
    {
        return HAL_WRAPPER_STAT_INVALID_PARAMS;
    }

    // set the new speeds
    HAL_ESC_setSpeed(HAL_ESC_MOTOR_TOP_LEFT, arg_pMotorsSpeed->topLeftSpeed);
    HAL_ESC_setSpeed(HAL_ESC_MOTOR_TOP_RIGHT, arg_pMotorsSpeed->topRightSpeed);
    HAL_ESC_setSpeed(HAL_ESC_MOTOR_BOTTOM_LEFT, arg_pMotorsSpeed->bottomLeftSpeed);
    HAL_ESC_setSpeed(HAL_ESC_MOTOR_BOTTOM_RIGHT, arg_pMotorsSpeed->bottomRightSpeed);

    return HAL_WRAPPER_STAT_OK;
}

/**
 * 
 */
HAL_WRAPPER_ErrStat_t HAL_WRAPPER_DisableEnableAppCommRecCallBack(LIB_CONSTANTS_DriverStates_t arg_Enable_Disable_t)
{
    // configure interrupt
    MCAL_WRAPPER_UART4RecITConfig(arg_Enable_Disable_t);

    return HAL_WRAPPER_STAT_OK;
}

/**
 * 
 */
HAL_WRAPPER_ErrStat_t HAL_WRAPPER_SetAppCommRecCallBack(functionCallBack_t arg_pUARTCallBack)
{
    MCAL_WRAPPER_SetUART4RecCallBack(arg_pUARTCallBack);
    return HAL_WRAPPER_STAT_OK;
}

/**
 * 
 */
HAL_WRAPPER_ErrStat_t HAL_WRAPPER_ReceiveSendAppCommMessage(HAL_WRAPPER_AppCommMsg_t* arg_AppCommMsg_t)
{

    // temp variables to allow synchronous send and receive at the same time
    uint16_t local_u16LenOfDataToSend = 0;
    uint16_t local_u16LenOfDataToReceive = 0;

    // to detect if there is anything in the receiver buffer (as by writing to UART data register clears the RXNE flag)
    MCAL_WRAPPER_ErrStat_t local_writeSuccess_t = MCAL_WRAPPER_STAT_OK;

    // loop until we send or received all messages
    while (arg_AppCommMsg_t->dataIsToSend || arg_AppCommMsg_t->dataIsToReceive)
    {
        // check if to send
        if(arg_AppCommMsg_t->dataIsToSend)
        {
            // send 1 byte
            local_writeSuccess_t = MCAL_WRAPPER_SendDataThroughUART4(arg_AppCommMsg_t->dataToSend + local_u16LenOfDataToSend, 1);
            
            if(MCAL_WRAPPER_STAT_OK == local_writeSuccess_t)
            {
                local_u16LenOfDataToSend++;
                
                // check if sending is done
                if(local_u16LenOfDataToSend == arg_AppCommMsg_t->dataToSendLen)
                {
                    
                    arg_AppCommMsg_t->dataIsToSend = 0;
                }  
            }
        }

        // check if to receive
        if(arg_AppCommMsg_t->dataIsToReceive)
        {
            // receive 1 byte
            MCAL_WRAPPER_ReceiveDataThroughUART4(arg_AppCommMsg_t->dataToReceive + local_u16LenOfDataToReceive, 1);
            local_u16LenOfDataToReceive++;

            // check if receiving is done
            if(local_u16LenOfDataToReceive == arg_AppCommMsg_t->dataToReceiveLen)
            {
                arg_AppCommMsg_t->dataIsToReceive = 0;

               // enable receuve interrupt
                HAL_WRAPPER_DisableEnableAppCommRecCallBack(LIB_CONSTANTS_ENABLED);
            }
        }
    }
    

    return HAL_WRAPPER_STAT_OK;
}

/**
 * 
 */
HAL_WRAPPER_ErrStat_t HAL_WRAPPER_GetCommMessage(uint8_t* arg_pu8Msg)
{
    // receive 1 byte
    MCAL_WRAPPER_ErrStat_t local_errState_t = MCAL_WRAPPER_ReceiveDataThroughUART4(arg_pu8Msg, 1);
    
    if(MCAL_WRAPPER_STAT_OK != local_errState_t)
    {
        local_errState_t = HAL_WRAPPER_STAT_APP_DIDNT_SND;
    }
    else
    {
        local_errState_t = HAL_WRAPPER_STAT_OK;
    }

    return local_errState_t;
}

/**
 * 
 */
HAL_WRAPPER_ErrStat_t HAL_WRAPPER_SendCommMessage(uint8_t arg_pu8Msg)
{
    MCAL_WRAPPER_ErrStat_t local_errState_t = MCAL_WRAPPER_SendDataThroughUART4(&arg_pu8Msg, 1);
    if(MCAL_WRAPPER_STAT_OK != local_errState_t)
    {
        local_errState_t = HAL_WRAPPER_STAT_APP_BOARD_BSY;
    }
    else
    {
        local_errState_t = HAL_WRAPPER_STAT_OK;
    }

    return local_errState_t;
}

/**
 * 
 */
HAL_WRAPPER_ErrStat_t HAL_WRAPPER_ReadPressure(HAL_WRAPPER_Pressure_t *arg_pPressure_t)
{
    // read pressure from BMP280
    arg_pPressure_t->pressure = BMP280_get_pressure();

    return HAL_WRAPPER_STAT_OK;
}

/**
 * 
 */
HAL_WRAPPER_ErrStat_t HAL_WRAPPER_ReadTemperature(HAL_WRAPPER_Temperature_t *arg_pTemperature_t)
{   
    // read temperature from BMP280
    arg_pTemperature_t->temperature = BMP280_get_temperature();

    return HAL_WRAPPER_STAT_OK;
}

/**
 * 
 */
HAL_WRAPPER_ErrStat_t HAL_WRAPPER_ReadAltitude(HAL_WRAPPER_Altitude_t *arg_pAltitude_t, HAL_WRAPPER_Pressure_t *ref)
{   
    // compute altitude from BMP280
    arg_pAltitude_t->altitude = BMP280_get_altitude(ref->pressure);

    // compute altitude from ultrasonic
//    HAL_HCSR04_GetDistance(&arg_pAltitude_t->ultrasonic_altitude);

    return HAL_WRAPPER_STAT_OK;
}

/**
 * 
 */
HAL_WRAPPER_ErrStat_t HAL_WRAPPER_GetBatteryCharge(HAL_WRAPPER_Battery_t *arg_pBatteryCharge)
{
    uint16_t local_u16Charge = 0;

    // get ADC readings
    MCAL_WRAPPER_GetADCBattery(&local_u16Charge);

    // get the actual volt on the input pin
    float local_f32Volt = 3.3 * (local_u16Charge / 4096.0);

    // map that volt to the original 12v range
    local_f32Volt = (local_f32Volt * 19.7) / 4.7;

    // assume min value is 10V and max is 12.6V for 3S lipo battery
    // actually min value is 9V but we don't want to reach that value so 10V is a safer value
    local_f32Volt = (local_f32Volt - LIPO_3S_MIN_V) / (LIPO_3S_MAX_V - LIPO_3S_MIN_V);

    // get it in percentage
    arg_pBatteryCharge->batteryCharge = (uint8_t)(local_f32Volt * 100);

    return HAL_WRAPPER_STAT_OK;
}


/*************** END OF FUNCTIONS ***************************************************************************/
