/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   PID utility for more stable motion                                                                          |
 * |    @file           :   pid.h                                                                                                       |
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


#ifndef PID_H_
#define PID_H_

/******************************************************************************
 * Includes
 *******************************************************************************/

/******************************************************************************
 * Preprocessor Constants
 *******************************************************************************/


/******************************************************************************
 * Configuration Constants
 *******************************************************************************/

// PID parameters
//#define ROLL_KP 0.00043714285 // 0.10 // 0.0876327724816902
//#define ROLL_KI 0.00255 // 0.001  // 0.0268134216559389
//#define ROLL_KD	0.00002571429 // 0.5 // 0.0243843061996966
//
//#define PITCH_KP 0.00043714285 //0.10 // 0.0876327724816902
//#define PITCH_KI 0.00255 // 0.001 // 0.0268134216559389
//#define PITCH_KD 0.00002571429 // 0.5 // 0.0243843061996966


#define KP 0.1
#define KI 0.000855
#define KD 1

#define ROLL_KP KP 	// 0.0876327724816902
#define ROLL_KI KI  // 0.0268134216559389
#define ROLL_KD	KD  // 0.0243843061996966

#define PITCH_KP KP // 0.0876327724816902
#define PITCH_KI KI // 0.0268134216559389
#define PITCH_KD KD // 0.0243843061996966

// YAW rate range from -500 to 500
#define YAW_KP 0.001
#define YAW_KI 0.00005
#define YAW_KD 0

#define THRUST_KP 0.995894926271201
#define THRUST_KI 0.304718769324561
#define THRUST_KD 0.27711330062044

// blocks extra parameters
#define ROLL_INTEGRAL_MIN	-100000
#define ROLL_INTEGRAL_MAX	100000
#define ROLL_BLOCK_WEIGHT	1			/**< TODO: make the weight = 1 after the end of experiment for production*/

#define PITCH_INTEGRAL_MIN	-100000
#define PITCH_INTEGRAL_MAX	100000
#define PITCH_BLOCK_WEIGHT	1			/**< TODO: make the weight = 1 after the end of experiment for production*/

#define YAW_INTEGRAL_MIN	-100000
#define YAW_INTEGRAL_MAX	100000
#define YAW_BLOCK_WEIGHT	1 //0.001	/**< TODO: make the weight = 1 after the end of experiment for production*/

#define THRUST_INTEGRAL_MIN	-11000
#define THRUST_INTEGRAL_MAX	11000
#define THRUST_BLOCK_WEIGHT	0.01		/**< TODO: make the weight = 1 after the end of experiment for production*/


/******************************************************************************
 * Macros
 *******************************************************************************/

/******************************************************************************
 * Typedefs
 *******************************************************************************/

/************
 * @brief: pid object
 * @param: kp: proportional gain
 * @param: ki: integral gain
 * @param: kd: derivative gain
 * @param: error: current error
 * @param: lastError: last error
 * @param: integral: integral term
 * @param: output: output
 **************/
typedef struct{

	// main pid parameters
    float kp;
    float ki;
    float kd;
    float error;
    float lastError;
    float integral;
    float output;

    // extra block infos
    float maxIntegralVal;
    float minIntegralVal;
    float blockWeight;

}pid_obj_t;

/******************************************************************************
 * Variables
 *******************************************************************************/

/******************************************************************************
 * Function Prototypes
 *******************************************************************************/
void pid_ctrl(pid_obj_t *pid_obj);

/*** End of File **************************************************************/
#endif /*PID_H_*/
