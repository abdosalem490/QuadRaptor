/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   wrapper file for the MCAL layer functions                                                                   |
 * |    @file           :   MCAL_config.h                                                                                               |
 * |    @author         :   Abdelrahman Mohamed Salem                                                                                   |
 * |    @origin_date    :   25/05/2024                                                                                                  |
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
 * |    25/05/2023      1.0.0           Abdelrahman Mohamed Salem       file Created.                                                   |
 * |    11/06/2023      1.0.0           Abdelrahman Mohamed Salem       created 'MCAL_WRAPEPR_SPI_POLL_TRANSFER'.                       |
 * |    12/06/2023      1.0.0           Mohab Zaghloul                  created 'I2C_start_transmission', 'I2C_write', 'I2C_stop',      |
 * |                                                                            'I2C_requestFrom', 'I2C_read' functions.                |
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
} MCAL_WRAPPER_ErrStat_t;


/******************************************************************************
 * Variables
 *******************************************************************************/

/******************************************************************************
 * Function Prototypes
 *******************************************************************************/

/**
 *  \b function                                 :       MCAL_WRAPPER_ErrStat_t MCAL_WRAPEPR_SPI_POLL_TRANSFER(MCAL_CONFIG_SPI_t *arg_pSPI, uint8_t* args_pu8InData, uint16_t arg_u16Len, uint8_t *args_pu8OutData);
 *  \b Description                              :       this functions is used as a wrapper function to the function of sending SPI data.
 *  @param  arg_pSPI [IN]                       :       pointer to the function that will represent our task to be executed
 *  @param  args_pu8InData [IN]                 :       base address of data to be transferred.
 *  @param  arg_u16Len [IN]                     :       length of data to be transferred.
 *  @param  args_u8OutData [OUT]                :       base address to store the received data from the SPI upon transfer.
 *                                                      make args_u16OutData = NULL incase you don't want to receive anything
 *  @note                                       :       this is a polling function halting the process execution until the SPI data is transferred.
 *  \b PRE-CONDITION                            :       make sure to call configure the configuration file in the current directory.
 *  \b POST-CONDITION                           :       None.
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
 *  local_errState = MCAL_WRAPEPR_SPI_POLL_TRANSFER(&MCAL_CFG_adxlSPI, 15, &temp);
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
MCAL_WRAPPER_ErrStat_t MCAL_WRAPEPR_SPI_POLL_TRANSFER(MCAL_CONFIG_SPI_t *arg_pSPI, uint8_t* args_pu8InData, uint16_t arg_u16Len, uint8_t *args_pu8OutData);



/**
 *  \b function                                 :       None
 *  \b Description                              :       None.
 *  @param  arg_pFuncTaskFunction [IN]          :       None
 *  @param  arg_pu8TaskName [IN]                :       None
 *  @param  arg_pTaskHandle [OUT]               :       None
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       None
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       None
 *  @see                                        :       None
 *
 *  \b Example:
 * @code
 * 
 *          None
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 12/06/2024 </td><td> 1.0.0            </td><td> MZ      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
void I2C_start_transmission(uint8_t receiver_address, uint8_t master_receive);

/**
 *  \b function                                 :       None
 *  \b Description                              :       None.
 *  @param  arg_pFuncTaskFunction [IN]          :       None
 *  @param  arg_pu8TaskName [IN]                :       None
 *  @param  arg_pTaskHandle [OUT]               :       None
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       None
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       None
 *  @see                                        :       None
 *
 *  \b Example:
 * @code
 * 
 *          None
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 12/06/2024 </td><td> 1.0.0            </td><td> MZ      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
void I2C_write(uint8_t value);


/**
 *  \b function                                 :       None
 *  \b Description                              :       None.
 *  @param  arg_pFuncTaskFunction [IN]          :       None
 *  @param  arg_pu8TaskName [IN]                :       None
 *  @param  arg_pTaskHandle [OUT]               :       None
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       None
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       None
 *  @see                                        :       None
 *
 *  \b Example:
 * @code
 * 
 *          None
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 12/06/2024 </td><td> 1.0.0            </td><td> MZ      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
void I2C_stop();

/**
 *  \b function                                 :       None
 *  \b Description                              :       None.
 *  @param  arg_pFuncTaskFunction [IN]          :       None
 *  @param  arg_pu8TaskName [IN]                :       None
 *  @param  arg_pTaskHandle [OUT]               :       None
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       None
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       None
 *  @see                                        :       None
 *
 *  \b Example:
 * @code
 * 
 *          None
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 12/06/2024 </td><td> 1.0.0            </td><td> MZ      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
uint8_t I2C_requestFrom(uint8_t address, uint8_t quantity);

/**
 *  \b function                                 :       None
 *  \b Description                              :       None.
 *  @param  arg_pFuncTaskFunction [IN]          :       None
 *  @param  arg_pu8TaskName [IN]                :       None
 *  @param  arg_pTaskHandle [OUT]               :       None
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       None
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       None
 *  @see                                        :       None
 *
 *  \b Example:
 * @code
 * 
 *          None
 * 
 * @endcode
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 12/06/2024 </td><td> 1.0.0            </td><td> MZ      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
uint8_t I2C_read();


/*** End of File **************************************************************/
#endif /*MCAL_WRAPPER_HEADER_H_*/
