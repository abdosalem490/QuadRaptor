/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   configuration file for the external hardware                                                                |
 * |    @file           :   HAL_config.h                                                                                                |
 * |    @author         :   Abdelrahman Mohamed Salem                                                                                   |
 * |    @origin_date    :   24/05/2024                                                                                                  |
 * |    @version        :   1.0.0                                                                                                       |
 * |    @tool_chain     :   RISC-V Cross GCC                                                                                            |
 * |    @compiler       :   GCC                                                                                                         |
 * |    @C_standard     :   ISO C99 (-std=c99)                                                                                          |
 * |    @target         :   CH32V203C8T6                                                                                                |
 * |    @notes          :   None                                                                                                        |
 * |    @license        :   MIT License                                                                                                 |
 * |    @brief          :   this file configure all the HAL layer hardware                                                              |
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
 * |    24/05/2023      1.0.0           Abdelrahman Mohamed Salem       file Created.                                                   |
 * |    24/05/2023      1.0.0           Abdelrahman Mohamed Salem       added the function 'HAL_Config_ConfigAllHW'.                    |
 * --------------------------------------------------------------------------------------------------------------------------------------
 */


#ifndef HAL_CONFIG_HEADER_H_
#define HAL_CONFIG_HEADER_H_

/******************************************************************************
 * Includes
 *******************************************************************************/

/**
 * @reason: contains ADXL345 typedefs
 */
#include "ADXL345_config.h"

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
  HAL_Config_STAT_OK,
  HAL_Config_STAT_INVALID_PARAMS,
} HAL_Config_ErrStat_t;

/******************************************************************************
 * Variables
 *******************************************************************************/

// TODO: define pins configurations as a table here to be read by configuration function to configure all pins (HAL Module task)


/**
 * @brief: a variable to be used by the main application to interface with ADXL345
 */
extern HAL_ADXL345_config_t global_adxl345Config_t;

/******************************************************************************
 * Function Prototypes
 *******************************************************************************/

/**
 *  \b function                                 :       HAL_Config_ErrStat_t HAL_Config_ConfigAllHW(void);
 *  \b Description                              :       this functions is used to configure all the external hardware of the MCU given the application.
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       make sure to call configure the peripherals of the HAL beforehand.
 *  \b POST-CONDITION                           :       all external hardware to the MCU are configured.
 *  @return                                     :       it return one of error states indicating whether a failure or success happened (refer to @HAL_Config_ErrStat_t in "HAL_config.h")
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * #include "HAL_config.h"
 * 
 * int main() {
 * HAL_Config_ErrStat_t local_TaskCreateState_t = HAL_Config_ConfigAllHW();
 * if(SERVICE_RTOS_STAT_OK == local_TaskCreateState_t)
 * {
 *  // the pins are configured successfully
 * }
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 24/05/2024 </td><td> 1.0.0            </td><td> AMS      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
HAL_Config_ErrStat_t HAL_Config_ConfigAllHW(void);

/*** End of File **************************************************************/
#endif /*HAL_CONFIG_HEADER_H_*/
