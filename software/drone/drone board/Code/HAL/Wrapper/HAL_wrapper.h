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
  uint16_t x; /**< acceleration in x-direction */
  uint16_t y; /**< acceleration in y-direction */
  uint16_t z; /**< acceleration in z-direction */
} HAL_WRAPPER_Acc_t;



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
 *  @return                                     :       it return one of error states indicating whether a failure or success happened (refer to @HAL_WRAPPER_Acc_t in "HAL_wrapper.h")
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

/*** End of File **************************************************************/
#endif /*HAL_WRAPPER_HEADER_H_*/