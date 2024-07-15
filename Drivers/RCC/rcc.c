#include <ch32v20x.h>
#include "rcc.h"

// Function to handle RCC_APB2RSTR register

void RCC_APB2_Reset(uint32_t peripheral, uint8_t reset)
{
    if (reset) {
    	 RCC->APB2PRSTR |= peripheral; // Set the bit to reset the peripheral
    } else {
    	 RCC->APB2PRSTR &= ~peripheral; // Clear the bit to disable the reset
    }
}


void RCC_APB1_Reset(uint32_t peripheral, uint8_t reset)
{
	if (reset) {
	    	 RCC->APB1PRSTR |= peripheral; // Set the bit to reset the peripheral
	    } else {
	    	 RCC->APB1PRSTR &= ~peripheral; // Clear the bit to disable the reset
	    }
}

// Function to handle RCC_APB2ENR register
void RCC_APB2_EnableClock(uint32_t peripheral, uint8_t enable)
{
    if (enable) {
        RCC->APB2PCENR |= peripheral; // Set the bit to enable the clock for the peripheral
    } else {
        RCC->APB2PCENR &= ~peripheral; // Clear the bit to disable the clock for the peripheral
    }
}

// Function to handle RCC_APB1ENR register
void RCC_APB1_EnableClock(uint32_t peripheral, uint8_t enable)
{
    if (enable) {
        RCC->APB1PCENR |= peripheral; // Set the bit to enable the clock for the peripheral
    } else {
        RCC->APB1PCENR &= ~peripheral; // Clear the bit to disable the clock for the peripheral
    }
}
