/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   ADXL345 Digital Accelerometer                                                                               |
 * |    @file           :   ADXL345_private.h                                                                                           |
 * |    @author         :   Abdelrahman Mohamed Salem                                                                                   |
 * |    @origin_date    :   15/03/2024                                                                                                  |
 * |    @version        :   1.0.0                                                                                                       |
 * |    @tool_chain     :   RISC-V Cross GCC                                                                                            |
 * |    @compiler       :   GCC                                                                                                         |
 * |    @C_standard     :   ISO C99 (-std=c99)                                                                                          |
 * |    @target         :   CH32V203C8T6                                                                                                |
 * |    @notes          :   None                                                                                                        |
 * |    @license        :   MIT License                                                                                                 |
 * |    @brief          :   this file contains private functions and definitions that deals with ADXL345.                               |
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
 * |    15/03/2024      1.0.0           Abdelrahman Mohamed Salem       Interface Created.                                              |
 * --------------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef HAL_ADXL345_PRIVATE_H_
#define HAL_ADXL345_PRIVATE_H_

/******************************************************************************
 * Includes
 *******************************************************************************/
/**
 * @reason: contains definition for function callback
 */
#include "common.h"

/**
 * @reason: contains definitions for standard integers
 */
#include "stdint.h"

/**
 * @reason: contains all math bits functions
 */
#include "math_btt.h"

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
 * Function Prototypes
 *******************************************************************************/

/**
 * @brief: used to write data to single register ADXL address
*/
void HAL_ADXL345_Write_Single(MCAL_CONFIG_SPI_t* arg_pADXLSPI, uint8_t arg_u8Register_Address, uint8_t arg_u8Data);

/**
 * @brief: used to read register content from a single register ADXL register
*/
uint8_t HAL_ADXL345_Read_Single(MCAL_CONFIG_SPI_t* arg_pADXLSPI, uint8_t arg_u8RegisterAddress);

/**
 * @brief: make a use of ADXL345 feature to write data to consecutive ADXL345 register addresses without writing address of the register every time as we just insert the initial register address and any sequence writing on SPI will shift that pointer automatically and write data on SPI on the next ADXL345 register address
*/
void HAL_ADXL345_Write_Mutliple(MCAL_CONFIG_SPI_t* arg_pADXLSPI, uint8_t arg_u8RegisterStartAddress, uint8_t* arg_pu8Data, uint8_t arg_u8Len);



/*** End of File **************************************************************/
#endif /*HAL_ADXL345_PRIVATE_H_*/
