/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   configuration file for the Micro-controller                                                                 |
 * |    @file           :   MCAL_config.h                                                                                               |
 * |    @author         :   Abdelrahman Mohamed Salem                                                                                   |
 * |    @origin_date    :   20/05/2024                                                                                                  |
 * |    @version        :   1.0.0                                                                                                       |
 * |    @tool_chain     :   RISC-V Cross GCC                                                                                            |
 * |    @compiler       :   GCC                                                                                                         |
 * |    @C_standard     :   ISO C99 (-std=c99)                                                                                          |
 * |    @target         :   CH32V203C8T6                                                                                                |
 * |    @notes          :   None                                                                                                        |
 * |    @license        :   MIT License                                                                                                 |
 * |    @brief          :   this file is the main entry to our application code that will run                                           |
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
 * |    20/05/2023      1.0.0           Abdelrahman Mohamed Salem       file Created.                                                   |
 * |    24/05/2023      1.0.0           Abdelrahman Mohamed Salem       Added configurations for SPI of ADXL345.                        |
 * --------------------------------------------------------------------------------------------------------------------------------------
 */


#ifndef MCAL_CONFIG_H_
#define MCAL_CONFIG_H_  

/******************************************************************************
 * Includes
 *******************************************************************************/

/**
 * @reason: contains definitons for peripherals
*/
#include "ch32v20x.h"

/**
 * @reason: contains definitions for SPI
*/
#include "ch32v20x_spi.h"

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
  MCAL_Config_STAT_OK,
  MCAL_Config_STAT_INVALID_PARAMS,
} MCAL_Config_ErrStat_t;

/**
 * @brief: this is the struct that deals with spi
*/
typedef struct{
    SPI_TypeDef* SPI;           /**< this is which SPI to use with ADXL345 */
    GPIO_TypeDef* GPIO;         /**< this is which GPIO the CSS pin is connected to use with ADXL345 */
    uint16_t SlavePin;          /**< this is which pin is for CSS for ADXL345 */
    SPI_InitTypeDef spiConfig;  /**< this the configuration for the SPI*/
} MCAL_CONFIG_SPI_t;

/******************************************************************************
 * Variables
 *******************************************************************************/

/**
 * @brief: to use the variable in HAL library
*/
extern MCAL_CONFIG_SPI_t MCAL_CFG_adxlSPI;


// TODO: define pins configurations as a table here to be read by configuration function to configure all pins (MCAL Module task)

/******************************************************************************
 * Function Prototypes
 *******************************************************************************/

/**
 *  \b function                                 :       MCAL_Config_ErrStat_t MCAL_Config_ConfigAllPins(void);
 *  \b Description                              :       this functions is used to configure all the pins of the MCU given the application and enable the clock of all the needed modules.
 *  @note                                       :       To be modified so that the configuration of the pins is given be a static array written inside configuration file.
 *  \b PRE-CONDITION                            :       make sure to call configure the clock of the MCU beforehand.
 *  \b POST-CONDITION                           :       enable all the clocks and peripheral needed of the MCU, modify the functionality of pins as per application.
 *  @return                                     :       it return one of error states indicating whether a failure or success happened (refer to @MCAL_Config_ErrStat_t in "MCAL_config.h")
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * 
 * #include "MCAL_config.h"
 * 
 * int main() {
 * SERVICE_RTOS_ErrStat_t local_TaskCreateState_t = MCAL_Config_ConfigAllPins();
 * if(SERVICE_RTOS_STAT_OK == local_TaskCreateState_t)
 * {
 *  // the pins are configured successfully
 * }
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 20/05/2024 </td><td> 1.0.0            </td><td> AMS      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
MCAL_Config_ErrStat_t MCAL_Config_ConfigAllPins(void);

/*** End of File **************************************************************/
#endif /*MCAL_CONFIG_H_*/