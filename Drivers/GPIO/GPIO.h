#ifndef GPIO_GPIO_H_
#define GPIO_GPIO_H_

#include "std_macros.h"   // Include standard macros header file
#include "GPIO_CONFIG.h"  // Include GPIO configuration header file

/* GPIO_pins_define */
/* Definitions for individual GPIO pins */
#define GPIO_Pin_0                      ((uint16_t)0x0001) /* Pin 0 selected */
#define GPIO_Pin_1                      ((uint16_t)0x0002) /* Pin 1 selected */
#define GPIO_Pin_2                      ((uint16_t)0x0004) /* Pin 2 selected */
#define GPIO_Pin_3                      ((uint16_t)0x0008) /* Pin 3 selected */
#define GPIO_Pin_4                      ((uint16_t)0x0010) /* Pin 4 selected */
#define GPIO_Pin_5                      ((uint16_t)0x0020) /* Pin 5 selected */
#define GPIO_Pin_6                      ((uint16_t)0x0040) /* Pin 6 selected */
#define GPIO_Pin_7                      ((uint16_t)0x0080) /* Pin 7 selected */
#define GPIO_Pin_8                      ((uint16_t)0x0100) /* Pin 8 selected */
#define GPIO_Pin_9                      ((uint16_t)0x0200) /* Pin 9 selected */
#define GPIO_Pin_10                     ((uint16_t)0x0400) /* Pin 10 selected */
#define GPIO_Pin_11                     ((uint16_t)0x0800) /* Pin 11 selected */
#define GPIO_Pin_12                     ((uint16_t)0x1000) /* Pin 12 selected */
#define GPIO_Pin_13                     ((uint16_t)0x2000) /* Pin 13 selected */
#define GPIO_Pin_14                     ((uint16_t)0x4000) /* Pin 14 selected */
#define GPIO_Pin_15                     ((uint16_t)0x8000) /* Pin 15 selected */
#define GPIO_Pin_All                    ((uint16_t)0xFFFF) /* All pins selected */

/* Definitions for pin numbers as uint8_t */
#define Pin_0     ((uint8_t) 0)
#define Pin_1     ((uint8_t) 1)
#define Pin_2     ((uint8_t) 2)
#define Pin_3     ((uint8_t) 3)
#define Pin_4     ((uint8_t) 4)
#define Pin_5     ((uint8_t) 5)
#define Pin_6     ((uint8_t) 6)
#define Pin_7     ((uint8_t) 7)
#define Pin_8     ((uint8_t) 8)
#define Pin_9     ((uint8_t) 9)
#define Pin_10    ((uint8_t) 10)
#define Pin_11    ((uint8_t) 11)
#define Pin_12    ((uint8_t) 12)
#define Pin_13    ((uint8_t) 13)
#define Pin_14    ((uint8_t) 14)
#define Pin_15    ((uint8_t) 15)

/* Function Prototypes */

/**
 * @brief Initializes the GPIO pins according to the specified parameters in the GPIO_Structure.
 *
 * @param port Pointer to the GPIO port
 * @param structure Pointer to a GPIO_Structure containing the configuration information for the specified GPIO pins
 */
void GPIO_Initialize(GPIO_TypeDef *port, GPIO_Structure *structure);

/**
 * @brief Reads the specified input pin.
 *
 * @param GPIOx Pointer to the GPIO port
 * @param pinNumber Specifies the pin number to read
 * @return The input pin value (0 or 1)
 */
uint8_t GPIO_Read_Pin(GPIO_TypeDef *GPIOx, uint16_t pinNumber);

/**
 * @brief Reads the input data from the specified GPIO port.
 *
 * @param GPIOx Pointer to the GPIO port
 * @return The input port value
 */
uint16_t GPIO_Read_Port(GPIO_TypeDef *GPIOx);

/**
 * @brief Sets or clears the selected data port bits.
 *
 * @param GPIOx Pointer to the GPIO port
 * @param pins_numbers Specifies the pin numbers to be written
 * @param bitValue Specifies the value to be written to the selected bits (0 or 1)
 */
void GPIO_Write_Pins(GPIO_TypeDef *GPIOx, uint16_t pins_numbers, GPIO_Bit_Value bitValue);

/**
 * @brief Toggles the specified GPIO pin.
 *
 * @param GPIOx Pointer to the GPIO port
 * @param PinNumber Specifies the pin number to toggle
 */
void GPIO_Toggle_Pin(GPIO_TypeDef *GPIOx, uint16_t PinNumber);

/**
 * @brief Writes data to the specified GPIO port.
 *
 * @param GPIOx Pointer to the GPIO port
 * @param portValue Specifies the value to be written to the port
 */
void GPIO_Write_Port(GPIO_TypeDef *GPIOx, uint16_t portValue);

/**
 * @brief Reads the output data register of the specified GPIO port.
 *
 * @param GPIOx Pointer to the GPIO port
 * @return The output data register value
 */
uint16_t GPIO_Read_Data_Register(GPIO_TypeDef *GPIOx);

/**
 * @brief Reads a specific bit in the output data register.
 *
 * @param GPIOx Pointer to the GPIO port
 * @param bitNumber Specifies the bit number to read
 * @return The bit value (0 or 1)
 */
uint8_t GPIO_Read_Bit_In_Data_Register(GPIO_TypeDef *GPIOx, uint16_t bitNumber);

#endif /* GPIO_GPIO_H_ */
