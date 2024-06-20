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
 * |    24/05/2023      1.0.0           Abdelrahman Mohamed Salem       Added configurations for SPI of ADXL345.                        |
 * |    12/06/2023      1.0.0           Mohab Zaghloul                  Added configurations for I2C of MPU6050.                        |
 * --------------------------------------------------------------------------------------------------------------------------------------
 */
 

/******************************************************************************
 * Includes
 *******************************************************************************/

/**
 * @reason: contains definitions for function of the current class
*/
#include "MCAL_config.h"

/**
 * @reason: to enable/disable clocks related to the peripherals
*/
#include "ch32v20x_rcc.h"


/**
 * @reason: to configure the pins
*/
#include "ch32v20x_gpio.h"


/**
 * @reason: contains definitons for peripherals
*/
#include "ch32v20x.h"

/**
 * @reason: contains definitions for SPI
*/
#include "ch32v20x_spi.h"

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

/**
 * @brief: the variable through which we will provide connection between ADXL345 and SPI
*/
MCAL_CONFIG_SPI_t MCAL_CFG_adxlSPI;

/******************************************************************************
 * Function Prototypes
 *******************************************************************************/

/******************************************************************************
 * Function Definitions
 *******************************************************************************/

MCAL_Config_ErrStat_t MCAL_Config_ConfigAllPins(void)
{   
    // enable clock for all needed peripherals
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, DISABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, DISABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_SRAM, DISABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, DISABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_OTG_FS, DISABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, DISABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, DISABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, DISABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, DISABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, DISABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, DISABLE);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, DISABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, DISABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, DISABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, DISABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, DISABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, DISABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, DISABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, DISABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, DISABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, DISABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, DISABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, DISABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, DISABLE);


    // dummy variables through which to configure the module
    GPIO_InitTypeDef local_dummy_t = {
        .GPIO_Mode = GPIO_Mode_AIN,
        .GPIO_Speed = GPIO_Speed_10MHz,
        .GPIO_Pin = GPIO_Pin_0,
    };

    // configure the pins 
    /******************************************/
    local_dummy_t.GPIO_Mode = GPIO_Mode_IPU;
    local_dummy_t.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIOA, &local_dummy_t);

    local_dummy_t.GPIO_Mode = GPIO_Mode_AF_PP;
    local_dummy_t.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOA, &local_dummy_t);

    local_dummy_t.GPIO_Mode = GPIO_Mode_AF_PP;
    local_dummy_t.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOA, &local_dummy_t);

    local_dummy_t.GPIO_Mode = GPIO_Mode_AF_PP;
    local_dummy_t.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIOA, &local_dummy_t);

    local_dummy_t.GPIO_Mode = GPIO_Mode_AIN;
    local_dummy_t.GPIO_Pin = GPIO_Pin_4;
    GPIO_Init(GPIOA, &local_dummy_t);

    local_dummy_t.GPIO_Mode = GPIO_Mode_AF_PP;
    local_dummy_t.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init(GPIOA, &local_dummy_t);

    local_dummy_t.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    local_dummy_t.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOA, &local_dummy_t);

    local_dummy_t.GPIO_Mode = GPIO_Mode_AF_PP;
    local_dummy_t.GPIO_Pin = GPIO_Pin_7;
    GPIO_Init(GPIOA, &local_dummy_t);

    local_dummy_t.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    local_dummy_t.GPIO_Pin = GPIO_Pin_8;
    GPIO_Init(GPIOA, &local_dummy_t);

    local_dummy_t.GPIO_Mode = GPIO_Mode_AF_PP;
    local_dummy_t.GPIO_Pin = GPIO_Pin_9;
    GPIO_Init(GPIOA, &local_dummy_t);

    local_dummy_t.GPIO_Mode = GPIO_Mode_AF_PP;
    local_dummy_t.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOA, &local_dummy_t);

    local_dummy_t.GPIO_Mode = GPIO_Mode_AF_PP;
    local_dummy_t.GPIO_Pin = GPIO_Pin_11;
    GPIO_Init(GPIOA, &local_dummy_t);

    local_dummy_t.GPIO_Mode = GPIO_Mode_IPD;
    local_dummy_t.GPIO_Pin = GPIO_Pin_12;
    GPIO_Init(GPIOA, &local_dummy_t);

    local_dummy_t.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    local_dummy_t.GPIO_Pin = GPIO_Pin_13;
    GPIO_Init(GPIOA, &local_dummy_t);

    local_dummy_t.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    local_dummy_t.GPIO_Pin = GPIO_Pin_14;
    GPIO_Init(GPIOA, &local_dummy_t);

    local_dummy_t.GPIO_Mode = GPIO_Mode_AF_PP;
    local_dummy_t.GPIO_Pin = GPIO_Pin_15;
    GPIO_Init(GPIOA, &local_dummy_t);

    /******************************************/
    local_dummy_t.GPIO_Mode = GPIO_Mode_AF_PP;
    local_dummy_t.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIOB, &local_dummy_t);

    local_dummy_t.GPIO_Mode = GPIO_Mode_AF_PP;
    local_dummy_t.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOB, &local_dummy_t);

    local_dummy_t.GPIO_Mode = GPIO_Mode_AF_PP;
    local_dummy_t.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOB, &local_dummy_t);

    local_dummy_t.GPIO_Mode = GPIO_Mode_AF_PP;
    local_dummy_t.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIOB, &local_dummy_t);

    local_dummy_t.GPIO_Mode = GPIO_Mode_AF_PP;
    local_dummy_t.GPIO_Pin = GPIO_Pin_4;
    GPIO_Init(GPIOB, &local_dummy_t);

    local_dummy_t.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    local_dummy_t.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init(GPIOB, &local_dummy_t);

    local_dummy_t.GPIO_Mode = GPIO_Mode_AF_PP;
    local_dummy_t.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOB, &local_dummy_t);

    local_dummy_t.GPIO_Mode = GPIO_Mode_AF_PP;
    local_dummy_t.GPIO_Pin = GPIO_Pin_7;
    GPIO_Init(GPIOB, &local_dummy_t);

    local_dummy_t.GPIO_Mode = GPIO_Mode_AF_PP;
    local_dummy_t.GPIO_Pin = GPIO_Pin_8;
    GPIO_Init(GPIOB, &local_dummy_t);

    local_dummy_t.GPIO_Mode = GPIO_Mode_AF_PP;
    local_dummy_t.GPIO_Pin = GPIO_Pin_9;
    GPIO_Init(GPIOB, &local_dummy_t);

    local_dummy_t.GPIO_Mode = GPIO_Mode_AF_OD;
    local_dummy_t.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOB, &local_dummy_t);

    local_dummy_t.GPIO_Mode = GPIO_Mode_AF_OD;
    local_dummy_t.GPIO_Pin = GPIO_Pin_11;
    GPIO_Init(GPIOB, &local_dummy_t);

    local_dummy_t.GPIO_Mode = GPIO_Mode_IPU;
    local_dummy_t.GPIO_Pin = GPIO_Pin_12;
    GPIO_Init(GPIOB, &local_dummy_t);

    local_dummy_t.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    local_dummy_t.GPIO_Pin = GPIO_Pin_13;
    GPIO_Init(GPIOB, &local_dummy_t);

    local_dummy_t.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    local_dummy_t.GPIO_Pin = GPIO_Pin_14;
    GPIO_Init(GPIOB, &local_dummy_t);

    local_dummy_t.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    local_dummy_t.GPIO_Pin = GPIO_Pin_15;
    GPIO_Init(GPIOB, &local_dummy_t);
    
    /******************************************/
    local_dummy_t.GPIO_Mode = GPIO_Mode_Out_PP; 
    local_dummy_t.GPIO_Pin = GPIO_Pin_14;
    GPIO_Init(GPIOC, &local_dummy_t);

    local_dummy_t.GPIO_Mode = GPIO_Mode_Out_PP;
    local_dummy_t.GPIO_Pin = GPIO_Pin_15;
    GPIO_Init(GPIOC, &local_dummy_t);


    // config all needed peripherals

    /******************************************/
    MCAL_CFG_adxlSPI.SPI = SPI1;
    MCAL_CFG_adxlSPI.GPIO = GPIOC;
    MCAL_CFG_adxlSPI.SlavePin = GPIO_Pin_14;
    MCAL_CFG_adxlSPI.spiConfig.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    MCAL_CFG_adxlSPI.spiConfig.SPI_Mode = SPI_Mode_Master;
    MCAL_CFG_adxlSPI.spiConfig.SPI_DataSize = SPI_DataSize_8b;
    MCAL_CFG_adxlSPI.spiConfig.SPI_CPOL = SPI_CPOL_High;
    MCAL_CFG_adxlSPI.spiConfig.SPI_CPHA = SPI_CPHA_2Edge;
    MCAL_CFG_adxlSPI.spiConfig.SPI_NSS = SPI_NSS_Soft;
    // IMPORTANT NOTE: ADXL345 isn't working
    MCAL_CFG_adxlSPI.spiConfig.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256; //SPI_BaudRatePrescaler_32; 
    MCAL_CFG_adxlSPI.spiConfig.SPI_FirstBit = SPI_FirstBit_MSB;
    MCAL_CFG_adxlSPI.spiConfig.SPI_CRCPolynomial = 0b101;
    SPI_Init(SPI1, &MCAL_CFG_adxlSPI.spiConfig);
    SPI_Cmd(SPI1, ENABLE);
    GPIO_SetBits(MCAL_CFG_adxlSPI.GPIO, MCAL_CFG_adxlSPI.SlavePin);

    /******************************************/
    I2C_InitTypeDef I2CConfig;
    I2CConfig.I2C_ClockSpeed = 400000;
    I2CConfig.I2C_Mode = I2C_Mode_I2C;
    I2CConfig.I2C_DutyCycle = I2C_DutyCycle_2;
    I2CConfig.I2C_OwnAddress1 = 0x2F;
    I2CConfig.I2C_Ack = I2C_Ack_Enable;
    I2CConfig.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Init(I2C2, &I2CConfig);
    I2C_Cmd(I2C2, ENABLE);

    /******************************************/
    TIM_TimeBaseInitTypeDef local_tim4Init_t = {0};
    local_tim4Init_t.TIM_CounterMode = TIM_CounterMode_CenterAligned1;
    local_tim4Init_t.TIM_ClockDivision = TIM_CKD_DIV4;
    local_tim4Init_t.TIM_Prescaler = 144-1;
    local_tim4Init_t.TIM_Period = 10000;
    TIM_TimeBaseInit(TIM4, &local_tim4Init_t);

    TIM_OCInitTypeDef local_pwm_t = {0};
    local_pwm_t.TIM_OCMode = TIM_OCMode_PWM2;
    local_pwm_t.TIM_OutputState = TIM_OutputState_Enable;
    local_pwm_t.TIM_Pulse = 0; // 0 ms
    local_pwm_t.TIM_OCPolarity = TIM_OCPolarity_Low;

    TIM_OC1Init(TIM4, &local_pwm_t);
    TIM_OC2Init(TIM4, &local_pwm_t);
    TIM_OC3Init(TIM4, &local_pwm_t);
    TIM_OC4Init(TIM4, &local_pwm_t);
    
	TIM_CtrlPWMOutputs(TIM4, ENABLE );
	TIM_OC1PreloadConfig( TIM4, TIM_OCPreload_Disable );
	TIM_OC2PreloadConfig( TIM4, TIM_OCPreload_Disable );
	TIM_OC3PreloadConfig( TIM4, TIM_OCPreload_Disable );
	TIM_OC4PreloadConfig( TIM4, TIM_OCPreload_Disable );
	TIM_ARRPreloadConfig( TIM4, ENABLE );
	TIM_Cmd( TIM4, ENABLE );

    return MCAL_Config_STAT_OK;
}


/*************** END OF FUNCTIONS ***************************************************************************/