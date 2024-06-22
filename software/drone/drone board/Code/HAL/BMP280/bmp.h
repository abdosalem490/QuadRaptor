/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   reg and bit position defs for BMP280                                                                        |
 * |    @file           :   bmp.h                                                                                                       |
 * |    @author         :   Ahmed Fawzy                                                                                                 |
 * |    @origin_date    :   22/06/2024                                                                                                  |
 * |    @version        :   1.0.0                                                                                                       |
 * |    @tool_chain     :   RISC-V Cross GCC                                                                                            |
 * |    @compiler       :   GCC                                                                                                         |
 * |    @C_standard     :   ISO C99 (-std=c99)                                                                                          |
 * |    @target         :   CH32V203C8T6                                                                                                |
 * |    @notes          :   None                                                                                                        |
 * |    @license        :   MIT License                                                                                                 |
 * |    @brief          :   this header file contains useful functions for interface with BMP280                                        |
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
 * |    22/06/2023      1.0.0           Ahmed Fawzy                     Interface Created.                                              |
 * --------------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef BMP280_H
#define BMP280_H


/******************************************************************************
 * Includes
 *******************************************************************************/

/**
 * 
 */
#include "stdint.h"

/**
 * 
 */
#include "BMP_def.h"


/******************************************************************************
 * Preprocessor Constants
 *******************************************************************************/

// BMP280 I2C address
#define BMP280_I2C_ADDRESS 0x76

/******************************************************************************
 * Configuration Constants
 *******************************************************************************/

/******************************************************************************
 * Macros
 *******************************************************************************/

/******************************************************************************
 * Typedefs
 *******************************************************************************/

// Trimming parameters structure
typedef struct {
    uint16_t dig_T1;
    int16_t dig_T2;
    int16_t dig_T3;
    uint16_t dig_P1;
    int16_t dig_P2;
    int16_t dig_P3;
    int16_t dig_P4;
    int16_t dig_P5;
    int16_t dig_P6;
    int16_t dig_P7;
    int16_t dig_P8;
    int16_t dig_P9;
} Trimming_TypeDef;


/******************************************************************************
 * Variables
 *******************************************************************************/

/**
 * 
 */
extern Trimming_TypeDef trimmingParameter;

/**
 * 
 */
extern int32_t t_fine;


/******************************************************************************
 * Function Prototypes
 *******************************************************************************/

/**
 *  \b function                                 :       None
 *  \b Description                              :       None
 *  @param  arg_pFuncTaskFunction [IN]          :       None
 *  @param  arg_pu8TaskName [IN]                :       None
 *  @param  arg_u16TaskStackDepth [IN]          :       None
 *  @param  arg_u32TaskPriority [IN]            :       None
 *  @param  arg_pTaskHandle [OUT]               :       None
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       None
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       None
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
 * <tr><td> 22/06/2024 </td><td> 1.0.0            </td><td> AF      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
void BMP280_Init(void);

/**
 *  \b function                                 :       None
 *  \b Description                              :       None
 *  @param  arg_pFuncTaskFunction [IN]          :       None
 *  @param  arg_pu8TaskName [IN]                :       None
 *  @param  arg_u16TaskStackDepth [IN]          :       None
 *  @param  arg_u32TaskPriority [IN]            :       None
 *  @param  arg_pTaskHandle [OUT]               :       None
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       None
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       None
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
 * <tr><td> 22/06/2024 </td><td> 1.0.0            </td><td> AF      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
float BMP280_get_temperature(void);


/**
 *  \b function                                 :       None
 *  \b Description                              :       None
 *  @param  arg_pFuncTaskFunction [IN]          :       None
 *  @param  arg_pu8TaskName [IN]                :       None
 *  @param  arg_u16TaskStackDepth [IN]          :       None
 *  @param  arg_u32TaskPriority [IN]            :       None
 *  @param  arg_pTaskHandle [OUT]               :       None
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       None
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       None
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
 * <tr><td> 22/06/2024 </td><td> 1.0.0            </td><td> AF      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
float BMP280_get_pressure(void);

/**
 *  \b function                                 :       None
 *  \b Description                              :       None
 *  @param  arg_pFuncTaskFunction [IN]          :       None
 *  @param  arg_pu8TaskName [IN]                :       None
 *  @param  arg_u16TaskStackDepth [IN]          :       None
 *  @param  arg_u32TaskPriority [IN]            :       None
 *  @param  arg_pTaskHandle [OUT]               :       None
 *  @note                                       :       None.
 *  \b PRE-CONDITION                            :       None
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       None
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
 * <tr><td> 22/06/2024 </td><td> 1.0.0            </td><td> AF      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
float BMP280_get_altitude(float reference);

/*** End of File **************************************************************/
#endif // BMP280_H
