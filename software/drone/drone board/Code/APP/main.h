/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   Application Code                                                                                            |
 * |    @file           :   main.h                                                                                                      |
 * |    @author         :   Abdelrahman Mohamed Salem                                                                                   |
 * |    @origin_date    :   14/06/2024                                                                                                  |
 * |    @version        :   1.0.0                                                                                                       |
 * |    @tool_chain     :   RISC-V Cross GCC                                                                                            |
 * |    @compiler       :   GCC                                                                                                         |
 * |    @C_standard     :   ISO C99 (-std=c99)                                                                                          |
 * |    @target         :   CH32V203C8T6                                                                                                |
 * |    @notes          :   None                                                                                                        |
 * |    @license        :   MIT License                                                                                                 |
 * |    @brief          :   this file is the header for main entry to our application code that will run                                |
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
 * |    14/06/2023      1.0.0           Abdelrahman Mohamed Salem       file Created.                                                   |
 * |    17/06/2023      1.0.0           Abdelrahman Mohamed Salem       added extra defs for structs to be sent over air.               |
 * --------------------------------------------------------------------------------------------------------------------------------------
 */



#ifndef MAIN_H_
#define MAIN_H_

/******************************************************************************
 * Includes
 *******************************************************************************/

/**
 * @reason: contains typedefs needed
 */
#include "HAL_wrapper.h"

/**
 * @reason: contains definitions for standard integer definitions
 */
#include "stdint.h"

/******************************************************************************
 * Module Preprocessor Constants
 *******************************************************************************/

/**
 * @brief: this is how frequent we collect sensors data in MS
 */
#define SENSOR_SAMPLE_PERIOD 5

/******************************************************************************
 * Module Preprocessor Macros
 *******************************************************************************/

/******************************************************************************
 * Module Typedefs
 *******************************************************************************/

/************************************************************************/
/**
* @brief: defines the data to be sent over nrf module (over the air)
*/
typedef enum {
  DATA_TYPE_MOVE = 0b01010101,   // from remote to drone
  DATA_TYPE_EXTRAS = 0b00110011, // from remote to drone
  DATA_TYPE_INFO = 0b10101010,   // from drone to remote
  DATA_TYPE_INVALID = 0b0,       // invalid message type received
} DATA_TYPE_t;

/**
* @brief: struct defines data that holds: yaw, roll, pitch, thrust commands
*/
typedef struct __attribute__((packed)){
  int8_t roll;
  int8_t pitch;
  int8_t thrust;
  int8_t yaw;
  uint8_t turnOnLeds;
  uint8_t playMusic;
} move_command_t;


/**
* @brief: struct defines data that holds info coming from the drone like temperature, battery charge, etc...
*/
typedef struct __attribute__((packed)){
  float distanceToOrigin;
  float altitude;
  float temperature;
  uint8_t batteryCharge;
} drone_info_t;

/**
* @brief: the struct that to be sent over the air
*/
typedef struct __attribute__((packed)){
  uint8_t type;

  union {
    move_command_t move;
    drone_info_t info;
  } data;

} data_t;

/************************************************************************/
/**
 * @brief: this is the struct definition of the items of the 'queue_RawSensorData_Handle_t' elements
*/
typedef struct {
    HAL_WRAPPER_Acc_t Acc;
    HAL_WRAPPER_Gyro_t Gyro;
    HAL_WRAPPER_Magnet_t Magnet;
    HAL_WRAPPER_Pressure_t Pressure;
    HAL_WRAPPER_Temperature_t Temperature;
} RawSensorDataItem_t;

/**
 * @brief: this is the struct definition of the items of the 'queue_FusedSensorData_Handle_t' elements
*/
typedef struct {
    
    // fused kalman angles
    float roll;
    float yaw;
    float pitch;

    // kalman uncertainty for each angle
    float roll_uncertainty;
    float yaw_uncertainty;
    float pitch_uncertainty;

} SensorFusionDataItem_t;


/**
 * @brief: this is the struct definition of the items of the 'queue_AppCommToDrone_Handle_t' elements
*/
typedef struct {
    data_t data;  // the variable through which we will send and recieve data
} AppToDroneDataItem_t;

/**
 * @brief: this is the struct definition of the items of the 'queue_DroneCommToApp_Handle_t' elements
*/
typedef struct {
    data_t data;  // the variable through which we will send and receive data
} DroneToAppDataItem_t;

/******************************************************************************
 * Module Variable Definitions
 *******************************************************************************/

/******************************************************************************
 * Function Prototypes
 *******************************************************************************/

/******************************************************************************
 * Function Definitions
 *******************************************************************************/


/*************** END OF FUNCTIONS ***************************************************************************/

#endif /*MAIN_H_*/
