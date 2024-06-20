#include "debug.h"
#include "bme.h"

// Global variable to store the baseline pressure
float baseLinePressure = 0;

int main(void) {
    SystemCoreClockUpdate();
    Delay_Init();
    USART_Printf_Init(115200);
    printf("SystemClk: %d\r\n", SystemCoreClock);
    printf("ChipID: %08x\r\n", DBGMCU_GetCHIPID());
    printf("This is a printf example\r\n");
    printf("******************************************\r\n");

    // Initialize I2C and BME280 sensor
    I2C_init();
    BME280_Init();

    // Get the baseline pressure
    baseLinePressure = BME280_get_pressure();
    Delay_Ms(500);

    while (1) {
        float temp = BME280_get_temperature();
        float press = BME280_get_pressure();
        float altitude = BME280_get_altitude(baseLinePressure);
        printf("Altitude: %.2f m, Temperature: %.2f °C, Pressure: %.2f hPa\r\n", altitude, temp, press);
        Delay_Ms(1000);
    }
}
