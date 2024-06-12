/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   ADXL345 Digital Accelerometer                                                                               |
 * |    @file           :   ADXL345.c                                                                                                   |
 * |    @author         :   Abdelrahman Mohamed Salem                                                                                   |
 * |    @origin_date    :   24/05/2024                                                                                                  |
 * |    @version        :   1.0.0                                                                                                       |
 * |    @tool_chain     :   RISC-V Cross GCC                                                                                            |
 * |    @compiler       :   GCC                                                                                                         |
 * |    @C_standard     :   ISO C99 (-std=c99)                                                                                          |
 * |    @target         :   CH32V203C8T6                                                                                                |
 * |    @notes          :   None                                                                                                        |
 * |    @license        :   MIT License                                                                                                 |
 * |    @brief          :   this file contains code implementation for the function of ADXL345                                          |
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
 * |    24/05/2024      1.0.0           Abdelrahman Mohamed Salem       Interface Created.                                              |
 * |    24/05/2024      1.0.0           Abdelrahman Mohamed Salem       added the initialization function.                              |
 * --------------------------------------------------------------------------------------------------------------------------------------
 */

/******************************************************************************
 * Includes
 *******************************************************************************/
/**
 * @reason: contains standard definitions for standard integers
 */
#include "stdint.h"

/**
 * @reason: contains definition for NULL
 */
#include "common.h"

/**
 * @reason: contains constants common values
 */
#include "constants.h"

/**
 * @reason: contains useful functions that deals with bit level math
 */
#include "math_btt.h"

/**
 * @reason: contains function deceleration of ADXL345
*/
#include "ADXL345_header.h"

/**
 * @reason: contains private decelerations of ADXL345
*/
#include "ADXL345_private.h"

/**
 * @reason: contains configurations of ADXL345
*/
#include "ADXL345_config.h"

/**
 * @reason: contains register definitions of ADXL345
*/
#include "ADXL345_reg.h"


/**
 * @reason: contains wrapper function for SPI
*/
#include "MCAL_wrapper.h"

/**
 * @reason: contains configurations for ADXL345 SPI
 */
#include "MCAL_config.h"


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
 * @brief: transfer single data
*/
void HAL_ADXL345_Write_Single(MCAL_CONFIG_SPI_t* arg_pADXLSPI, uint8_t arg_u8Register_Address, uint8_t arg_u8Data) {

  uint16_t local_p16ArrData[] = {arg_u8Register_Address & 0x3F, arg_u8Data};
  MCAL_WRAPEPR_SPI_POLL_TRANSFER(arg_pADXLSPI, (uint8_t*) local_p16ArrData, 2, NULL);
}

/**
 * @brief: reads a single data
*/
uint8_t HAL_ADXL345_Read_Single(MCAL_CONFIG_SPI_t* arg_pADXLSPI, uint8_t arg_u8RegisterAddress)
{
  uint8_t local_u8Data = 0x80 | arg_u8RegisterAddress;
  MCAL_WRAPEPR_SPI_POLL_TRANSFER(arg_pADXLSPI, (uint8_t*) &local_u8Data, 1, (uint8_t*) &local_u8Data);
  return local_u8Data;
}


/**
 * @brief: sends multiple data writes utilizing coalesced write feature
*/
void HAL_ADXL345_Write_Mutliple(MCAL_CONFIG_SPI_t* arg_pADXLSPI, uint8_t arg_u8RegisterStartAddress, uint8_t* arg_pu8Data, uint8_t arg_u8Len) {

  uint8_t local_8Temp = 0x40 | (arg_u8RegisterStartAddress & 0x3F); // write register adreess and make multiple by 1 to write to consecutive registers
  MCAL_WRAPEPR_SPI_POLL_TRANSFER(arg_pADXLSPI, (uint8_t*) &local_8Temp, 1, NULL);
  MCAL_WRAPEPR_SPI_POLL_TRANSFER(arg_pADXLSPI, arg_pu8Data, arg_u8Len, NULL);

}


/**
 * 
*/
HAL_ADXL345_ErrStates_t HAL_ADXL345_Init(HAL_ADXL345_config_t* arg_pADXLConfig, MCAL_CONFIG_SPI_t* arg_pADXLSPI)
{

    HAL_ADXL345_Read_Single(arg_pADXLSPI, HAL_ADXL345_REG_DEVID);

    uint8_t local_u8Temp = 0;
    
    // TODO: configure free-fall if needed

    // use the update rate of 100 HZ as it's best for noise
    LIB_MATH_BTT_ASSIGN_BITS(local_u8Temp, HAL_ADXL345_REG_BW_RATE_RATE, arg_pADXLConfig->bandwidth_rate, 4);
    HAL_ADXL345_Write_Single(arg_pADXLSPI, HAL_ADXL345_REG_BW_RATE, local_u8Temp);

    // configure INT0 and INT1 for DATA_READY & FREE_FALL
    uint8_t local_u8TempArr[2] = {0};
    // LIB_MATH_BTT_SET_BIT(local_u8TempArr[0], HAL_ADXL345_REG_INT_ENABLE_DATA_READY);  
    // LIB_MATH_BTT_SET_BIT(local_u8TempArr[0], HAL_ADXL345_REG_INT_ENABLE_FREE_FALL);  
    // LIB_MATH_BTT_SET_BIT(local_u8TempArr[1], HAL_ADXL345_REG_INT_MAP_DATA_READY);      
    LIB_MATH_BTT_SET_BIT(local_u8TempArr[0], arg_pADXLConfig->int0_src);  
    LIB_MATH_BTT_SET_BIT(local_u8TempArr[0], arg_pADXLConfig->int1_src);  
    LIB_MATH_BTT_SET_BIT(local_u8TempArr[1], arg_pADXLConfig->int1_src);  
    HAL_ADXL345_Write_Mutliple(arg_pADXLSPI, HAL_ADXL345_REG_INT_ENABLE, local_u8TempArr, 2);

    // configure Data Format for ADXL345
    local_u8Temp = 0;
    // LIB_MATH_BTT_SET_BIT(local_u8Temp, HAL_ADXL345_REG_DATA_FORMAT_FULL_RES);  
    // LIB_MATH_BTT_ASSIGN_BITS(local_u8Temp, HAL_ADXL345_REG_DATA_FORMAT_RANGE, 0b10, 2);
    // HAL_ADXL345_Write_Single(HAL_ADXL345_REG_DATA_FORMAT, local_u8Temp);
    LIB_MATH_BTT_ASSIGN_BIT(local_u8Temp, HAL_ADXL345_REG_DATA_FORMAT_FULL_RES, arg_pADXLConfig->enableFullRange);  
    LIB_MATH_BTT_ASSIGN_BITS(local_u8Temp, HAL_ADXL345_REG_DATA_FORMAT_RANGE, arg_pADXLConfig->g_range, 2);
    HAL_ADXL345_Write_Single(arg_pADXLSPI, HAL_ADXL345_REG_DATA_FORMAT, local_u8Temp);


    // TODO: update offset registers

    // TODO: search for free-fall

    // put the device in measure mode
    local_u8Temp = 0; 
    LIB_MATH_BTT_SET_BIT(local_u8Temp, HAL_ADXL345_REG_POWER_CTL_MEASURE); 
    HAL_ADXL345_Write_Single(arg_pADXLSPI, HAL_ADXL345_REG_POWER_CTL, local_u8Temp);

    return HAL_ADXL345_OK;
}


/**
 * 
*/
HAL_ADXL345_ErrStates_t HAL_ADXL345_ReadAcc(MCAL_CONFIG_SPI_t* arg_pADXLSPI, HAL_ADXL345_Acc_t* arg_pReadings_t) 
{

  uint8_t local_u8Dummy[] = {0xC0 | HAL_ADXL345_REG_DATAX0};
  MCAL_WRAPEPR_SPI_POLL_TRANSFER(arg_pADXLSPI, (uint8_t*) local_u8Dummy, 1, NULL);

  local_u8Dummy[0] = 0;
  local_u8Dummy[1] = 0;
  MCAL_WRAPEPR_SPI_POLL_TRANSFER(arg_pADXLSPI, (uint8_t*) local_u8Dummy, 2, (uint8_t*) local_u8Dummy);
  arg_pReadings_t->x = local_u8Dummy[1] << 8 | local_u8Dummy[0];
  
  local_u8Dummy[0] = 0;
  local_u8Dummy[1] = 0;
  MCAL_WRAPEPR_SPI_POLL_TRANSFER(arg_pADXLSPI, (uint8_t*) local_u8Dummy, 1, (uint8_t*) local_u8Dummy);
  arg_pReadings_t->y = local_u8Dummy[1] << 8 | local_u8Dummy[0];

  local_u8Dummy[0] = 0;
  local_u8Dummy[1] = 0;
  MCAL_WRAPEPR_SPI_POLL_TRANSFER(arg_pADXLSPI, (uint8_t*) local_u8Dummy, 1, (uint8_t*) local_u8Dummy);
  arg_pReadings_t->z = local_u8Dummy[1] << 8 | local_u8Dummy[0];

  return HAL_ADXL345_OK;
}



/*************** END OF FUNCTIONS ***************************************************************************/
