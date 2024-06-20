#ifndef BME280_H
#define BME280_H

#include <stdint.h>
#include <stdbool.h>
#include "bme_def.h"

// BME280 I2C address
#define BME280_I2C_ADDRESS 0x76

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

extern Trimming_TypeDef trimmingParameter;
extern int32_t t_fine;

// Function declarations
void I2C_init(void);
void BME280_Init(void);
float BME280_get_temperature(void);
float BME280_get_pressure(void);
float BME280_get_altitude(float reference);

#endif // BME280_H
