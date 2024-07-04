/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   header file for ESCs                                                                                        |
 * |    @file           :   ESC.h                                                                                                       |
 * |    @author         :   Abdelrahman Mohamed Salem                                                                                   |
 * |    @origin_date    :   15/06/2024                                                                                                  |
 * |    @version        :   1.0.0                                                                                                       |
 * |    @tool_chain     :   RISC-V Cross GCC                                                                                            |
 * |    @compiler       :   GCC                                                                                                         |
 * |    @C_standard     :   ISO C99 (-std=c99)                                                                                          |
 * |    @target         :   CH32V203C8T6                                                                                                |
 * |    @notes          :   None                                                                                                        |
 * |    @license        :   MIT License                                                                                                 |
 * |    @brief          :   this file is the header for ESCs that controls brushless dc motors                                          |
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
 * |    15/06/2023      1.0.0           Abdelrahman Mohamed Salem       file Created.                                                   |
 * --------------------------------------------------------------------------------------------------------------------------------------
 */


#ifndef HAL_ESC_H_
#define HAL_ESC_H_

/******************************************************************************
 * Includes
 *******************************************************************************/

/**
 * @reason: contains definitions for standard integers
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
 * @enum: HAL_ESC_ErrStates_t
 * @brief: contains all possible errors that can result from dealing with the ESC brushless dc motor.
 */
typedef enum
{
    HAL_ESC_OK,                 /**< it means everything has gone as intended so no errors*/
    HAL_ESC_ERR_INVALID_PARAMS, /**< it means that the supplied parameters of the function are invalid*/
} HAL_ESC_ErrStates_t;


typedef enum
{
    HAL_ESC_MOTOR_TOP_LEFT,         /**< TOP LEFT motor*/
    HAL_ESC_MOTOR_TOP_RIGHT,        /**< TOP RIGHT motor*/
    HAL_ESC_MOTOR_BOTTOM_LEFT,      /**< BOTTOM LEFT motor*/
    HAL_ESC_MOTOR_BOTTOM_RIGHT,     /**< BOTTOM RIGHT motor*/
} HAL_ESC_MotorNum_t;

/******************************************************************************
 * Variables
 *******************************************************************************/

/******************************************************************************
 * Function Prototypes
 *******************************************************************************/

/**
 *  \b function                                 :       HAL_ESC_ErrStates_t HAL_ESC_init(void);
 *  \b Description                              :       this functions is used initialize ESC.
 *  @param  -                                   :       None.
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       make sure to call configure the configuration file in the current directory.
 *  \b POST-CONDITION                           :       initialized the ESC brushless dc motor drivers.
 *  @return                                     :       it return one of error states indicating whether a failure or success happened (refer to @HAL_ESC_ErrStates_t in "ESC.h")
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * #include "ESC.h"
 * 
 * 
 * int main() {
 * HAL_ESC_ErrStates_t local_TaskCreateState_t = HAL_ESC_init());
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
 * <tr><td> 15/06/2024 </td><td> 1.0.0            </td><td> AMS      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
HAL_ESC_ErrStates_t HAL_ESC_init(void);


/**
 *  \b function                                 :       HAL_ESC_ErrStates_t HAL_ESC_setSpeed(HAL_ESC_MotorNum_t arg_MotorNum_t, float motorSpeed);
 *  \b Description                              :       this functions is used change speed of motor connected to ESC.
 *  @param  arg_MotorNum_t [IN]                 :       which motor to change its speed.
 *  @param  motorSpeed [IN]                     :       percent of speed of the motor, possible values are from 0.0 to 100.0.
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       make sure to call configure the configuration file in the current directory and initialized the motor.
 *  \b POST-CONDITION                           :       motor speed is changed.
 *  @return                                     :       it return one of error states indicating whether a failure or success happened (refer to @HAL_ESC_ErrStates_t in "ESC.h")
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * #include "ESC.h"
 * 
 * 
 * int main() {
 * HAL_ESC_ErrStates_t local_TaskCreateState_t = HAL_ESC_init());
 * if(HAL_ESC_OK == local_TaskCreateState_t)
 * {
 *  local_TaskCreateState_t = HAL_ESC_setSpeed(HAL_ESC_MOTOR_TOP_LEFT, 50);
 *  if(HAL_ESC_OK == local_TaskCreateState_t)
 *  {
 *      // do what you want here
 *  }
 *  
 * }
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 15/06/2024 </td><td> 1.0.0            </td><td> AMS      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
HAL_ESC_ErrStates_t HAL_ESC_setSpeed(HAL_ESC_MotorNum_t arg_MotorNum_t, float motorSpeed);


/*** End of File **************************************************************/
#endif /*HAL_ESC_H_*/