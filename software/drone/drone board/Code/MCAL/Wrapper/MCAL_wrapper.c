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
 * |    12/06/2023      1.0.0           Mohab Zaghloul                  created 'I2C_start_transmission', 'I2C_write', 'I2C_stop',      |
 * |                                                                            'I2C_requestFrom', 'I2C_read' functions.                |
 * |    15/06/2023      1.0.0           Abdelrahman Mohamed Salem       created 'MCAL_WRAPEPR_TIM4_PWM_OUT'.                            |
 * |    15/06/2023      1.0.0           Abdelrahman Mohamed Salem       created 'MCAL_WRAPPER_SendDataThroughUART4'.                    |
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
 * @reason: contains some configuration constants
 */
#include "MPU6050.h"

/**
 * @reason: contains UART functionality
 */
#include "ch32v20x_usart.h"

/**
 * @reason: contains timer functionality
 */
#include "ch32v20x_tim.h"

/**
 * @reason: contains freeRTOS blocking functionality
 */
#include "Service_RTOS_wrapper.h"

/******************************************************************************
 * Module Preprocessor Constants
 *******************************************************************************/

/******************************************************************************
 * Module Preprocessor Macros
 *******************************************************************************/

#define portDISABLE_INTERRUPTS()	__asm volatile( "csrw mstatus,%0" ::"r"(0x1800) )
#define portENABLE_INTERRUPTS()		__asm volatile( "csrw mstatus,%0" ::"r"(0x1888) )

#define GET_INT_SP()   __asm volatile("csrrw sp,mscratch,sp")
#define FREE_INT_SP()  __asm volatile("csrrw sp,mscratch,sp")

/******************************************************************************
 * Module Typedefs
 *******************************************************************************/

/******************************************************************************
 * Module Variable Definitions
 *******************************************************************************/

/**
 * @brief: the callback function that will be called when UART receive interrupt happenss
 */
functionCallBack_t global_UART4RecCallback = NULL;

/**
 * @brief: calculated number of ticks for a timer to compute width of a pulse
 */
volatile uint32_t global_u32TicksNum = 0;

/**
 * @brief: flag to indicate the capture of width of a pulse
 */
volatile uint8_t global_u8IsCaptured = 0;

/**
 * @brief: the current task executing the measure pulse width
 */
RTOS_TaskHandle_t global_CurrentPWTask_t = NULL;

/**
 * @brief: variable shared between 2 different types of interrupts
 */
volatile uint16_t tempreg = 0;

/******************************************************************************
 * Function Prototypes
 *******************************************************************************/

/**
 * @brief: USART4 IRQ handler
 */
 void UART4_IRQHandler(void); // __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM1_CC_IRQHandler(void) __attribute__((interrupt()));
void TIM1_UP_IRQHandler(void) __attribute__((interrupt()));

/******************************************************************************
 * Function Definitions
 *******************************************************************************/

/**
 * 
 */
MCAL_WRAPPER_ErrStat_t MCAL_WRAPEPR_SPI_POLL_TRANSFER(MCAL_CONFIG_SPI_t *arg_pSPI, uint8_t* args_pu8InData, uint16_t arg_u16Len, uint8_t *args_pu8OutData)
{
    if(NULL == arg_pSPI || NULL == args_pu8InData)
        return MCAL_WRAPPER_STAT_INVALID_PARAMS;

    GPIO_ResetBits(arg_pSPI->GPIO, arg_pSPI->SlavePin);

    while (arg_u16Len > 0)
    {
        SPI_I2S_SendData(arg_pSPI->SPI, *args_pu8InData);
        while(SPI_I2S_GetFlagStatus(arg_pSPI->SPI, SPI_I2S_FLAG_TXE) != SET);
        while(SPI_I2S_GetFlagStatus(arg_pSPI->SPI, SPI_I2S_FLAG_BSY) == SET);        
        args_pu8InData++;
        if(args_pu8OutData != NULL)
        {
            *args_pu8OutData = SPI_I2S_ReceiveData(arg_pSPI->SPI);
            args_pu8OutData++;
        }

        arg_u16Len--;
    }

    GPIO_SetBits(arg_pSPI->GPIO, arg_pSPI->SlavePin);

    return MCAL_WRAPPER_STAT_OK;
}



/**
 * 
 */
void I2C_start_transmission(uint8_t receiver_address, uint8_t master_receive){
    uint8_t i2c_dir = I2C_Direction_Transmitter;
    uint32_t i2c_event = I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED;

    if(master_receive){
        i2c_dir = I2C_Direction_Receiver;
        i2c_event = I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED;
    }

    while( I2C_GetFlagStatus( I2C2, I2C_FLAG_BUSY ) != RESET );

    I2C_GenerateSTART(I2C2, ENABLE);
    while( !I2C_CheckEvent( I2C2, I2C_EVENT_MASTER_MODE_SELECT ) );

    I2C_Send7bitAddress(I2C2, receiver_address << 1, i2c_dir);
    while( !I2C_CheckEvent( I2C2, i2c_event ) );
}

/**
 * 
 */
void I2C_write(uint8_t value){
    while(I2C_GetFlagStatus(I2C2, I2C_FLAG_TXE)!=SET);
    I2C_SendData(I2C2, value);
}

/**
 * 
 */
void I2C_stop(){
    while(I2C_GetFlagStatus(I2C2, I2C_FLAG_TXE)!=SET);
    I2C_GenerateSTOP(I2C2, ENABLE);
}

/**
 * 
 */
uint8_t I2C_read(){
    static uint8_t i = 0;
    uint8_t result = RxData[i];
    i = (i+1) % I2C_Rx_BUFFER_SIZE;
    return result;
}

/**
 * 
 */
uint8_t I2C_requestFrom(uint8_t address, uint8_t quantity){
    uint8_t i = 0;

    I2C_start_transmission(address, MASTER_RECEIVER_MODE);

    while(i < quantity){
        if( I2C_GetFlagStatus( I2C2, I2C_FLAG_RXNE ) !=  RESET ){
            RxData[i] = I2C_ReceiveData( I2C2 );
            i++;
        }
        if(i == I2C_Rx_BUFFER_SIZE-1) I2C_NACKPositionConfig(I2C2, I2C_NACKPosition_Next);
    }

    while(I2C_GetFlagStatus(I2C2, I2C_FLAG_RXNE)!=SET);
    I2C_GenerateSTOP(I2C2, ENABLE);

    return i;
}

/**
 * 
 */
MCAL_WRAPPER_ErrStat_t MCAL_WRAPEPR_TIM4_PWM_OUT(MCAL_WRAPPER_TIM_CH_t arg_channel_t, uint16_t arg_u8DutyPercent)
{
    if(arg_channel_t > MCAL_WRAPPER_TIM_CH4  || arg_u8DutyPercent > 1000 )
        return MCAL_WRAPPER_STAT_INVALID_PARAMS;

    // 500 -> 1ms pulse
    uint16_t local_u16NewPulse = 1000 + arg_u8DutyPercent;
    if(MCAL_WRAPPER_TIM_CH1 == arg_channel_t)
    {
        TIM_SetCompare1(TIM4, local_u16NewPulse);
    }
    else if(MCAL_WRAPPER_TIM_CH2 == arg_channel_t)
    {
        TIM_SetCompare2(TIM4, local_u16NewPulse);
    }
    else if(MCAL_WRAPPER_TIM_CH3 == arg_channel_t)
    {
        TIM_SetCompare3(TIM4, local_u16NewPulse);
    }
    else if(MCAL_WRAPPER_TIM_CH4 == arg_channel_t)
    {
        TIM_SetCompare4(TIM4, local_u16NewPulse);
    }
    else 
    {

    }

    return MCAL_WRAPPER_STAT_OK;
}

/**
 *
 */
void UART4_IRQHandler(void)
{
   if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET && NULL != global_UART4RecCallback)
   {
		global_UART4RecCallback();
   }
}


/**
 * 
 */
void TIM1_UP_IRQHandler(void)
{   
	if( TIM_GetITStatus( TIM1, TIM_IT_Update ) != RESET )
	{
        // interrupt happened due to overflow of the counter
        // add 10000 which is the period of the timer or the remaining time of timer overflow in case of first overflow
        global_u32TicksNum = (global_u32TicksNum == 0) ? (10000 - tempreg)  : (global_u32TicksNum + 10000);
        
	}

    TIM_ClearITPendingBit( TIM1, TIM_IT_Update );
}



/**
 * 
 */
void TIM1_CC_IRQHandler(void)
{   

    // interrupt happened due to rising edge
	if( TIM_GetITStatus( TIM1, TIM_IT_CC1 ) != RESET )
	{
        // store the value of the input capture register 
        tempreg = TIM_GetCapture1(TIM1);
        
        // start of the pulse
        global_u32TicksNum = 0;
        global_u8IsCaptured = 0;
	}
    // interrupt happened due to falling edge
    else if(TIM_GetITStatus( TIM1, TIM_IT_CC2 ) != RESET )
    {
        // store the value of the input capture register 
        tempreg = TIM_GetCapture2(TIM1);

        // end of the pulse
        global_u32TicksNum += tempreg;
        global_u8IsCaptured = 1;

        // notify the task
        SERVICE_RTOS_Notify(global_CurrentPWTask_t, LIB_CONSTANTS_ENABLED);
    }

	TIM_ClearITPendingBit( TIM1, TIM_IT_CC1 | TIM_IT_CC2 );
}

/**
 * 
 */
MCAL_WRAPPER_ErrStat_t MCAL_WRAPPER_TIM1GetWidthOfPulse(uint32_t* arg_u32TimeUS)
{
	MCAL_WRAPPER_ErrStat_t local_errState = MCAL_WRAPPER_STAT_OK;
    if(arg_u32TimeUS == NULL)
    {
        return MCAL_WRAPPER_STAT_INVALID_PARAMS;
    }

    // get the current handle
    SERVICE_RTOS_GetCurrentTaskHandle(&global_CurrentPWTask_t);

    // do some initialization
    global_u8IsCaptured = 0;
    global_u32TicksNum = 0;

    // enable the timer interrupt and clear flags if any
    TIM_Cmd(TIM1, ENABLE);

    // block until we get a readings (max expected time is 23.52 millisecond as the range for ultrasonic sensor is 400 centimeter)
    SERVICE_RTOS_WaitForNotification(25);

    // disable the timer interrupt
    TIM_Cmd(TIM1, DISABLE);

    if(1 == global_u8IsCaptured)
    {
        // assign the current time
        *arg_u32TimeUS = global_u32TicksNum;
    }
    else
    {
    	local_errState = MCAL_WRAPPER_STAT_ECHO_ERR;
    }


    return local_errState;

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
MCAL_WRAPPER_ErrStat_t MCAL_WRAPPER_UART4RecITConfig(LIB_CONSTANTS_DriverStates_t arg_Enable_Disable_t)
{
	NVIC_InitTypeDef  uart_nvic_t = {0};
    uart_nvic_t.NVIC_IRQChannel = UART4_IRQn;
    uart_nvic_t.NVIC_IRQChannelPreemptionPriority = 1;
    uart_nvic_t.NVIC_IRQChannelSubPriority = 1;

    switch (arg_Enable_Disable_t)
    {
    case LIB_CONSTANTS_DISABLED:
            // disable receive interrupt
            USART_ITConfig(UART4, USART_IT_RXNE, DISABLE);
            // configure NVIC for uart4 interrupt channel
            uart_nvic_t.NVIC_IRQChannelCmd = DISABLE;
            NVIC_Init(&uart_nvic_t);
        break;

    case LIB_CONSTANTS_ENABLED:
            // enable receive interrupt
            USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
            // configure NVIC for uart4 interrupt channel
            uart_nvic_t.NVIC_IRQChannelCmd = ENABLE;
            NVIC_Init(&uart_nvic_t);
        break;

    default:
        break;
    }
    
    return MCAL_WRAPPER_STAT_OK;
}

/**
 * 
 */
MCAL_WRAPPER_ErrStat_t MCAL_WRAPPER_SendDataThroughUART4(uint8_t* arg_pu8Data, uint16_t arg_u16DataLen)
{
    MCAL_WRAPPER_ErrStat_t local_errState_t = MCAL_WRAPPER_STAT_OK;

    if(NULL == arg_pu8Data)
    {
        return MCAL_WRAPPER_STAT_INVALID_PARAMS;
    }

    while (arg_u16DataLen > 0)
    {
        // check if we can send
        if(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == SET && USART_GetFlagStatus(UART4, USART_FLAG_RXNE) == RESET)
        {
            USART_SendData(UART4, (uint16_t) *arg_pu8Data);
            arg_pu8Data++;
            arg_u16DataLen--;
        }
        else
        {
            local_errState_t = MCAL_WRAPPER_STAT_UART_BUSY;
            break;
        }

    }
    
    return local_errState_t;
}

/**
 * 
 */
MCAL_WRAPPER_ErrStat_t MCAL_WRAPPER_ReceiveDataThroughUART4(uint8_t* arg_pu8Data, uint16_t arg_u16DataLen)
{

    MCAL_WRAPPER_ErrStat_t local_errState_t = MCAL_WRAPPER_STAT_OK;

    if(NULL == arg_pu8Data)
    {
        return MCAL_WRAPPER_STAT_INVALID_PARAMS;
    }


    while (arg_u16DataLen > 0)
    {
        if(USART_GetFlagStatus(UART4, USART_FLAG_RXNE) == SET)
        {
            *arg_pu8Data = USART_ReceiveData(UART4);
            arg_pu8Data++;
            arg_u16DataLen--;
            // clear the interrupt by writing 0 
            USART_ClearFlag(UART4, USART_IT_RXNE);
        }
        else
        {
            local_errState_t = MCAL_WRAPPER_STAT_UART_EMPTY;
            break;
        }

    }

    return local_errState_t;
}

/**
 * 
 */
MCAL_WRAPPER_ErrStat_t MCAL_WRAPPER_DelayUS(uint32_t arg_u16US)
{   
    
    uint16_t local_u16Dummy = 0;

    while (arg_u16US)
    {
        if(arg_u16US < 10000)
        {
            local_u16Dummy = arg_u16US % 10000;
            arg_u16US = 0;
        }
        else
        {
            local_u16Dummy = 10000;
            arg_u16US -= 10000;
        }
        TIM_ClearFlag(TIM2, TIM_FLAG_Update);
        TIM_SetCounter(TIM2, local_u16Dummy);
        TIM_Cmd( TIM2, ENABLE );
        while (TIM_GetCounter(TIM2) < local_u16Dummy+1);
        TIM_Cmd( TIM2, DISABLE );
    }
    
    return MCAL_WRAPPER_STAT_OK;   
}

// /**
//  * 
//  */
// MCAL_WRAPPER_ErrStat_t MCAL_WRAPPER_DelayMS(uint16_t arg_u16MS)
// {
//     TIM_ClearFlag(TIM2, TIM_FLAG_Update);
//     TIM_SetCounter(TIM2, arg_u16MS);
//     TIM_Cmd( TIM2, ENABLE );
//     while (TIM_GetCounter(TIM2) < arg_u16MS+1);
//     TIM_Cmd( TIM2, DISABLE );

//     return MCAL_WRAPPER_STAT_OK;   
// }

/**
 * 
 */
MCAL_WRAPPER_ErrStat_t MCAL_WRAPPER_HCSR04Trig(uint16_t arg_16PWuS)
{
    // set the bit
    GPIO_SetBits(GPIOA, GPIO_Pin_15);

    // wait for the delay given
    MCAL_WRAPPER_DelayUS(arg_16PWuS);

    // reset the bit
    GPIO_ResetBits(GPIOA, GPIO_Pin_15);

    return MCAL_WRAPPER_STAT_OK; 
}

/**
 * 
 */
MCAL_WRAPPER_ErrStat_t MCAL_WRAPPER_GetADCBattery(uint16_t* arg_pu16ADCReadings)
{
    // select the channel
    ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_71Cycles5);

    // start conversion
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);

    // wait till conversion end
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
    
    // return value  
    *arg_pu16ADCReadings = ADC_GetConversionValue(ADC1);

    return MCAL_WRAPPER_STAT_OK; 
}

/*************** END OF FUNCTIONS ***************************************************************************/
