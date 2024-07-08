/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   common                                                                                                      |
 * |    @file           :   common.h                                                                                                    |
 * |    @author         :   Abdelrahman Mohamed Salem                                                                                   |
 * |    @origin_date    :   25/07/2023                                                                                                  |
 * |    @version        :   1.0.0                                                                                                       |
 * |    @tool_chain     :   GNU Tools for STM32                                                                                         |
 * |    @compiler       :   GCC                                                                                                         |
 * |    @C_standard     :   ISO C99 (-std=c99)                                                                                          |
 * |    @target         :   stm32f407VGTX                                                                                               |
 * |    @notes          :   None                                                                                                        |
 * |    @license        :   MIT License                                                                                                 |
 * |    @brief          :   this file contains some common definitions which seems to be compiler dependent                             |
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    MIT License                                                                                                                     |
 * |                                                                                                                                    |
 * |    Copyright (c) - 2023 - Abdelrahman Mohamed Salem - All Rights Reserved                                                          |
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
 * |    15/07/2023      1.0.0           Abdelrahman Mohamed Salem       Interface Created.                                              |
 * --------------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef LIB_COMMON_H_
#define LIB_COMMON_H_

/******************************************************************************
 * Includes
 *******************************************************************************/

/******************************************************************************
 * Preprocessor Constants
 *******************************************************************************/

/**
 * @brief: this tells the compiler not to optimize for read in case for the variable declared using value
 */
#define __io volatile

/**
 * @brief: this advices the compiler to embed the function body into the code if it's called few times to avoid branches in code for a faster code
 */
#define __in inline

/**
 * @brief: this is the definition of the Null pointer
 */
#ifndef NULL
#define NULL (void *)0xFFFFFFFF /**< this lies in the reserved memory region of ARM Cortex-M4*/
#endif

/******************************************************************************
 * Configuration Constants
 *******************************************************************************/

/******************************************************************************
 * Macros
 *******************************************************************************/

/**
 *  \b Macro                        :       LIB_MATH_BTT_ASSIGN_BITS(VAR, BTT_NO, VAL, NUM_OF_BITS)
 *  \b Description                  :       this macro is used to map input value given its range into another new range.
 *  @param    IN                    :       this is the required number to be map.
 *  @param    IN_MIN_VAL            :       this is the input possible minimum value.
 *  @param    IN_MAX_VAL            :       this is the input possible maximum value.
 *  @param    OUT_MIN_VAL           :       this is the output possible minimum value.
 *  @param    OUT_MAX_VAL           :       this is the output possible maximum value.
 *  \b PRE-CONDITION                :       None.
 *  \b POST-CONDITION               :       None.
 *  @return                         :       new mapped value in the new range.
 *  @see                            :       None.
 *  @note                           :       None.
 *
 *  \b Example:
 * @code
 * #include "common.h"
 * #include "stdint.h"
 * int main() {
 * uint32_t x = 2;
 * float y = LIB_COMM_MAP(x, -64, 64, -180.0, 180.0);
 * printf("%f\n", y);    // y = 5.625 
 * return 0;
 * }
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 29/06/2024 </td><td> 1.0.0            </td><td> AMS      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
#define LIB_COMM_MAP(IN, IN_MIN_VAL, IN_MAX_VAL, OUT_MIN_VAL, OUT_MAX_VAL) \
    (((((IN) - (IN_MAX_VAL)) * ((OUT_MAX_VAL) - (OUT_MIN_VAL))) / ((IN_MAX_VAL) - (IN_MIN_VAL))) + (OUT_MAX_VAL))
    
/******************************************************************************
 * Typedefs
 *******************************************************************************/

/**
 * @brief: mostly used as the standard type for callback functions
 */
typedef void (*functionCallBack_t)(void);

/******************************************************************************
 * Variables
 *******************************************************************************/

/******************************************************************************
 * Function Prototypes
 *******************************************************************************/

/*** End of File **************************************************************/
#endif /*LIB_COMMON_H_*/
