#include "debug.h" // Include the debug header for debugging functionalities
#include <string.h> // Include the string header for string manipulation functions
#include "uart.h" // Include the UART header for UART specific definitions and functions
#include "std_macros.h" // Include the standard macros header for bit manipulation macros


void USART_initialize(uint32_t baudRate, uint32_t wordLength, uint32_t stopBits, uint32_t parity, uint32_t mode, uint32_t hardwareFlowControl)
{
    // Ensure USART is disabled before configuration
    CLEAR_BIT(UART4->CTLR1, USART_CR1_UE);

    // Configure stop bits
    UART4->CTLR2 = (UART4->CTLR2 & CTLR2_STOP_CLEAR_Mask) | stopBits;

    // Configure word length, parity, and mode
    uint32_t cr1_temp = UART4->CTLR1 & CTLR1_CLEAR_Mask;
    cr1_temp |= wordLength | parity | mode;
    UART4->CTLR1 = cr1_temp;

    // Configure hardware flow control
    UART4->CTLR3 = (UART4->CTLR3 & CTLR3_CLEAR_Mask) | hardwareFlowControl;

    // Calculate and set the baud rate
    uint32_t apbclock = SystemCoreClock / 2; // Assuming APB1 clock is half of SystemCoreClock
    uint32_t integerdivider = ((25 * apbclock) / (4 * baudRate));
    uint32_t tmpreg = (integerdivider / 100) << 4;
    uint32_t fractionaldivider = integerdivider - (100 * (tmpreg >> 4));
    tmpreg |= (((fractionaldivider * 16) + 50) / 100) & 0x0F;
    UART4->BRR = tmpreg;

    // Enable USART
    SET_BIT(UART4->CTLR1, USART_CR1_UE);
}


void UART_WriteData(uint16_t data)
{
    // Ensure the data is within the correct range
    data &= 0x01FF;
    UART4->DATAR = data;
}


uint16_t UART_ReadData(void)
{
    // Read the data from the UART4 data register
    return (uint16_t)(UART4->DATAR & 0x01FF);
}


FlagStatus UART_CheckFlag(uint16_t UART4_FLAG)
{
    // Check if the specified flag is set in the UART4 status register
    return (READ_BIT(UART4->STATR, UART4_FLAG)) ? SET : RESET;
}


void UART_ResetFlag(uint16_t flag)
{
    // Clear the specified flag by writing the inverted flag value to the status register
    CLEAR_BIT(UART4->STATR, flag);
}
