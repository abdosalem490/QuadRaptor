#include "SPI.h"  // Include the SPI header file


void SPI_Initialize(SPI_TypeDef *SPIx, SPI_Structure *structure)
{
    // Set the SPI mode (Master or Slave)
    if (structure->SPI_Mode_Selection == SPI_Master)
    {
        SET_BIT(SPIx->CTLR1, 2);  // Set the Master mode bit
    }
    else
    {
        CLEAR_BIT(SPIx->CTLR1, 2);  // Clear the Master mode bit
    }

    // Set the data size (8 or 16 bits)
    if (structure->SPI_Data_Size == SPI_Data_Size_16_bits)
    {
        SET_BIT(SPIx->CTLR1, 11);  // Set the data size to 16 bits
    }
    else
    {
        CLEAR_BIT(SPIx->CTLR1, 11);  // Set the data size to 8 bits
    }

    // Set the data rate
    uint16_t dataRate = structure->SPI_Data_Rate;
    SPIx->CTLR1 |= dataRate;  // Configure the data rate

    // Transmit the LSB first
    SET_BIT(SPIx->CTLR1, 7);

    // Manage the NSS by software to use less pins
    SET_BIT(SPIx->CTLR1, 9);
}


void SPI_Turn_On_Off(SPI_TypeDef *SPIx, Status status)
{
    if (status == ON)
    {
        SET_BIT(SPIx->CTLR1, 6);  // Enable the SPI peripheral
    }
    else
    {
        CLEAR_BIT(SPIx->CTLR1, 6);  // Disable the SPI peripheral
    }
}


void SPI_Send_Data(SPI_TypeDef *SPIx, uint16_t data)
{
    SPIx->DATAR = data;  // Put the data in the data register
}


uint16_t SPI_Receive_Data(SPI_TypeDef *SPIx)
{
    return (uint16_t)SPIx->DATAR;  // Return the data from the data register
}


Status SPI_IS_Transmit_Buffer_Empty(SPI_TypeDef *SPIx)
{
    return READ_BIT(SPIx->STATR, 1);  // Check the transmit buffer empty flag
}


Status SPI_IS_Receive_Buffer_Not_Empty(SPI_TypeDef *SPIx)
{
    return READ_BIT(SPIx->STATR, 0);  // Check the receive buffer not empty flag
}
