/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   Application Code                                                                                            |
 * |    @file           :   main.c                                                                                                      |
 * |    @author         :   Abdelrahman Mohamed Salem                                                                                   |
 * |    @origin_date    :   18/06/2024                                                                                                  |
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
 * |    18/06/2023      1.0.0           Abdelrahman Mohamed Salem       file Created.                                                   |
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
 * @reason: contains definition for some constants values
 */
#include "constants.h"

/**
 * @reason: contains map function
 */
#include "common.h"

/******************************************************************************
 * Module Preprocessor Constants
 *******************************************************************************/

/************************************************************************/
/**
 * @brief: size of stack for remote control data communication task in words
*/
#define TASK_RC_COMM_STACK_SIZE 256

/**
 * @brief: size of stack for actions to be taken task in words
*/
#define TASK_TACK_ACTION_STACK_SIZE 256

/**
 * @brief: size of stack for communication with drone board task in words
*/
#define TASK_DRONE_COMM_STACK_SIZE 256



/************************************************************************/
/**
 * @brief: priority for emote control data communication task
*/
#define TASK_RC_COMM_PRIO 3

/**
 * @brief: priority for actions to be taken task
*/
#define TASK_TAKE_ACTIONS_PRIO 4

/**
 * @brief: priority for communication with drone board task
*/
#define TASK_DRONE_COMM_PRIO 2


/************************************************************************/
/**
 * @brief: Queue length for 'queue_RawRCData_Handle_t'
*/
#define QUEUE_RAW_RC_DATA_LEN   30

/**
 * @brief: Queue length for 'queue_TakeAction_Handle_t'
*/
#define QUEUE_TAKE_ACTION_DATA_LEN   10

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
 * @brief: this is the queue that the remote control task will put its output into it
*/
RTOS_QueueHandle_t queue_RawRCData_Handle_t;

/**
 * @brief: this is the queue that the sensor fusion task will put its output into it
*/
RTOS_QueueHandle_t queue_TakeAction_Handle_t;

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
 * @brief: handler which act as identifier for the remote control data communication task through which we will deal with anything related to this task 
*/
RTOS_TaskHandle_t task_RCComm_Handle_t;

/**
 * @brief: handler which act as identifier for the take action task through which we will deal with anything related to this task 
*/
RTOS_TaskHandle_t task_TakeAction_Handle_t;

/**
 * @brief: handler which act as identifier for the app board communication task through which we will deal with anything related to this task 
*/
RTOS_TaskHandle_t task_DroneComm_Handle_t;


/************************************************************************/
/**
 * @brief: strcut through which we will communicate with Drone board 
*/
HAL_WRAPPER_AppCommMsg_t global_DroneCommMsg_t = {0};

/**
 * @brief: actual place where the received data will be placed
 */
DroneToAppDataItem_t global_MsgToRec_t = {0};

/******************************************************************************
 * Function Prototypes
 *******************************************************************************/

/******************************************************************************
 * Function Definitions
 *******************************************************************************/

/************************************************************************/
void UARTReceivedISR(void)
{
    static uint8_t local_u8MsgType = DATA_TYPE_INVALID;
    static uint16_t local_u16CurrentItem = 0;
    static HAL_WRAPPER_ErrStat_t local_errState = HAL_WRAPPER_STAT_OK;
    static uint8_t local_u8Dummy = 0;

    // see if there is anything to receive
    local_errState = HAL_WRAPPER_GetCommMessage(&local_u8Dummy);

    if(HAL_WRAPPER_STAT_OK == local_errState)
    {
        if(0 == global_DroneCommMsg_t.dataIsToReceive)
        {
            // check if the received byte is of correct type
            local_u8MsgType = local_u8Dummy;
            if(DATA_TYPE_INFO == local_u8MsgType)
            {
                local_u16CurrentItem = 1;
                global_DroneCommMsg_t.dataIsToReceive = 1;
                *global_DroneCommMsg_t.dataToReceive = local_u8MsgType;
            }
            else
            {
                // invalid header, discard
            }

        }
        else
        {
            // stare data in the variable
            *(global_DroneCommMsg_t.dataToReceive + local_u16CurrentItem) = local_u8Dummy;
            local_u16CurrentItem++;

            // check if we reached the correct length of the message to receive
            if(local_u16CurrentItem == global_DroneCommMsg_t.dataToReceiveLen)
            {
                global_DroneCommMsg_t.IsDataReceived = 1;
            }
        }
    }
}

/************************************************************************/
/**
 * @brief: this task is responsible for the communication with the remote control
*/
void Task_RCComm(void)
{   
    HAL_WRAPPER_RCMsg_t local_RCData_t = {0};
    HAL_WRAPPER_ErrStat_t local_errState = HAL_WRAPPER_STAT_OK;
    uint8_t local_u8LenOfRemaining = 0;
    AppToDroneDataItem_t local_itemToRec_t = {0};
    DroneToAppDataItem_t local_itemToSend_t = {0};

    while (1)
    {
        // TODO: make a timer every 10 seconds to check if we received anything to switch to landing mode 

        // check if there is anything to receive from nrf module
        local_errState = HAL_WRAPPER_RCReceive(&local_RCData_t);
        if(HAL_WRAPPER_STAT_OK == local_errState)
        {
            // TODO: comment the below line
             printf("Roll: %d, Pitch: %d, Thrust: %d, Yaw: %d, LEDs: %d, Music: %d\r\n",
             local_RCData_t.MsgToReceive.data.move.roll, local_RCData_t.MsgToReceive.data.move.pitch, local_RCData_t.MsgToReceive.data.move.thrust,
             local_RCData_t.MsgToReceive.data.move.yaw, local_RCData_t.MsgToReceive.data.move.turnOnLeds, local_RCData_t.MsgToReceive.data.move.playMusic);

            // map the values "from -63 to 64" coming from the remote control into values "from -180.0 to 180.0"
            local_itemToRec_t.roll = LIB_COMM_MAP(local_RCData_t.MsgToReceive.data.move.roll, -64.0, 64.0, -90.0, 90.0);
            local_itemToRec_t.pitch = LIB_COMM_MAP(local_RCData_t.MsgToReceive.data.move.pitch, -64.0, 64.0, -90.0, 90.0);
            local_itemToRec_t.yaw = LIB_COMM_MAP(local_RCData_t.MsgToReceive.data.move.yaw, -64.0, 64.0, -90.0, 90.0);
            local_itemToRec_t.thrust = LIB_COMM_MAP(local_RCData_t.MsgToReceive.data.move.thrust, -64.0, 64.0, -10.0, 10.0); // TODO: check possible values for thrust
            local_itemToRec_t.startDrone = local_RCData_t.MsgToReceive.data.move.startDrone;
            local_itemToRec_t.type = local_RCData_t.MsgToReceive.type;

            // prevent the input pitch and yaw to have absolute values more than 20 degrees
            if(local_itemToRec_t.roll > 20)
            {
                local_itemToRec_t.roll = 20.0;
            }
            else if(local_itemToRec_t.roll < -20)
            {
                local_itemToRec_t.roll = -20.0;
            }

            if(local_itemToRec_t.pitch > 20)
            {
                local_itemToRec_t.pitch = 20.0;
            }          
            else if(local_itemToRec_t.pitch < -20)
            {
                local_itemToRec_t.pitch = -20.0;
            }

            // push the data into the queue for sending to drone communication task
            SERVICE_RTOS_AppendToBlockingQueue(0, (const void *) &local_itemToRec_t, queue_AppCommToDrone_Handle_t);
            SERVICE_RTOS_Notify(task_DroneComm_Handle_t, LIB_CONSTANTS_DISABLED);

            // push the data into the queue for sending to actions task (TODO)
            // SERVICE_RTOS_AppendToBlockingQueue(1000, (const void *) &local_out_t, queue_RawSensorData_Handle_t);
        }

        // check if there is anything to send to the remote control
        local_errState = SERVICE_RTOS_ReadFromBlockingQueue(0, (void *) &local_itemToSend_t, queue_DroneCommToApp_Handle_t, &local_u8LenOfRemaining);
        if(HAL_WRAPPER_STAT_OK == local_errState)
        {
            // assign the variables
            local_RCData_t.MsgToSend = local_itemToSend_t.data;

            // send data
            HAL_WRAPPER_RCSend(&local_RCData_t);
        }


        // sleep for 5 ms
//        SERVICE_RTOS_BlockFor(1);
    }
}

/************************************************************************/
/**
 * @brief: this task is responsible for communication with the drone board 
 * @note: it has no delay so it will running instead of the idle task
*/
void Task_DroneComm(void)
{
    
    SERVICE_RTOS_ErrStat_t local_RTOSErrStatus = SERVICE_RTOS_STAT_OK;
    AppToDroneDataItem_t local_MsgToSend_t = {0};
    uint8_t local_u8LenOfRemaining = 0;

    // assign pointers and lengths of data to be always sent
    global_DroneCommMsg_t.dataToSend = (uint8_t*)&local_MsgToSend_t;
    global_DroneCommMsg_t.dataToSendLen = sizeof(local_MsgToSend_t);

    while (1)
    {
        // // wait for notification
        // SERVICE_RTOS_WaitForNotification(1000);

        // check if there is anything in the queue to be sent
        local_RTOSErrStatus = SERVICE_RTOS_ReadFromBlockingQueue(0, (void *) &local_MsgToSend_t, queue_AppCommToDrone_Handle_t, &local_u8LenOfRemaining);

        // loop until all message are sent
        while (local_u8LenOfRemaining && SERVICE_RTOS_STAT_OK == local_RTOSErrStatus)
        {

            // send the message
            size_t i = 0;
            while (i < global_DroneCommMsg_t.dataToSendLen)
            {
                if(HAL_WRAPPER_SendCommMessage(*(global_DroneCommMsg_t.dataToSend + i)) == HAL_WRAPPER_STAT_OK)
                {
                    i++;
                }
                else
                {
                    // check if there anything Drone board is sending in case of failure of sending, it maybe due receive buffer not empty
                    UARTReceivedISR();
                    if(global_DroneCommMsg_t.IsDataReceived)
                    {   
                        // append the new received message to the queue
                        SERVICE_RTOS_AppendToBlockingQueue(1000, (const void *) &global_MsgToRec_t, queue_DroneCommToApp_Handle_t);
                        SERVICE_RTOS_Notify(task_RCComm_Handle_t, LIB_CONSTANTS_DISABLED);  

                        global_DroneCommMsg_t.dataIsToReceive = 0;
                        global_DroneCommMsg_t.IsDataReceived = 0;
                    }
                }
            }

            // read next message
            local_RTOSErrStatus = SERVICE_RTOS_ReadFromBlockingQueue(0, (void *) &local_MsgToSend_t, queue_AppCommToDrone_Handle_t, &local_u8LenOfRemaining);
        }
        
        // check if there anything Drone board is sending
        UARTReceivedISR();
        if(global_DroneCommMsg_t.IsDataReceived)
        {   
             // append the new received message to the queue
            SERVICE_RTOS_AppendToBlockingQueue(1000, (const void *) &global_MsgToRec_t, queue_DroneCommToApp_Handle_t);
            SERVICE_RTOS_Notify(task_RCComm_Handle_t, LIB_CONSTANTS_DISABLED);  
            
             global_DroneCommMsg_t.dataIsToReceive = 0;
             global_DroneCommMsg_t.IsDataReceived = 0;
        }

       


    }
}

/************************************************************************/
/**
 * @brief: this task is responsible for processing of sensor data
*/
void Task_TakeAction(void)
{
    //                      SOME INITIALIZATION 
    // INITIALIZATION CAN'T BE DONE IN MAIN AS SCHEDULAR HAS TO START FIRST BEFORE DOING 
    // ANYTHING (RECEIVING INTERRUPTS HAS TO WAIT BEFORE INITIALIZING)
    /************************************************************************/
    // assign pointers and lengths of data to be always received
    global_DroneCommMsg_t.dataToReceive = (uint8_t*) &global_MsgToRec_t.data;
    global_DroneCommMsg_t.dataToReceiveLen = sizeof(global_MsgToRec_t.data);
    global_DroneCommMsg_t.dataIsToReceive = 0;
    global_DroneCommMsg_t.IsDataReceived = 0;
    /************************************************************************/

    // Configure/enable Clock and all needed peripherals 
    SystemInit();
    SystemCoreClockUpdate();

    // configure NVIC
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    // // set call back for board receive
    // HAL_WRAPPER_SetAppCommRecCallBack(UARTReceivedISR);

    // configure all pins and peripherals 
    MCAL_Config_ConfigAllPins();

    // configure the external hardware as sensors, motors, etc... 
    HAL_Config_ConfigAllHW();

    // TODO: comment the below line
    USART_Printf_Init(115200);

    
    // TODO: comment the below line
//     USART_Printf_Init(115200);

    SERVICE_RTOS_ErrStat_t local_ErrStatus = SERVICE_RTOS_STAT_OK;
    uint8_t local_u8LenOfRemaining = 0;

    while (1)
    {
        // wait for notification
        SERVICE_RTOS_WaitForNotification(10000);  

        // read item from raw actions
        // local_ErrStatus = SERVICE_RTOS_ReadFromBlockingQueue(1000, (void *) &local_in_t, queue_RawSensorData_Handle_t, &local_u8LenOfRemaining);

        // check if we got back a reading
        if(SERVICE_RTOS_STAT_OK == local_ErrStatus)
        {
            // play some music with buzzer and flash leds

        }

    }
}

/************************************************************************/
/**
 * @brief: main function of the app board
*/
int main(void)
{
    // create the Queue for sensor collection data task to put its data into it
    SERVICE_RTOS_CreateBlockingQueue(QUEUE_RAW_RC_DATA_LEN,
                                    sizeof(RawRCDataItem_t),
                                    &queue_RawRCData_Handle_t);

    // create the Queue for sensor fusion task to put its data into it
    SERVICE_RTOS_CreateBlockingQueue(QUEUE_TAKE_ACTION_DATA_LEN,
                                    sizeof(AppTakeAction_t),
                                    &queue_TakeAction_Handle_t);

    // create the Queue for sensor collection data to put its data into it
    SERVICE_RTOS_CreateBlockingQueue(QUEUE_APP_TO_DRONE_DATA_LEN,
                                    sizeof(AppToDroneDataItem_t),
                                    &queue_AppCommToDrone_Handle_t);

    // create the Queue for sensor collection data to put its data into it
    SERVICE_RTOS_CreateBlockingQueue(QUEUE_DRONE_TO_APP_DATA_LEN,
                                    sizeof(DroneToAppDataItem_t),
                                    &queue_DroneCommToApp_Handle_t);


    // create a task for reading sensor data
    SERVICE_RTOS_TaskCreate((SERVICE_RTOS_TaskFunction_t)Task_RCComm,
                "RC Communication",
                TASK_RC_COMM_STACK_SIZE,
                TASK_RC_COMM_PRIO,
                &task_RCComm_Handle_t);

    // create a task for taking actions
    SERVICE_RTOS_TaskCreate((SERVICE_RTOS_TaskFunction_t)Task_TakeAction,
                "Take Action",
                TASK_TACK_ACTION_STACK_SIZE,
                TASK_TAKE_ACTIONS_PRIO,
                &task_TakeAction_Handle_t);

    // create a task for communication with app board 
    SERVICE_RTOS_TaskCreate((SERVICE_RTOS_TaskFunction_t)Task_DroneComm,
                "Drone Communication",
                TASK_DRONE_COMM_STACK_SIZE,
                TASK_DRONE_COMM_PRIO,
                &task_DroneComm_Handle_t);
    

    // start the schedular
    SERVICE_RTOS_StartSchedular();

    while (1)
    {
        printf("shouldn't run at here!!\n");
    }
}


/*************** END OF FUNCTIONS ***************************************************************************/
