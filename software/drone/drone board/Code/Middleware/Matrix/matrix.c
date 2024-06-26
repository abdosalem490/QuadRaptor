/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   Utility to handle 2d matrix operations                                                                      |
 * |    @file           :   matrix.c                                                                                                    |
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


/******************************************************************************
 * Includes
 *******************************************************************************/

/**
 * 
 */
#include "matrix.h"

/**
 * 
 */
#include <math.h>

/**
 * @reason: for malloc and free functions
 */
#include <stdlib.h>

/**
 * @reaon: contains standard integer definitions
 */
#include "stdint.h"

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
void matrix_create(matrix_2d_t* matrix, int rows, int cols, float* values)
{
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->values = values;
}

/**
 *
 */
void matrix_destroy(matrix_2d_t* matrix)
{
    free(matrix->values);
    free(matrix);
}

/**
 *
 */
uint8_t matrix_add(matrix_2d_t* matrix1, matrix_2d_t* matrix2, matrix_2d_t* result)
{
    if(matrix1->rows != matrix2->rows || matrix1->cols != matrix2->cols)
    {
        return 0;
    }

    result->rows = matrix1->rows;
    result->cols = matrix1->cols;
    result->values = (float*)malloc(result->rows * result->cols * sizeof(float));

    for(int i = 0; i < matrix1->rows; i++)
    {
        for(int j = 0; j < matrix1->cols; j++)
        {
            result->values[i * result->cols + j] = matrix1->values[i * matrix1->cols + j] + matrix2->values[i * matrix2->cols + j];
        }
    }

    return 1;
}

/**
 *
 */
uint8_t matrix_subtract(matrix_2d_t* matrix1, matrix_2d_t* matrix2, matrix_2d_t* result)
{
    if(matrix1->rows != matrix2->rows || matrix1->cols != matrix2->cols)
    {
        return 0;
    }

    result->rows = matrix1->rows;
    result->cols = matrix1->cols;
    result->values = (float*)malloc(result->rows * result->cols * sizeof(float));

    for(int i = 0; i < matrix1->rows; i++)
    {
        for(int j = 0; j < matrix1->cols; j++)
        {
            result->values[i * result->cols + j] = matrix1->values[i * matrix1->cols + j] - matrix2->values[i * matrix2->cols + j];
        }
    }

    return 1;
}

/**
 *
 */
uint8_t matrix_multiply(matrix_2d_t* matrix1, matrix_2d_t* matrix2, matrix_2d_t* result)
{
    if(matrix1->cols != matrix2->rows)
    {
        return 0;
    }

    result->rows = matrix1->rows;
    result->cols = matrix2->cols;
    result->values = (float*)malloc(result->rows * result->cols * sizeof(float));

    for(int i = 0; i < matrix1->rows; i++)
    {
        for(int j = 0; j < matrix2->cols; j++)
        {
            result->values[i * result->cols + j] = 0;
            for(int k = 0; k < matrix1->cols; k++)
            {
                result->values[i * result->cols + j] += matrix1->values[i * matrix1->cols + k] * matrix2->values[k * matrix2->cols + j];
            }
        }
    }

    return 1;
}

/**
 *
 */
void matrix_transpose(matrix_2d_t* matrix, matrix_2d_t* result)
{
    result->rows = matrix->cols;
    result->cols = matrix->rows;
    result->values = (float*)malloc(result->rows * result->cols * sizeof(float));

    for(int i = 0; i < matrix->rows; i++)
    {
        for(int j = 0; j < matrix->cols; j++)
        {
            result->values[j * result->cols + i] = matrix->values[i * matrix->cols + j];
        }
    }
}

/*************** END OF FUNCTIONS ***************************************************************************/
