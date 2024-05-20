/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   Application Code                                                                                            |
 * |    @file           :   main.c                                                                                                      |
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

/*
 *@Note
 *task1 and task2 alternate printing
 */

#include "debug.h"
#include "Service_RTOS_wrapper.h"
#include "MCAL_config.h"


/* Global define */
#define TASK1_TASK_PRIO 5
#define TASK1_STK_SIZE 256
#define TASK2_TASK_PRIO 5
#define TASK2_STK_SIZE 256

/* Global Variable */
RTOS_TaskHandle_t Task2Task_Handler;

/*********************************************************************
 * @fn      GPIO_Toggle_INIT
 *
 * @brief   Initializes GPIOA.0/1
 *
 * @return  none
 */
void GPIO_Toggle_INIT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}


/*********************************************************************
 * @fn      task2_task
 *
 * @brief   task2 program.
 *
 * @param  *pvParameters - Parameters point of task2
 *
 * @return  none
 */
// void task2_task(void *pvParameters)
// {
//     while (1)
//     {
//         printf("task2 entry\r\n");
//         GPIO_ResetBits(GPIOA, GPIO_Pin_1);
//         vTaskDelay(500);
//         GPIO_SetBits(GPIOA, GPIO_Pin_1);
//         vTaskDelay(500);
//     }
// }




/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    // Configure Clock and enable all needed peripherals 
    SystemInit();
    SystemCoreClockUpdate();
    MCAL_Config_ConfigAllPins();
    
    // configure NVIC
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    
    
    
    // Delay_Init();
    // USART_Printf_Init(115200);
    // printf("SystemClk:%d\r\n", SystemCoreClock);
    // printf("ChipID:%08x\r\n", DBGMCU_GetCHIPID());

    // GPIO_Toggle_INIT();
    // /* create two task */
    // SERVICE_RTOS_TaskCreate((SERVICE_RTOS_TaskFunction_t)task2_task,
    //             "task2",
    //             TASK2_STK_SIZE,
    //             (UBaseType_t)TASK2_TASK_PRIO,
    //             (RTOS_TaskHandle_t *)&Task2Task_Handler);


    // // vTaskStartScheduler();

    // while (1)
    // {
    //     printf("shouldn't run at here!!\n");
    // }
}
