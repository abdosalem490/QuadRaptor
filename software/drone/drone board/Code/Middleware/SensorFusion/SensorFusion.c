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

/**
 * @reason: for malloc and free call functions
 */
#include <stdlib.h>

/**
 * 
 */
#include "matrix.h"

/******************************************************************************
 * Module Preprocessor Constants
 *******************************************************************************/

/* Kalman Filter constants */
#define STD_DEV_GYR (4.0)   // Standard Deviation of the gyroscope
#define STD_DEV_ACC (3.0)   // Standard Deviation of the accelerometer
#define STD_DEV_MAG (1.0)   // Standard Deviation of the magnetometer

#define PI (3.14159265)
#define EPSILON (1.4e-14)

#define BAROMETER_MEASUREMENT_UNCERTAINTY (900)  // 30cm

/******************************************************************************
 * Module Preprocessor Macros
 *******************************************************************************/

/******************************************************************************
 * Module Typedefs
 *******************************************************************************/

/******************************************************************************
 * Module Variable Definitions
 *******************************************************************************/
matrix_2d_t S = {0}, F = {0}, G = {0}, U = {0}, H = {0}, Q = {0}, P = {0}, K = {0}, L = {0}, R = {0}, M = {0}, I = {0};
float  Ts = SENSOR_SAMPLE_PERIOD/1000.0;

/******************************************************************************
 * Function Prototypes
 *******************************************************************************/

/**
 * Computes the azimuth angle based on the magnetic sensor readings along the X and Y axes.
 * The azimuth angle is calculated in radians from the North direction, using the arctangent of the Y and X magnetic field values.
 *
 * @param mag_x The magnetic field reading along the X-axis.
 * @param mag_y The magnetic field reading along the Y-axis.
 *
 * @return The azimuth angle in radians.
 */
float compute_azimuth(float mag_x, float mag_y);

/**
 * Performs a single iteration of the Kalman filter on a one-dimensional system. This function updates the Kalman state
 * and uncertainty based on the new input and measurement.
 *
 * @param KalmanState Pointer to the current state estimate of the Kalman filter. Updated by this function.
 * @param KalmanUncertainty Pointer to the current estimate uncertainty of the Kalman filter. Updated by this function.
 * @param KalmanInput The control input to the system.
 * @param KalmanMeasurement The new measurement for the update step.
 * @param Ts The sampling time or time step between the current and previous measurements.
 * @param process_noise The process noise covariance, representing the uncertainty in the system model.
 * @param measure_covar The measurement noise covariance, representing the uncertainty in the measurement.
 *
 * @return void.
 */
void kalman_filter(float * KalmanState, float * KalmanUncertainty, float KalmanInput, float KalmanMeasurement, float Ts, float process_noise, float measure_covar);

/**
 * Applies a 2D Kalman filter to estimate the true position based on a single measurement and inertial acceleration.
 * This simplified function is designed for systems where a full 2D state estimation is required but only a single
 * measurement is available. It abstracts the complexities of a full 2D Kalman filter implementation.
 *
 * @param measurement The measurement value used for the update step of the Kalman filter.
 * @param inertial_acc The acceleration value from an inertial measurement unit, used as part of the system model.
 *
 * @return void.
 */
void kalman_filter_2d(float measurement, float inertial_acc);
/******************************************************************************
 * Function Definitions
 *******************************************************************************/

/**
 *
 */
float compute_azimuth(float mag_x, float mag_y)
{
    float declination_angle, heading;
    // Declination angle
    declination_angle = (DECLINATION_DEGREE + (DECLINATION_MINUTE / 60.0)) * (PI / 180);
    // Calculate heading
    heading = atan2(mag_x, mag_y);
    heading += declination_angle;

    return heading * (180/PI);
}


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
 * @param S: State matrix
 * @param F: State transition matrix
 * @param G: Control matrix
 * @param U: Input variable matrix
 * @param H: Measurement matrix
 * @param Q: Process noise covariance matrix
 * @param R: Measurement noise covariance matrix
 * @param P: Covariance matrix
 * @param K: Kalman gain matrix
 * @param L: Temporary matrix for storing intermediate values during Kalman gain calculation
 * @param M: Measurement matrix
 * @param I: Identity matrix
 * @param F_T: Transpose of the state transition matrix
 * @param H_T: Transpose of the measurement matrix
 * @param temp_1, temp_2, temp_3, temp_4: Temporary matrices for intermediate calculations
 */
void kalman_filter_2d(float measurement, float inertial_acc)
{
    matrix_2d_t temp_1, temp_2, temp_3, temp_4;
    matrix_2d_t F_T, H_T;

    U.values[0] = inertial_acc;

    // Predict
    matrix_multiply(&F, &S, &temp_1);
    matrix_multiply(&G, &U, &temp_2);
    matrix_add(&temp_1, &temp_2, &S);
    matrix_clear(&temp_1);
    matrix_clear(&temp_2);

    // Update
    matrix_multiply(&F, &P, &temp_1);
    matrix_transpose(&F, &F_T);
    matrix_multiply(&temp_1, &F_T, &temp_2);
    matrix_add(&temp_2, &Q, &P);
    matrix_clear(&temp_1);
    matrix_clear(&temp_2);

    // Kalman Gain
    matrix_transpose(&H, &H_T);
    matrix_multiply(&H, &P, &temp_1);
    matrix_multiply(&temp_1, &H_T, &temp_2);
    matrix_add(&temp_2, &R, &L);
    matrix_clear(&temp_1);
    matrix_clear(&temp_2);
    L.values[0] = 1/(L.values[0]+EPSILON);

    matrix_multiply(&P, &H_T, &temp_1);
    matrix_multiply(&temp_1, &L, &K);
    matrix_clear(&temp_1);

    // Update State
    M.values[0] = measurement;
    matrix_multiply(&H, &S, &temp_1);
    matrix_subtract(&M, &temp_1, &temp_2);
    matrix_multiply(&K, &temp_2, &temp_3);
    matrix_add(&S, &temp_3, &temp_4);
    matrix_clear(&S);
    matrix_copy(&temp_4, &S);
    matrix_clear(&temp_1);
    matrix_clear(&temp_2);
    matrix_clear(&temp_3);

    // Update Uncertainty
    matrix_multiply(&K, &H, &temp_1);
    matrix_subtract(&I, &temp_1, &temp_2);
    matrix_multiply(&temp_2, &P, &temp_3);
    matrix_clear(&P);
    matrix_clear(&temp_1);
    matrix_clear(&temp_2);
    matrix_copy(&temp_3, &P);
}

/**
 *
 */
void SensorFuseWithKalman(RawSensorDataItem_t* arg_pSensorsReadings, SensorFusionDataItem_t* arg_pFusedReadings)
{
    float roll_rad, pitch_rad;
    float mag_x, mag_y, mag_z;
    float measured_roll, measured_pitch, measured_yaw;
    float vertical_acc;

    // Roll and Pitch angles
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
    

    // Inertial vertical velocity
    vertical_acc =  - arg_pSensorsReadings->Acc.x * sin(pitch_rad)
                    + arg_pSensorsReadings->Acc.y * sin(roll_rad) * cos(pitch_rad) 
                    + arg_pSensorsReadings->Acc.z * cos(roll_rad) * cos(pitch_rad);
    vertical_acc = (vertical_acc-1)*9.81*100;

    // 2D kalman filter for altitude estimation
    kalman_filter_2d(arg_pSensorsReadings->Altitude.altitude*100, vertical_acc);
    arg_pFusedReadings->altitude = S.values[0];
    arg_pFusedReadings->vertical_velocity = S.values[1];

    // compute yaw rate
    arg_pFusedReadings->yaw_rate = arg_pSensorsReadings->Gyro.yaw;

}


void Altitude_Kalman_2D_init()
{
    matrix_2d_t G_T;

    // State Matrix S
    float* S_values = (float*)malloc(2 * 1 * sizeof(float));
    S_values[0] = 0; S_values[1] = 0;
    matrix_set(&S, 2, 1, S_values);

    // Covariance Matrix P
    float* P_values = (float*)malloc(2 * 2 * sizeof(float));
    P_values[0] = 0; P_values[1] = 0;
    P_values[2] = 0; P_values[3] = 0;
    matrix_set(&P, 2, 2, P_values);

    // State Transition Matrix F
    float* F_values = (float*)malloc(2 * 2 * sizeof(float));
    F_values[0] = 1; F_values[1] = Ts;
    F_values[2] = 0; F_values[3] = 1;
    matrix_set(&F, 2, 2, F_values);

    // Control Matrix G
    float* G_values = (float*)malloc(2 * 1 * sizeof(float));
    G_values[0] = 0.5 * Ts * Ts; G_values[1] = Ts;
    matrix_set(&G, 2, 1, G_values);

    // Input Matrix U
    float* U_values = (float*)malloc(1 * 1 * sizeof(float));
    U_values[0] = 0;
    matrix_set(&U, 1, 1, U_values);

    // Observation Matrix H
    float* H_values = (float*)malloc(1 * 2 * sizeof(float));
    H_values[0] = 1; H_values[1] = 0;
    matrix_set(&H, 1, 2, H_values);

    // Process Noise Covariance Matrix Q (assume process variance = 1)
    matrix_transpose(&G, &G_T);
    matrix_multiply(&G, &G_T, &Q);

    // Measurement Noise Covariance Matrix R
    float* R_values = (float*)malloc(1 * 1 * sizeof(float));
    R_values[0] = BAROMETER_MEASUREMENT_UNCERTAINTY;
    matrix_set(&R, 1, 1, R_values);

    // Intermediate Matrix L
    float* L_values = (float*)malloc(1 * 1 * sizeof(float));
    L_values[0] = 0;
    matrix_set(&L, 1, 1, L_values);

    // Kalman Gain Matrix K
    float* K_values = (float*)malloc(2 * 1 * sizeof(float));
    K_values[0] = 0; K_values[1] = 0;
    matrix_set(&K, 2, 1, K_values);

    // Measurement matrix M
    float* M_values = (float*)malloc(1 * 1 * sizeof(float));
    M_values[0] = 0;
    matrix_set(&M, 1, 1, M_values);

    // Identity Matrix I
    float* I_values = (float*)malloc(2 * 2 * sizeof(float));
    I_values[0] = 1; I_values[1] = 0;
    I_values[2] = 0; I_values[3] = 1;
    matrix_set(&I, 2, 2, I_values);

}

 

/*************** END OF FUNCTIONS ***************************************************************************/
