/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   source file for ESCs                                                                                        |
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
 * |    @brief          :   this file is the source code file for ESCs that controls brushless dc motors                                |
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

/******************************************************************************
 * Includes
 *******************************************************************************/

/**
 * @reason: contains definitions for standard integers
 */
#include "stdint.h"

/**
 * @reason: header file for ESC
 */
#include "ESC.h"

/**
 * @reason: contains wrapper function to deal with timers PWMs
 */
#include "MCAL_wrapper.h"

/**
 * @reason: contains delay functionality
 */
#include "debug.h"


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

#include "ch32v20x_gpio.h"
/**
 * 
 */
HAL_ESC_ErrStates_t HAL_ESC_init(void)
{

    // set all the motors to low for a period of time
    MCAL_WRAPEPR_TIM4_PWM_OUT(MCAL_WRAPPER_TIM_CH1, 0);
    MCAL_WRAPEPR_TIM4_PWM_OUT(MCAL_WRAPPER_TIM_CH2, 0);
    MCAL_WRAPEPR_TIM4_PWM_OUT(MCAL_WRAPPER_TIM_CH3, 0);
    MCAL_WRAPEPR_TIM4_PWM_OUT(MCAL_WRAPPER_TIM_CH4, 0);

//    // wait for some time
//    Delay_Ms(5000);
//
//    // set all the motors to high for a period of time then to low
//    MCAL_WRAPEPR_TIM4_PWM_OUT(MCAL_WRAPPER_TIM_CH1, 100);
//    MCAL_WRAPEPR_TIM4_PWM_OUT(MCAL_WRAPPER_TIM_CH2, 100);
//    MCAL_WRAPEPR_TIM4_PWM_OUT(MCAL_WRAPPER_TIM_CH3, 100);
//    MCAL_WRAPEPR_TIM4_PWM_OUT(MCAL_WRAPPER_TIM_CH4, 100);
//
//    // wait for some time
//    Delay_Ms(5000);
//
//    // set all the motors to low
//    MCAL_WRAPEPR_TIM4_PWM_OUT(MCAL_WRAPPER_TIM_CH1, 0);
//    MCAL_WRAPEPR_TIM4_PWM_OUT(MCAL_WRAPPER_TIM_CH2, 0);
//    MCAL_WRAPEPR_TIM4_PWM_OUT(MCAL_WRAPPER_TIM_CH3, 0);
//    MCAL_WRAPEPR_TIM4_PWM_OUT(MCAL_WRAPPER_TIM_CH4, 0);

    // wait for some time
    Delay_Ms(5000);

    MCAL_WRAPEPR_TIM4_PWM_OUT(MCAL_WRAPPER_TIM_CH1, 50);
    MCAL_WRAPEPR_TIM4_PWM_OUT(MCAL_WRAPPER_TIM_CH2, 50);
    MCAL_WRAPEPR_TIM4_PWM_OUT(MCAL_WRAPPER_TIM_CH3, 50);
    MCAL_WRAPEPR_TIM4_PWM_OUT(MCAL_WRAPPER_TIM_CH4, 50);

    return HAL_ESC_OK;
}

/**
 * 
 */
HAL_ESC_ErrStates_t HAL_ESC_setSpeed(HAL_ESC_MotorNum_t arg_MotorNum_t, uint8_t motorSpeed)
{
    if(arg_MotorNum_t > HAL_ESC_MOTOR_BOTTOM_RIGHT || motorSpeed > 100)
    {
        return HAL_ESC_ERR_INVALID_PARAMS;
    }

    switch (arg_MotorNum_t)
    {
    case HAL_ESC_MOTOR_TOP_LEFT:
        MCAL_WRAPEPR_TIM4_PWM_OUT(MCAL_WRAPPER_TIM_CH1, motorSpeed);
        break;
    case HAL_ESC_MOTOR_TOP_RIGHT:
        MCAL_WRAPEPR_TIM4_PWM_OUT(MCAL_WRAPPER_TIM_CH2, motorSpeed);
        break;
    case HAL_ESC_MOTOR_BOTTOM_LEFT:
        MCAL_WRAPEPR_TIM4_PWM_OUT(MCAL_WRAPPER_TIM_CH3, motorSpeed);
        break;
    case HAL_ESC_MOTOR_BOTTOM_RIGHT:
        MCAL_WRAPEPR_TIM4_PWM_OUT(MCAL_WRAPPER_TIM_CH4, motorSpeed);
        break;    
    default:
        break;
    }

    return HAL_ESC_OK;
}

/*************** END OF FUNCTIONS ***************************************************************************/
