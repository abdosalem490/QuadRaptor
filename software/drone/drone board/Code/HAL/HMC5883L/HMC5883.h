/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   header file for HMC5883L                                                                                    |
 * |    @file           :   HMC5883.h                                                                                                   |
 * |    @author         :   Mohab Zaghloul                                                                                              |
 * |    @origin_date    :   14/06/2024                                                                                                  |
 * |    @version        :   1.0.0                                                                                                       |
 * |    @tool_chain     :   RISC-V Cross GCC                                                                                            |
 * |    @compiler       :   GCC                                                                                                         |
 * |    @C_standard     :   ISO C99 (-std=c99)                                                                                          |
 * |    @target         :   CH32V203C8T6                                                                                                |
 * |    @notes          :   None                                                                                                        |
 * |    @license        :   MIT License                                                                                                 |
 * |    @brief          :   this file is the header file for HMC5883L Sensor                                                            |
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
 * |    14/06/2023      1.0.0           Mohab Zaghloul                  file Created.                                                   |
 * --------------------------------------------------------------------------------------------------------------------------------------
 */


#ifndef HAL_HMC5883L_H_
#define HAL_HMC5883L_H_

/******************************************************************************
 * Includes
 *******************************************************************************/

/**
 * 
 */
#include "stdint.h"

/******************************************************************************
 * Preprocessor Constants
 *******************************************************************************/

/* I2C master mode flag */
#define MASTER_TRANSMIT_MODE 0
#define MASTER_RECEIVER_MODE 1

/* Receiver buffer size */
#define I2C_Rx_BUFFER_SIZE   6

/* HMC5883L Constants */
#define HMC5883L_SLAVE_ADDRESS   (0x1E)
#define HMC5883L_REG_DATA        (0x03)
#define HMC5883L_REG_ID          (0x0A)

#define HMC5883L_REG_MODE        (0x02)
#define HMC5883L_CONTINUOUS_MODE (0x00)
#define HMC5883L_SINGLE_MODE     (0x01)

#define HMC5883L_REG_CONFIG_A    (0x00)
#define HMC5883L_SAMPLES_1       (0x00)
#define HMC5883L_SAMPLES_8       (0x60)
#define HMC5883L_OUTPUT_RATE_15  (0x10)

#define HMC5883L_REG_CONFIG_B    (0x01)
#define HMC5883L_RANGE_1_3       (0x20)
#define HMC5883L_GAIN            (1090.0)

/* MPU6050 auxiliary options*/
#define GY87_AUXILIARY           (1)
#define MPU6050_SLAVE_ADDRESS    (0x68)
#define MPU6050_REG_USER_CTRL    (0x6A)
#define MPU6050_DISABLE_MASTER   (0x00)
#define MPU6050_REG_BYPASS       (0x37)
#define MPU6050_ENABLE_BYPASS    (0x02)
#define MPU6050_REG_PWR_MGMT_1   (0x6B)



/******************************************************************************
 * Configuration Constants
 *******************************************************************************/

/******************************************************************************
 * Macros
 *******************************************************************************/

/******************************************************************************
 * Typedefs
 *******************************************************************************/

struct packet{

    // readings
    int16_t magnetometer_raw_x;
    int16_t magnetometer_raw_y;
    int16_t magnetometer_raw_z;

    // calibrated
    float calibrated_x;
    float calibrated_y;
    float calibrated_z;    

    // azimuths
    float azimuth;

};
typedef struct packet hmc5883l_packet;

/******************************************************************************
 * Variables
 *******************************************************************************/

/******************************************************************************
 * Function Prototypes
 *******************************************************************************/

/**
 *  \b function                                 :       None
 *  \b Description                              :       Initialize magnetometer.
 *  @param  arg_pFuncTaskFunction [IN]          :       None
 *  @param  arg_pu8TaskName [IN]                :       None.
 *  @param  arg_u16TaskStackDepth [IN]          :       None.
 *  @param  arg_u32TaskPriority [IN]            :       None.
 *  @param  arg_pTaskHandle [OUT]               :       None.
 *  @note                                       :       Only called once.
 *  \b PRE-CONDITION                            :       None.
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       None.
 *  @see                                        :       None.
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
 * <tr><td> 14/06/2024 </td><td> 1.0.0            </td><td> MZ      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
void hmc5883l_init();

/**
 *  \b function                                 :       None
 *  \b Description                              :       Get magnetometer measurements.
 *  @param  arg_pFuncTaskFunction [IN]          :       None
 *  @param  arg_pu8TaskName [IN]                :       None.
 *  @param  arg_u16TaskStackDepth [IN]          :       None.
 *  @param  arg_u32TaskPriority [IN]            :       None.
 *  @param  arg_pTaskHandle [OUT]               :       None.
 *  @note                                       :       hmc5883l_init must be called once in the program before using this function.
 *  \b PRE-CONDITION                            :       None.
 *  \b POST-CONDITION                           :       None.
 *  @return                                     :       None.
 *  @see                                        :       None.
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
 * <tr><td> 14/06/2024 </td><td> 1.0.0            </td><td> MZ      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */
void hmc5883l_read(hmc5883l_packet* data);

/*** End of File **************************************************************/
#endif /*HAL_HMC5883L_H_*/