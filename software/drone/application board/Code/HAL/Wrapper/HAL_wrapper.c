/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   wrapper file for the HAL layer functions                                                                    |
 * |    @file           :   HAL_wrapper.c                                                                                               |
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


/******************************************************************************
 * Module Preprocessor Constants
 *******************************************************************************/

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

/******************************************************************************
 * Function Definitions
 *******************************************************************************/

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
    // check if there anything to receive
    if(arg_AppCommMsg_t->dataIsToReceive)
    {
        MCAL_WRAPPER_ReceiveDataThroughUART4(arg_AppCommMsg_t->dataToReceive, arg_AppCommMsg_t->dataToReceiveLen);
        arg_AppCommMsg_t->dataIsToReceive = 0;
    }

    // check if there is anything to send
    if(arg_AppCommMsg_t->dataIsToSend)
    {
        MCAL_WRAPPER_SendDataThroughUART4(arg_AppCommMsg_t->dataToSend, arg_AppCommMsg_t->dataToSendLen);
        arg_AppCommMsg_t->dataIsToSend = 0;
    }

    return HAL_WRAPPER_STAT_OK;
}

/*************** END OF FUNCTIONS ***************************************************************************/
