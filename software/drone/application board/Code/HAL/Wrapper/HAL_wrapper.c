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


/**
 * @reason: contains NRF interface functions
 */
#include "nrf.h"

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
HAL_WRAPPER_ErrStat_t HAL_WRAPPER_DisableEnableAppCommRecCallBack(LIB_CONSTANTS_DriverStates_t arg_Enable_Disable_t)
{
    // configure interrupt
    MCAL_WRAPPER_UART4RecITConfig(arg_Enable_Disable_t);

    return HAL_WRAPPER_STAT_OK;
}


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
    // temp variables to allow synchronous send and receive at the same time
    uint16_t local_u16LenOfDataToSend = 0;
    uint16_t local_u16LenOfDataToReceive = 0;

    // to detect if there is anything in the receiver buffer (as by writing to UART data register clears the RXNE flag)
    MCAL_WRAPPER_ErrStat_t local_writeSuccess_t = MCAL_WRAPPER_STAT_OK;

    // loop until we send or received all messages
    while (arg_AppCommMsg_t->dataIsToSend || arg_AppCommMsg_t->dataIsToReceive)
    {
        // check if to send
        if(arg_AppCommMsg_t->dataIsToSend)
        {
            // send 1 byte
            local_writeSuccess_t = MCAL_WRAPPER_SendDataThroughUART4(arg_AppCommMsg_t->dataToSend + local_u16LenOfDataToSend, 1);
            
            if(MCAL_WRAPPER_STAT_OK == local_writeSuccess_t)
            {
                local_u16LenOfDataToSend++;
                
                // check if sending is done
                if(local_u16LenOfDataToSend == arg_AppCommMsg_t->dataToSendLen)
                {
                    
                    arg_AppCommMsg_t->dataIsToSend = 0;
                }  
            }
        }

        // check if to receive
        if(arg_AppCommMsg_t->dataIsToReceive)
        {
            // receive 1 byte
            MCAL_WRAPPER_ReceiveDataThroughUART4(arg_AppCommMsg_t->dataToReceive + local_u16LenOfDataToReceive, 1);
            local_u16LenOfDataToReceive++;

            // check if receiving is done
            if(local_u16LenOfDataToReceive == arg_AppCommMsg_t->dataToReceiveLen)
            {
                arg_AppCommMsg_t->dataIsToReceive = 0;

               // enable receuve interrupt
                HAL_WRAPPER_DisableEnableAppCommRecCallBack(LIB_CONSTANTS_ENABLED);
            }
        }
    }
    

    return HAL_WRAPPER_STAT_OK;
}

/**
 * 
 */
HAL_WRAPPER_ErrStat_t HAL_WRAPPER_GetCommMessage(uint8_t* arg_pu8Msg)
{
    // receive 1 byte
    MCAL_WRAPPER_ErrStat_t local_errState_t = MCAL_WRAPPER_ReceiveDataThroughUART4(arg_pu8Msg, 1);
    
    if(MCAL_WRAPPER_STAT_OK != local_errState_t)
    {
        local_errState_t = HAL_WRAPPER_STAT_DRONE_DIDNT_SND;
    }
    else
    {
        local_errState_t = HAL_WRAPPER_STAT_OK;
    }

    return local_errState_t;
}

/**
 * 
 */
HAL_WRAPPER_ErrStat_t HAL_WRAPPER_SendCommMessage(uint8_t arg_pu8Msg)
{
    MCAL_WRAPPER_ErrStat_t local_errState_t = MCAL_WRAPPER_SendDataThroughUART4(&arg_pu8Msg, 1);
    if(MCAL_WRAPPER_STAT_OK != local_errState_t)
    {
        local_errState_t = HAL_WRAPPER_STAT_DRONE_BOARD_BSY;
    }
    else
    {
        local_errState_t = HAL_WRAPPER_STAT_OK;
    }

    return local_errState_t;
}

/**
 * 
 */
HAL_WRAPPER_ErrStat_t HAL_WRAPPER_RCSend(HAL_WRAPPER_RCMsg_t* arg_pMsg_t)
{
    HAL_WRAPPER_ErrStat_t local_errState_t = HAL_WRAPPER_STAT_OK;
    NRF_write((void*)&arg_pMsg_t->MsgToSend, sizeof(arg_pMsg_t->MsgToSend));
    return local_errState_t; 
}

/**
 * 
 */
HAL_WRAPPER_ErrStat_t HAL_WRAPPER_RCReceive(HAL_WRAPPER_RCMsg_t* arg_pMsg_t)
{
    HAL_WRAPPER_ErrStat_t local_errState_t = HAL_WRAPPER_STAT_OK;

    NRF_start_listening();
    if (NRF_data_available()) 
    {
        NRF_read((void*)&arg_pMsg_t->MsgToReceive, sizeof(arg_pMsg_t->MsgToReceive));
    }
    else
    {
        local_errState_t = HAL_WRAPPER_STAT_RC_DIDNT_SND;
    }
    NRF_stop_listening();
    
    return local_errState_t;
}

/*************** END OF FUNCTIONS ***************************************************************************/
