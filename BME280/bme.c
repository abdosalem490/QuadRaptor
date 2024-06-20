#include "bme.h"
#include "debug.h"
#include <math.h>
#include <stdint.h>

Trimming_TypeDef trimmingParameter;
int32_t t_fine;

// Initialize I2C peripheral
void I2C_init(void) {
    I2C_InitTypeDef I2C_InitStruct;
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    I2C_InitStruct.I2C_ClockSpeed = 100000;
    I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStruct.I2C_OwnAddress1 = 0x00;
    I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Init(I2C1, &I2C_InitStruct);
    I2C_Cmd(I2C1, ENABLE);
}

// Read a byte from a BME280 register
uint8_t BME280_ReadRegister(uint8_t reg) {
    uint8_t value;

    I2C_AcknowledgeConfig(I2C1, ENABLE);
    I2C_GenerateSTART(I2C1, ENABLE);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
    I2C_Send7bitAddress(I2C1, BME280_I2C_ADDRESS << 1, I2C_Direction_Transmitter);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    I2C_SendData(I2C1, reg);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    I2C_GenerateSTART(I2C1, ENABLE);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
    I2C_Send7bitAddress(I2C1, BME280_I2C_ADDRESS << 1, I2C_Direction_Receiver);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
    value = I2C_ReceiveData(I2C1);
    I2C_GenerateSTOP(I2C1, ENABLE);

    return value;
}

// Write a byte to a BME280 register
void BME280_WriteRegister(uint8_t reg, uint8_t value) {
    I2C_AcknowledgeConfig(I2C1, ENABLE);
    I2C_GenerateSTART(I2C1, ENABLE);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
    I2C_Send7bitAddress(I2C1, BME280_I2C_ADDRESS << 1, I2C_Direction_Transmitter);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    I2C_SendData(I2C1, reg);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    I2C_SendData(I2C1, value);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    I2C_GenerateSTOP(I2C1, ENABLE);
}

// Read an unsigned 16-bit value from a BME280 register
uint16_t BME280_ReadUnsignedShort(uint8_t reg) {
    uint8_t msb, lsb;
    uint16_t value;

    lsb = BME280_ReadRegister(reg);
    msb = BME280_ReadRegister(reg + 1);

    value = (msb << 8) | lsb;
    return value;
}

// Read a signed 16-bit value from a BME280 register
int16_t BME280_ReadSignedShort(uint8_t reg) {
    uint8_t msb, lsb;
    int16_t value;

    lsb = BME280_ReadRegister(reg);
    msb = BME280_ReadRegister(reg + 1);

    value = (msb << 8) | lsb;
    return value;
}

// Retrieve trimming parameters from the BME280 sensor
void BME280_get_trimming_parameters() {
    trimmingParameter.dig_T1 = BME280_ReadUnsignedShort(DIG_T1);
    trimmingParameter.dig_P1 = BME280_ReadUnsignedShort(DIG_P1);

    trimmingParameter.dig_T2 = BME280_ReadSignedShort(DIG_T2);
    trimmingParameter.dig_T3 = BME280_ReadSignedShort(DIG_T3);

    trimmingParameter.dig_P2 = BME280_ReadSignedShort(DIG_P2);
    trimmingParameter.dig_P3 = BME280_ReadSignedShort(DIG_P3);
    trimmingParameter.dig_P4 = BME280_ReadSignedShort(DIG_P4);
    trimmingParameter.dig_P5 = BME280_ReadSignedShort(DIG_P5);
    trimmingParameter.dig_P6 = BME280_ReadSignedShort(DIG_P6);
    trimmingParameter.dig_P7 = BME280_ReadSignedShort(DIG_P7);
    trimmingParameter.dig_P8 = BME280_ReadSignedShort(DIG_P8);
    trimmingParameter.dig_P9 = BME280_ReadSignedShort(DIG_P9);
}

// Read a 20-bit value from the BME280 sensor
uint32_t BME280_ReadDataRegisters(uint8_t reg) {
    uint8_t msb, lsb, xlsb;
    uint32_t value;

    msb = BME280_ReadRegister(reg);
    lsb = BME280_ReadRegister(reg + 1);
    xlsb = BME280_ReadRegister(reg + 2);

    value = ((uint32_t)msb << 16) | ((uint32_t)lsb << 8) | xlsb;
    return value;
}

// Retrieve raw temperature data from the BME280 sensor
void BME280_GetTemperatureRawData(int32_t *adc_T) {
    *adc_T = BME280_ReadDataRegisters(TEMP_MSB);
    *adc_T >>= 4; // The data is stored in the 20 most significant bits
}

// Retrieve raw pressure data from the BME280 sensor
void BME280_GetPressureRawData(int32_t *adc_P) {
    *adc_P = BME280_ReadDataRegisters(PRESS_MSB);
    *adc_P >>= 4; // The data is stored in the 20 most significant bits
}

// Compensate the temperature value using the raw data and trimming parameters
float BME280_CompensateTemperature(int32_t adc_T) {
    int32_t var1, var2;

    var1 = ((((adc_T >> 3) - ((int32_t)trimmingParameter.dig_T1 << 1))) * ((int32_t)trimmingParameter.dig_T2)) >> 11;
    var2 = (((((adc_T >> 4) - ((int32_t)trimmingParameter.dig_T1)) * ((adc_T >> 4) - ((int32_t)trimmingParameter.dig_T1))) >> 12) * ((int32_t)trimmingParameter.dig_T3)) >> 14;

    t_fine = var1 + var2;

    float T = (t_fine * 5 + 128) >> 8;
    T /= 100.0;
    return T;
}

// Compensate the pressure value using the raw data and trimming parameters
float BME280_CompensatePressure(int32_t adc_P) {
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

// Initialize the BME280 sensor
void BME280_Init() {
    BME280_get_trimming_parameters();
    BME280_WriteRegister(CONFIG, 0x00);
    BME280_WriteRegister(CTRL_MEAS, 0xB7);
    Delay_Ms(150);
}

// Get the temperature value from the BME280 sensor
float BME280_get_temperature() {
    int32_t adc_T;
    BME280_GetTemperatureRawData(&adc_T);
    return BME280_CompensateTemperature(adc_T);
}

// Get the pressure value from the BME280 sensor
float BME280_get_pressure() {
    int32_t adc_P;
    BME280_get_temperature(); // Ensure t_fine is updated
    BME280_GetPressureRawData(&adc_P);
    return BME280_CompensatePressure(adc_P);
}

// Calculate the altitude based on the pressure and a reference pressure
float BME280_get_altitude(float reference) {
    float pressure = BME280_get_pressure();
    float altitude = 44330.0 * (1.0 - pow((pressure / reference), 0.1903));
    return altitude > 0.0 ? altitude : 0;
}
