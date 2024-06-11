/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   Wrapper File for RTOS function                                                                              |
 * |    @file           :   Service_RTOS_wrapper.h                                                                                      |
 * |    @author         :   Abdelrahman Mohamed Salem                                                                                   |
 * |    @origin_date    :   18/05/2024                                                                                                  |
 * |    @version        :   1.0.0                                                                                                       |
 * |    @tool_chain     :   RISC-V Cross GCC                                                                                            |
 * |    @compiler       :   GCC                                                                                                         |
 * |    @C_standard     :   ISO C99 (-std=c99)                                                                                          |
 * |    @target         :   CH32V203C8T6                                                                                                |
 * |    @notes          :   None                                                                                                        |
 * |    @license        :   MIT License                                                                                                 |
 * |    @brief          :   this header file contains useful functions to easily change RTOS without changing much in code              |
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
 * |    18/05/2023      1.0.0           Abdelrahman Mohamed Salem       Interface Created.                                              |
 * |    11/06/2023      1.0.0           Abdelrahman Mohamed Salem       created 'MCAL_WRAPEPR_SPI_POLL_TRANSFER'.                       |
 * --------------------------------------------------------------------------------------------------------------------------------------
 */
 

/******************************************************************************
 * Includes
 *******************************************************************************/

/**
 * @reason: contains definitions and decelerations for functions/variables for MCAL wrapper
*/
#include "MCAL_wrapper.h"

/**
 * @reason: contains GPIO functionality
 */
#include "ch32v20x_gpio.h"

/**
 * @reason: contains SPI functionality
 */
#include "ch32v20x_spi.h"

/**
 * @reason: contains common definitions
 */
#include "common.h"

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
MCAL_WRAPPER_ErrStat_t MCAL_WRAPEPR_SPI_POLL_TRANSFER(MCAL_CONFIG_SPI_t *arg_pSPI, uint16_t* args_pu16InData, uint16_t arg_u16Len, uint16_t *args_pu16OutData)
{
    if(NULL == arg_pSPI || NULL == args_pu16InData)
        return MCAL_WRAPPER_STAT_INVALID_PARAMS;

    GPIO_ResetBits(arg_pSPI->GPIO, arg_pSPI->SlavePin);

    while (arg_u16Len > 0)
    {
        SPI_I2S_SendData(arg_pSPI->SPI, *args_pu16InData);
        args_pu16InData++;
        if(args_pu16OutData != NULL)
            *args_pu16OutData = SPI_I2S_ReceiveData(arg_pSPI->SPI);
        while(SPI_I2S_GetFlagStatus(arg_pSPI->SPI, SPI_I2S_FLAG_TXE) != SET);
        while(SPI_I2S_GetFlagStatus(arg_pSPI->SPI, SPI_I2S_FLAG_BSY) == SET);
        arg_u16Len--;
    }

    GPIO_SetBits(arg_pSPI->GPIO, arg_pSPI->SlavePin);

    return MCAL_WRAPPER_STAT_OK;
}



/*************** END OF FUNCTIONS ***************************************************************************/


// to be the IdleTask (called when no other tasks are running)
// void vApplicationIdleHook( void );