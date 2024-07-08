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

/**
 * @reason: contains pid ctrl block
 */
#include "pid.h"

/**
 * @reason: contains some common constants
 */
#include "constants.h"

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
#define QUEUE_RAW_SENSOR_DATA_LEN   30

/**
 * @brief: Queue length for 'queue_FusedSensorData_Handle_t'
*/
#define QUEUE_SENSOR_FUSION_DATA_LEN   30

/**
 * @brief: Queue length for 'queue_AppCommToDrone_Handle_t'
*/
#define QUEUE_APP_TO_DRONE_DATA_LEN   30

/**
 * @brief: Queue length for 'queue_DroneCommToApp_Handle_t'
*/
#define QUEUE_DRONE_TO_APP_DATA_LEN   30

/************************************************************************/
/**
 * @brief: maximum speed for motors to prevent damage
*/
#define MAX_MOTOR_SPEED   75

/**
 * @brief: minimum speed for motors to prevent damage
*/
#define MIN_MOTOR_SPEED   15

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
RTOS_TaskHandle_t task_CollectSensorData_Handle_t = NULL;

/**
 * @brief: handler which act as identifier for the sensor fusion task through which we will deal with anything related to this task 
*/
RTOS_TaskHandle_t task_SensorFusion_Handle_t = NULL;

/**
 * @brief: handler which act as identifier for the app board communication task through which we will deal with anything related to this task 
*/
RTOS_TaskHandle_t task_AppComm_Handle_t = NULL;

/**
 * @brief: handler which act as identifier for the master task through which we will deal with anything related to this task 
*/
RTOS_TaskHandle_t task_Master_Handle_t = NULL;

/************************************************************************/

/**
 * @brief: strcut through which we will communicate with app board 
*/
HAL_WRAPPER_AppCommMsg_t global_AppCommMsg_t = {0};

/**
 * @brief: actual place where the received data will be placed
 */
AppToDroneDataItem_t global_MsgToRec_t = {0};


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
        if(0 == global_AppCommMsg_t.dataIsToReceive)
        {
            // check if the received byte is of correct type
            local_u8MsgType = local_u8Dummy;
            if(DATA_TYPE_MOVE == local_u8MsgType)
            {
                local_u16CurrentItem = 1;
                global_AppCommMsg_t.dataIsToReceive = 1;
                *global_AppCommMsg_t.dataToReceive = local_u8MsgType;
            }
            else
            {
                // invalid header, discard
            }

        }
        else
        {
            // stare data in the variable
            *(global_AppCommMsg_t.dataToReceive + local_u16CurrentItem) = local_u8Dummy;
            local_u16CurrentItem++;

            // check if we reached the correct length of the message to receive
            if(local_u16CurrentItem == global_AppCommMsg_t.dataToReceiveLen)
            {
                global_AppCommMsg_t.IsDataReceived = 1;
            }
        }
    }

}

/************************************************************************/
/**
 * @brief: this task is responsible for the collection of sensor data
*/
void Task_CollectSensorData(void)
{   
    

    while (1)
    {
        
    }
}

/************************************************************************/
/**
 * @brief: this task is responsible for processing of sensor data
*/
void Task_SensorFusion(void)
{
    RawSensorDataItem_t local_in_t = {0};
    SensorFusionDataItem_t local_temp_t = {0};
    SensorFusionDataItem_t local_out_t = {0};
    SERVICE_RTOS_ErrStat_t local_ErrStatus = SERVICE_RTOS_STAT_OK;
    DroneToAppDataItem_t local_DataToSendtoApp_t = {0};
    uint8_t local_u8LenOfRemaining = 0;
    uint32_t CurrentTimeMS = 0;
    uint32_t CurrentTimeCounterS = 0;

    // Initialize 2d-kalman filter matrices
    Altitude_Kalman_2D_init();

    while (1)
    {
        // read item from raw sensor queue
        local_ErrStatus = SERVICE_RTOS_ReadFromBlockingQueue(1000, (void *) &local_in_t, queue_RawSensorData_Handle_t, &local_u8LenOfRemaining);

        // check if we got back a reading
        if(SERVICE_RTOS_STAT_OK == local_ErrStatus)
        {
            // apply kalman filter with sensor fusion
            SensorFuseWithKalman(&local_in_t, &local_temp_t);

            // actual measurements showed that roll and pitch are reversed and pitch is in negative
            local_out_t.pitch = -local_temp_t.roll;
            local_out_t.roll = local_temp_t.pitch;
            local_out_t.yaw = local_temp_t.yaw;
            local_out_t.yaw_rate = local_temp_t.yaw_rate;
            local_out_t.altitude = local_temp_t.altitude;
            local_out_t.vertical_velocity = local_temp_t.vertical_velocity;

            // check if a second passed to send some info to the application board
            SERVICE_RTOS_CurrentMSTime(&CurrentTimeMS);
            if(1000 < CurrentTimeMS - CurrentTimeCounterS)
            {
            	// assign new time
            	CurrentTimeCounterS += 1000;

                // set type of data to send
                local_DataToSendtoApp_t.data.type = DATA_TYPE_INFO;

                // read temperature data
                local_DataToSendtoApp_t.data.data.info.temperature = local_in_t.Temperature.temperature;

                // read battery charge
                local_DataToSendtoApp_t.data.data.info.batteryCharge = local_in_t.Battery.batteryCharge;

                // assign current altitude
                local_DataToSendtoApp_t.data.data.info.altitude = local_in_t.Altitude.ultrasonic_altitude / 100.0;

                // assign distanceToOrigin (TODO)
                local_DataToSendtoApp_t.data.data.info.distanceToOrigin = 1.5;       

                // push data into queue to be sent to the app board and notify the AppComm with new data
                SERVICE_RTOS_AppendToBlockingQueue(0, (const void *) &local_DataToSendtoApp_t, queue_DroneCommToApp_Handle_t);
                SERVICE_RTOS_Notify(task_AppComm_Handle_t, LIB_CONSTANTS_DISABLED);       
            }


            // append to the queue the the current state
            SERVICE_RTOS_AppendToBlockingQueue(0, (const void *) &local_out_t, queue_FusedSensorData_Handle_t);
            SERVICE_RTOS_Notify(task_Master_Handle_t, LIB_CONSTANTS_DISABLED); 

            // TODO: move the below line
//            if(local_out_t.vertical_velocity >= 1)
//            printf("%d,%d,%d,%d\n\r", (int)local_out_t.pitch, (int)local_out_t.roll, (int)local_out_t.yaw, (int)local_out_t.vertical_velocity);

        }
    }
}

/************************************************************************/
/**
 * @brief: this task is responsible for communication with the application board 
 * @note: it has no delay so it will running instead of the idle task
*/
void Task_AppComm(void)
{
    
    SERVICE_RTOS_ErrStat_t local_RTOSErrStatus = SERVICE_RTOS_STAT_OK;
    
    DroneToAppDataItem_t local_MsgToSend_t = {0};
    uint8_t local_u8LenOfRemaining = 0;

    // assign pointers and lengths of data to be always send
    global_AppCommMsg_t.dataToSend = (uint8_t*)&local_MsgToSend_t.data;
    global_AppCommMsg_t.dataToSendLen = sizeof(local_MsgToSend_t.data);

    while (1)
    {
        // // wait for notification (this task will run instead of idle task)
        // SERVICE_RTOS_WaitForNotification(1000);

        // check if there is anything in the queue to be sent
        local_RTOSErrStatus = SERVICE_RTOS_ReadFromBlockingQueue(0, (void *) &local_MsgToSend_t, queue_DroneCommToApp_Handle_t, &local_u8LenOfRemaining);

        // loop until all message are sent
        while (local_u8LenOfRemaining && SERVICE_RTOS_STAT_OK == local_RTOSErrStatus)
        {
            // send the message
            size_t i = 0;
            while (i < global_AppCommMsg_t.dataToSendLen)
            {
                if(HAL_WRAPPER_SendCommMessage(*(global_AppCommMsg_t.dataToSend + i)) == HAL_WRAPPER_STAT_OK)
                {
                    i++;
                }
                else
                {
                    // check if there anything app board is sending as in case of failure of sending, it maybe due receive buffer not empty
                    UARTReceivedISR();
                    if(global_AppCommMsg_t.IsDataReceived)
                    {   
                        // append the new state received to the queue
                        SERVICE_RTOS_AppendToBlockingQueue(0, (const void *) &global_MsgToRec_t, queue_AppCommToDrone_Handle_t);
                        SERVICE_RTOS_Notify(task_Master_Handle_t, LIB_CONSTANTS_DISABLED);  

                        global_AppCommMsg_t.dataIsToReceive = 0;
                        global_AppCommMsg_t.IsDataReceived = 0;
                    }
                }

            }
            
            // read next message
            local_RTOSErrStatus = SERVICE_RTOS_ReadFromBlockingQueue(0, (void *) &local_MsgToSend_t, queue_DroneCommToApp_Handle_t, &local_u8LenOfRemaining);
        }
        
        // check if there anything app board is sending
        UARTReceivedISR();
        if(global_AppCommMsg_t.IsDataReceived)
        {   
            // append the new state received to the queue
            SERVICE_RTOS_AppendToBlockingQueue(0, (const void *) &global_MsgToRec_t, queue_AppCommToDrone_Handle_t);
            SERVICE_RTOS_Notify(task_Master_Handle_t, LIB_CONSTANTS_DISABLED);  

            // TODO: remove the below line
            // printf("type = %d, roll = %d, pitch = %d, thrust = %d, yaw = %d, turnOnLeds = %d, playMusic = %d\r\n",
            // global_MsgToRec_t.data.type, global_MsgToRec_t.data.data.move.roll, global_MsgToRec_t.data.data.move.pitch,
            // global_MsgToRec_t.data.data.move.thrust, global_MsgToRec_t.data.data.move.yaw, global_MsgToRec_t.data.data.move.turnOnLeds,
            // global_MsgToRec_t.data.data.move.playMusic);

            global_AppCommMsg_t.dataIsToReceive = 0;
            global_AppCommMsg_t.IsDataReceived = 0;
        }

        
    }
}


/************************************************************************/
/**
 * @brief: this is the master task that will take action upon commands given from the application board or new updates from the sensor data to stabilize the drone
*/
void Task_Master(void)
{

    // for indication if we received something from queue
    SERVICE_RTOS_ErrStat_t local_RTOSErrStatus = SERVICE_RTOS_STAT_OK;

    // to control motor speeds
    HAL_WRAPPER_MotorSpeeds_t local_MotorSpeeds = {0};
    float local_f32TopLeftSpeed = 0;
    float local_f32TopRightSpeed = 0;
    float local_f32BottomLeftSpeed = 0;
    float local_f32BottomRightSpeed = 0;

    // sensor readings
    SensorFusionDataItem_t local_SensorFusedReadings_t = {0};
    SensorFusionDataItem_t local_SensorFusedInitReadings_t = {0};
    uint8_t local_u8FirstReading = 1;
    uint32_t local_u32StartCommand = 0;
    uint32_t local_u32EndCommand = 0;
    
    // unused variable but needed for Queue receive API
    uint8_t local_u8LenOfRemaining = 0;
    
    // for communication with app board.
    AppToDroneDataItem_t local_RCRequiredVal = {0};

    // pid objects
    pid_obj_t roll_pid = {0};
    pid_obj_t pitch_pid = {0};
    pid_obj_t yaw_pid = {0};
    pid_obj_t thrust_pid = {0};

    
    //                      SOME INITIALIZATION 
    // INITIALIZATION CAN'T BE DONE IN MAIN AS SCHEDULAR HAS TO START FIRST BEFORE DOING 
    // ANYTHING (RECEIVING INTERRUPTS HAS TO WAIT BEFORE INITIALIZING)
    /************************************************************************/
    // assign pointers and lengths of data to be always received
    global_AppCommMsg_t.dataToReceive = (uint8_t*) &global_MsgToRec_t;
    global_AppCommMsg_t.dataToReceiveLen = sizeof(global_MsgToRec_t);
    global_AppCommMsg_t.dataIsToReceive = 0;
    global_AppCommMsg_t.IsDataReceived = 0;
    /************************************************************************/
    // initialize the pid controllers
    roll_pid.kp = ROLL_KP;		pitch_pid.kp = PITCH_KP;		yaw_pid.kp = YAW_KP;		thrust_pid.kp = THRUST_KP;
    roll_pid.ki = ROLL_KI;		pitch_pid.ki = PITCH_KI;       	yaw_pid.ki = YAW_KI;		thrust_pid.ki = THRUST_KI;
    roll_pid.kd = ROLL_KD;		pitch_pid.kd = PITCH_KD;		yaw_pid.kd = YAW_KD;		thrust_pid.kd = THRUST_KD;
    // add extra info for blocks
    roll_pid.minIntegralVal = ROLL_INTEGRAL_MIN;		pitch_pid.minIntegralVal = PITCH_INTEGRAL_MIN;		yaw_pid.minIntegralVal = YAW_INTEGRAL_MIN;		thrust_pid.minIntegralVal = THRUST_INTEGRAL_MIN;
    roll_pid.maxIntegralVal = ROLL_INTEGRAL_MAX;		pitch_pid.maxIntegralVal = PITCH_INTEGRAL_MAX;		yaw_pid.maxIntegralVal = YAW_INTEGRAL_MAX;		thrust_pid.maxIntegralVal = THRUST_INTEGRAL_MAX;
    roll_pid.blockWeight = ROLL_BLOCK_WEIGHT;			pitch_pid.blockWeight = PITCH_BLOCK_WEIGHT;			yaw_pid.blockWeight = YAW_BLOCK_WEIGHT;			thrust_pid.blockWeight = THRUST_BLOCK_WEIGHT;
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

    

    while (1)
    {
        // wait for notification
        SERVICE_RTOS_WaitForNotification(1000);

        // read desired action from AppComm
        local_RTOSErrStatus = SERVICE_RTOS_ReadFromBlockingQueue(0, (void *) &local_RCRequiredVal, queue_AppCommToDrone_Handle_t, &local_u8LenOfRemaining);

        // check for new State from AppComm
        if(SERVICE_RTOS_STAT_OK == local_RTOSErrStatus)
        {
            // assign the required state
        
            // TODO: remove the below line
            // printf("type = %d, roll = %f, pitch = %f, thrust = %f, yaw = %f,\r\n",
            // local_RCRequiredVal.type, local_RCRequiredVal.roll, local_RCRequiredVal.pitch,
            // local_RCRequiredVal.thrust, local_RCRequiredVal.yaw);

            // check if we wanted to stop the drone
            if(!local_RCRequiredVal.startDrone)
            {
                // stop the motors
                local_MotorSpeeds.topLeftSpeed = 0;
                local_MotorSpeeds.topRightSpeed = 0;
                local_MotorSpeeds.bottomLeftSpeed = 0;
                local_MotorSpeeds.bottomRightSpeed = 0;
                HAL_WRAPPER_SetESCSpeeds(&local_MotorSpeeds);

                // for the next run, we will need to get initial readings 
                local_u8FirstReading = 1;

                // zero out all PID blocks
                roll_pid.integral = 0;
                roll_pid.lastError = 0;
                roll_pid.error = 0;
                roll_pid.output = 0;

                pitch_pid.integral = 0;
                pitch_pid.lastError = 0;
                pitch_pid.error = 0;
                pitch_pid.output = 0;

                yaw_pid.integral = 0;
                yaw_pid.lastError = 0;
                yaw_pid.error = 0;
                yaw_pid.output = 0;

                thrust_pid.integral = 0;
                thrust_pid.lastError = 0;
                thrust_pid.error = 0;
                thrust_pid.output = 0;

                // zero the time
                local_u32StartCommand = 0;
                local_u32EndCommand = 0;
            }


        }

        // read sensor fused readings
        local_RTOSErrStatus = SERVICE_RTOS_ReadFromBlockingQueue(0, (void *) &local_SensorFusedReadings_t, queue_FusedSensorData_Handle_t, &local_u8LenOfRemaining);

        // get sensor fused readings with Kalman filter as long as the drone is commanded to start
        if(SERVICE_RTOS_STAT_OK == local_RTOSErrStatus && local_RCRequiredVal.startDrone)
        {
            // get the initial time of start 
            if(0 == local_u32StartCommand)
            {
                SERVICE_RTOS_CurrentMSTime(&local_u32StartCommand);
            }
            // get readings every time
            SERVICE_RTOS_CurrentMSTime(&local_u32EndCommand);

            // TODO: take initial data from sensor to act as start from which we will compute the change
            if(local_u8FirstReading && (local_u32EndCommand - local_u32StartCommand) > 5000)
            {
                // store the initial readings
                local_SensorFusedInitReadings_t = local_SensorFusedReadings_t;

                // indicate we get the first readings
                local_u8FirstReading = 0;

                // assign base velocity to the motors
                local_MotorSpeeds.topLeftSpeed     = MIN_MOTOR_SPEED;
                local_MotorSpeeds.topRightSpeed    = MIN_MOTOR_SPEED;
                local_MotorSpeeds.bottomLeftSpeed  = MIN_MOTOR_SPEED;
                local_MotorSpeeds.bottomRightSpeed = MIN_MOTOR_SPEED;

                // apply actions on the motors
                HAL_WRAPPER_SetESCSpeeds(&local_MotorSpeeds);
            }
            else if(!local_u8FirstReading)
            {
                // handle the subtraction between initial readings and the current readings
                local_SensorFusedReadings_t.roll  -= local_SensorFusedInitReadings_t.roll;
                local_SensorFusedReadings_t.pitch -= local_SensorFusedInitReadings_t.pitch;
                local_SensorFusedReadings_t.yaw_rate  -= local_SensorFusedInitReadings_t.yaw_rate;
                local_SensorFusedReadings_t.vertical_velocity -= local_SensorFusedInitReadings_t.vertical_velocity;

                // Compute error
                roll_pid.error      = local_RCRequiredVal.roll   - local_SensorFusedReadings_t.roll;
                pitch_pid.error     = local_RCRequiredVal.pitch  - local_SensorFusedReadings_t.pitch;
                yaw_pid.error       = local_RCRequiredVal.yaw 	 - local_SensorFusedReadings_t.yaw_rate;
                thrust_pid.error    = local_RCRequiredVal.thrust - local_SensorFusedReadings_t.vertical_velocity;
                
                // apply PID to compensate error
                pid_ctrl(&roll_pid);
                pid_ctrl(&pitch_pid);
                pid_ctrl(&yaw_pid);
//                pid_ctrl(&thrust_pid);

                // Motor mixing algorithm
                local_f32TopLeftSpeed     = MIN_MOTOR_SPEED + (thrust_pid.output - roll_pid.output + pitch_pid.output + yaw_pid.output);
                local_f32TopRightSpeed    = MIN_MOTOR_SPEED + (thrust_pid.output + roll_pid.output + pitch_pid.output - yaw_pid.output);
                local_f32BottomLeftSpeed  = MIN_MOTOR_SPEED + (thrust_pid.output - roll_pid.output - pitch_pid.output - yaw_pid.output);
                local_f32BottomRightSpeed = MIN_MOTOR_SPEED + (thrust_pid.output + roll_pid.output - pitch_pid.output + yaw_pid.output);

    //          local_f32TopLeftSpeed     = (thrust_pid.output - roll_pid.output - pitch_pid.output - yaw_pid.output);
    //			local_f32TopRightSpeed    = (thrust_pid.output + roll_pid.output - pitch_pid.output + yaw_pid.output);
    //			local_f32BottomLeftSpeed  = (thrust_pid.output - roll_pid.output + pitch_pid.output + yaw_pid.output);
    //			local_f32BottomRightSpeed = (thrust_pid.output + roll_pid.output + pitch_pid.output - yaw_pid.output);

                // apply max limits to the motor speeds
                if(local_f32TopLeftSpeed     > MAX_MOTOR_SPEED)  local_f32TopLeftSpeed     = MAX_MOTOR_SPEED;
                if(local_f32TopRightSpeed    > MAX_MOTOR_SPEED)  local_f32TopRightSpeed    = MAX_MOTOR_SPEED;
                if(local_f32BottomLeftSpeed  > MAX_MOTOR_SPEED)  local_f32BottomLeftSpeed  = MAX_MOTOR_SPEED;
                if(local_f32BottomRightSpeed > MAX_MOTOR_SPEED)  local_f32BottomRightSpeed = MAX_MOTOR_SPEED;
                
                // apply min limits to the motor speeds
                if(local_f32TopLeftSpeed     < MIN_MOTOR_SPEED)  local_f32TopLeftSpeed     = MIN_MOTOR_SPEED;
                if(local_f32TopRightSpeed    < MIN_MOTOR_SPEED)  local_f32TopRightSpeed    = MIN_MOTOR_SPEED;
                if(local_f32BottomLeftSpeed  < MIN_MOTOR_SPEED)  local_f32BottomLeftSpeed  = MIN_MOTOR_SPEED;
                if(local_f32BottomRightSpeed < MIN_MOTOR_SPEED)  local_f32BottomRightSpeed = MIN_MOTOR_SPEED;
                
//                printf("speeds: TL: %d, TR: %d, BL: %d, BR: %d\n\r", local_MotorSpeeds.topLeftSpeed, local_MotorSpeeds.topRightSpeed, local_MotorSpeeds.bottomLeftSpeed, local_MotorSpeeds.bottomRightSpeed );
//                printf("%d,%d,%d,%d\n\r", local_MotorSpeeds.topLeftSpeed, local_MotorSpeeds.topRightSpeed, local_MotorSpeeds.bottomLeftSpeed, local_MotorSpeeds.bottomRightSpeed );
//                printf("%f,%f\r\n", local_SensorFusedReadings_t.roll, local_SensorFusedReadings_t.pitch);
//                 printf("%f,%f\r\n", roll_pid.output, pitch_pid.output);
//                printf("%f,%f\r\n", local_SensorFusedReadings_t.yaw, local_SensorFusedReadings_t.yaw_rate);
//                printf("%f\r\n", local_SensorFusedReadings_t.yaw_rate);
//                printf("%f,%f\r\n", local_SensorFusedReadings_t.yaw_rate, local_RCRequiredVal.yaw);

                // assign values to motors
                local_MotorSpeeds.topLeftSpeed     = (uint8_t) local_f32TopLeftSpeed;
                local_MotorSpeeds.topRightSpeed    = (uint8_t) local_f32TopRightSpeed;
                local_MotorSpeeds.bottomLeftSpeed  = (uint8_t) local_f32BottomLeftSpeed;
                local_MotorSpeeds.bottomRightSpeed = (uint8_t) local_f32BottomRightSpeed;
                
                // apply actions on the motors
                HAL_WRAPPER_SetESCSpeeds(&local_MotorSpeeds);

                // FOR SERIAL PLOTTER
         //       printf("test\n\r");
//                printf("%d,%d,%d,%d\n\r", (int)local_SensorFusedReadings_t.pitch, (int)local_SensorFusedReadings_t.roll, (int)local_SensorFusedReadings_t.yaw, (int)local_SensorFusedReadings_t.vertical_velocity);
                // printf("%d,%d,%d,%d\n\r", (int)roll_pid.error, (int)pitch_pid.error, (int)yaw_pid.error, (int)thrust_pid.error);

                // TODO: examine system response


            }

        }

    }
}

/************************************************************************/
/**
 * @brief: main function of the drone board
*/
int main(void)
{

    // Initialize the sensor data collectors
    HAL_WRAPPER_Pressure_t ref_pressure_t = {0};
    RawSensorDataItem_t raw_data = {0};
    // read the start pressure
    HAL_WRAPPER_ReadPressure(&ref_pressure_t);

    // Initialize sensor fusion
    SensorFusionDataItem_t local_temp_t = {0};
    SensorFusionDataItem_t fused_data = {0};
    DroneToAppDataItem_t local_DataToSendtoApp_t = {0};
    // Initialize 2d-kalman filter matrices
    Altitude_Kalman_2D_init();

   // create a task for communication with app board


    // create a task for master


    // start the schedular


    while (1)
    {
        /************************************************ Collect Sensors data *************************************************/
        // read accelerometer data
        HAL_WRAPPER_ReadAcc(&(raw_data.Acc));
        
        // read gyroscope data
        HAL_WRAPPER_ReadGyro(&(raw_data.Gyro));

        // read magnetometer data
        HAL_WRAPPER_ReadMagnet(&(raw_data.Magnet));

        // read barometer data
        // HAL_WRAPPER_ReadPressure(&(raw_data.Pressure));

        // read temperature data
        // HAL_WRAPPER_ReadTemperature(&(raw_data.Temperature));

        // read altitude from barometer
        HAL_WRAPPER_ReadAltitude(&(raw_data.Altitude), &ref_pressure_t);

        // read battery charge
        // HAL_WRAPPER_GetBatteryCharge(&(raw_data.Battery));

// FOR SERIAL PLOTTER
    //    printf("%d,%d,%d\r\n", raw_data.Magnet.x, raw_data.Magnet.y, raw_data.Magnet.z);


        
        /********************************************** Perform Sensor fusion **************************************************/
        // apply kalman filter with sensor fusion
        SensorFuseWithKalman(&raw_data, &local_temp_t);

        // actual measurements showed that roll and pitch are reversed and pitch is in negative
        fused_data.pitch = -local_temp_t.roll;
        fused_data.roll = local_temp_t.pitch;
        fused_data.yaw = local_temp_t.yaw;
        fused_data.yaw_rate = local_temp_t.yaw_rate;
        fused_data.altitude = local_temp_t.altitude;
        fused_data.vertical_velocity = local_temp_t.vertical_velocity;

        // Send some info to the application board
        // set type of data to send
        local_DataToSendtoApp_t.data.type = DATA_TYPE_INFO;

        // read temperature data
        local_DataToSendtoApp_t.data.data.info.temperature = raw_data.Temperature.temperature;

        // read battery charge
        local_DataToSendtoApp_t.data.data.info.batteryCharge = raw_data.Battery.batteryCharge;

        // assign current altitude
        local_DataToSendtoApp_t.data.data.info.altitude = raw_data.Altitude.ultrasonic_altitude / 100.0;

        // assign distanceToOrigin (TODO)
        local_DataToSendtoApp_t.data.data.info.distanceToOrigin = 1.5;       

        // push data into queue to be sent to the app board and notify the AppComm with new data (TODO)




    }
}


/*************** END OF FUNCTIONS ***************************************************************************/
