/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   ADXL345 Digital Accelerometer                                                                               |
 * |    @file           :   ADXL345_reg.h                                                                                               |
 * |    @author         :   Abdelrahman Mohamed Salem                                                                                   |
 * |    @origin_date    :   15/03/2024                                                                                                  |
 * |    @version        :   1.0.0                                                                                                       |
 * |    @tool_chain     :   RISC-V Cross GCC                                                                                            |
 * |    @compiler       :   GCC                                                                                                         |
 * |    @C_standard     :   ISO C99 (-std=c99)                                                                                          |
 * |    @target         :   CH32V203C8T6                                                                                                |
 * |    @notes          :   None                                                                                                        |
 * |    @license        :   MIT License                                                                                                 |
 * |    @brief          :   this file contains registers addresses and definitions structs that deals with ADXL345 registers            |
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
 * |    15/03/2024      1.0.0           Abdelrahman Mohamed Salem       Interface Created.                                              |
 * --------------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef HAL_ADXL345_REG_H_
#define HAL_ADXL345_REG_H_

/******************************************************************************
 * Includes
 *******************************************************************************/
/**
 * @reason: contains standard definitions for the integer variables
 */
#include "stdint.h"

/**
 * @reason: contains volatile keyword definition regarding selected compiler
 */
#include "common.h"

/******************************************************************************
 * Preprocessor Constants
 *******************************************************************************/

/******************************************************************************
 * Configuration Constants
 *******************************************************************************/

/******************************************************************************
 * Macros
 *******************************************************************************/

/**
 * @brief: bit position definitions for Register ACT_INACT_CTL
 */
#define HAL_ADXL345_REG_ACT_INACT_CTL_ACT_AC_DC 7      /**< */
#define HAL_ADXL345_REG_ACT_INACT_CTL_ACT_X_ENABLE 6   /**< */
#define HAL_ADXL345_REG_ACT_INACT_CTL_ACT_Y_ENABLE 5   /**< */
#define HAL_ADXL345_REG_ACT_INACT_CTL_ACT_Z_ENABLE 4   /**< */
#define HAL_ADXL345_REG_ACT_INACT_CTL_INACT_AC_DC 3    /**< */
#define HAL_ADXL345_REG_ACT_INACT_CTL_INACT_X_ENABLE 2 /**< */
#define HAL_ADXL345_REG_ACT_INACT_CTL_INACT_Y_ENABLE 1 /**< */
#define HAL_ADXL345_REG_ACT_INACT_CTL_INACT_Z_ENABLE 0 /**< */

/**
 * @brief: bit position definitions for Register TAP_AXES
 */
#define HAL_ADXL345_REG_TAP_AXES_SUPPRESS 3     /**< */
#define HAL_ADXL345_REG_TAP_AXES_TAP_X_ENABLE 2 /**< */
#define HAL_ADXL345_REG_TAP_AXES_TAP_Y_ENABLE 1 /**< */
#define HAL_ADXL345_REG_TAP_AXES_TAP_Z_ENABLE 0 /**< */

/**
 * @brief: bit position definitions for Register BW_RATE
 */
#define HAL_ADXL345_REG_BW_RATE_LOW_POWER 4 /**< */
#define HAL_ADXL345_REG_BW_RATE_RATE 0      /**< */

/**
 * @brief: bit position definitions for Register POWER_CTL
 */
#define HAL_ADXL345_REG_POWER_CTL_LINK 5       /**< */
#define HAL_ADXL345_REG_POWER_CTL_AUTO_SLEEP 4 /**< */
#define HAL_ADXL345_REG_POWER_CTL_MEASURE 3    /**< */
#define HAL_ADXL345_REG_POWER_CTL_SLEEP 2      /**< */
#define HAL_ADXL345_REG_POWER_CTL_WAKEUP 0     /**< */

/**
 * @brief: bit position definitions for Register INT_ENABLE
 */
#define HAL_ADXL345_REG_INT_ENABLE_DATA_READY 7 /**< */
#define HAL_ADXL345_REG_INT_ENABLE_SINGLE_TAP 6 /**< */
#define HAL_ADXL345_REG_INT_ENABLE_DOUBLE_TAP 5 /**< */
#define HAL_ADXL345_REG_INT_ENABLE_ACTIVITY 4   /**< */
#define HAL_ADXL345_REG_INT_ENABLE_INACTIVITY 3 /**< */
#define HAL_ADXL345_REG_INT_ENABLE_FREE_FALL 2  /**< */
#define HAL_ADXL345_REG_INT_ENABLE_WATERMARK 1  /**< */
#define HAL_ADXL345_REG_INT_ENABLE_OVERRUN 0    /**< */

/**
 * @brief: bit position definitions for Register INT_MAP
 */
#define HAL_ADXL345_REG_INT_MAP_DATA_READY 7 /**< */
#define HAL_ADXL345_REG_INT_MAP_SINGLE_TAP 6 /**< */
#define HAL_ADXL345_REG_INT_MAP_DOUBLE_TAP 5 /**< */
#define HAL_ADXL345_REG_INT_MAP_ACTIVITY 4   /**< */
#define HAL_ADXL345_REG_INT_MAP_INACTIVITY 3 /**< */
#define HAL_ADXL345_REG_INT_MAP_FREE_FALL 2  /**< */
#define HAL_ADXL345_REG_INT_MAP_WATERMARK 1  /**< */
#define HAL_ADXL345_REG_INT_MAP_OVERRUN 0    /**< */

/**
 * @brief: bit position definitions for Register INT_SOURCE
 */
#define HAL_ADXL345_REG_INT_SOURCE_DATA_READY 7 /**< */
#define HAL_ADXL345_REG_INT_SOURCE_SINGLE_TAP 6 /**< */
#define HAL_ADXL345_REG_INT_SOURCE_DOUBLE_TAP 5 /**< */
#define HAL_ADXL345_REG_INT_SOURCE_ACTIVITY 4   /**< */
#define HAL_ADXL345_REG_INT_SOURCE_INACTIVITY 3 /**< */
#define HAL_ADXL345_REG_INT_SOURCE_FREE_FALL 2  /**< */
#define HAL_ADXL345_REG_INT_SOURCE_WATERMARK 1  /**< */
#define HAL_ADXL345_REG_INT_SOURCE_OVERRUN 0    /**< */

/**
 * @brief: bit position definitions for Register DATA_FORMAT
 */
#define HAL_ADXL345_REG_DATA_FORMAT_SELF_TEST 7  /**< */
#define HAL_ADXL345_REG_DATA_FORMAT_SPI 6        /**< */
#define HAL_ADXL345_REG_DATA_FORMAT_INT_INVERT 5 /**< */
#define HAL_ADXL345_REG_DATA_FORMAT_FULL_RES 3   /**< */
#define HAL_ADXL345_REG_DATA_FORMAT_JUSTIFY 2    /**< */
#define HAL_ADXL345_REG_DATA_FORMAT_RANGE 0      /**< */

/**
 * @brief: bit position definitions for Register FIFO_CTL
 */
#define HAL_ADXL345_REG_FIFO_CTL_FIFO_MODE 6 /**< */
#define HAL_ADXL345_REG_FIFO_CTL_TRIGGER 5   /**< */
#define HAL_ADXL345_REG_FIFO_CTL_SAMPLES 0   /**< */

/**
 * @brief: bit position definitions for Register FIFO_STATUS
 */
#define HAL_ADXL345_REG_FIFO_STATUS_FIFO_TRIG 7 /**< */
#define HAL_ADXL345_REG_FIFO_STATUS_ENTRIES 0   /**< */

/******************************************************************************
 * Typedefs
 *******************************************************************************/

/**
 * @brief: this holds all registers used to configure ADXL345
 */
typedef enum
{
    HAL_ADXL345_REG_DEVID = 0x00,          /**< Device ID (a fixed device ID code of 0xE5) -> (R).*/
    HAL_ADXL345_REG_THRESH_TAP = 0x1D,     /**< Tap threshold -> (R/W).*/
    HAL_ADXL345_REG_OFSX = 0x1E,           /**< X-axis offset -> (R/W).*/
    HAL_ADXL345_REG_OFSY = 0x1F,           /**< Y-axis offset -> (R/W).*/
    HAL_ADXL345_REG_OFSZ = 0x20,           /**< Z-axis offset -> (R/W).*/
    HAL_ADXL345_REG_DUR = 0x21,            /**< Tap duration -> (R/W).*/
    HAL_ADXL345_REG_Latent = 0x22,         /**< Tap latency -> (R/W).*/
    HAL_ADXL345_REG_Window = 0x23,         /**< Tap window -> (R/W).*/
    HAL_ADXL345_REG_THRESH_ACT = 0x24,     /**< Activity threshold -> (R/W).*/
    HAL_ADXL345_REG_THRESH_INACT = 0x25,   /**< Inactivity threshold -> (R/W).*/
    HAL_ADXL345_REG_TIME_INACT = 0x26,     /**< Inactivity time -> (R/W).*/
    HAL_ADXL345_REG_ACT_INACT_CTL = 0x27,  /**< Axis enable control for activity and inactivity detection -> (R/W).*/
    HAL_ADXL345_REG_THRESH_FF = 0x28,      /**< Free-fall threshold -> (R/W).*/
    HAL_ADXL345_REG_TIME_FF = 0x29,        /**< Free-fall time -> (R/W).*/
    HAL_ADXL345_REG_TAP_AXES = 0x2A,       /**< Axis control for single tap/double tap -> (R/W).*/
    HAL_ADXL345_REG_ACT_TAP_STATUS = 0x2B, /**< Source of single tap/double tap -> (R).*/
    HAL_ADXL345_REG_BW_RATE = 0x2C,        /**< Data rate and power mode control -> (R/W).*/
    HAL_ADXL345_REG_POWER_CTL = 0x2D,      /**< Power-saving features control -> (R/W).*/
    HAL_ADXL345_REG_INT_ENABLE = 0x2E,     /**< Interrupt enable control -> (R/W).*/
    HAL_ADXL345_REG_INT_MAP = 0x2F,        /**< Interrupt mapping control -> (R/W).*/
    HAL_ADXL345_REG_INT_SOURCE = 0x30,     /**< Source of interrupts -> (R).*/
    HAL_ADXL345_REG_DATA_FORMAT = 0x31,    /**< Data format control -> (R/W).*/
    HAL_ADXL345_REG_DATAX0 = 0x32,         /**< X-Axis Data 0 -> (R).*/
    HAL_ADXL345_REG_DATAX1 = 0x33,         /**< X-Axis Data 1 -> (R).*/
    HAL_ADXL345_REG_DATAY0 = 0x34,         /**< Y-Axis Data 0 -> (R).*/
    HAL_ADXL345_REG_DATAY1 = 0x35,         /**< Y-Axis Data 1 -> (R).*/
    HAL_ADXL345_REG_DATAZ0 = 0x36,         /**< Z-Axis Data 0 -> (R).*/
    HAL_ADXL345_REG_DATAZ1 = 0x37,         /**< Z-Axis Data 1 -> (R).*/
    HAL_ADXL345_REG_FIFO_CTL = 0x38,       /**< FIFO control -> (R/W).*/
    HAL_ADXL345_REG_FIFO_STATUS = 0x39,    /**<  FIFO status -> (R).*/
} HAL_ADXL345_RegDef_t;

/******************************************************************************
 * Variables
 *******************************************************************************/

/******************************************************************************
 * Function Prototypes
 *******************************************************************************/

/*** End of File **************************************************************/
#endif /*HAL_ADXL345_REG_H_*/
