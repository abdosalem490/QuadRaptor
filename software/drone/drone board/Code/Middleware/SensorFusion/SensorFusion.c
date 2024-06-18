/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   Sensor fusion utility for readings correction                                                               |
 * |    @file           :   SensorFusion.h                                                                                              |
 * |    @author         :   Mohab Zaghloul                                                                                              |
 * |    @origin_date    :   14/06/2024                                                                                                  |
 * |    @version        :   1.0.0                                                                                                       |
 * |    @tool_chain     :   RISC-V Cross GCC                                                                                            |
 * |    @compiler       :   GCC                                                                                                         |
 * |    @C_standard     :   ISO C99 (-std=c99)                                                                                          |
 * |    @target         :   CH32V203C8T6                                                                                                |
 * |    @notes          :   None                                                                                                        |
 * |    @license        :   MIT License                                                                                                 |
 * |    @brief          :   this file is the main file for correction of sensor readings                                                |
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
 * |    18/06/2023      1.0.0           Mohab Zaghloul                  HMC fused.                                                      |
 * --------------------------------------------------------------------------------------------------------------------------------------
 */


/******************************************************************************
 * Includes
 *******************************************************************************/

/**
 * 
 */
#include "SensorFusion.h"

/**
 * 
 */
#include "main.h"

/**
 * 
 */
#include "HAL_wrapper.h"

/**
 * 
 */
#include <math.h>

/******************************************************************************
 * Module Preprocessor Constants
 *******************************************************************************/

/* Kalman Filter constants */
#define STD_DEV_GYR (4.0)   // Standard Deviation of the gyroscope
#define STD_DEV_ACC (3.0)   // Standard Deviation of the accelerometer
#define STD_DEV_MAG (1.0)   // Standard Deviation of the magnetometer

#define PI 3.14159265

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

/**
 * 
 */
void kalman_filter(float * KalmanState, float * KalmanUncertainty, float KalmanInput, float KalmanMeasurement, float Ts, float process_noise, float measure_covar);

/**
 * 
 */


/******************************************************************************
 * Function Definitions
 *******************************************************************************/



/**
 *
 */
void kalman_filter(float * KalmanState, float * KalmanUncertainty, float KalmanInput, float KalmanMeasurement, float Ts, float process_noise, float measure_covar)
{
    float KalmanGain;
    *KalmanState = *KalmanState + Ts*KalmanInput;
    *KalmanUncertainty = *KalmanUncertainty + Ts*Ts * process_noise*process_noise;
    KalmanGain = *KalmanUncertainty * 1/(1*(*KalmanUncertainty) + measure_covar*measure_covar);
    *KalmanState = *KalmanState + KalmanGain*(KalmanMeasurement-*KalmanState);
    *KalmanUncertainty = (1-KalmanGain) * (*KalmanUncertainty);
}

/**
 *
 */
float compute_azimuth(float mag_x, float mag_y)
{
    float declination_angle, heading;
    // Declination angle
    declination_angle = (DECLINATION_DEGREE + (DECLINATION_MINUTE / 60.0)) / (180 / PI);
    // Calculate heading
    heading = atan2(mag_x, mag_y);
    heading += declination_angle;

    return heading * (180/PI);
}

/**
 *
 */
void SensorFuseWithKalman(RawSensorDataItem_t* arg_pSensorsReadings, SensorFusionDataItem_t* arg_pFusedReadings)
{
    float roll_rad, pitch_rad;
    float mag_x, mag_y, mag_z;
    float measured_roll, measured_pitch, measured_yaw;
    float  Ts;
    Ts = SENSOR_SAMPLE_PERIOD/1000.0;

    roll_rad  = atan(arg_pSensorsReadings->Acc.y / sqrt(arg_pSensorsReadings->Acc.x * arg_pSensorsReadings->Acc.x + arg_pSensorsReadings->Acc.z * arg_pSensorsReadings->Acc.z) );
    pitch_rad = -atan(arg_pSensorsReadings->Acc.x / sqrt(arg_pSensorsReadings->Acc.y * arg_pSensorsReadings->Acc.y + arg_pSensorsReadings->Acc.z * arg_pSensorsReadings->Acc.z) );

    measured_roll  = roll_rad  * (180/PI);
    measured_pitch = pitch_rad * (180/PI);

    kalman_filter(&arg_pFusedReadings->roll, &arg_pFusedReadings->roll_uncertainty, arg_pSensorsReadings->Gyro.roll, measured_roll, Ts, STD_DEV_GYR, STD_DEV_ACC);
    kalman_filter(&arg_pFusedReadings->pitch, &arg_pFusedReadings->pitch_uncertainty, arg_pSensorsReadings->Gyro.pitch, measured_pitch, Ts, STD_DEV_GYR, STD_DEV_ACC);

    // Yaw angle
    roll_rad = arg_pFusedReadings->roll * (PI/180);
    pitch_rad = arg_pFusedReadings->pitch * (PI/180);

    mag_x = arg_pSensorsReadings->Magnet.x;
    mag_y = arg_pSensorsReadings->Magnet.y;
    mag_z = arg_pSensorsReadings->Magnet.z;

    mag_x = mag_x*cos(roll_rad) + mag_z*sin(roll_rad);
    mag_y = mag_y*cos(pitch_rad) + mag_z*sin(pitch_rad);

    measured_yaw = compute_azimuth(mag_x, mag_y);

    kalman_filter(&(arg_pFusedReadings->yaw), &(arg_pFusedReadings->yaw_uncertainty), arg_pSensorsReadings->Gyro.yaw, measured_yaw, Ts, STD_DEV_GYR, STD_DEV_MAG);
    
}
 

/*************** END OF FUNCTIONS ***************************************************************************/
