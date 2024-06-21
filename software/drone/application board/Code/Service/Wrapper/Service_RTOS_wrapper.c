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
 * |    21/05/2023      1.0.0           Abdelrahman Mohamed Salem       added the function 'SERVICE_RTOS_StartSchedular'.               |
 * |    22/05/2023      1.0.0           Abdelrahman Mohamed Salem       added the function 'SERVICE_RTOS_CreateBlockingQueue'.          |
 * |    22/05/2023      1.0.0           Abdelrahman Mohamed Salem       added the function 'SERVICE_RTOS_AppendToBlockingQueue'.        |
 * |    14/06/2023      1.0.0           Abdelrahman Mohamed Salem       added the function 'SERVICE_RTOS_ReadFromBlockingQueue'.        |
 * |    18/06/2023      1.0.0           Abdelrahman Mohamed Salem       added support for getting remaining messages in queue in the.   |
 * |                                                                    function 'SERVICE_RTOS_ReadFromBlockingQueue'.                  |
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

/**
 * @reason: contains functions related to RTOS tasks
*/
#include "task.h"

/**
 * @reason: contains functions related to RTOS queues
*/
#include "queue.h"

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

    if(NULL == arg_pFuncTaskFunction || NULL == arg_pu8TaskName  || 0 == arg_u16TaskStackDepth)
    {
        local_ErrStatus = SERVICE_RTOS_STAT_INVALID_PARAMS;
    }
    else{
        // create the task
        xTaskCreate((TaskFunction_t)arg_pFuncTaskFunction,
                (const char *)arg_pu8TaskName,
                (uint16_t)arg_u16TaskStackDepth,
                (void *)NULL,
                (UBaseType_t)arg_u32TaskPriority,
                (TaskHandle_t *)arg_pTaskHandle);
    }

    return local_ErrStatus;
}


/**
 * 
*/
SERVICE_RTOS_ErrStat_t SERVICE_RTOS_StartSchedular(void)
{
    vTaskStartScheduler();

    return SERVICE_RTOS_STAT_OK;
}

/**
 * 
*/
SERVICE_RTOS_ErrStat_t SERVICE_RTOS_CreateBlockingQueue(uint16_t arg_u16QueueLen, uint16_t arg_u16ElementSize, RTOS_QueueHandle_t* arg_pQueueHandle)
{
    SERVICE_RTOS_ErrStat_t local_ErrStatus = SERVICE_RTOS_STAT_OK;

    if(0 == arg_u16QueueLen|| 0 == arg_u16ElementSize  || NULL == arg_pQueueHandle) 
    {
        local_ErrStatus = SERVICE_RTOS_STAT_INVALID_PARAMS;
    }
    else
    {
        *arg_pQueueHandle = xQueueCreate((UBaseType_t)arg_u16QueueLen, (UBaseType_t) arg_u16ElementSize);

        if(NULL == arg_pQueueHandle)
        {
            local_ErrStatus = SERVICE_RTOS_STAT_INVALID_PARAMS;
        }
        else
        {
            // do nothing
        }
    }

    return local_ErrStatus;
}
 
/**
 * 
*/
SERVICE_RTOS_ErrStat_t SERVICE_RTOS_AppendToBlockingQueue(uint32_t arg_u32TimeoutMS, const void * arg_pItemToAdd, RTOS_QueueHandle_t arg_QueueHandle)
{
    SERVICE_RTOS_ErrStat_t local_ErrStatus = SERVICE_RTOS_STAT_OK;

    if(NULL == arg_pItemToAdd || NULL == arg_QueueHandle)
    {
        local_ErrStatus = SERVICE_RTOS_STAT_INVALID_PARAMS;
    }
    else
    {
        if(xQueueSendToBack((QueueHandle_t)arg_QueueHandle, (const void *)arg_pItemToAdd, (TickType_t)(arg_u32TimeoutMS / portTICK_PERIOD_MS)) != pdPASS)
        {
            local_ErrStatus = SERVICE_RTOS_STAT_QUEUE_FULL;
        }
    }

    return local_ErrStatus;
}

/**
 * 
*/
SERVICE_RTOS_ErrStat_t SERVICE_RTOS_ReadFromBlockingQueue(uint32_t arg_u32TimeoutMS, void * arg_pItemToReceive, RTOS_QueueHandle_t arg_QueueHandle, uint8_t* lenOfRemainingItems)
{
    SERVICE_RTOS_ErrStat_t local_ErrStatus = SERVICE_RTOS_STAT_OK;

    if(NULL == arg_pItemToReceive || NULL == arg_QueueHandle)
    {
        local_ErrStatus = SERVICE_RTOS_STAT_INVALID_PARAMS;
    }
    else
    {
        if(xQueueReceive((QueueHandle_t)arg_QueueHandle, (void * const)arg_pItemToReceive, (TickType_t)(arg_u32TimeoutMS / portTICK_PERIOD_MS)) != pdPASS)
        {
            local_ErrStatus = SERVICE_RTOS_STAT_QUEUE_EMPTY;
        }
        else
        {
            *lenOfRemainingItems = uxQueueMessagesWaiting((QueueHandle_t)arg_QueueHandle) + 1;
        }
    }

    return local_ErrStatus;  
}

/**
 * 
 */
SERVICE_RTOS_ErrStat_t SERVICE_RTOS_BlockFor(uint32_t arg_u32TimeMS)
{
    SERVICE_RTOS_ErrStat_t local_ErrStatus = SERVICE_RTOS_STAT_OK;

    vTaskDelay((TickType_t)(arg_u32TimeMS / portTICK_PERIOD_MS));
   
    return local_ErrStatus;
}


/**
 * 
 */
SERVICE_RTOS_ErrStat_t SERVICE_RTOS_WaitForNotification(uint32_t arg_u32TimeoutMS)
{
    SERVICE_RTOS_ErrStat_t local_ErrStatus = SERVICE_RTOS_STAT_OK;

    ulTaskNotifyTake(pdFALSE, pdMS_TO_TICKS(arg_u32TimeoutMS));

    return local_ErrStatus;
}

/**
 * 
 */
SERVICE_RTOS_ErrStat_t SERVICE_RTOS_Notify(RTOS_TaskHandle_t arg_TaskToNotify_t, uint8_t arg_u8IsFromISR)
{
    SERVICE_RTOS_ErrStat_t local_ErrStatus = SERVICE_RTOS_STAT_OK;

    if(NULL == arg_TaskToNotify_t)
    {
        local_ErrStatus = SERVICE_RTOS_STAT_INVALID_PARAMS;
    }
    else 
    {
        if(LIB_CONSTANTS_DISABLED == arg_u8IsFromISR)
        {
            xTaskNotifyGive(arg_TaskToNotify_t);
        } 
        else if(LIB_CONSTANTS_ENABLED == arg_u8IsFromISR)
        {
            vTaskNotifyGiveFromISR(arg_TaskToNotify_t, NULL);
        }
        else
        {
            //
        }
    }

    return local_ErrStatus;

}


/*************** END OF FUNCTIONS ***************************************************************************/
 
// to be the IdleTask (called when no other tasks are running)
// void vApplicationIdleHook( void );
