/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   wrapper file for the HAL layer functions                                                                    |
 * |    @file           :   HAL_wrapper.h                                                                                               |
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
 * |    17/06/2023      1.0.0           Abdelrahman Mohamed Salem       added 'HAL_WRAPPER_SetAppCommRecCallBack'.                      |
 * |    17/06/2023      1.0.0           Abdelrahman Mohamed Salem       added 'HAL_WRAPPER_ReceiveSendAppCommMessage'.                  |
 * |    20/06/2023      1.0.0           Abdelrahman Mohamed Salem       added 'HAL_WRAPPER_DisableEnableAppCommRecCallBack'.            |
 * |    20/06/2023      1.0.0           Abdelrahman Mohamed Salem       added 'HAL_WRAPPER_GetAppCommMessageType'.                      |
 * |    22/06/2023      1.0.0           Abdelrahman Mohamed Salem       added 'HAL_WRAPPER_ReadPressure'.                               |
 * |    22/06/2023      1.0.0           Abdelrahman Mohamed Salem       added 'HAL_WRAPPER_ReadTemperature'.                            |
 * |    22/06/2023      1.0.0           Abdelrahman Mohamed Salem       added 'HAL_WRAPPER_GetBatteryCharge'.                            |
 * --------------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef HAL_WRAPPER_HEADER_H_
#define HAL_WRAPPER_HEADER_H_

/******************************************************************************
 * Includes
 *******************************************************************************/

/**
 * @reason: contains definition struct for all the hardware
 */
#include "HAL_config.h"

/**
 * @reason: contains standard definitions
 */
#include "stdint.h"

/**
 * @reason: contains type definition for call back function
 */
#include "common.h"


/******************************************************************************
 * Preprocessor Constants
 *******************************************************************************/

/******************************************************************************
 * Configuration Constants
 *******************************************************************************/

/******************************************************************************
 * Macros
 *******************************************************************************/

/******************************************************************************
 * Typedefs
 *******************************************************************************/

/**
 * @brief: contains error states for this module
*/
typedef enum {
  HAL_WRAPPER_STAT_OK,
  HAL_WRAPPER_STAT_INVALID_PARAMS,
  HAL_WRAPPER_STAT_APP_BOARD_BSY,
  HAL_WRAPPER_STAT_APP_DIDNT_SND,
} HAL_WRAPPER_ErrStat_t;

/**
 * @brief: contains definitions to be used with reading accelerometer data
 */
typedef struct
{
  float x; /**< acceleration in x-direction */
  float y; /**< acceleration in y-direction */
  float z; /**< acceleration in z-direction */
} HAL_WRAPPER_Acc_t;

/**
 * @brief: contains definitions to be used with reading gyroscope data
 */
typedef struct
{
  float roll;  /**< gyroscope in x-direction */
  float pitch; /**< gyroscope in y-direction */
  float yaw;   /**< gyroscope in z-direction */
} HAL_WRAPPER_Gyro_t;


/**
 * @brief: contains definitions to be used with reading Magnetometer data
 */
typedef struct
{
  float x;  /**< Magnetometer in x-direction */
  float y;  /**< Magnetometer in y-direction */
  float z;  /**< Magnetometer in z-direction */  
} HAL_WRAPPER_Magnet_t;

/**
 * @brief: contains definitions to be used with reading pressure data
 */
typedef struct
{
  float pressure;  /**< barometric pressure */
} HAL_WRAPPER_Pressure_t;

/**
 * @brief: contains definitions to be used with reading pressure data
 */
typedef struct
{
  float temperature;  /**< temperature in Degree Celsius */
} HAL_WRAPPER_Temperature_t;

/**
 * @brief: contains definitions to be used with reading pressure data
 */
typedef struct
{
  float altitude;  /**< Altitude in cm */
  float ultrasonic_altitude;  /**< Altitude in cm from ultrasonic sensor */
} HAL_WRAPPER_Altitude_t;

/**
 * @brief: contains definitions to be used with reading battery charge data
 */
typedef struct
{
  uint8_t batteryCharge;  /**< Altitude in cm */
} HAL_WRAPPER_Battery_t;

/**
 * @brief: contains defintions to be used to set motor speeds associated with ESCs
 */
typedef struct 
{
  float topLeftSpeed; /**< speed of top left motor in range 0 to 100 */
  float topRightSpeed; /**< speed of top Right motor in range 0 to 100 */
  float bottomLeftSpeed; /**< speed of bottom left motor in range 0 to 100 */
  float bottomRightSpeed; /**< speed of bottom right motor in range 0 to 100 */
} HAL_WRAPPER_MotorSpeeds_t;

/**
 * @brief: contains definitions to be used with communication with app board
 */
typedef struct
{
  uint8_t* dataToSend;                /**< base address of data to send through app comm port */
  uint8_t* dataToReceive;             /**< base address of data to receive through app comm port */
  uint16_t dataToSendLen;             /**< length of data to send through app comm port */
  uint16_t dataToReceiveLen;          /**< length of data to receive through app comm port */
  volatile uint8_t dataIsToReceive;   /**< boolean flag to indicate whether a data is to be received or not */
  uint8_t dataIsToSend;               /**< boolean flag to indicate whether a data is to be sent or not */
  uint8_t  IsDataReceived;            /**< boolean flag to indicate whether a whole data packet is received or not */
} HAL_WRAPPER_AppCommMsg_t;

/******************************************************************************
 * Variables
 *******************************************************************************/

/******************************************************************************
 * Function Prototypes
 *******************************************************************************/

/**
 *  \b function                                 :       HAL_WRAPPER_ErrStat_t HAL_WRAPPER_ReadAcc(HAL_WRAPPER_Acc_t *arg_pAcc);
 *  \b Description                              :       this functions is used as a wrapper function to the function of reading accelerometer from different sensors on the board.
 *  @param  arg_pAcc [OUT]                      :       base address to store the received data from the SPI upon transfer.
 *  @note                                       :       this is a polling function halting the process execution until the SPI data is transferred.
 *  \b PRE-CONDITION                            :       make sure to call configure function the configuration file in the current directory.
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       it return one of error states indicating whether a failure or success happened (refer to @HAL_WRAPPER_ErrStat_t in "HAL_wrapper.h")
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * #include "HAL_wrapper.h"
 * 
 * 
 * int main() {
 * 
 * MCAL_Config_ErrStat_t local_errState = HAL_Config_ConfigAllHW();
 * if(HAL_Config_STAT_OK == local_errState)
 * {
 *  HAL_WRAPPER_Acc_t *temp = {0};
 *  local_errState = HAL_WRAPPER_ReadAcc(temp);
 *  if(HAL_WRAPPER_STAT_OK == local_errState)
 *  {
 *  
 *  }
 * }
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 12/06/2024 </td><td> 1.0.0            </td><td> AMS      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
HAL_WRAPPER_ErrStat_t HAL_WRAPPER_ReadAcc(HAL_WRAPPER_Acc_t *arg_pAcc);




/**
 *  \b function                                 :       HAL_WRAPPER_ErrStat_t HAL_WRAPPER_ReadGyro(HAL_WRAPPER_Gyro_t *arg_pGyro);
 *  \b Description                              :       this functions is used as a wrapper function to the function of reading gyroscope from different sensors on the board.
 *  @param  arg_pGyro [OUT]                     :       base address to store the received data from the I2C upon transfer.
 *  @note                                       :       this is a polling function halting the process execution until the I2C data is transferred.
 *  \b PRE-CONDITION                            :       make sure to call configure function the configuration file in the current directory.
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       it return one of error states indicating whether a failure or success happened (refer to @HAL_WRAPPER_ErrStat_t in "HAL_wrapper.h")
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * #include "HAL_wrapper.h"
 * 
 * 
 * int main() {
 * 
 * MCAL_Config_ErrStat_t local_errState = HAL_Config_ConfigAllHW();
 * if(HAL_Config_STAT_OK == local_errState)
 * {
 *  HAL_WRAPPER_Gyro_t *temp = {0};
 *  local_errState = HAL_WRAPPER_ReadGyro(temp);
 *  if(HAL_WRAPPER_STAT_OK == local_errState)
 *  {
 *  
 *  }
 * }
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 13/06/2024 </td><td> 1.0.0            </td><td> AMS      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
HAL_WRAPPER_ErrStat_t HAL_WRAPPER_ReadGyro(HAL_WRAPPER_Gyro_t *arg_pGyro);


/**
 *  \b function                                 :       HAL_WRAPPER_ErrStat_t HAL_WRAPPER_ReadMagnet(HAL_WRAPPER_Magnet_t *arg_pMagnet);
 *  \b Description                              :       this functions is used as a wrapper function to the function of reading magnetometer from different sensors on the board.
 *  @param  arg_pMagnet [OUT]                   :       base address to store the received data from the I2C upon transfer.
 *  @note                                       :       this is a polling function halting the process execution until the I2C data is transferred.
 *  \b PRE-CONDITION                            :       make sure to call configure function the configuration file in the current directory.
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       it return one of error states indicating whether a failure or success happened (refer to @HAL_WRAPPER_ErrStat_t in "HAL_wrapper.h")
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * #include "HAL_wrapper.h"
 * 
 * 
 * int main() {
 * 
 * MCAL_Config_ErrStat_t local_errState = HAL_Config_ConfigAllHW();
 * if(HAL_Config_STAT_OK == local_errState)
 * {
 *  HAL_WRAPPER_Magnet_t temp = {0};
 *  local_errState = HAL_WRAPPER_ReadMagnet(&temp);
 *  if(HAL_WRAPPER_STAT_OK == local_errState)
 *  {
 *    
 *  }
 * }
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 14/06/2024 </td><td> 1.0.0            </td><td> AMS      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
HAL_WRAPPER_ErrStat_t HAL_WRAPPER_ReadMagnet(HAL_WRAPPER_Magnet_t *arg_pMagnet);

/**
 *  \b function                                 :       HAL_WRAPPER_ErrStat_t HAL_WRAPPER_ReadPressure(HAL_WRAPPER_Pressure_t *arg_pMagnet);
 *  \b Description                              :       this functions is used as a wrapper function to the function of reading pressure from different sensors on the board.
 *  @param  arg_pPressure_t [OUT]               :       base address to store the received data from the I2C upon transfer.
 *  @note                                       :       this is a polling function halting the process execution until the data is transferred.
 *  \b PRE-CONDITION                            :       make sure to call configure function the configuration file in the current directory.
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       it return one of error states indicating whether a failure or success happened (refer to @HAL_WRAPPER_ErrStat_t in "HAL_wrapper.h")
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * #include "HAL_wrapper.h"
 * 
 * 
 * int main() {
 * 
 * MCAL_Config_ErrStat_t local_errState = HAL_Config_ConfigAllHW();
 * if(MCAL_Config_STAT_OK == local_errState)
 * {
 *  HAL_WRAPPER_Pressure_t temp = {0};
 *  HAL_WRAPPER_ErrStat_t local_errState = HAL_WRAPPER_ReadPressure(&temp);
 *  if(HAL_WRAPPER_STAT_OK == local_errState)
 *  {
 *    // pressure is read
 *  }
 * }
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 22/06/2024 </td><td> 1.0.0            </td><td> AMS      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
HAL_WRAPPER_ErrStat_t HAL_WRAPPER_ReadPressure(HAL_WRAPPER_Pressure_t *arg_pPressure_t);

/**
 *  \b function                                 :       HAL_WRAPPER_ErrStat_t HAL_WRAPPER_ReadTemperature(HAL_WRAPPER_Temperature_t *arg_pTemperature_t);
 *  \b Description                              :       this functions is used as a wrapper function to the function of reading Temperature from different sensors on the board.
 *  @param  arg_pTemperature_t [OUT]            :       base address to store the received temperature from the different sensor upon transfer.
 *  @note                                       :       this is a polling function halting the process execution until the data is transferred.
 *  \b PRE-CONDITION                            :       make sure to call configure function the configuration file in the current directory.
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       it return one of error states indicating whether a failure or success happened (refer to @HAL_WRAPPER_ErrStat_t in "HAL_wrapper.h")
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * #include "HAL_wrapper.h"
 * 
 * 
 * int main() {
 * 
 * MCAL_Config_ErrStat_t local_errState = HAL_Config_ConfigAllHW();
 * if(MCAL_Config_STAT_OK == local_errState)
 * {
 *  HAL_WRAPPER_Temperature_t temp = {0};
 *  HAL_WRAPPER_ErrStat_t local_errState = HAL_WRAPPER_ReadTemperature(&temp);
 *  if(HAL_WRAPPER_STAT_OK == local_errState)
 *  {
 *    // pressure is read
 *  }
 * }
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 22/06/2024 </td><td> 1.0.0            </td><td> AMS      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
HAL_WRAPPER_ErrStat_t HAL_WRAPPER_ReadTemperature(HAL_WRAPPER_Temperature_t *arg_pTemperature_t);


/**
 *  \b function                                 :       HAL_WRAPPER_ErrStat_t HAL_WRAPPER_ReadAltitude(HAL_WRAPPER_Altitude_t *arg_pAltitude_t, HAL_WRAPPER_Pressure_t *arg_pPressure_t);
 *  \b Description                              :       this functions is used as a wrapper function to the function of reading Altitude from different sensors on the board.
 *  @param  arg_pAltitude_t [OUT]               :       None.
 *  @param  arg_pPressure_t [OUT]               :       None.
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       make sure to call configure function the configuration file in the current directory.
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       it return one of error states indicating whether a failure or success happened (refer to @HAL_WRAPPER_ErrStat_t in "HAL_wrapper.h")
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * None
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 26/06/2024 </td><td> 1.0.0            </td><td> MZ      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
HAL_WRAPPER_ErrStat_t HAL_WRAPPER_ReadAltitude(HAL_WRAPPER_Altitude_t *arg_pAltitude_t, HAL_WRAPPER_Pressure_t *arg_pPressure_t);

/**
 *  \b function                                 :       HAL_WRAPPER_ErrStat_t HAL_WRAPPER_SetESCSeeds(HAL_WRAPPER_MotorSpeeds_t *arg_pMotorsSpeed);
 *  \b Description                              :       this functions is used as a wrapper function to set the speeds of ESCs motors.
 *  @param  arg_pMotorsSpeed [INT]              :       base address of new motors speeds to set, refer to @HAL_WRAPPER_MotorSpeeds_t in "HAL_wrapper.h".
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       make sure to call configure function the configuration file in the current directory.
 *  \b POST-CONDITION                           :       Motors Speeds are changed.
 *  @return                                     :       it return one of error states indicating whether a failure or success happened (refer to @HAL_WRAPPER_ErrStat_t in "HAL_wrapper.h")
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * #include "HAL_wrapper.h"
 * 
 * 
 * int main() {
 * HAL_WRAPPER_MotorSpeeds_t speeds = {
 *  .topLeftSpeed = 50,
 *  .topRightSpeed = 10,
 *  .bottomLeftSpeed = 30,
 *  .bottomRightSpeed = 40
 * };
 * MCAL_Config_ErrStat_t local_errState = HAL_Config_ConfigAllHW();
 * if(HAL_Config_STAT_OK == local_errState)
 * {
 *  HAL_WRAPPER_Magnet_t *temp = {0};
 *  local_errState = HAL_WRAPPER_SetESCSeeds(&speeds);
 *  if(HAL_WRAPPER_STAT_OK == local_errState)
 *  {
 *    // motor speeds are set
 *  }
 * }
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 15/06/2024 </td><td> 1.0.0            </td><td> AMS      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
HAL_WRAPPER_ErrStat_t HAL_WRAPPER_SetESCSpeeds(HAL_WRAPPER_MotorSpeeds_t *arg_pMotorsSpeed);

/**
 *  \b function                                 :       HAL_WRAPPER_ErrStat_t HAL_WRAPPER_GetBatteryCharge(HAL_WRAPPER_Battery_t *arg_pBatteryCharge);
 *  \b Description                              :       this functions is used as a wrapper function to set get the charge of the battery.
 *  @param  arg_pBatteryCharge [OUT]            :       base address of battery charge to insert. refer to @HAL_WRAPPER_Battery_t in "HAL_wrapper.h".
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       make sure to call configure function the configuration file in the current directory.
 *  \b POST-CONDITION                           :       Motors Speeds are changed.
 *  @return                                     :       it return one of error states indicating whether a failure or success happened (refer to @HAL_WRAPPER_ErrStat_t in "HAL_wrapper.h")
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * #include "HAL_wrapper.h"
 * 
 * 
 * int main() {
 * HAL_WRAPPER_Battery_t batteryCharge = {0};
 * MCAL_Config_ErrStat_t local_errState = HAL_Config_ConfigAllHW();
 * if(HAL_Config_STAT_OK == local_errState)
 * {
 *  local_errState = HAL_WRAPPER_GetBatteryCharge(&batteryCharge);
 *  if(HAL_WRAPPER_STAT_OK == local_errState)
 *  {
 *    // motor speeds are set
 *  }
 * }
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 27/06/2024 </td><td> 1.0.0            </td><td> AMS      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
HAL_WRAPPER_ErrStat_t HAL_WRAPPER_GetBatteryCharge(HAL_WRAPPER_Battery_t *arg_pBatteryCharge);


/**
 *  \b function                                 :       HAL_WRAPPER_ErrStat_t HAL_WRAPPER_SetAppCommRecCallBack(functionCallBack_t *arg_pUARTCallBack);
 *  \b Description                              :       this functions is used as a wrapper function to set callback function to execute when board receives anything on its uart interface with App board.
 *  @param  arg_pUARTCallBack [INT]             :       base address of function to be executed when board receives anything.
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       make sure to call configure function the configuration file in the current directory.
 *  \b POST-CONDITION                           :       Callback function is assigned to be executed whenever board receives anything.
 *  @return                                     :       it return one of error states indicating whether a failure or success happened (refer to @HAL_WRAPPER_ErrStat_t in "HAL_wrapper.h")
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * #include "HAL_wrapper.h"
 * 
 * void func(void)
 * {
 *  // callback code
 * }
 * 
 * int main() {
 *  MCAL_Config_ErrStat_t local_errState = HAL_Config_ConfigAllHW();
 *  if(HAL_Config_STAT_OK == local_errState)
 *  {
 *    local_errState = HAL_WRAPPER_SetAppCommRecCallBack(func);
 *    if(HAL_WRAPPER_STAT_OK == local_errState)
 *    {
 *    
 *    }
 *  }
 * }
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 17/06/2024 </td><td> 1.0.0            </td><td> AMS      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
HAL_WRAPPER_ErrStat_t HAL_WRAPPER_SetAppCommRecCallBack(functionCallBack_t arg_pUARTCallBack);


/**
 *  \b function                                 :       HAL_WRAPPER_ErrStat_t HAL_WRAPPER_DisableEnableAppCommRecCallBack(LIB_CONSTANTS_DriverStates_t arg_Enable_Disable_t);
 *  \b Description                              :       this functions is used as a wrapper function to set callback function to enable/disable app board byte received interrupt.
 *  @param arg_Enable_Disable_t [IN]            :       to enable or disable the interrupt, refer to @LIB_CONSTANTS_DriverStates_t in "constants.h".
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       make sure to call configure function the configuration file in the current directory.
 *  \b POST-CONDITION                           :       app board receive interrupt is enabled/disabled.
 *  @return                                     :       it return one of error states indicating whether a failure or success happened (refer to @HAL_WRAPPER_ErrStat_t in "HAL_wrapper.h")
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * #include "HAL_wrapper.h"
 * 
 * void func(void)
 * {
 *  // callback code
 * }
 * 
 * int main() {
 *  MCAL_Config_ErrStat_t local_errState = HAL_Config_ConfigAllHW();
 *  if(HAL_Config_STAT_OK == local_errState)
 *  {
 *    local_errState = HAL_WRAPPER_DisableEnableAppCommRecCallBack(LIB_CONSTANTS_ENABLED);
 *    if(HAL_WRAPPER_STAT_OK == local_errState)
 *    {
 *    
 *    }
 *  }
 * }
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 20/06/2024 </td><td> 1.0.0            </td><td> AMS      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
HAL_WRAPPER_ErrStat_t HAL_WRAPPER_DisableEnableAppCommRecCallBack(LIB_CONSTANTS_DriverStates_t arg_Enable_Disable_t);

/**
 *  \b function                                 :       HAL_WRAPPER_ErrStat_t HAL_WRAPPER_ReceiveSendAppCommMessage(HAL_WRAPPER_AppCommMsg_t* arg_AppCommMsg_t);
 *  \b Description                              :       this functions is used as a wrapper function to set receive and send messages with App board.
 *  @param  arg_AppCommMsg_t [IN][OUT]          :       base address of function to be executed when board receives anything, refer to @HAL_WRAPPER_AppCommMsg_t in "HAL_wrapper.h".
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       make sure to call configure function the configuration file in the current directory.
 *  \b POST-CONDITION                           :       a message is exchanged between the 2 boards.
 *  @return                                     :       it return one of error states indicating whether a failure or success happened (refer to @HAL_WRAPPER_ErrStat_t in "HAL_wrapper.h")
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * #include "HAL_wrapper.h"
 * 
 * void func(void)
 * {
 *  // callback code
 * }
 * 
 * int main() {
 *  MCAL_Config_ErrStat_t local_errState = HAL_Config_ConfigAllHW();
 *  if(HAL_Config_STAT_OK == local_errState)
 *  {
 *    local_errState = HAL_WRAPPER_SetAppCommRecCallBack(func);
 *    if(HAL_WRAPPER_STAT_OK == local_errState)
 *    {
 *      uint8_t dataSend[] = [3, 4];
 *      uint8_t dataRec[] = [1, 2];
 *      HAL_WRAPPER_AppCommMsg_t temp = {
 *        .dataToSend=dataSend,
 *        .dataToReceive=dataRec, 
 *        .dataToSendLen=2,
 *        .dataToReceiveLen=2,
 *        .dataIsToReceive=1
 *        .dataIsToSend=1
 *      };
 *      local_errState = HAL_WRAPPER_ReceiveSendAppCommMessage(&temp);
 *    }
 *  }
 * }
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 17/06/2024 </td><td> 1.0.0            </td><td> AMS      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
HAL_WRAPPER_ErrStat_t HAL_WRAPPER_ReceiveSendAppCommMessage(HAL_WRAPPER_AppCommMsg_t* arg_AppCommMsg_t);

/**
 *  \b function                                 :       HAL_WRAPPER_ErrStat_t HAL_WRAPPER_GetCommMessage(uint8_t* arg_pu8Msg);
 *  \b Description                              :       this functions is used as a wrapper function to get 1 byte of received message.
 *  @param  arg_pu8Msg [OUT]                    :       base address of variable to put inside it the  of message received.
 *  @note                                       :       it reads a byte from UART to know if it's a valid message header or not.
 *  \b PRE-CONDITION                            :       make sure to call configure function the configuration file in the current directory.
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       it return one of error states indicating whether a failure or success happened (refer to @HAL_WRAPPER_ErrStat_t in "HAL_wrapper.h")
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * #include "HAL_wrapper.h"
 * 
 * void func(void)
 * {
 *  // callback code
 *  uint8_t message;
 *  HAL_WRAPPER_GetCommMessage(&message);
 *  if(DATA_TYPE_INFO == message)
 *  {
 *    // a info message header is received
 *  }
 * }
 * 
 * int main() {
 *  MCAL_Config_ErrStat_t local_errState = HAL_Config_ConfigAllHW();
 *  if(HAL_Config_STAT_OK == local_errState)
 *  {
 *    local_errState = HAL_WRAPPER_SetAppCommRecCallBack(func);
 *    if(HAL_WRAPPER_STAT_OK == local_errState)
 *    {
 *    
 *    }
 *  }
 * }
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 20/06/2024 </td><td> 1.0.0            </td><td> AMS      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
HAL_WRAPPER_ErrStat_t HAL_WRAPPER_GetCommMessage(uint8_t* arg_pu8Msg);

/**
 *  \b function                                 :       HAL_WRAPPER_ErrStat_t HAL_WRAPPER_SendCommMessage(uint8_t arg_pu8Msg);
 *  \b Description                              :       this functions is used as a wrapper function to send 1 byte of message.
 *  @param  arg_pu8Msg [IN]                     :       value of data to send to the comm gateway with the other board.
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       make sure to call configure function the configuration file in the current directory.
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       it return one of error states indicating whether a failure or success happened (refer to @HAL_WRAPPER_ErrStat_t in "HAL_wrapper.h")
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * #include "HAL_wrapper.h"
 * 
 * void func(void)
 * {
 *  // callback code
 *  uint8_t message = 22;
 *  HAL_WRAPPER_ErrStat_t local_errState = HAL_WRAPPER_SendCommMessage(message);
 *  if(HAL_WRAPPER_STAT_OK == local_errState)
 *  {
 *    // message is send
 *  }
 * }
 * 
 * int main() {
 *  MCAL_Config_ErrStat_t local_errState = HAL_Config_ConfigAllHW();
 *  if(HAL_Config_STAT_OK == local_errState)
 *  {
 *    local_errState = HAL_WRAPPER_SetAppCommRecCallBack(func);
 *    if(HAL_WRAPPER_STAT_OK == local_errState)
 *    {
 *    
 *    }
 *  }
 * }
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 20/06/2024 </td><td> 1.0.0            </td><td> AMS      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
HAL_WRAPPER_ErrStat_t HAL_WRAPPER_SendCommMessage(uint8_t arg_pu8Msg);

/*** End of File **************************************************************/
#endif /*HAL_WRAPPER_HEADER_H_*/
