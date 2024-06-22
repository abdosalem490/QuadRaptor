/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   reg and bit position defs for BMP280                                                                        |
 * |    @file           :   bmp_def.h                                                                                                   |
 * |    @author         :   Ahmed Fawzy                                                                                                 |
 * |    @origin_date    :   22/06/2024                                                                                                  |
 * |    @version        :   1.0.0                                                                                                       |
 * |    @tool_chain     :   RISC-V Cross GCC                                                                                            |
 * |    @compiler       :   GCC                                                                                                         |
 * |    @C_standard     :   ISO C99 (-std=c99)                                                                                          |
 * |    @target         :   CH32V203C8T6                                                                                                |
 * |    @notes          :   None                                                                                                        |
 * |    @license        :   MIT License                                                                                                 |
 * |    @brief          :   this header file contains bit position definition and register addresses for interface with BMP280          |
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
 * |    22/06/2023      1.0.0           Ahmed Fawzy                     Interface Created.                                              |
 * --------------------------------------------------------------------------------------------------------------------------------------
 */


/******************************************************************************
 * Includes
 *******************************************************************************/


/******************************************************************************
 * Preprocessor Constants
 *******************************************************************************/


#ifndef USER_BMP_DEFINITIONS_H_
#define USER_BMP_DEFINITIONS_H_


/*------------- REGISTERS --------------------------*/
#define DIG_T1          0x88
#define DIG_T2          0x8A
#define DIG_T3          0x8C
#define DIG_P1          0x8E
#define DIG_P2          0x90
#define DIG_P3          0x92
#define DIG_P4          0x94
#define DIG_P5          0x96
#define DIG_P6          0x98
#define DIG_P7          0x9A
#define DIG_P8          0x9C
#define DIG_P9          0x9E
#define DIG_H1          0xA1
#define DIG_H2          0xE1
#define DIG_H3          0xE3
#define DIG_H4          0xE4
#define DIG_H5          0xE5
#define DIG_H6          0xE7

#define CHIP_ID         0xD0
#define RESET_REG       0xE0
#define STATUS          0xF3
#define CTRL_HUM        0xF2
#define CTRL_MEAS       0xF4
#define CONFIG          0xF5
#define PRESS_MSB       0xF7
#define PRESS_LSB       0xF8
#define PRESS_XLSB      0xF9
#define TEMP_MSB        0xFA
#define TEMP_LSB        0xFB
#define TEMP_XLSB       0xFC
#define HUM_MSB         0xFD
#define HUM_LSB         0xFE

/*------------- BIT MASKS --------------------------*/
#define CHIP_ID_VAL         0x60

#define RESET_CMD           0xB6

#define STATUS_MEASURING    0x08
#define STATUS_IM_UPDATE    0x01

#define CTRL_HUM_MASK       0x07

#define CTRL_MEAS_MODE_MASK 0x03
#define CTRL_MEAS_OSRS_P_MASK 0x1C
#define CTRL_MEAS_OSRS_T_MASK 0xE0

#define CONFIG_STANDBY_MASK 0xE0
#define CONFIG_FILTER_MASK  0x1C
#define CONFIG_SPI3W_MASK   0x01


/*
 * These are the trimming values for my chip
The value of t1 = 28459
The value of t2 = 26496
The value of t3 = 50
The value of p1 = 37204
The value of p2 = -10725
The value of p3 = 3024
The value of p4 = 7864
The value of p5 = -90
The value of p6 = -7
The value of p7 = 9900
The value of p8 = -10230
The value of p9 = 4285
*/


/******************************************************************************
 * Configuration Constants
 *******************************************************************************/

/******************************************************************************
 * Macros
 *******************************************************************************/

/******************************************************************************
 * Typedefs
 *******************************************************************************/

/******************************************************************************
 * Variables
 *******************************************************************************/

/******************************************************************************
 * Function Prototypes
 *******************************************************************************/


#endif /* USER_BMP_DEFINITIONS_H_ */
