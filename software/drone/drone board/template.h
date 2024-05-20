/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   configuration file for the Micro-controller                                                                 |
 * |    @file           :   MCAL_config.h                                                                                               |
 * |    @author         :   Abdelrahman Mohamed Salem                                                                                   |
 * |    @origin_date    :   20/05/2024                                                                                                  |
 * |    @version        :   1.0.0                                                                                                       |
 * |    @tool_chain     :   RISC-V Cross GCC                                                                                            |
 * |    @compiler       :   GCC                                                                                                         |
 * |    @C_standard     :   ISO C99 (-std=c99)                                                                                          |
 * |    @target         :   CH32V203C8T6                                                                                                |
 * |    @notes          :   None                                                                                                        |
 * |    @license        :   MIT License                                                                                                 |
 * |    @brief          :   this file is the main entry to our application code that will run                                           |
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
 * |    20/05/2023      1.0.0           Abdelrahman Mohamed Salem       file Created.                                                   |
 * --------------------------------------------------------------------------------------------------------------------------------------
 */


#ifndef SERVICE_RTOS_WRAPPER_H_
#define SERVICE_RTOS_WRAPPER_H_

/******************************************************************************
 * Includes
 *******************************************************************************/


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

/*** End of File **************************************************************/
#endif /*SERVICE_RTOS_WRAPPER_H_*/