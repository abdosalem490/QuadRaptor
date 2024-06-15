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

# define M_PI           3.14159265358979323846  /* pi */

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
void SensorFuseWithKalman(RawSensorDataItem_t* arg_pSensorsReadings, SensorFusionDataItem_t* arg_pFusedReadings)
{
    
    float measured_roll, measured_pitch, Ts;
    Ts = SENSOR_SAMPLE_PERIOD/1000.0;

    measured_roll  = atan(arg_pSensorsReadings->Acc.y / sqrt(arg_pSensorsReadings->Acc.x * arg_pSensorsReadings->Acc.x + arg_pSensorsReadings->Acc.z * arg_pSensorsReadings->Acc.z) ) * (180/M_PI);
    measured_pitch = -atan(arg_pSensorsReadings->Acc.x / sqrt(arg_pSensorsReadings->Acc.y * arg_pSensorsReadings->Acc.y + arg_pSensorsReadings->Acc.z * arg_pSensorsReadings->Acc.z) ) * (180/M_PI);

    kalman_filter(&arg_pFusedReadings->roll, &arg_pFusedReadings->roll_uncertainty, arg_pSensorsReadings->Gyro.roll, measured_roll, Ts, STD_DEV_GYR, STD_DEV_ACC);
    kalman_filter(&arg_pFusedReadings->pitch, &arg_pFusedReadings->pitch_uncertainty, arg_pSensorsReadings->Gyro.pitch, measured_pitch, Ts, STD_DEV_GYR, STD_DEV_ACC);

}
 

/*************** END OF FUNCTIONS ***************************************************************************/
