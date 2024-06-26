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

/************************************************************************/
/**
 * @brief: maximum speed for motors to prevent damage
*/
#define MAX_MOTOR_SPEED   75

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
    HAL_WRAPPER_Acc_t local_Acc_t = {0};
    HAL_WRAPPER_Gyro_t local_gyro_t = {0};
    HAL_WRAPPER_Magnet_t local_magnet_t = {0};
    HAL_WRAPPER_Pressure_t local_pressure_t = {0};
    HAL_WRAPPER_Pressure_t ref_pressure_t = {0};
    HAL_WRAPPER_Temperature_t local_temperature_t = {0};
    HAL_WRAPPER_Altitude_t local_altitude_t = {0};

    RawSensorDataItem_t local_out_t = {0};


    HAL_WRAPPER_ReadPressure(&ref_pressure_t);

    while (1)
    {
        // read accelerometer data
        HAL_WRAPPER_ReadAcc(&local_Acc_t);
        
        // read gyroscope data
        HAL_WRAPPER_ReadGyro(&local_gyro_t);

        // read magnetometer data
        HAL_WRAPPER_ReadMagnet(&local_magnet_t);

        // read barometer data
        HAL_WRAPPER_ReadPressure(&local_pressure_t);

        // read temperature data
        HAL_WRAPPER_ReadTemperature(&local_temperature_t);

        // read altitude from barometer
        HAL_WRAPPER_ReadAltitude(&local_altitude_t, &ref_pressure_t);

        // read battery charge


// FOR SERIAL MONITOR
//        printf("MPU6050 ACC: x: %f,  y: %f,  z: %f\r\n", local_Acc_t.x, local_Acc_t.y, local_Acc_t.z);
//        printf("MPU6050 Gyro: roll: %f,  pitch: %f,  yaw: %f\r\n", local_gyro_t.roll, local_gyro_t.pitch, local_gyro_t.yaw);
//        printf("MPU6050 ACC: x: %f,  y: %f,  z: %f\r\n", local_Acc_t.x, local_Acc_t.y, local_Acc_t.z);
// printf("MPU6050 ACC: x: %f,  y: %f,  z: %f\r\n", local_Acc_t.x, local_Acc_t.y, local_Acc_t.z);

// FOR SERIAL PLOTTER
    //    printf("%d,%d,%d\r\n", local_magnet_t.x, local_magnet_t.y, local_magnet_t.z);

        // assign variables
        local_out_t.Acc = local_Acc_t;
        local_out_t.Gyro = local_gyro_t;
        local_out_t.Magnet = local_magnet_t;
        local_out_t.Pressure = local_pressure_t;
        local_out_t.Temperature = local_temperature_t;

        // push the data into the queue for fusion
        SERVICE_RTOS_AppendToBlockingQueue(1000, (const void *) &local_out_t, queue_RawSensorData_Handle_t);

        // sleep for 5 ms
        SERVICE_RTOS_BlockFor(SENSOR_SAMPLE_PERIOD);
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
                local_DataToSendtoApp_t.data.data.info.batteryCharge = 76;

                // assign current altitude
                local_DataToSendtoApp_t.data.data.info.altitude = 12.3;

                // assign distanceToOrigin (TODO)
                local_DataToSendtoApp_t.data.data.info.distanceToOrigin = 1.5;       

                // push data into queue to be sent to the app board and notify the AppComm with new data
                SERVICE_RTOS_AppendToBlockingQueue(1000, (const void *) &local_DataToSendtoApp_t, queue_DroneCommToApp_Handle_t);
                SERVICE_RTOS_Notify(task_AppComm_Handle_t, LIB_CONSTANTS_DISABLED);       
            }

            // FOR SERIAL PLOTTER
//           printf("%f,%f,%f\n\r", local_out_t.pitch, local_out_t.roll, local_out_t.yaw);

            // append to the queue the the current state
            SERVICE_RTOS_AppendToBlockingQueue(1000, (const void *) &local_out_t, queue_FusedSensorData_Handle_t);
            SERVICE_RTOS_Notify(task_Master_Handle_t, LIB_CONSTANTS_DISABLED); 

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
                        SERVICE_RTOS_AppendToBlockingQueue(1000, (const void *) &global_MsgToRec_t, queue_AppCommToDrone_Handle_t);
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
            SERVICE_RTOS_AppendToBlockingQueue(1000, (const void *) &global_MsgToRec_t, queue_AppCommToDrone_Handle_t);
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
    // needed variables
    HAL_WRAPPER_MotorSpeeds_t local_MotorSpeeds = {0};
    SERVICE_RTOS_ErrStat_t local_RTOSErrStatus = SERVICE_RTOS_STAT_OK;
    SensorFusionDataItem_t local_SensorFusedReadings_t = {0};
    uint8_t local_u8LenOfRemaining = 0;
    AppToDroneDataItem_t local_RCRequiredVal = {0};
    pid_obj_t roll_pid = {0};
    pid_obj_t pitch_pid = {0};
    pid_obj_t yaw_pid = {0};
    pid_obj_t thrust_pid = {0};

    
    //                      SOME INITIALIZATION 
    // INITIALIZATION CAN'T BE DONE IN MAIN AS SCHEDULAR HAS TO START FIRST BEFORE DOING 
    // ANYTHING (RECEIVING INTERRUPTS HAS TO WAIT BEFORE INITIALIZING)
    /************************************************************************/
    // assign pointers and lengths of data to be always received
    global_AppCommMsg_t.dataToReceive = (uint8_t*) &global_MsgToRec_t.data;
    global_AppCommMsg_t.dataToReceiveLen = sizeof(global_MsgToRec_t.data);
    global_AppCommMsg_t.dataIsToReceive = 0;
    global_AppCommMsg_t.IsDataReceived = 0;
    /************************************************************************/
    // initialize the pid controllers
    roll_pid.kp = ROLL_KP;      roll_pid.ki = ROLL_KI;       roll_pid.kd = ROLL_KD;
    pitch_pid.kp = PITCH_KP;    pitch_pid.ki = PITCH_KI;     pitch_pid.kd = PITCH_KD;
    yaw_pid.kp = YAW_KP;        yaw_pid.ki = YAW_KI;         yaw_pid.kd = YAW_KD;
    thrust_pid.kp = THRUST_KP;  thrust_pid.ki = THRUST_KI;   thrust_pid.kd = THRUST_KD;
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

    // TODO: wait 5 seconds for the ESCs


    // TODO: comment the below line
   USART_Printf_Init(115200);

   // Initialize 2d-kalman filter matrices
   Altitude_Kalman_2D_init();


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
            // printf("type = %d, roll = %d, pitch = %d, thrust = %d, yaw = %d, turnOnLeds = %d, playMusic = %d\r\n",
            // local_RCRequiredVal.data.type, local_RCRequiredVal.data.data.move.roll, local_RCRequiredVal.data.data.move.pitch,
            // local_RCRequiredVal.data.data.move.thrust, local_RCRequiredVal.data.data.move.yaw, local_RCRequiredVal.data.data.move.turnOnLeds,
            // local_RCRequiredVal.data.data.move.playMusic);
        }

        // read sensor fused readings
        local_RTOSErrStatus = SERVICE_RTOS_ReadFromBlockingQueue(0, (void *) &local_SensorFusedReadings_t, queue_FusedSensorData_Handle_t, &local_u8LenOfRemaining);

        // get sensor fused readings with Kalman filter
        if(SERVICE_RTOS_STAT_OK == local_RTOSErrStatus)
        {
            // Compute error
            roll_pid.error = local_RCRequiredVal.data.data.move.roll - local_SensorFusedReadings_t.roll;
            pitch_pid.error = local_RCRequiredVal.data.data.move.pitch - local_SensorFusedReadings_t.pitch;
            yaw_pid.error = local_RCRequiredVal.data.data.move.yaw - local_SensorFusedReadings_t.yaw;
            thrust_pid.error = local_RCRequiredVal.data.data.move.thrust - local_SensorFusedReadings_t.thrust;
            
            // apply PID to compensate error
            pid_ctrl(&roll_pid);
            pid_ctrl(&pitch_pid);
            pid_ctrl(&yaw_pid);
            pid_ctrl(&thrust_pid);

            // Motor mixing algorithm
            local_MotorSpeeds.topLeftSpeed     = thrust_pid.output - roll_pid.output + pitch_pid.output - yaw_pid.output;
            local_MotorSpeeds.topRightSpeed    = thrust_pid.output + roll_pid.output + pitch_pid.output + yaw_pid.output;
            local_MotorSpeeds.bottomLeftSpeed  = thrust_pid.output - roll_pid.output - pitch_pid.output + yaw_pid.output;
            local_MotorSpeeds.bottomRightSpeed = thrust_pid.output + roll_pid.output - pitch_pid.output - yaw_pid.output;

            // apply limits to the motor speeds
            if(local_MotorSpeeds.topLeftSpeed > MAX_MOTOR_SPEED) local_MotorSpeeds.topLeftSpeed = MAX_MOTOR_SPEED;
            if(local_MotorSpeeds.topRightSpeed > MAX_MOTOR_SPEED) local_MotorSpeeds.topRightSpeed = MAX_MOTOR_SPEED;
            if(local_MotorSpeeds.bottomLeftSpeed > MAX_MOTOR_SPEED) local_MotorSpeeds.bottomLeftSpeed = MAX_MOTOR_SPEED;
            if(local_MotorSpeeds.bottomRightSpeed > MAX_MOTOR_SPEED) local_MotorSpeeds.bottomRightSpeed = MAX_MOTOR_SPEED;
            
            // apply actions on the motors
            HAL_WRAPPER_SetESCSpeeds(&local_MotorSpeeds);
        }

        
    }
}

/************************************************************************/
/**
 * @brief: main function of the drone board
*/
int main(void)
{

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

    // create a task for fusing sensor data
    SERVICE_RTOS_TaskCreate((SERVICE_RTOS_TaskFunction_t)Task_SensorFusion,
                "Sensor Fusion",
                TASK_SENSOR_FUSION_STACK_SIZE,
                TASK_SENSOR_FUSION_PRIO,
                &task_SensorFusion_Handle_t);

   // create a task for communication with app board
   SERVICE_RTOS_TaskCreate((SERVICE_RTOS_TaskFunction_t)Task_AppComm,
               "App Communication",
               TASK_APP_COMM_STACK_SIZE,
               TASK_APP_COMM_PRIO,
               &task_AppComm_Handle_t);

    // create a task for master
    SERVICE_RTOS_TaskCreate((SERVICE_RTOS_TaskFunction_t)Task_Master,
                "Master",
                TASK_MASTER_STACK_SIZE,
                TASK_MASTER_PRIO,
                &task_Master_Handle_t);

    // start the schedular
    SERVICE_RTOS_StartSchedular();


    while (1)
    {
        printf("shouldn't run at here!!\n");
    }
}


/*************** END OF FUNCTIONS ***************************************************************************/
