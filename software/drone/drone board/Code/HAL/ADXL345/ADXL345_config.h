/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   ADXL345 Digital Accelerometer                                                                               |
 * |    @file           :   ADXL345_config.h                                                                                            |
 * |    @author         :   Abdelrahman Mohamed Fathy                                                                                   |
 * |    @origin_date    :   24/05/2024                                                                                                  |
 * |    @version        :   1.0.0                                                                                                       |
 * |    @tool_chain     :   RISC-V Cross GCC                                                                                            |
 * |    @compiler       :   GCC                                                                                                         |
 * |    @C_standard     :   ISO C99 (-std=c99)                                                                                          |
 * |    @target         :   CH32V203C8T6                                                                                                |
 * |    @notes          :   None                                                                                                        |
 * |    @license        :   MIT License                                                                                                 |
 * |    @brief          :   this header file contains configurations set by user for adxl345                                            |
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
 * |    24/05/2024      1.0.0           Abdelrahman Mohamed Salem       added configuration variable.                                   |
 * --------------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef HAL_ADXL345_CONFIG_H_
#define HAL_ADXL345_CONFIG_H_

/******************************************************************************
 * Includes
 *******************************************************************************/

/**
 * @reason: it contains standard definition for integers
 */
#include "stdint.h"

/**
 * @reason: it holds the definitions for (ENABLED and DISABLED)
 */
#include "constants.h"

/**
 * @reason: contains bit position defintions for ADXL345
*/
#include "ADXL345_reg.h"

/******************************************************************************
 * Preprocessor Constants
 *******************************************************************************/

/******************************************************************************
 * Configuration Constants
 *******************************************************************************/

/**
 * @enum: HAL_ADXL345_BW_RATE_t
 * @brief: the available frequencies for capturing new datas
*/
typedef enum{
    HAL_ADXL345_BW_RATE_3200HZ = 0b1111, /**< 3200 HZ*/
    HAL_ADXL345_BW_RATE_1600HZ = 0b1110, /**< 1600 HZ*/
    HAL_ADXL345_BW_RATE_800HZ  = 0b1101,  /**< 800 HZ*/
    HAL_ADXL345_BW_RATE_400HZ  = 0b1100,  /**< 400 HZ*/
    HAL_ADXL345_BW_RATE_200HZ  = 0b1011,  /**< 200 HZ*/
    HAL_ADXL345_BW_RATE_100HZ  = 0b1010,  /**< 100 HZ*/
    HAL_ADXL345_BW_RATE_50HZ   = 0b1001,   /**< 50 HZ*/
    HAL_ADXL345_BW_RATE_25HZ   = 0b1000,   /**< 25 HZ*/
} HAL_ADXL345_BW_RATE_t;


/**
 * @enum: HAL_ADXL345_INT_SRC_t
 * @brief: interrupt sources for the ADXL345
*/
typedef enum{
    HAL_ADXL345_INT_SRC_DATA_READY = 7, /**< The DATA_READY bit is set when new data is available and is cleared when no new data is available. */
    HAL_ADXL345_INT_SRC_SINGLE_TAP = 6, /**< The SINGLE_TAP bit is set when a single acceleration event that is greater than the value in the THRESH_TAP register (Address 0x1D) occurs for less time than is specified in the DUR register (Address 0x21).. */
    HAL_ADXL345_INT_SRC_DOUBLE_TAP = 5, /**< The DOUBLE_TAP bit is set when two acceleration events that are greater than the value in the THRESH_TAP register (Address 0x1D) occur for less time than is specified in the DUR register (Address 0x21), with the second tap starting after the time specified by the latent register (Address 0x22) but within the time specified in the window register (Address 0x23). See the Tap Detection section for more details. */
    HAL_ADXL345_INT_SRC_ACTIVITY   = 4,   /**< The activity bit is set when acceleration greater than the value stored in the THRESH_ACT register (Address 0x24) is experienced on any participating axis, set by the ACT_INACT_CTL register (Address 0x27). */
    HAL_ADXL345_INT_SRC_INACTIVITY = 3, /**< The inactivity bit is set when acceleration of less than the value stored in the THRESH_INACT register (Address 0x25) is experienced for more time than is specified in the TIME_INACT register (Address 0x26) on all participating axes, as set by the ACT_INACT_CTL register (Address 0x27). The maximum value for TIME_INACT is 255 sec. */
    HAL_ADXL345_INT_SRC_FREE_FALL  = 2,  /**< The FREE_FALL bit is set when acceleration of less than the value stored in the THRESH_FF register (Address 0x28) is experienced for more time than is specified in the TIME_FF register (Address 0x29) on all axes (logical AND). The FREE_FALL interrupt differs from the inactivity interrupt as follows: all axes always participate and are logically AND’ed, the timer period is much smaller (1.28 sec maximum), and the mode of operation is always dc-coupled. */
    HAL_ADXL345_INT_SRC_WATERMARK  = 1,  /**< The watermark bit is set when the number of samples in FIFO equals the value stored in the samples bits (Register FIFO_CTL, Address 0x38). The watermark bit is cleared automatically when FIFO is read, and the content returns to a value below the value stored in the samples bits. */
    HAL_ADXL345_INT_SRC_OVERRUN    = 0,    /**< The overrun bit is set when new data replaces unread data. The precise operation of the overrun function depends on the FIFO mode. In bypass mode, the overrun bit is set when new data replaces unread data in the DATAX, DATAY, and DATAZ registers (Address 0x32 to Address 0x37). In all other modes, the overrun bit is set when FIFO is filled. The overrun bit is automatically cleared when the contents of FIFO are read. */
} HAL_ADXL345_INT_SRC_t;

/**
 * @enum:HAL_ADXL345_G_RANGE_t
 * @brief: define range for g
*/
typedef enum{
    HAL_ADXL345_G_RANGE_2  = 0,  /**< -2g to +2g*/
    HAL_ADXL345_G_RANGE_4  = 1,  /**< -4g to +4g*/
    HAL_ADXL345_G_RANGE_8  = 2,  /**< -8g to +8g*/
    HAL_ADXL345_G_RANGE_16 = 3, /**< -16g to +16g*/
} HAL_ADXL345_G_RANGE_t;

/**
 * @enum: HAL_ADXL345_INT_POL_t
 * @brief: specify the polarity for interrupt
*/
typedef enum{
  HAL_ADXL345_INT_POL_ACT_HIGH, /**< active high*/  
  HAL_ADXL345_INT_POL_ACT_LOW, /**< active low*/  
} HAL_ADXL345_INT_POL_t;

/******************************************************************************
 * Macros
 *******************************************************************************/

/******************************************************************************
 * Tables
 *******************************************************************************/


/******************************************************************************
 * Typedefs
 *******************************************************************************/

/**
 * @struct: HAL_ADXL345_config_t
 * @brief: this the template of the struct to be supplied to our initialization function to act as configuration 
*/
typedef struct 
{
    uint8_t bandwidth_rate;     /**< how frequent you want readings, refer to @HAL_ADXL345_BW_RATE_t in "ADXL345_config.h" */
    uint8_t int0_src;           /**< specify the source of interrupt for pin 'INT0', refer to @HAL_ADXL345_INT_SRC_t in "ADXL345_config.h" */
    uint8_t int1_src;           /**< specify the source of interrupt for pin 'INT1', refer to @HAL_ADXL345_INT_SRC_t in "ADXL345_config.h" */
    uint8_t int_pol;            /**< specify the polarity of the interrupt, refer to @HAL_ADXL345_INT_POL_t in "ADXL345_config.h"*/
    uint8_t g_range;            /**< specify the range for g, refer to @HAL_ADXL345_G_RANGE_t in "ADXL345_config.h" */
    uint8_t enableFullRange;    /**< if enabled then the device will work in full range to maintain 4mg/LSB otherwise the device work in 10 bit mode, refer to @LIB_CONSTANTS_DriverStates_t in "constants.h" */
} HAL_ADXL345_config_t;

/******************************************************************************
 * Variables
 *******************************************************************************/

/******************************************************************************
 * Function Prototypes
 *******************************************************************************/

/*** End of File **************************************************************/
#endif /*HAL_ADXL345_CONFIG_H_*/
