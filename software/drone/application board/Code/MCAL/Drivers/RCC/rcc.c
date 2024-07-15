#ifndef RCC_PERIPHERAL_RCC_H_
#define RCC_PERIPHERAL_RCC_H_

// Define peripheral reset bit positions for RCC_APB2RSTR
#define RCC_APB2_AFIO   ((uint32_t)(1 << 0))  // Alternate Function I/O reset
#define RCC_APB2_IOPA   ((uint32_t)(1 << 2))  // IO port A reset
#define RCC_APB2_IOPB   ((uint32_t)(1 << 3))  // IO port B reset
#define RCC_APB2_TIM1   ((uint32_t)(1 << 11)) // Timer 1 reset
#define RCC_APB2_SPI1   ((uint32_t)(1 << 12)) // SPI 1 reset
#define RCC_APB2_USART1 ((uint32_t)(1 << 14)) // USART 1 reset

// Define peripheral reset bit positions for RCC_APB1RSTR
#define RCC_APB1_TIM2    ((uint32_t)(1 << 0))  // Timer 2 reset
#define RCC_APB1_TIM4    ((uint32_t)(1 << 2))  // Timer 4 reset
#define RCC_APB1_SPI2    ((uint32_t)(1 << 14)) // SPI 2 reset
#define RCC_APB1_USART3  ((uint32_t)(1 << 18)) // USART 3 reset
#define RCC_APB1_I2C1    ((uint32_t)(1 << 21)) // I2C 1 reset
#define RCC_APB1_I2C2    ((uint32_t)(1 << 22)) // I2C 2 reset

#include "std_macros.h"

void RCC_APB2_Reset(uint32_t peripheral, uint8_t reset);
void RCC_APB1_Reset(uint32_t peripheral, uint8_t reset);
void RCC_APB2_EnableClock(uint32_t peripheral, uint8_t enable);
void RCC_APB1_EnableClock(uint32_t peripheral, uint8_t enable);

#endif /* RCC_PERIPHERAL_RCC_H_ */

#include <ch32v20x.h>
#include "rcc.h"

// Function to handle RCC_APB2RSTR register
void RCC_APB2_Reset(uint32_t peripheral, uint8_t reset)
{
    if (reset) {
        SET_BIT(RCC->APB2PRSTR, peripheral); // Set the bit to reset the peripheral
    } else {
        CLEAR_BIT(RCC->APB2PRSTR, peripheral); // Clear the bit to disable the reset
    }
}

void RCC_APB1_Reset(uint32_t peripheral, uint8_t reset)
{
    if (reset) {
        SET_BIT(RCC->APB1PRSTR, peripheral); // Set the bit to reset the peripheral
    } else {
        CLEAR_BIT(RCC->APB1PRSTR, peripheral); // Clear the bit to disable the reset
    }
}

// Function to handle RCC_APB2ENR register
void RCC_APB2_EnableClock(uint32_t peripheral, uint8_t enable)
{
    if (enable) {
        SET_BIT(RCC->APB2PCENR, peripheral); // Set the bit to enable the clock for the peripheral
    } else {
        CLEAR_BIT(RCC->APB2PCENR, peripheral); // Clear the bit to disable the clock for the peripheral
    }
}

// Function to handle RCC_APB1ENR register
void RCC_APB1_EnableClock(uint32_t peripheral, uint8_t enable)
{
    if (enable) {
        SET_BIT(RCC->APB1PCENR, peripheral); // Set the bit to enable the clock for the peripheral
    } else {
        CLEAR_BIT(RCC->APB1PCENR, peripheral); // Clear the bit to disable the clock for the peripheral
    }
}
