/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   ADXL345 Digital Accelerometer                                                                               |
 * |    @file           :   ADXL345_header.h                                                                                            |
 * |    @author         :   Abdelrahman Mohamed Salem                                                                                   |
 * |    @origin_date    :   16/03/2024                                                                                                  |
 * |    @version        :   1.0.0                                                                                                       |
 * |    @tool_chain     :   RISC-V Cross GCC                                                                                            |
 * |    @compiler       :   GCC                                                                                                         |
 * |    @C_standard     :   ISO C99 (-std=c99)                                                                                          |
 * |    @target         :   CH32V203C8T6                                                                                                |
 * |    @notes          :   None                                                                                                        |
 * |    @license        :   MIT License                                                                                                 |
 * |    @brief          :   this header file contains useful functions to interface with the ADXL345 Digital Accelerometer              |
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
 * |    16/03/2024      1.0.0           Abdelrahman Mohamed Salem       Interface Created.                                              |
 * |    24/05/2024      1.0.0           Abdelrahman Mohamed Salem       added the initialization function.                              |
 * --------------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef HAL_ADXL345_HEADER_H_
#define HAL_ADXL345_HEADER_H_

/******************************************************************************
 * Includes
 *******************************************************************************/

/**
 * @reason: contains standard integer definition
 */
#include "stdint.h"

/**
 * @reason: contains configuration template
*/
#include "ADXL345_config.h"

/**
 * @reason: contains the definitions for which SPI the ADXL is connected to
*/
#include "MCAL_config.h"

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
 * @enum: Hal_ADXL345_ErrStates_t
 * @brief: contains all possible errors that can result from dealing with the ADXL335 Digital Accelerometer.
 */
typedef enum
{
    HAL_ADXL345_OK,                 /**< it means everything has gone as intended so no errors*/
    HAL_ADXL345_ERR_INVALID_PARAMS, /**< it means that the supplied parameters of the function are invalid*/
    HAL_ADXL345_ERR_INVALID_CONFIG, /**< it means that the supplied configurations in the "ADXL345_config.h" file are incorrect*/
} HAL_ADXL345_ErrStates_t;


/**
 * @struct:
 * @brief: to read the acceleration values using this struct
*/
typedef struct {
    int16_t x; /**< acceleration in x-direction*/
    int16_t y; /**< acceleration in x-direction*/
    int16_t z; /**< acceleration in x-direction*/
} HAL_ADXL345_Acc_t;

/******************************************************************************
 * Variables
 *******************************************************************************/

/******************************************************************************
 * Function Prototypes
 *******************************************************************************/

/**
 *  \b function                     :       HAL_ADXL345_ErrStates_t HAL_ADXL345_Init(HAL_ADXL345_config_t* arg_pADXLConfig, MCAL_CONFIG_ADXLl345SPI_t* arg_pADXLSPI);
 *  \b Description                  :       this functions initialize the ADXL with the configurations supplied.
 *  @param  arg_pADXLConfig [IN]    :       these are the configurations related to the ADXL345 where the struct is defined in "ADXL345_config.h".
 *  @param  arg_pADXLSPI [IN]       :       these are the configurations related to the SPI communication where the struct is defined in "MCAL_config.h".
 *  @note                           :       This shall be the first function to be called before using any other function in this interface, also it's a blocking function
 *                                          IT IS ADVISED TO CALL HAL_ADXL345_Init() BEFORE CALLING ANY OTHER FUNCTION
 *  \b PRE-CONDITION                :       make sure to edit all configurations in file "MCAL_config.h" (any array labeled with @user_todo shall be edited)
 *  \b POST-CONDITION               :       it configures the ADXL345 pins IC.
 *  @return                         :       it return one of error states indicating whether a failure or success happened during initialization (refer to @HAL_ADXL345_ErrStates_t in "ADXL345_header.h")
 *  @see                            :       HAL_ADXL345_ReadAcc(HAL_ADXL345_Acc_t* arg_pReadings_t)
 *
 *  \b Example:
 * @code
 * #include "ADXL345_header.h"
 * int main() {
 *  HAL_ADXL345_config_t local_adxl345Config_t;
 *  local_adxl345Config_t.bandwidth_rate = HAL_ADXL345_BW_RATE_800HZ;
 *  local_adxl345Config_t.enableFullRange = LIB_CONSTANTS_ENABLED;
 *  local_adxl345Config_t.g_range = HAL_ADXL345_G_RANGE_8;
 *  local_adxl345Config_t.int_pol = HAL_ADXL345_INT_POL_ACT_LOW;
 *  local_adxl345Config_t.int0_src = HAL_ADXL345_INT_SRC_DATA_READY;
 *  local_adxl345Config_t.int1_src = HAL_ADXL345_INT_SRC_FREE_FALL;
 * 
 *  MCAL_CONFIG_ADXLl345SPI_t MCAL_CFG_adxlSPI;
 *  MCAL_CFG_adxlSPI.SPI = SPI1;
 *  MCAL_CFG_adxlSPI.GPIO = GPIOC;
 *  MCAL_CFG_adxlSPI.SlavePin = GPIO_Pin_14;
 *  MCAL_CFG_adxlSPI.spiConfig.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
 *  MCAL_CFG_adxlSPI.spiConfig.SPI_Mode = SPI_Mode_Master;
 *  MCAL_CFG_adxlSPI.spiConfig.SPI_DataSize = SPI_DataSize_8b;
 *  MCAL_CFG_adxlSPI.spiConfig.SPI_CPOL = SPI_CPOL_High;
 *  MCAL_CFG_adxlSPI.spiConfig.SPI_CPHA = SPI_CPHA_2Edge;
 *  MCAL_CFG_adxlSPI.spiConfig.SPI_NSS = SPI_NSS_Soft;
 *  MCAL_CFG_adxlSPI.spiConfig.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
 *  MCAL_CFG_adxlSPI.spiConfig.SPI_FirstBit = SPI_FirstBit_MSB;
 *  MCAL_CFG_adxlSPI.spiConfig.SPI_CRCPolynomial = 0b101;
 * 
 *  HAL_ADXL345_Init(&local_adxl345Config_t, &MCAL_CFG_adxlSPI);
 *  HAL_ADXL345_ErrStates_t local_errState_t = HAL_ADXL345_Init(&local_adxl345Config_t, &MCAL_CFG_adxlSPI);
 *  if (local_errState_t == HAL_ADXL345_OK)
 *  {
 *      // ADXL345 initialized successfully
 *  }
 *  return 0;
 * }
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 03/09/2023 </td><td> 1.0.0            </td><td> AMS      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
HAL_ADXL345_ErrStates_t HAL_ADXL345_Init(HAL_ADXL345_config_t* arg_pADXLConfig, MCAL_CONFIG_SPI_t* arg_pADXLSPI);

/**
 *  \b function                                 :       HAL_ADXL345_ErrStates_t HAL_ADXL345_ReadAcc(HAL_ADXL345_Acc_t* arg_pReadings_t)
 *  \b Description                              :       this functions is used to read acceleration of the ADXL345.
 *  @param  arg_pADXLSPI [IN]                   :       this is the SPI through which ADXL345 is connected to, refer to @MCAL_CONFIG_SPI_t in "MCAL_config.h".
 *  @param  arg_pReadings_t [OUT]               :       these are the readings we get out out of the ADXL345.
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       make sure to call HAL_ADXL345_Init().
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       it return one of error states indicating whether a failure or success happened (refer to @HAL_ADXL345_ErrStates_t in "ADXL345_header.h")
 *  @see                                        :       HAL_ADXL345_Init()
 *  @see                                        :       HAL_ADXL345_PinStateModify(uint16_t arg_u16ADXL345Name, uint16_t arg_u16PinNumber, const uint8_t argConst_u8Operation)
 *
 *  \b Example:
 * @code
 * #include "ADXL345_header.h"
 * int main() {
 *  HAL_ADXL345_Init();    // make sure that you edited any array in "ADXL345_config.h" labeled with @user_todo so that ADXL345 can be initialized correctly
 *  uint8_t state = 0;
 *  HAL_ADXL345_ErrStates_t local_errState_t = HAL_ADXL345_PinStateRead(HAL_ADXL345_PORTC, HAL_ADXL345_PIN7, &state);
 *  if (local_errState_t == HAL_ADXL345_OK)
 *  {
 *      // state of pin 7 on port C is written into variable state
 *  }
 *  return 0;
 * }
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 03/09/2023 </td><td> 1.0.0            </td><td> AMS      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
HAL_ADXL345_ErrStates_t HAL_ADXL345_ReadAcc(MCAL_CONFIG_SPI_t* arg_pADXLSPI, HAL_ADXL345_Acc_t* arg_pReadings_t);

/*** End of File **************************************************************/
#endif /*HAL_ADXL345_HEADER_H_*/