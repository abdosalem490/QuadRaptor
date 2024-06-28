/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   source file for the HC_SR04 ultrasonic sensor                                                               |
 * |    @file           :   HC_SR04.c                                                                                                   |
 * |    @author         :   Abdelrahman Mohamed Salem                                                                                   |
 * |    @origin_date    :   26/06/2024                                                                                                  |
 * |    @version        :   1.0.0                                                                                                       |
 * |    @tool_chain     :   RISC-V Cross GCC                                                                                            |
 * |    @compiler       :   GCC                                                                                                         |
 * |    @C_standard     :   ISO C99 (-std=c99)                                                                                          |
 * |    @target         :   CH32V203C8T6                                                                                                |
 * |    @notes          :   None                                                                                                        |
 * |    @license        :   MIT License                                                                                                 |
 * |    @brief          :   this file is the source code file for HC SR04 ultrasonic sensor                                             |
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
 * |    26/06/2023      1.0.0           Abdelrahman Mohamed Salem       file Created.                                                   |
 * --------------------------------------------------------------------------------------------------------------------------------------
 */

 

/******************************************************************************
 * Includes
 *******************************************************************************/

/**
 * @reason: contains header file which has main functionality 
 */
#include "HC_SR04.h"

/**
 * @reason: contains standard integer definitions
 */
#include "stdint.h"

/**
 * @reason: contains MCU wrapper functions 
 */
#include "MCAL_wrapper.h"

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


/**
 * 
 */
HAL_HCSR04_ErrStates_t HAL_HCSR04_GetDistance(float* arg_pf32Distance)
{
    // local variables
    uint32_t timeInuS = 0;

    // insert pulse onto trig pin
    MCAL_WRAPPER_HCSR04Trig(10);

    // measure pulse width on the echo pin
    MCAL_WRAPPER_ErrStat_t local_errState = MCAL_WRAPPER_TIM1GetWidthOfPulse(&timeInuS);

    
    if(MCAL_WRAPPER_STAT_OK == local_errState)
    {
        // compute distance using the equation
        *arg_pf32Distance = timeInuS * 0.017;

        return HAL_HCSR04_OK;
    }
    else
    {
        // assign high value for distance to indicate it's invalid
        *arg_pf32Distance = 800; // 800 cm

        return HAL_HCSR04_ERR_ECHO;
    }
    
}




/*************** END OF FUNCTIONS ***************************************************************************/
