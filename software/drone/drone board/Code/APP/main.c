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
 * |    21/05/2023      1.0.0           Abdelrahman Mohamed Salem       created the initial blueprint for tasks.                        |
 * |    22/05/2023      1.0.0           Abdelrahman Mohamed Salem       created the Queues for the IPC.                                 |
 * --------------------------------------------------------------------------------------------------------------------------------------
 */

/******************************************************************************
 * Includes
 *******************************************************************************/

/**
 * @reason: contains printf function for debugging
*/
#include "debug.h"

/**
 * @reason: contains wrapper functions for needed RTOS functions
*/
#include "Service_RTOS_wrapper.h"

/**
 * @reason: initialize the pins of the micro-controller
*/
#include "MCAL_config.h"

/**
 * @reason: initialization of the all the external hardware
 */
#include "HAL_config.h"

/**
 * @reason: contains wrapper functions for HAL layer
 */
#include "HAL_wrapper.h"

/**
 * @reason: contains typedef for main code
 */
#include "main.h"

/**
 * @reason: contains sensors fusion functionality along with kalman filter
 */
#include "SensorFusion.h"

/******************************************************************************
 * Module Preprocessor Constants
 *******************************************************************************/

/************************************************************************/
/**
 * @brief: size of stack for sensor data collection task in words
*/
#define TASK_SENSOR_COLLECT_STACK_SIZE 256

/**
 * @brief: size of stack for sensor fusion task in words
*/
#define TASK_SENSOR_FUSION_STACK_SIZE 256

/**
 * @brief: size of stack for communication with application board task in words
*/
#define TASK_APP_COMM_STACK_SIZE 256

/**
 * @brief: size of stack for master task in words
*/
#define TASK_MASTER_STACK_SIZE 256



/************************************************************************/
/**
 * @brief: priority for sensor data collection task
*/
#define TASK_SENSOR_COLLECT_PRIO 4

/**
 * @brief: priority for sensor fusion task
*/
#define TASK_SENSOR_FUSION_PRIO 3

/**
 * @brief: priority for communication with application board task
*/
#define TASK_APP_COMM_PRIO 2

/**
 * @brief: priority for master task
*/
#define TASK_MASTER_PRIO 5

/************************************************************************/
/**
 * @brief: Queue length for 'queue_RawSensorData_Handle_t'
*/
#define QUEUE_RAW_SENSOR_DATA_LEN   10

/**
 * @brief: Queue length for 'queue_FusedSensorData_Handle_t'
*/
#define QUEUE_SENSOR_FUSION_DATA_LEN   10

/**
 * @brief: Queue length for 'queue_AppCommToDrone_Handle_t'
*/
#define QUEUE_APP_TO_DRONE_DATA_LEN   10

/**
 * @brief: Queue length for 'queue_DroneCommToApp_Handle_t'
*/
#define QUEUE_DRONE_TO_APP_DATA_LEN   10

/******************************************************************************
 * Module Preprocessor Macros
 *******************************************************************************/

/******************************************************************************
 * Module Typedefs
 *******************************************************************************/

/******************************************************************************
 * Module Variable Definitions
 *******************************************************************************/


/************************************************************************/
/**
 * @brief: this is the queue that the sensor data collection task will put its output into it
*/
RTOS_QueueHandle_t queue_RawSensorData_Handle_t;

/**
 * @brief: this is the queue that the sensor fusion task will put its output into it
*/
RTOS_QueueHandle_t queue_FusedSensorData_Handle_t;

/**
 * @brief: this is the queue that the app communication task will put its output into it from app board to the drone board
*/
RTOS_QueueHandle_t queue_AppCommToDrone_Handle_t;

/**
 * @brief: this is the queue that the app communication task will put its output into it from drone board to the app board
*/
RTOS_QueueHandle_t queue_DroneCommToApp_Handle_t;

/************************************************************************/
/**
 * @brief: handler which act as identifier for the sensor data collection task through which we will deal with anything related to this task 
*/
RTOS_TaskHandle_t task_CollectSensorData_Handle_t;

/**
 * @brief: handler which act as identifier for the sensor fusion task through which we will deal with anything related to this task 
*/
RTOS_TaskHandle_t task_SensorFusion_Handle_t;

/**
 * @brief: handler which act as identifier for the app board communication task through which we will deal with anything related to this task 
*/
RTOS_TaskHandle_t task_AppComm_Handle_t;

/**
 * @brief: handler which act as identifier for the master task through which we will deal with anything related to this task 
*/
RTOS_TaskHandle_t task_Master_Handle_t;


/******************************************************************************
 * Function Prototypes
 *******************************************************************************/

/******************************************************************************
 * Function Definitions
 *******************************************************************************/

/************************************************************************/
/**
 * @brief: this task is responsible for the collection of sensor data
*/
void Task_CollectSensorData(void)
{   
    HAL_WRAPPER_Acc_t local_Acc_t = {0};
    HAL_WRAPPER_Gyro_t local_gyro_t = {0};
    RawSensorDataItem_t local_item_t = {0};

    while (1)
    {
        // read accelerometer data
        HAL_WRAPEPR_ReadAcc(&local_Acc_t);
        
        // read gyroscope data
        HAL_WRAPEPR_ReadGyro(&local_gyro_t);

        // read magnetometer data

        // read barometer data

        // read temperature data

        // assign variables
        local_item_t.Acc = local_Acc_t;
        local_item_t.Gyro = local_gyro_t;

        // push the data into the queue for fusion
        SERVICE_RTOS_AppendToBlockingQueue(1000, (const void *) &local_item_t, queue_RawSensorData_Handle_t);
    }
}

/************************************************************************/
/**
 * @brief: this task is responsible for processing of sensor data
*/
void Task_SensorFusion(void)
{
    RawSensorDataItem_t local_in_t = {0};
    SensorFusionDataItem_t local_out_t = {0};
    SERVICE_RTOS_ErrStat_t local_ErrStatus = SERVICE_RTOS_STAT_OK;

    while (1)
    {
        // read item from raw sensor queue
        local_ErrStatus = SERVICE_RTOS_ReadFromBlockingQueue(1000, (const void *) &local_in_t, queue_RawSensorData_Handle_t);

        // check if we got back a reading
        if(SERVICE_RTOS_STAT_QUEUE_EMPTY == local_ErrStatus)
        {
            // apply kalman filter with sensor fusion
            SensorFuseWithKalman(&local_in_t, &local_out_t);

            // append to the queue the the current state
            SERVICE_RTOS_AppendToBlockingQueue(1000, (const void *) &local_out_t, queue_FusedSensorData_Handle_t);
        }

    }
}

/************************************************************************/
/**
 * @brief: this task is responsible for communication with the application board 
*/
void Task_AppComm(void)
{
    while (1)
    {
        // check if there anything app board is sending
        if(1)
        {
            // change the state
        }

        // append the new state to the queue

        // check if there anything to send to the App board
        if(1)
        {
            // send the info to the board using UART
        }

    }
}

/************************************************************************/
/**
 * @brief: this is the master task that will take action upon commands given from the application board or new updates from the sensor data to stabilize the drone
*/
void Task_Master(void)
{
    while (1)
    {
        // check for new State from AppComm
        if(1)
        {
            // assign the required state
        }

        // get sensor fused readings with kalman filter
        
        // apply PID to compute error

        // apply actions on the motors

    }
}

/************************************************************************/
/**
 * @brief: main function of the drone board
*/
int main(void)
{
    // Configure/enable Clock and all needed peripherals 
    SystemInit();
    SystemCoreClockUpdate();

    // configure NVIC
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    // configure all pins and peripherals 
    MCAL_Config_ConfigAllPins();

    // configure the external hardware as sensors, motors, etc... 
    HAL_Config_ConfigAllHW();

    // create the Queue for sensor collection data task to put its data into it
    SERVICE_RTOS_CreateBlockingQueue(QUEUE_RAW_SENSOR_DATA_LEN,
                                    sizeof(RawSensorDataItem_t),
                                    &queue_RawSensorData_Handle_t);

    // create the Queue for sensor fusion task to put its data into it
    SERVICE_RTOS_CreateBlockingQueue(QUEUE_SENSOR_FUSION_DATA_LEN,
                                    sizeof(SensorFusionDataItem_t),
                                    &queue_FusedSensorData_Handle_t);

    // create the Queue for sensor collection data to put its data into it
    SERVICE_RTOS_CreateBlockingQueue(QUEUE_APP_TO_DRONE_DATA_LEN,
                                    sizeof(AppToDroneDataItem_t),
                                    &queue_AppCommToDrone_Handle_t);

    // create the Queue for sensor collection data to put its data into it
    SERVICE_RTOS_CreateBlockingQueue(QUEUE_DRONE_TO_APP_DATA_LEN,
                                    sizeof(DroneToAppDataItem_t),
                                    &queue_DroneCommToApp_Handle_t);


    // create a task for reading sensor data
    SERVICE_RTOS_TaskCreate((SERVICE_RTOS_TaskFunction_t)Task_CollectSensorData,
                "Sensor Collection",
                TASK_SENSOR_COLLECT_STACK_SIZE,
                TASK_SENSOR_COLLECT_PRIO,
                &task_CollectSensorData_Handle_t);

    // // create a task for fusing sensor data
    // SERVICE_RTOS_TaskCreate((SERVICE_RTOS_TaskFunction_t)Task_SensorFusion,
    //             "Sensor Fusion",
    //             TASK_SENSOR_FUSION_STACK_SIZE,
    //             TASK_SENSOR_FUSION_PRIO,
    //             &task_SensorFusion_Handle_t);

    // // create a task for communication with app board 
    // SERVICE_RTOS_TaskCreate((SERVICE_RTOS_TaskFunction_t)Task_AppComm,
    //             "App Communication",
    //             TASK_APP_COMM_STACK_SIZE,
    //             TASK_APP_COMM_PRIO,
    //             &task_AppComm_Handle_t);

    // // create a task for master
    // SERVICE_RTOS_TaskCreate((SERVICE_RTOS_TaskFunction_t)Task_Master,
    //             "Master",
    //             TASK_MASTER_STACK_SIZE,
    //             TASK_MASTER_PRIO,
    //             &task_Master_Handle_t);

    // start the schedular
    SERVICE_RTOS_StartSchedular();

    while (1)
    {
        printf("shouldn't run at here!!\n");
    }
}


/*************** END OF FUNCTIONS ***************************************************************************/
