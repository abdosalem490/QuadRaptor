/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   Wrapper File for RTOS function                                                                              |
 * |    @file           :   Service_RTOS_wrapper.h                                                                                      |
 * |    @author         :   Abdelrahman Mohamed Salem                                                                                   |
 * |    @origin_date    :   18/05/2024                                                                                                  |
 * |    @version        :   1.0.0                                                                                                       |
 * |    @tool_chain     :   RISC-V Cross GCC                                                                                            |
 * |    @compiler       :   GCC                                                                                                         |
 * |    @C_standard     :   ISO C99 (-std=c99)                                                                                          |
 * |    @target         :   CH32V203C8T6                                                                                                |
 * |    @notes          :   None                                                                                                        |
 * |    @license        :   MIT License                                                                                                 |
 * |    @brief          :   this header file contains useful functions to easily change RTOS without changing much in code              |
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
 * |    18/05/2023      1.0.0           Abdelrahman Mohamed Salem       Interface Created.                                              |
 * --------------------------------------------------------------------------------------------------------------------------------------
 */
 

/******************************************************************************
 * Includes
 *******************************************************************************/
/**
 * @reason: contains standard definitions for standard integers
 */
#include "stdint.h"

/**
 * @reason: contains definition for NULL
 */
#include "common.h"

/**
 * @reason: contains constants common values
 */
#include "constants.h"

/**
 * @reason: contains useful functions that deals with bit level math
 */
#include "math_btt.h"


/**
 * @reason: contains definition for our functions
*/
#include "Service_RTOS_wrapper.h"


/**
 * @reason: contains functions of our RTOS
 */
#include "FreeRTOS.h"
#include "task.h"

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
SERVICE_RTOS_ErrStat_t SERVICE_RTOS_TaskCreate(SERVICE_RTOS_TaskFunction_t arg_pFuncTaskFunction, const char * const arg_pu8TaskName, uint16_t arg_u16TaskStackDepth, uint32_t arg_u32TaskPriority, RTOS_TaskHandle_t* arg_pTaskHandle)
{
    SERVICE_RTOS_ErrStat_t local_ErrStatus = SERVICE_RTOS_STAT_OK;

    if(arg_pFuncTaskFunction == NULL || arg_pu8TaskName == NULL || arg_u16TaskStackDepth == 0 || arg_pTaskHandle == NULL)
    {
        local_ErrStatus = SERVICE_RTOS_STAT_INVALID_PARAMS;
    }

    // create the task
    xTaskCreate((TaskFunction_t)arg_pFuncTaskFunction,
            (const char *)arg_pu8TaskName,
            (uint16_t)arg_u16TaskStackDepth,
            (void *)NULL,
            (UBaseType_t)arg_u32TaskPriority,
            (TaskHandle_t *)&arg_pTaskHandle);


    return local_ErrStatus;
}





/*************** END OF FUNCTIONS ***************************************************************************/


// to be the IdleTask (called when no other tasks are running)
// void vApplicationIdleHook( void );