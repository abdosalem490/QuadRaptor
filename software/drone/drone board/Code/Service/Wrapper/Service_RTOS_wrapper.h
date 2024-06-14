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
 * --------------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef SERVICE_RTOS_WRAPPER_H_
#define SERVICE_RTOS_WRAPPER_H_

/******************************************************************************
 * Includes
 *******************************************************************************/

/**
 * @reason: contains functions of our RTOS
 */
#include "FreeRTOS.h"

/**
 * @reason: contains defintions for standard integer defintions
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
 * @brief: the handle for the task through which we can deal with the RTOS
*/
typedef struct tskTaskControlBlock * RTOS_TaskHandle_t;

/**
 * @brief: the handle for the queue through which we can deal with RTOS queues
*/
typedef struct QueueDefinition * RTOS_QueueHandle_t;

/**
 * @brief: the type of function that will represent the task
*/
typedef void (* SERVICE_RTOS_TaskFunction_t)( void * );

/**
 * @brief: contains error states for this module
*/
typedef enum {
  SERVICE_RTOS_STAT_OK,
  SERVICE_RTOS_STAT_INVALID_PARAMS,
  SERVICE_RTOS_STAT_QUEUE_FULL,
  SERVICE_RTOS_STAT_QUEUE_EMPTY,
} SERVICE_RTOS_ErrStat_t;

/******************************************************************************
 * Variables
 *******************************************************************************/

/******************************************************************************
 * Function Prototypes
 *******************************************************************************/

/**
 *  \b function                                 :       SERVICE_RTOS_TaskCreate(SERVICE_RTOS_TaskFunction_t arg_pFuncTaskFunction, const char * const arg_pu8TaskName, uint16_t arg_u16TaskStackDepth, uint32_t arg_u32TaskPriority, RTOS_TaskHandle_t* arg_pTaskHandle)
 *  \b Description                              :       this functions is used as a wrapper function to the creation of tasks according to the RTOS used.
 *  @param  arg_pFuncTaskFunction [IN]          :       pointer to the function that will represent our task to be executed
 *  @param  arg_pu8TaskName [IN]                :       Name given to the task.
 *  @param  arg_u16TaskStackDepth [IN]          :       the stack size given to this task in words.
 *  @param  arg_u32TaskPriority [IN]            :       the priority of this task (higher is more important).
 *  @param  arg_pTaskHandle [OUT]               :       a handle to the task that will act as identifier to the task so that we can deal with the task.
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       make sure to call configure the configuration file in the current directory.
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       it return one of error states indicating whether a failure or success happened (refer to @SERVICE_RTOS_ErrStat_t in "Service_RTOS_wrapper.h")
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * #include "Service_RTOS_wrapper.h"
 * 
 * RTOS_TaskHandle_t Task1Task_Handler;
 * 
 * void task2_task(void *pvParameters)
 * {
 *   while (1)
 *   {
 *       printf("task2 entry\r\n");
 *       GPIO_ResetBits(GPIOA, GPIO_Pin_1);
 *       vTaskDelay(500);
 *       GPIO_SetBits(GPIOA, GPIO_Pin_1);
 *       vTaskDelay(500);
 *   }
 * }
 * 
 * int main() {
 * SERVICE_RTOS_ErrStat_t local_TaskCreateState_t = SERVICE_RTOS_TaskCreate((SERVICE_RTOS_TaskFunction_t)task2_task, "task", 256, 3, &Task1Task_Handler);
 * if(SERVICE_RTOS_STAT_OK == local_TaskCreateState_t)
 * {
 *  // do what you want to do
 * }
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 19/05/2024 </td><td> 1.0.0            </td><td> AMS      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
SERVICE_RTOS_ErrStat_t SERVICE_RTOS_TaskCreate(SERVICE_RTOS_TaskFunction_t arg_pFuncTaskFunction, const char * const arg_pu8TaskName, uint16_t arg_u16TaskStackDepth, uint32_t arg_u32TaskPriority, RTOS_TaskHandle_t* arg_pTaskHandle);


/**
 *  \b function                                 :       SERVICE_RTOS_ErrStat_t SERVICE_RTOS_StartSchedular(void);
 *  \b Description                              :       this functions is used as a wrapper function to start the schedular according to the RTOS used.
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       make sure to have created all needed tasks before starting the schedular.
 *  \b POST-CONDITION                           :       RTOS tasks will be up and running.
 *  @return                                     :       it return one of error states indicating whether a failure or success happened (refer to @SERVICE_RTOS_ErrStat_t in "Service_RTOS_wrapper.h")
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * #include "Service_RTOS_wrapper.h"
 * 
 * RTOS_TaskHandle_t Task1Task_Handler;
 * 
 * void task2_task(void *pvParameters)
 * {
 *   while (1)
 *   {
 *       printf("task2 entry\r\n");
 *       GPIO_ResetBits(GPIOA, GPIO_Pin_1);
 *       vTaskDelay(500);
 *       GPIO_SetBits(GPIOA, GPIO_Pin_1);
 *       vTaskDelay(500);
 *   }
 * }
 * 
 * int main() {
 * SERVICE_RTOS_ErrStat_t local_TaskCreateState_t = SERVICE_RTOS_TaskCreate((SERVICE_RTOS_TaskFunction_t)task2_task, "task", 256, 3, &Task1Task_Handler);
 * if(SERVICE_RTOS_STAT_OK == local_TaskCreateState_t)
 * {
 *  if(SERVICE_RTOS_STAT_OK ==  SERVICE_RTOS_StartSchedular())
 *  {
 *    // do what you want here
 *  }
 * }
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 21/05/2024 </td><td> 1.0.0            </td><td> AMS      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
SERVICE_RTOS_ErrStat_t SERVICE_RTOS_StartSchedular(void);


/**
 *  \b function                                 :       SERVICE_RTOS_ErrStat_t SERVICE_RTOS_CreateQueue(uint16_t arg_u16QueueLen, uint16_t arg_u16ElementSize, RTOS_QueueHandle_t* arg_pQueueHandle);
 *  \b Description                              :       this functions is used as a wrapper function to create a blocked Queue for interprocess communication.
 *  @param  arg_u16QueueLen [IN]                :       maximum length of the Queue at any time.
 *  @param  arg_u16ElementSize [IN]             :       the size of each element of the Queue.
 *  @param  arg_pQueueHandle [OUT]              :       a handle to the Queue that will act as identifier to the Queue so that we can deal with the Queue.
 *  @note                                       :       Any reading to this Queue while the queue is empty will make the task in blocked state and any write to the queue while the queue is full will make the task in blocked task.
 *  \b PRE-CONDITION                            :       None.
 *  \b POST-CONDITION                           :       a blocking Queue is created.
 *  @return                                     :       it return one of error states indicating whether a failure or success happened (refer to @SERVICE_RTOS_ErrStat_t in "Service_RTOS_wrapper.h")
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * #include "Service_RTOS_wrapper.h"
 * 
 * RTOS_QueueHandle_t Queue1_Handler;
 * 
 * struct Message 
 * {
 *  char ucMessageID;
 *  char ucData[ 20 ];
 * };
 * 
 * int main() {
 * SERVICE_RTOS_ErrStat_t local_TaskCreateState_t = SERVICE_RTOS_CreateBlockingQueue(10, sizeof(struct Message), &Queue1_Handler);
 * if(SERVICE_RTOS_STAT_OK == local_TaskCreateState_t)
 * {
 *  // do what you want here
 * }
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 22/05/2024 </td><td> 1.0.0            </td><td> AMS      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
SERVICE_RTOS_ErrStat_t SERVICE_RTOS_CreateBlockingQueue(uint16_t arg_u16QueueLen, uint16_t arg_u16ElementSize, RTOS_QueueHandle_t* arg_pQueueHandle);


/**
 *  \b function                                 :       SERVICE_RTOS_ErrStat_t SERVICE_RTOS_AppendToBlockingQueue(uint32_t arg_u32TimeoutMS, const void * arg_pItemToAdd, RTOS_QueueHandle_t arg_QueueHandle);
 *  \b Description                              :       this functions is used as a wrapper function to add item to a blocking Queue for interprocess communication.
 *  @param  arg_u32TimeoutMS [IN]               :       The maximum amount of time in Millisecond the task should block waiting for space to become available on the queue, should it already be full. The call will return immediately if this is set to 0.
 *  @param  arg_pItemToAdd [IN]                 :       A pointer to the item that is to be placed on the queue..
 *  @param  arg_QueueHandle [IN]                :       The handle to the queue on which the item is to be posted.
 *  @note                                       :       Any reading to this Queue while the queue is empty will make the task in blocked state and any write to the queue while the queue is full will make the task in blocked task.
 *  \b PRE-CONDITION                            :       a Queue must be created beforehand.
 *  \b POST-CONDITION                           :       a blocking Queue is created.
 *  @return                                     :       it return one of error states indicating whether a failure or success happened (refer to @SERVICE_RTOS_ErrStat_t in "Service_RTOS_wrapper.h")
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * #include "Service_RTOS_wrapper.h"
 * 
 * RTOS_QueueHandle_t Queue1_Handler;
 * 
 * typedef struct Message 
 * {
 *  char ucMessageID;
 *  char ucData[ 20 ];
 * }Message_t;
 * 
 * int main() {
 * Message_t message = {0};
 * SERVICE_RTOS_ErrStat_t local_TaskCreateState_t = SERVICE_RTOS_CreateBlockingQueue(10, sizeof(Message_t), &Queue1_Handler);
 * if(SERVICE_RTOS_STAT_OK == local_TaskCreateState_t)
 * {  
 *    if(SERVICE_RTOS_AppendToBlockingQueue(100, (const void*)&message, Queue1_Handler) == SERVICE_RTOS_STAT_OK)
 *    {
 *      // do what you want here
 *    }
 * }
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 22/05/2024 </td><td> 1.0.0            </td><td> AMS      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
SERVICE_RTOS_ErrStat_t SERVICE_RTOS_AppendToBlockingQueue(uint32_t arg_u32TimeoutMS, const void * arg_pItemToAdd, RTOS_QueueHandle_t arg_QueueHandle);

/**
 *  \b function                                 :       SERVICE_RTOS_ErrStat_t SERVICE_RTOS_ReadFromBlockingQueue(uint32_t arg_u32TimeoutMS, const void * arg_pItemToReceive, RTOS_QueueHandle_t arg_QueueHandle);
 *  \b Description                              :       this functions is used as a wrapper function to receive item from a blocking Queue for interprocess communication.
 *  @param  arg_u32TimeoutMS [IN]               :       The maximum amount of time in Millisecond the task should block waiting for space to become available on the queue, should it already be empty. The call will return immediately if this is set to 0.
 *  @param  arg_pItemToReceive [IN]             :       A pointer to the item that is to be received from the queue.
 *  @param  arg_QueueHandle [IN]                :       The handle to the queue on which the item is to be posted.
 *  @note                                       :       Any reading to this Queue while the queue is empty will make the task in blocked state and any write to the queue while the queue is full will make the task in blocked task.
 *  \b PRE-CONDITION                            :       a Queue must be created beforehand.
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       it return one of error states indicating whether a failure or success happened (refer to @SERVICE_RTOS_ErrStat_t in "Service_RTOS_wrapper.h")
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * #include "Service_RTOS_wrapper.h"
 * 
 * RTOS_QueueHandle_t Queue1_Handler;
 * 
 * typedef struct Message 
 * {
 *  char ucMessageID;
 *  char ucData[ 20 ];
 * }Message_t;
 * 
 * int main() {
 * Message_t message = {0};
 * SERVICE_RTOS_ErrStat_t local_TaskCreateState_t = SERVICE_RTOS_CreateBlockingQueue(10, sizeof(Message_t), &Queue1_Handler);
 * if(SERVICE_RTOS_STAT_OK == local_TaskCreateState_t)
 * {  
 *    if(SERVICE_RTOS_ReadFromBlockingQueue(100, (const void*)&message, Queue1_Handler) == SERVICE_RTOS_STAT_OK)
 *    {
 *      // do what you want here
 *    }
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
SERVICE_RTOS_ErrStat_t SERVICE_RTOS_ReadFromBlockingQueue(uint32_t arg_u32TimeoutMS, const void * arg_pItemToReceive, RTOS_QueueHandle_t arg_QueueHandle);

/*** End of File **************************************************************/
#endif /*SERVICE_RTOS_WRAPPER_H_*/
