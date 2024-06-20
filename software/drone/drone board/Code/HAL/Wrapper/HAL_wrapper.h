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
 * @brief: contains defintions to be used to set motor speeds associated with ESCs
 */
typedef struct 
{
  uint8_t topLeftSpeed; /**< speed of top left motor in range 0 to 100 */
  uint8_t topRightSpeed; /**< speed of top Right motor in range 0 to 100 */
  uint8_t bottomLeftSpeed; /**< speed of bottom left motor in range 0 to 100 */
  uint8_t bottomRightSpeed; /**< speed of bottom right motor in range 0 to 100 */
} HAL_WRAPPER_MotorSpeeds_t;



/******************************************************************************
 * Variables
 *******************************************************************************/

/******************************************************************************
 * Function Prototypes
 *******************************************************************************/

/**
 *  \b function                                 :       HAL_WRAPPER_ErrStat_t HAL_WRAPEPR_ReadAcc(HAL_WRAPPER_Acc_t *arg_pAcc);
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
 * MCAL_Config_ErrStat_t local_errState = HAL_Config_ConfigAllPins();
 * if(HAL_Config_STAT_OK == local_errState)
 * {
 *  HAL_WRAPPER_Acc_t *temp = {0};
 *  local_errState = HAL_WRAPEPR_ReadAcc(temp);
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
HAL_WRAPPER_ErrStat_t HAL_WRAPEPR_ReadAcc(HAL_WRAPPER_Acc_t *arg_pAcc);




/**
 *  \b function                                 :       HAL_WRAPPER_ErrStat_t HAL_WRAPEPR_ReadGyro(HAL_WRAPPER_Gyro_t *arg_pGyro);
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
 * MCAL_Config_ErrStat_t local_errState = HAL_Config_ConfigAllPins();
 * if(HAL_Config_STAT_OK == local_errState)
 * {
 *  HAL_WRAPPER_Gyro_t *temp = {0};
 *  local_errState = HAL_WRAPEPR_ReadGyro(temp);
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
HAL_WRAPPER_ErrStat_t HAL_WRAPEPR_ReadGyro(HAL_WRAPPER_Gyro_t *arg_pGyro);


/**
 *  \b function                                 :       HAL_WRAPPER_ErrStat_t HAL_WRAPEPR_ReadMagnet(HAL_WRAPPER_Magnet_t *arg_pMagnet);
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
 * MCAL_Config_ErrStat_t local_errState = HAL_Config_ConfigAllPins();
 * if(HAL_Config_STAT_OK == local_errState)
 * {
 *  HAL_WRAPPER_Magnet_t *temp = {0};
 *  local_errState = HAL_WRAPEPR_ReadMagnet(temp);
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
HAL_WRAPPER_ErrStat_t HAL_WRAPEPR_ReadMagnet(HAL_WRAPPER_Magnet_t *arg_pMagnet);


/**
 *  \b function                                 :       HAL_WRAPPER_ErrStat_t HAL_WRAPEPR_SetESCSeeds(HAL_WRAPPER_MotorSpeeds_t *arg_pMotorsSpeed);
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
 * MCAL_Config_ErrStat_t local_errState = HAL_Config_ConfigAllPins();
 * if(HAL_Config_STAT_OK == local_errState)
 * {
 *  HAL_WRAPPER_Magnet_t *temp = {0};
 *  local_errState = HAL_WRAPEPR_SetESCSeeds(&speeds);
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
HAL_WRAPPER_ErrStat_t HAL_WRAPEPR_SetESCSeeds(HAL_WRAPPER_MotorSpeeds_t *arg_pMotorsSpeed);

/*** End of File **************************************************************/
#endif /*HAL_WRAPPER_HEADER_H_*/