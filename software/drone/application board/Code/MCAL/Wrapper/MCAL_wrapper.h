/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   wrapper file for the MCAL layer functions                                                                   |
 * |    @file           :   MCAL_config.h                                                                                               |
 * |    @author         :   Abdelrahman Mohamed Salem                                                                                   |
 * |    @origin_date    :   18/06/2024                                                                                                  |
 * |    @version        :   1.0.0                                                                                                       |
 * |    @tool_chain     :   RISC-V Cross GCC                                                                                            |
 * |    @compiler       :   GCC                                                                                                         |
 * |    @C_standard     :   ISO C99 (-std=c99)                                                                                          |
 * |    @target         :   CH32V203C8T6                                                                                                |
 * |    @notes          :   None                                                                                                        |
 * |    @license        :   MIT License                                                                                                 |
 * |    @brief          :   this file is a wrapper file for the MCAL layer so that when we change MCAL, the code could be portable      |
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
 * |    18/06/2023      1.0.0           Abdelrahman Mohamed Salem       file Created.                                                   |
 * |    20/06/2023      1.0.0           Abdelrahman Mohamed Salem       created 'MCAL_WRAPPER_UART4RecITConfig'.                        |
 * --------------------------------------------------------------------------------------------------------------------------------------
 */


#ifndef MCAL_WRAPPER_HEADER_H_
#define MCAL_WRAPPER_HEADER_H_

/******************************************************************************
 * Includes
 *******************************************************************************/

/**
 * @reason: contains definition struct for SPI
 */
#include "MCAL_config.h"

/**
 * @reason: contains standard definitions for int
 */
#include "stdint.h"

/**
 * @reason: contains common definitions
 */
#include "common.h"

/**
 * @reason: contains some constant definitions
 */
#include "constants.h"


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

/**
 * @brief: contains error states for this module
*/
typedef enum {
  MCAL_WRAPPER_STAT_OK,
  MCAL_WRAPPER_STAT_INVALID_PARAMS,
  MCAL_WRAPPER_STAT_REC_BUFF_FULL,
  MCAL_WRAPPER_STAT_UART_BUSY,
  MCAL_WRAPPER_STAT_UART_EMPTY,
} MCAL_WRAPPER_ErrStat_t;

// /**
//  * @brief: define which channel of time we are taking about
//  */
// typedef enum {
//   MCAL_WRAPPER_TIM_CH1, /**< timer channel 1*/
//   MCAL_WRAPPER_TIM_CH2, /**< timer channel 2*/
//   MCAL_WRAPPER_TIM_CH3, /**< timer channel 3*/
//   MCAL_WRAPPER_TIM_CH4, /**< timer channel 4*/
// } MCAL_WRAPPER_TIM_CH_t;

/******************************************************************************
 * Variables
 *******************************************************************************/

/******************************************************************************
 * Function Prototypes
 *******************************************************************************/

/**
 *  \b function                                 :       MCAL_WRAPPER_ErrStat_t MCAL_WRAPEPR_TIM4_PWM_OUT(MCAL_WRAPPER_TIM_CH_t arg_channel_t, uint8_t arg_u8DutyPercent);
 *  \b Description                              :       this functions is used as a wrapper function to the function of changing pwm signal of TIM4.
 *  @param  arg_channel_t [IN]                  :       which channel of TIM4 PWM channels to change its duty cycle, refer to @MCAL_WRAPPER_TIM_CH_t in "MCAL_wrapper.h".
 *  @param  arg_u8DutyPercent [IN]              :       percent of period to make signal high, possible values are from 1 to 100.
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       make sure to call configure the configuration file in the current directory.
 *  \b POST-CONDITION                           :       the PWM duty cycle of the output is changed.
 *  @return                                     :       it return one of error states indicating whether a failure or success happened (refer to @MCAL_WRAPPER_ErrStat_t in "MCAL_wrapper.h")
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * #include "MCAL_wrapper.h"
 * 
 * 
 * int main() {
 * 
 * MCAL_Config_ErrStat_t local_errState = MCAL_Config_ConfigAllPins();
 * if(MCAL_Config_STAT_OK == local_errState)
 * {
 *  uint8_t temp = 0;
 *  local_errState = MCAL_WRAPEPR_TIM4_PWM_OUT(MCAL_WRAPPER_TIM_CH2, 1);
 *  if(MCAL_WRAPPER_STAT_OK == local_errState)
 *  {
 *  
 *  }
 * }
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 11/06/2024 </td><td> 1.0.0            </td><td> AMS      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
// MCAL_WRAPPER_ErrStat_t MCAL_WRAPEPR_TIM4_PWM_OUT(MCAL_WRAPPER_TIM_CH_t arg_channel_t, uint8_t arg_u8DutyPercent);

/**
 *  \b function                                 :       MCAL_WRAPPER_SetUART4RecCallBack HAL_WRAPPER_SetUART4CallBack(functionCallBack_t *arg_pUARTCallBack);
 *  \b Description                              :       this functions is used as a wrapper function to set callback function to execute when UART4 receives anything.
 *  @param  arg_pUARTCallBack [IN]              :       base address of function to be executed when UART4 receives anything.
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       make sure to call configure function the configuration file in the current directory.
 *  \b POST-CONDITION                           :       Callback function is assigned to be executed whenever UART4 receives anything.
 *  @return                                     :       it return one of error states indicating whether a failure or success happened (refer to @HAL_WRAPPER_ErrStat_t in "HAL_wrapper.h")
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * #include "MCAL_wrapper.h"
 * 
 * void func(void)
 * {
 *  // callback code
 * }
 * 
 * int main() {
 *  MCAL_Config_ErrStat_t local_errState = MCAL_Config_ConfigAllPins();
 *  if(MCAL_Config_STAT_OK == local_errState)
 *  {
 *    local_errState = MCAL_WRAPPER_SetUART4RecCallBack(func);
 *    if(MCAL_WRAPPER_STAT_OK == local_errState)
 *    {
 *    
 *    }
 *  }
 * }
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 17/06/2024 </td><td> 1.0.0            </td><td> AMS      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
MCAL_WRAPPER_ErrStat_t MCAL_WRAPPER_SetUART4RecCallBack(functionCallBack_t arg_pUARTCallBack);

/**
 *  \b function                                 :       MCAL_WRAPPER_ErrStat_t MCAL_WRAPPER_UART4RecITConfig(LIB_CONSTANTS_DriverStates_t arg_Enable_Disable_t);
 *  \b Description                              :       this functions is used as a wrapper function to enable/disable uart4 byte received interrupt.
 *  @param arg_Enable_Disable_t [IN]            :       to enable or disable the interrupt, refer to @LIB_CONSTANTS_DriverStates_t in "constants.h".
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       make sure to call configure function the configuration file in the current directory.
 *  \b POST-CONDITION                           :       UART receive interrupt is enabled
 *  @return                                     :       it return one of error states indicating whether a failure or success happened (refer to @HAL_WRAPPER_ErrStat_t in "HAL_wrapper.h")
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * #include "MCAL_wrapper.h"
 * 
 * void func(void)
 * {
 *  // callback code
 * }
 * 
 * int main() {
 *  MCAL_Config_ErrStat_t local_errState = MCAL_Config_ConfigAllPins();
 *  if(MCAL_Config_STAT_OK == local_errState)
 *  {
 *    local_errState = MCAL_WRAPPER_UART4RecITConfig(LIB_CONSTANTS_ENABLED);
 *    if(MCAL_WRAPPER_STAT_OK == local_errState)
 *    {
 *      // interrupt is enabled
 *    }
 *  }
 * }
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 20/06/2024 </td><td> 1.0.0            </td><td> AMS      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
MCAL_WRAPPER_ErrStat_t MCAL_WRAPPER_UART4RecITConfig(LIB_CONSTANTS_DriverStates_t arg_Enable_Disable_t);

/**
 *  \b function                                 :       MCAL_WRAPPER_ErrStat_t MCAL_WRAPPER_SendDataThroughUART4(uint8_t* arg_pu8Data, uint16_t arg_u16DataLen);
 *  \b Description                              :       this functions is used as a wrapper function to send data through UART4.
 *  @param  arg_pu8Data [IN]                    :       base address of data to be send over UART4.
 *  @param  arg_u16DataLen [IN]                 :       length of data in bytes to be send over UART4.
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       make sure to call configure function the configuration file in the current directory.
 *  \b POST-CONDITION                           :       data is sent over UART4.
 *  @return                                     :       it return one of error states indicating whether a failure or success happened (refer to @HAL_WRAPPER_ErrStat_t in "HAL_wrapper.h")
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * #include "MCAL_wrapper.h"
 * 
 * 
 * int main() {
 *  MCAL_Config_ErrStat_t local_errState = MCAL_Config_ConfigAllPins();
 *  uint8_t data[] = [0, 1, 2, 4];
 *  if(MCAL_Config_STAT_OK == local_errState)
 *  {
 *    local_errState = MCAL_WRAPPER_SendDataThroughUART4(data, 4);
 *    if(HAL_WRAPPER_STAT_OK == local_errState)
 *    {
 *      // data is sent successfully
 *    }
 *  }
 * }
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 18/06/2024 </td><td> 1.0.0            </td><td> AMS      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
MCAL_WRAPPER_ErrStat_t MCAL_WRAPPER_SendDataThroughUART4(uint8_t* arg_pu8Data, uint16_t arg_u16DataLen);


/**
 *  \b function                                 :       MCAL_WRAPPER_ErrStat_t MCAL_WRAPPER_SendDataThroughUART4(uint8_t* arg_pu8Data, uint16_t arg_u16DataLen);
 *  \b Description                              :       this functions is used as a wrapper function to send receive through UART4.
 *  @param  arg_pu8Data [IN]                    :       base address of data to be received over UART4.
 *  @param  arg_u16DataLen [IN]                 :       length of data in bytes to be received over UART4.
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       make sure to call configure function the configuration file in the current directory.
 *  \b POST-CONDITION                           :       data is received over UART4.
 *  @return                                     :       it return one of error states indicating whether a failure or success happened (refer to @HAL_WRAPPER_ErrStat_t in "HAL_wrapper.h")
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * #include "MCAL_wrapper.h"
 * 
 * void func(void)
 * {
 *    SERVICE_RTOS_Notify(task_AppComm_Handle_t, LIB_CONSTANTS_ENABLED);
 * }
 * 
 * int main() {
 *  MCAL_Config_ErrStat_t local_errState = MCAL_Config_ConfigAllPins();
 *  uint8_t data[4];
 *  if(MCAL_Config_STAT_OK == local_errState)
 *  {
 *    local_errState = MCAL_WRAPPER_ReceiveDataThroughUART4(data, 4);
 *    if(HAL_WRAPPER_STAT_OK == local_errState)
 *    {
 *      // data is sent successfully
 *    }
 *  }
 * }
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 18/06/2024 </td><td> 1.0.0            </td><td> AMS      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
MCAL_WRAPPER_ErrStat_t MCAL_WRAPPER_ReceiveDataThroughUART4(uint8_t* arg_pu8Data, uint16_t arg_u16DataLen);


/**
 *  \b function                                 :       None.
 *  \b Description                              :       Sets the CSN pin low..
 *  @param  arg_pu8Data [IN]                    :       None.
 *  @param  arg_u16DataLen [IN]                 :       None.
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       None.
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       None.
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * None.
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 18/06/2024 </td><td> 1.0.0            </td><td> AF      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
void CSN_LOW();



/**
 *  \b function                                 :       None.
 *  \b Description                              :       Sets the CSN pin high.
 *  @param  arg_pu8Data [IN]                    :       None.
 *  @param  arg_u16DataLen [IN]                 :       None.
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       None.
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       None.
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * None.
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 18/06/2024 </td><td> 1.0.0            </td><td> AF      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
void CSN_HIGH();



/**
 *  \b function                                 :       None.
 *  \b Description                              :       Sets the CE pin low.
 *  @param  arg_pu8Data [IN]                    :       None.
 *  @param  arg_u16DataLen [IN]                 :       None.
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       None.
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       None.
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * None.
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 18/06/2024 </td><td> 1.0.0            </td><td> AF      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
void CE_LOW();

/**
 *  \b function                                 :       None.
 *  \b Description                              :       Sets the CE pin high.
 *  @param  arg_pu8Data [IN]                    :       None.
 *  @param  arg_u16DataLen [IN]                 :       None.
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       None.
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       None.
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * None.
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 18/06/2024 </td><td> 1.0.0            </td><td> AF      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
void CE_HIGH();

/**
 *  \b function                                 :       None
 *  \b Description                              :       Transfers a byte over SPI.
 *  @param  data [IN]                           :       The byte to transfer.
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       None
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       The byte received from the SPI transfer.
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * None
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 18/06/2024 </td><td> 1.0.0            </td><td> AF      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
uint8_t SPI_transfer(uint8_t data);

/**
 *  \b function                                 :       MCAL_WRAPPER_ErrStat_t MCAL_WRAPPER_DelayUS(uint32_t arg_u16US);
 *  \b Description                              :       this functions is used as a wrapper function to delay for a given micro seconds.
 *  @param  arg_u16MS [IN]                      :       time to delay for in micro seconds.
 *  @note                                       :       This is a blocking function until the delay is achieved and it uses Timer2.
 *  \b PRE-CONDITION                            :       make sure to call configure function the configuration file in the current directory.
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       it return one of error states indicating whether a failure or success happened (refer to @MCAL_WRAPPER_ErrStat_t in "MCAL_wrapper.h")
 *  @see                                        :       MCAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * #include "MCAL_wrapper.h"
 * 
 * int main() {
 *  MCAL_Config_ErrStat_t local_errState = MCAL_Config_ConfigAllPins();
 *  if(MCAL_Config_STAT_OK == local_errState)
 *  {
 *    local_errState = MCAL_WRAPPER_DelayUS(15);
 *    if(MCAL_WRAPPER_STAT_OK == local_errState)
 *    {
 *      // function delay success
 *    }
 *  }
 * }
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 21/06/2024 </td><td> 1.0.0            </td><td> AMS      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
MCAL_WRAPPER_ErrStat_t MCAL_WRAPPER_DelayUS(uint32_t arg_u16US);

/*** End of File **************************************************************/
#endif /*MCAL_WRAPPER_HEADER_H_*/
