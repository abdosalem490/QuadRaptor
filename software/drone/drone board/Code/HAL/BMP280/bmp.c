/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   source code file for BMP280                                                                                 |
 * |    @file           :   bmp.c                                                                                                       |
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


/******************************************************************************
 * Includes
 *******************************************************************************/

/**
 * 
 */
#include "BMP.h"

/**
 * 
 */
#include "MCAL_wrapper.h"

/**
 * 
 */
#include <math.h>

/**
 * 
 */
#include "stdint.h"

/**
 * @reason: contains definition for SPI through which BMP280 is connected
 */
#include "MCAL_config.h"


/**
 * @reason: contains NULL definitions
 */
#include "common.h"

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

Trimming_TypeDef trimmingParameter;
int32_t t_fine;

/******************************************************************************
 * Function Prototypes
 *******************************************************************************/

/******************************************************************************
 * Function Definitions
 *******************************************************************************/

/**
 * @brief: Read a byte from a BMP280 register
 */
uint8_t BMP280_ReadRegister(uint8_t reg) {
    reg = reg & (~0x80);
    uint8_t value[2] = {reg | 0x80 , 0};
    MCAL_WRAPEPR_SPI_POLL_TRANSFER(&MCAL_CFG_BMPSPI, value, 2, value);
    return value[1];
}

/**
 * @brief: Write a byte to a BMP280 register
 */
void BMP280_WriteRegister(uint8_t reg, uint8_t value) {
    reg = reg & (~0x80);
    uint8_t data[2] = {reg & (~0x80) , value};
    MCAL_WRAPEPR_SPI_POLL_TRANSFER(&MCAL_CFG_BMPSPI, data, 2, NULL);
}

/**
 * @brief: Read an unsigned 16-bit value from a BMP280 register
 */
uint16_t BMP280_ReadUnsignedShort(uint8_t reg) {
    uint8_t msb, lsb;
    uint16_t value;

    lsb = BMP280_ReadRegister(reg);
    msb = BMP280_ReadRegister(reg + 1);

    value = (msb << 8) | lsb;
    return value;
}

/**
 * @brief: Read a signed 16-bit value from a BMP280 register
 */
int16_t BMP280_ReadSignedShort(uint8_t reg) {
    uint8_t msb, lsb;
    int16_t value;

    lsb = BMP280_ReadRegister(reg);
    msb = BMP280_ReadRegister(reg + 1);

    value = (msb << 8) | lsb;
    return value;
}


/**
 * @brief: Retrieve trimming parameters from the BMP280 sensor
 */
void BMP280_get_trimming_parameters() {
    trimmingParameter.dig_T1 = BMP280_ReadUnsignedShort(DIG_T1);
    trimmingParameter.dig_P1 = BMP280_ReadUnsignedShort(DIG_P1);

    trimmingParameter.dig_T2 = BMP280_ReadSignedShort(DIG_T2);
    trimmingParameter.dig_T3 = BMP280_ReadSignedShort(DIG_T3);

    trimmingParameter.dig_P2 = BMP280_ReadSignedShort(DIG_P2);
    trimmingParameter.dig_P3 = BMP280_ReadSignedShort(DIG_P3);
    trimmingParameter.dig_P4 = BMP280_ReadSignedShort(DIG_P4);
    trimmingParameter.dig_P5 = BMP280_ReadSignedShort(DIG_P5);
    trimmingParameter.dig_P6 = BMP280_ReadSignedShort(DIG_P6);
    trimmingParameter.dig_P7 = BMP280_ReadSignedShort(DIG_P7);
    trimmingParameter.dig_P8 = BMP280_ReadSignedShort(DIG_P8);
    trimmingParameter.dig_P9 = BMP280_ReadSignedShort(DIG_P9);
}

/**
 * @brief: Read a 20-bit value from the BMP280 sensor
 */
uint32_t BMP280_ReadDataRegisters(uint8_t reg) {
    uint8_t msb, lsb, xlsb;
    uint32_t value;

    msb = BMP280_ReadRegister(reg);
    lsb = BMP280_ReadRegister(reg + 1);
    xlsb = BMP280_ReadRegister(reg + 2);

    value = ((uint32_t)msb << 16) | ((uint32_t)lsb << 8) | xlsb;
    return value;
}

/**
 * @brief: Retrieve raw temperature data from the BMP280 sensor
 */
void BMP280_GetTemperatureRawData(int32_t *adc_T) {
    *adc_T = BMP280_ReadDataRegisters(TEMP_MSB);
    *adc_T >>= 4; // The data is stored in the 20 most significant bits
}

/**
 * @brief: Retrieve raw pressure data from the BMP280 sensor
 */
void BMP280_GetPressureRawData(int32_t *adc_P) {
    *adc_P = BMP280_ReadDataRegisters(PRESS_MSB);
    *adc_P >>= 4; // The data is stored in the 20 most significant bits
}

/**
 * @brief: Compensate the temperature value using the raw data and trimming parameters
 */
float BMP280_CompensateTemperature(int32_t adc_T) {
    int32_t var1, var2;

    var1 = ((((adc_T >> 3) - ((int32_t)trimmingParameter.dig_T1 << 1))) * ((int32_t)trimmingParameter.dig_T2)) >> 11;
    var2 = (((((adc_T >> 4) - ((int32_t)trimmingParameter.dig_T1)) * ((adc_T >> 4) - ((int32_t)trimmingParameter.dig_T1))) >> 12) * ((int32_t)trimmingParameter.dig_T3)) >> 14;

    t_fine = var1 + var2;

    float T = (t_fine * 5 + 128) >> 8;
    T /= 100.0;
    return T;
}

/**
 * @brief: Compensate the pressure value using the raw data and trimming parameters
 */
float BMP280_CompensatePressure(int32_t adc_P) {
    int64_t var1, var2, p;

    var1 = ((int64_t)t_fine) - 128000;
    var2 = var1 * var1 * (int64_t)trimmingParameter.dig_P6;
    var2 = var2 + ((var1 * (int64_t)trimmingParameter.dig_P5) << 17);
    var2 = var2 + (((int64_t)trimmingParameter.dig_P4) << 35);
    var1 = ((var1 * var1 * (int64_t)trimmingParameter.dig_P3) >> 8) + ((var1 * (int64_t)trimmingParameter.dig_P2) << 12);
    var1 = (((((int64_t)1) << 47) + var1)) * ((int64_t)trimmingParameter.dig_P1) >> 33;

    if (var1 == 0) {
        return 0; // Avoid division by zero
    }
    p = 1048576 - adc_P;
    p = (((p << 31) - var2) * 3125) / var1;
    var1 = (((int64_t)trimmingParameter.dig_P9) * (p >> 13) * (p >> 13)) >> 25;
    var2 = (((int64_t)trimmingParameter.dig_P8) * p) >> 19;

    p = ((p + var1 + var2) >> 8) + (((int64_t)trimmingParameter.dig_P7) << 4);
    return (float)p / 25600.0;
}


/**
 * @brief: Initialize the BMP280 sensor
 */
void BMP280_Init() {
    BMP280_get_trimming_parameters();
    BMP280_WriteRegister(CONFIG, 0x00);
    BMP280_WriteRegister(CTRL_MEAS, 0xB7);
    MCAL_WRAPPER_DelayMS(150);
}

/**
 * @brief: Get the temperature value from the BMP280 sensor
 */
float BMP280_get_temperature() {
    int32_t adc_T;
    BMP280_GetTemperatureRawData(&adc_T);
    return BMP280_CompensateTemperature(adc_T);
}

/**
 * @brief: Get the pressure value from the BMP280 sensor
 */
float BMP280_get_pressure() {
    int32_t adc_P;
    BMP280_get_temperature(); // Ensure t_fine is updated
    BMP280_GetPressureRawData(&adc_P);
    return BMP280_CompensatePressure(adc_P);
}

/**
 * @brief: Calculate the altitude based on the pressure and a reference pressure
 */
float BMP280_get_altitude(float reference) {
    float pressure = BMP280_get_pressure();
    float altitude = 44330.0 * (1.0 - pow((pressure / reference), 0.1903));
    return altitude > 0.0 ? altitude : 0;
}

/*************** END OF FUNCTIONS ***************************************************************************/
