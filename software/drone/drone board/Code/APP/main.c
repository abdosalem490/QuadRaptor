/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2021/06/06
 * Description        : Main program body.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/*
 *@Note
 *task1 and task2 alternate printing
 */

#include "debug.h"
#include "Service_RTOS_wrapper.h"


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
    // Configure Clock

    // configure NVIC

    // configure Pins

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    SystemCoreClockUpdate();
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
