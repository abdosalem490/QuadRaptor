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

/**
 * @reason: contains definitions for USART
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

/**
 * @brief: the variable through which we will provide connection between ADXL345 and SPI
*/
MCAL_CONFIG_SPI_t MCAL_CFG_adxlSPI;

/**
 * @brief: the variable through which we will provide connection between BMP280 and SPI
*/
MCAL_CONFIG_SPI_t MCAL_CFG_BMPSPI;

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
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, DISABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, DISABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, DISABLE);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, DISABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, DISABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, DISABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, DISABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, DISABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, DISABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
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

    local_dummy_t.GPIO_Mode = GPIO_Mode_Out_PP;
    local_dummy_t.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOA, &local_dummy_t);

    local_dummy_t.GPIO_Mode = GPIO_Mode_Out_PP;
    local_dummy_t.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOA, &local_dummy_t);

    local_dummy_t.GPIO_Mode = GPIO_Mode_Out_PP;
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

    local_dummy_t.GPIO_Mode = GPIO_Mode_Out_PP;
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

    local_dummy_t.GPIO_Mode = GPIO_Mode_Out_PP;
    local_dummy_t.GPIO_Pin = GPIO_Pin_15;
    GPIO_Init(GPIOA, &local_dummy_t);

    /******************************************/
    local_dummy_t.GPIO_Mode = GPIO_Mode_AF_PP;
    local_dummy_t.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIOB, &local_dummy_t);

    local_dummy_t.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    local_dummy_t.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOB, &local_dummy_t);

    local_dummy_t.GPIO_Mode = GPIO_Mode_AF_PP;
    local_dummy_t.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOB, &local_dummy_t);

    local_dummy_t.GPIO_Mode = GPIO_Mode_IN_FLOATING;
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
    local_dummy_t.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
    local_dummy_t.GPIO_Pin = GPIO_Pin_13;
    GPIO_Init(GPIOC, &local_dummy_t);

    local_dummy_t.GPIO_Mode = GPIO_Mode_Out_PP; 
    local_dummy_t.GPIO_Pin = GPIO_Pin_14;
    GPIO_Init(GPIOC, &local_dummy_t);

    local_dummy_t.GPIO_Mode = GPIO_Mode_Out_PP;
    local_dummy_t.GPIO_Pin = GPIO_Pin_15;
    GPIO_Init(GPIOC, &local_dummy_t);

    
    // initial value for pins
    /******************************************/
    GPIO_ResetBits(GPIOA, GPIO_Pin_15);

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

    // this is the same initialization for BMP280
    MCAL_CFG_BMPSPI.SPI = SPI1;
    MCAL_CFG_BMPSPI.GPIO = GPIOC;
    MCAL_CFG_BMPSPI.SlavePin = GPIO_Pin_15;
    MCAL_CFG_BMPSPI.spiConfig = MCAL_CFG_adxlSPI.spiConfig;

    SPI_Init(SPI1, &MCAL_CFG_adxlSPI.spiConfig);
    GPIO_SetBits(MCAL_CFG_adxlSPI.GPIO, MCAL_CFG_adxlSPI.SlavePin);
    GPIO_SetBits(MCAL_CFG_BMPSPI.GPIO, MCAL_CFG_BMPSPI.SlavePin);
    SPI_Cmd(SPI1, ENABLE);

    
     

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
    local_tim4Init_t.TIM_CounterMode = TIM_CounterMode_Up;
    local_tim4Init_t.TIM_ClockDivision = TIM_CKD_DIV4;
    local_tim4Init_t.TIM_Prescaler = 144-1;
    local_tim4Init_t.TIM_Period = 20000;
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

    /******************************************/
    TIM_TimeBaseInitTypeDef local_tim2Init_t = {0};
    local_tim2Init_t.TIM_CounterMode = TIM_CounterMode_Down;
    local_tim2Init_t.TIM_ClockDivision = TIM_CKD_DIV4;
    local_tim2Init_t.TIM_Prescaler = 144-1;
    local_tim2Init_t.TIM_Period = 30000;
    TIM_TimeBaseInit(TIM2, &local_tim2Init_t);
	TIM_ARRPreloadConfig( TIM2, ENABLE );
    TIM_UpdateRequestConfig(TIM2, TIM_UpdateSource_Regular);
    TIM_UpdateDisableConfig(TIM2, ENABLE);
	// TIM_Cmd( TIM2, ENABLE );

    /******************************************/
    TIM_TimeBaseInitTypeDef local_tim1Init_t = {0};
    local_tim1Init_t.TIM_CounterMode = TIM_CounterMode_Up;
    local_tim1Init_t.TIM_ClockDivision = TIM_CKD_DIV4;
    local_tim1Init_t.TIM_Prescaler = 144-1;
    local_tim1Init_t.TIM_Period = 10000;
    TIM_TimeBaseInit(TIM1, &local_tim1Init_t);
	TIM_ARRPreloadConfig( TIM1, ENABLE );
    TIM_UpdateRequestConfig(TIM1, TIM_UpdateSource_Regular);

    TIM_ICInitTypeDef local_tim1ICInit_t = {0};
    local_tim1ICInit_t.TIM_Channel = TIM_Channel_1;
    local_tim1ICInit_t.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    local_tim1ICInit_t.TIM_ICFilter = 0x00;
    local_tim1ICInit_t.TIM_ICPolarity = TIM_ICPolarity_Rising;
    local_tim1ICInit_t.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_PWMIConfig(TIM1, &local_tim1ICInit_t);  // CC1 will capture timer at rising edge on IC1 while falling edge on IC1 will capture timer value at CC2 

    NVIC_InitTypeDef local_tim1NVICInit_t = {0};
    local_tim1NVICInit_t.NVIC_IRQChannel = TIM1_CC_IRQn;
    local_tim1NVICInit_t.NVIC_IRQChannelPreemptionPriority = 1;
    local_tim1NVICInit_t.NVIC_IRQChannelSubPriority = 1;
    local_tim1NVICInit_t.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&local_tim1NVICInit_t);
    local_tim1NVICInit_t.NVIC_IRQChannel = TIM1_UP_IRQn;
    NVIC_Init(&local_tim1NVICInit_t);    

    TIM_ITConfig(TIM1, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_Update, ENABLE);
    TIM_SelectInputTrigger(TIM1, TIM_TS_TI1FP1);    // synchronize timer with filtered input from channel1
    TIM_SelectSlaveMode(TIM1, TIM_SlaveMode_Reset); // reset counter upon rising edge on TI1FP1
    TIM_SelectMasterSlaveMode(TIM1, TIM_MasterSlaveMode_Enable);    // enable the above 3 lines actions
    // TIM_Cmd(TIM1, ENABLE);

    /******************************************/

    // USART_ClockInitTypeDef local_usart4_clock_t = {0};
    // local_usart4_clock_t.USART_Clock = USART_Clock_Enable;
    // local_usart4_clock_t.USART_CPHA = USART_CPOL_Low;
    // local_usart4_clock_t.USART_CPOL = USART_CPHA_1Edge;
    // local_usart4_clock_t.USART_LastBit = USART_LastBit_Enable;
    // USART_ClockInit(UART4, &local_usart4_clock_t);

    USART_InitTypeDef local_usart4_t = {0};
    local_usart4_t.USART_BaudRate = 115200;
    local_usart4_t.USART_WordLength = USART_WordLength_8b;
    local_usart4_t.USART_StopBits = USART_StopBits_1;
    local_usart4_t.USART_Parity = USART_Parity_No;
    local_usart4_t.USART_HardwareFlowControl = USART_HardwareFlowControl_RTS_CTS;
    local_usart4_t.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(UART4, &local_usart4_t);

    // USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
    // interrupt is causing Systick timer interrupt to stop which is in return responsible for stopping freeRTOS kernal from work
    // // configure NVIC for uart4 interrupt channel
    // NVIC_InitTypeDef  uart_nvic_t = {0};
    // uart_nvic_t.NVIC_IRQChannel = UART4_IRQn;
    // uart_nvic_t.NVIC_IRQChannelPreemptionPriority = 1;
    // uart_nvic_t.NVIC_IRQChannelSubPriority = 1;
    // uart_nvic_t.NVIC_IRQChannelCmd = ENABLE;
    // NVIC_Init(&uart_nvic_t);

    USART_Cmd(UART4, ENABLE);

    /******************************************/
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);
    ADC_InitTypeDef  ADC_InitStructure = {0};
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConv  = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    // ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_71Cycles5);
    ADC_Cmd(ADC1, ENABLE);

    return MCAL_Config_STAT_OK;
}


/*************** END OF FUNCTIONS ***************************************************************************/
