/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   PID utility for more stable motion                                                                          |
 * |    @file           :   pid.c                                                                                                       |
 * |    @author         :   Mohab Zaghloul                                                                                              |
 * |    @origin_date    :   26/06/2024                                                                                                  |
 * |    @version        :   1.0.0                                                                                                       |
 * |    @tool_chain     :   RISC-V Cross GCC                                                                                            |
 * |    @compiler       :   GCC                                                                                                         |
 * |    @C_standard     :   ISO C99 (-std=c99)                                                                                          |
 * |    @target         :   CH32V203C8T6                                                                                                |
 * |    @notes          :   None                                                                                                        |
 * |    @license        :   MIT License                                                                                                 |
 * |    @brief          :   this file is the main file for pid control                                                                  |
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
 * |    26/06/2023      1.0.0           Mohab Zaghloul                  file Created.                                                   |
 * --------------------------------------------------------------------------------------------------------------------------------------
 */


/******************************************************************************
 * Includes
 *******************************************************************************/

/**
 * 
 */
#include "pid.h"

/**
 * 
 */
#include "main.h"

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
void pid_ctrl(pid_obj_t *pid_obj)
{
    pid_obj->integral += pid_obj->error;

    // check if we reached min or max possible values for error
    if(pid_obj->integral > pid_obj->maxIntegralVal)
    {
        pid_obj->integral = pid_obj->maxIntegralVal;
    }
    else if(pid_obj->integral < pid_obj->minIntegralVal)
    {
        pid_obj->integral = pid_obj->minIntegralVal;
    }
    else
    {
        // do nothing
    }

    pid_obj->output = pid_obj->blockWeight * (pid_obj->kp * pid_obj->error + pid_obj->ki * pid_obj->integral + pid_obj->kd * (pid_obj->error - pid_obj->lastError));
    pid_obj->lastError = pid_obj->error;
}


/*************** END OF FUNCTIONS ***************************************************************************/
