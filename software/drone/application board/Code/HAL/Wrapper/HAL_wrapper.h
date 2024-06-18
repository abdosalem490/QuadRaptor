/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   wrapper file for the HAL layer functions                                                                    |
 * |    @file           :   HAL_wrapper.h                                                                                               |
 * |    @author         :   Abdelrahman Mohamed Salem                                                                                   |
 * |    @origin_date    :   18/06/2024                                                                                                  |
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
 * |    18/06/2023      1.0.0           Abdelrahman Mohamed Salem       file Created.                                                   |
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
} HAL_WRAPPER_ErrStat_t;

/**
 * @brief: contains definitions to be used with communication with app board
 */
typedef struct
{
  uint8_t* dataToSend;        /**< base address of data to send through app comm port */
  uint8_t* dataToReceive;     /**< base address of data to receive through app comm port */
  uint16_t dataToSendLen;     /**< length of data to send through app comm port */
  uint16_t dataToReceiveLen;  /**< length of data to receive through app comm port */
  uint8_t  dataIsToReceive;   /**< boolean flag to indicate whether a data is to be received or not */
  uint8_t  dataIsToSend;      /**< boolean flag to indicate whether a data is to be sent or not */
} HAL_WRAPPER_AppCommMsg_t;

/******************************************************************************
 * Variables
 *******************************************************************************/

/******************************************************************************
 * Function Prototypes
 *******************************************************************************/

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
 *  MCAL_Config_ErrStat_t local_errState = HAL_Config_ConfigAllPins();
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
 * <tr><td> 18/06/2024 </td><td> 1.0.0            </td><td> AMS      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
HAL_WRAPPER_ErrStat_t HAL_WRAPPER_SetAppCommRecCallBack(functionCallBack_t arg_pUARTCallBack);


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
 *  MCAL_Config_ErrStat_t local_errState = HAL_Config_ConfigAllPins();
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
 * <tr><td> 18/06/2024 </td><td> 1.0.0            </td><td> AMS      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
HAL_WRAPPER_ErrStat_t HAL_WRAPPER_ReceiveSendAppCommMessage(HAL_WRAPPER_AppCommMsg_t* arg_AppCommMsg_t);

/*** End of File **************************************************************/
#endif /*HAL_WRAPPER_HEADER_H_*/
