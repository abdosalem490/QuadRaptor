/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   Utility to handle 2d matrix operations                                                                      |
 * |    @file           :   matrix.h                                                                                                    |
 * |    @author         :   Mohab Zaghloul                                                                                              |
 * |    @origin_date    :   26/06/2024                                                                                                  |
 * |    @version        :   1.0.0                                                                                                       |
 * |    @tool_chain     :   RISC-V Cross GCC                                                                                            |
 * |    @compiler       :   GCC                                                                                                         |
 * |    @C_standard     :   ISO C99 (-std=c99)                                                                                          |
 * |    @target         :   CH32V203C8T6                                                                                                |
 * |    @notes          :   None                                                                                                        |
 * |    @license        :   MIT License                                                                                                 |
 * |    @brief          :   this file is the main file for matrix operations                                                            |
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


#ifndef MATRIX_H_
#define MATRIX_H_

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
typedef struct{
    float * values = 0;
    int rows;
    int cols;
} matrix_2d_t;

/******************************************************************************
 * Variables
 *******************************************************************************/

/******************************************************************************
 * Function Prototypes
 *******************************************************************************/

void matrix_create(matrix_2d_t* matrix, int rows, int cols, float* values);

void matrix_destroy(matrix_2d_t* matrix);

bool matrix_add(matrix_2d_t* matrix1, matrix_2d_t* matrix2, matrix_2d_t* result);

bool matrix_subtract(matrix_2d_t* matrix1, matrix_2d_t* matrix2, matrix_2d_t* result);

bool matrix_multiply(matrix_2d_t* matrix1, matrix_2d_t* matrix2, matrix_2d_t* result);

void matrix_transpose(matrix_2d_t* matrix, matrix_2d_t* result);

/*** End of File **************************************************************/
#endif /*PID_H_*/