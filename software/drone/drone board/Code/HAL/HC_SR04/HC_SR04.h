/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   header file for the HC_SR04 ultrasonic sensor                                                               |
 * |    @file           :   HC_SR04.h                                                                                                   |
 * |    @author         :   Abdelrahman Mohamed Salem                                                                                   |
 * |    @origin_date    :   26/05/2024                                                                                                  |
 * |    @version        :   1.0.0                                                                                                       |
 * |    @tool_chain     :   RISC-V Cross GCC                                                                                            |
 * |    @compiler       :   GCC                                                                                                         |
 * |    @C_standard     :   ISO C99 (-std=c99)                                                                                          |
 * |    @target         :   CH32V203C8T6                                                                                                |
 * |    @notes          :   None                                                                                                        |
 * |    @license        :   MIT License                                                                                                 |
 * |    @brief          :   this file is the header file for HC SR04 ultrasonic sensor                                                  |
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


#ifndef HC_SR04_H_
#define HC_SR04_H_

/******************************************************************************
 * Includes
 *******************************************************************************/

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
 * @enum: HAL_HCSR04_ErrStates_t
 * @brief: contains all possible errors that can result from dealing with HC SR04 ultrasonic sensor.
 */
typedef enum
{
    HAL_HCSR04_OK,                  /**< it means everything has gone as intended so no errors*/
    HAL_HCSR04_ERR_INVALID_PARAMS,  /**< it means that the supplied parameters of the function are invalid*/
    HAL_HCSR04_ERR_ECHO,            /**< it means that there is some error with the echo signal*/
} HAL_HCSR04_ErrStates_t;


/******************************************************************************
 * Variables
 *******************************************************************************/

/******************************************************************************
 * Function Prototypes
 *******************************************************************************/

/**
 *  \b function                                 :       HAL_HCSR04_ErrStates_t HAL_HCSR04_GetDistance();
 *  \b Description                              :       this functions is to compute distance measured by ultrasonic sensor.
 *  @param  arg_pf32Distance [OUT]              :       the returned measured distance in centimeters.
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       make sure to call configure the configuration file in the current directory.
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       it return one of error states indicating whether a failure or success happened (refer to @HAL_HCSR04_ErrStates_t in "HC_SR04.h")
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * #include "HC_SR04.h"
 * 
 * int main() {
 * float Distance = 0.0;
 * HAL_HCSR04_ErrStates_t local_errSate_t = HAL_HCSR04_GetDistance(&Distance);
 * if(SERVICE_RTOS_STAT_OK == local_errSate_t)
 * {
 *  // do what you want to do
 * }
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 26/06/2024 </td><td> 1.0.0            </td><td> AMS      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
HAL_HCSR04_ErrStates_t HAL_HCSR04_GetDistance(float* arg_pf32Distance);

/*** End of File **************************************************************/
#endif /*HC_SR04_H_*/