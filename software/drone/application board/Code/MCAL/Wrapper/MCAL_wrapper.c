/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   Wrapper File for RTOS function                                                                              |
 * |    @file           :   Service_RTOS_wrapper.h                                                                                      |
 * |    @author         :   Abdelrahman Mohamed Salem                                                                                   |
 * |    @origin_date    :   18/06/2024                                                                                                  |
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
 * |    18/06/2023      1.0.0           Abdelrahman Mohamed Salem       Interface Created.                                              |
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
 * @reason: contains I2C funcitonality
 */
#include "ch32v20x_i2c.h"

/**
 * @reason: contains common definitions
 */
#include "common.h"

/**
 * @reason: contains UART functionality
 */
#include "ch32v20x_usart.h"

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
functionCallBack_t global_UART4RecCallback = NULL;

/******************************************************************************
 * Function Prototypes
 *******************************************************************************/

/******************************************************************************
 * Function Definitions
 *******************************************************************************/

/**
 * 
 */
// MCAL_WRAPPER_ErrStat_t MCAL_WRAPEPR_TIM4_PWM_OUT(MCAL_WRAPPER_TIM_CH_t arg_channel_t, uint8_t arg_u8DutyPercent)
// {
//     if(arg_channel_t > MCAL_WRAPPER_TIM_CH4  || arg_u8DutyPercent > 100 )
//         return MCAL_WRAPPER_STAT_INVALID_PARAMS;

//     // 500 -> 1ms pulse
//     uint16_t local_u16NewPulse = 500 + 5 * arg_u8DutyPercent;
//     if(MCAL_WRAPPER_TIM_CH1 == arg_channel_t)
//     {
//         TIM_SetCompare1(TIM4, local_u16NewPulse);
//     }
//     else if(MCAL_WRAPPER_TIM_CH1 == arg_channel_t)
//     {
//         TIM_SetCompare2(TIM4, local_u16NewPulse);
//     }
//     else if(MCAL_WRAPPER_TIM_CH1 == arg_channel_t)
//     {
//         TIM_SetCompare3(TIM4, local_u16NewPulse);
//     }
//     else if(MCAL_WRAPPER_TIM_CH1 == arg_channel_t)
//     {
//         TIM_SetCompare4(TIM4, local_u16NewPulse);
//     }
//     else 
//     {

//     }

//     return MCAL_WRAPPER_STAT_OK;
// }

/**
 * 
 */
void UART4_IRQHandler(void)
{
    if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
    {
    	global_UART4RecCallback();
    }
}

/**
 * 
 */
MCAL_WRAPPER_ErrStat_t MCAL_WRAPPER_SetUART4RecCallBack(functionCallBack_t arg_pUARTCallBack)
{
    if(arg_pUARTCallBack == NULL)
    {
        return MCAL_WRAPPER_STAT_INVALID_PARAMS;
    }

    global_UART4RecCallback = arg_pUARTCallBack;

    return MCAL_WRAPPER_STAT_OK;
}

/**
 * 
 */
MCAL_WRAPPER_ErrStat_t MCAL_WRAPPER_SendDataThroughUART4(uint8_t* arg_pu8Data, uint16_t arg_u16DataLen)
{
    if(NULL == arg_pu8Data)
    {
        return MCAL_WRAPPER_STAT_INVALID_PARAMS;
    }

    while (arg_u16DataLen > 0)
    {
        USART_SendData(UART4, (uint16_t) *arg_pu8Data);
        while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET) /* waiting for sending finish */
        arg_pu8Data++;
        arg_u16DataLen--;
    }
    

    return MCAL_WRAPPER_STAT_OK;
}

/**
 * 
 */
MCAL_WRAPPER_ErrStat_t MCAL_WRAPPER_ReceiveDataThroughUART4(uint8_t* arg_pu8Data, uint16_t arg_u16DataLen)
{
    if(NULL == arg_pu8Data)
    {
        return MCAL_WRAPPER_STAT_INVALID_PARAMS;
    }

    // disable receive interrupt
    USART_ITConfig(UART4, USART_IT_RXNE, DISABLE);

    while (arg_u16DataLen > 0)
    {
        while(USART_GetFlagStatus(UART4, USART_FLAG_RXNE) == RESET);
        *arg_pu8Data = USART_ReceiveData(UART4);
        arg_pu8Data++;
        arg_u16DataLen--;
    }

    // enable receive interrupt
    USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);

    return MCAL_WRAPPER_STAT_OK;
}


/*************** END OF FUNCTIONS ***************************************************************************/
