#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>
#include "debug.h"
#include "nrf_config.h"
#include "nrf24L01.h"
#include "nrf.h"

// Set CSN pin low
void CSN_LOW() {
    GPIO_ResetBits(NRF_PORT, NRF_CSN_PIN);
}

// Set CSN pin high
void CSN_HIGH() {
    GPIO_SetBits(NRF_PORT, NRF_CSN_PIN);
}

// Set CE pin high
void CE_HIGH() {
    GPIO_SetBits(NRF_PORT, NRF_CE_PIN);
}

// Set CE pin low
void CE_LOW() {
    GPIO_ResetBits(NRF_PORT, NRF_CE_PIN);
}

// Initialize SPI interface
void SPI_init(GPIO_TypeDef* GPIOx, uint16_t SPI_SCK_Pin, uint16_t SPI_MISO_Pin, uint16_t SPI_MOSI_Pin) {
    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef SPI_InitStructure;

    // Enable GPIO and SPI clocks
    if (SPIx == SPI1) {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1, ENABLE);
    } else if (SPIx == SPI2) {
        RCC_APB1PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB1Periph_SPI2, ENABLE);
    }

    // Initialize SCK and MOSI as Alternate Function Push Pull
    GPIO_InitStructure.GPIO_Pin = SPI_SCK_Pin | SPI_MOSI_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOx, &GPIO_InitStructure);

    // Initialize MISO as Input Floating
    GPIO_InitStructure.GPIO_Pin = SPI_MISO_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOx, &GPIO_InitStructure);

    // SPI configuration
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPIx, &SPI_InitStructure);

    // Enable SPI
    SPI_Cmd(SPIx, ENABLE);
}

// Transfer a byte over SPI
uint8_t SPI_transfer(uint8_t data) {
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    SPI_I2S_SendData(SPI1, data);
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
    return SPI_I2S_ReceiveData(SPI1);
}

// Write a value to an NRF register
uint8_t NRF_write_register(uint8_t reg, uint8_t value) {
    uint8_t status = 0;
    CSN_LOW();
    status = SPI_transfer(WRITE_REG | (reg & 0x1F));
    SPI_transfer(value);
    CSN_HIGH();
    return status;
}

// Write a buffer to an NRF register
void NRF_write_data_register(uint8_t reg, const uint8_t *buf, uint8_t len) {
    CSN_LOW();
    SPI_transfer(WRITE_REG | (reg & 0x1F));
    while (len--) {
        SPI_transfer(*buf++);
    }
    CSN_HIGH();
}

// Send a command to the NRF module
uint8_t NRF_send_command(uint8_t command) {
    CSN_LOW();
    uint8_t status = SPI_transfer(WRITE_REG | command);
    CSN_HIGH();
    return status;
}

// Get the status of the NRF module
uint8_t get_status() {
    return NRF_send_command(0xFF);
}

// Read a value from an NRF register
uint8_t NRF_read_register(uint8_t reg) {
    CSN_LOW();
    SPI_transfer(READ_REG | (reg & 0x1F));
    uint8_t value = SPI_transfer(NOP);
    CSN_HIGH();
    return value;
}

// Write data to the NRF module
void NRF_write(const void* buf, uint8_t data_len) {
    const uint8_t* current = (const uint8_t*)buf;
    uint8_t blank_len = 32 - data_len;

    CSN_LOW();
    SPI_transfer(0xA0);
    while (data_len--) {
        SPI_transfer(*current++);
    }
    while (blank_len--) {
        SPI_transfer(0);
    }
    CSN_HIGH();

    CE_HIGH();
    Delay_Ms(5);
    CE_LOW();

    //uint8_t status = NRF_write_register(STATUS, SHIFT_LEFT(6) | SHIFT_LEFT(5) | SHIFT_LEFT(4));
   /* if (status & SHIFT_LEFT(4)) {
        NRF_send_command(FLUSH_TX);
        return 0;
    }*/
    return ;
}

// Open a writing pipe with a specific address
void NRF_openWritingPipe(const uint8_t *address) {
    NRF_write_data_register(RX_ADDR_P0, address, 5);
    NRF_write_data_register(TX_ADDR, address, 5);
}

// Open a reading pipe with a specific address
void NRF_openReadingPipe(uint8_t child, const uint8_t *address) {
    NRF_write_data_register(PIPE_ADDRESS_1, address, 5);
    uint8_t en_rxaddr = NRF_read_register(EN_RXADDR);
    NRF_write_register(EN_RXADDR, en_rxaddr | SHIFT_LEFT(PIPE_ENABLE_1));
}

// Initialize the NRF module
void NRF_init() {
    // Enable the clock for the GPIO port used by the NRF module
    if (NRF_PORT == GPIOA) {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    } else if (NRF_PORT == GPIOB) {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    }

    // Configure CE and CSN pins as output push-pull
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = NRF_CE_PIN | NRF_CSN_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(NRF_PORT, &GPIO_InitStructure);

    // Reset CE and set CSN pins
    GPIO_ResetBits(NRF_PORT, NRF_CE_PIN);
    GPIO_SetBits(NRF_PORT, NRF_CSN_PIN);
    Delay_Ms(110); // Delay to ensure the NRF module is properly reset

    // Set auto-retransmit delay to 1500us and up to 15 retransmit attempts
    NRF_write_register(SETUP_RETR, 0x5F);

    // Read the RF setup register, mask out unnecessary bits, and write back the data rate settings
    uint8_t data_rate = NRF_read_register(RF_SETUP);
    uint8_t mask = ~(1 << 3 | 1 << 5);
    data_rate &= mask;
    NRF_write_register(RF_SETUP, data_rate);

    // Enable auto acknowledgment for all data pipes
    NRF_write_register(EN_AA, 0x3F);

    // Enable RX addresses for data pipes 0 and 1
    NRF_write_register(EN_RXADDR, 0x03);

    // Set the payload size to 32 bytes for all pipes
    for (uint8_t pipe = 0; pipe <= 5; pipe++) {
        NRF_write_register(RX_PW_P0 + pipe, 32);
    }

    // Set the address width to 5 bytes
    NRF_write_register(SETUP_AW, 0x03);

    // Set the RF channel to 115
    NRF_write_register(RF_CH, 115);

    // Clear the status register
    NRF_write_register(STATUS, SHIFT_LEFT(6) | SHIFT_LEFT(5) | SHIFT_LEFT(4));

    // Flush RX and TX FIFOs
    NRF_send_command(FLUSH_RX);
    NRF_send_command(FLUSH_TX);

    // Set the NRF configuration register (power up, enable CRC, CRC 2 bytes)
    NRF_write_register(CONFIG, 0x0E);

    // Wait for the NRF module to power up properly
    Delay_Ms(5000);
}

// Start listening for incoming data
void NRF_start_listening() {
    uint8_t config_value = NRF_read_register(CONFIG);
    config_value |= SHIFT_LEFT(0);

    NRF_write_register(CONFIG, config_value);
    NRF_write_register(STATUS, (SHIFT_LEFT(4) | SHIFT_LEFT(5) | SHIFT_LEFT(6)));

    CE_HIGH();
    NRF_write_register(EN_RXADDR, (NRF_read_register(EN_RXADDR) & ~SHIFT_LEFT(0)));
}

// Stop listening for incoming data
void NRF_stop_listening() {
    CE_LOW();
    Delay_Us(100);
    NRF_write_register(CONFIG, (NRF_read_register(CONFIG) & ~(0x01)));
    NRF_write_register(EN_RXADDR, (NRF_read_register(EN_RXADDR) | SHIFT_LEFT(0)));
}

// Read data from an NRF register into a buffer
uint8_t NRF_read_data_register(uint8_t reg, uint8_t *buf, uint8_t len) {
    uint8_t status = 0;

    CSN_LOW();
    status = SPI_transfer(READ_REG | (reg & 0x1F));
    while (len--) {
        *buf++ = SPI_transfer(NOP);
    }

    CSN_HIGH();
    return status;
}

// Read payload data from the NRF module
uint8_t NRF_read_payload(void *buf, uint8_t len) {
    uint8_t status;
    uint8_t *current = (uint8_t *)buf;
    uint8_t data_len = len;
    uint8_t blank_len = 32 - data_len;

    CSN_LOW();
    status = SPI_transfer(0x61);
    while (data_len--) {
        *current++ = SPI_transfer(NOP);
    }
    while (blank_len--) {
        SPI_transfer(NOP);
    }
    CSN_HIGH();

    return status;
}

// Read data from the NRF module into a buffer
void NRF_read(void *buf, uint8_t len) {
    NRF_read_payload(buf, len);
    NRF_write_register(STATUS, SHIFT_LEFT(6));
}

// Check if data is available in the NRF module
uint8_t NRF_data_available() {
    if (NRF_read_register(FIFO_STATUS) & 1) {
        return 0;
    }
    return 1;
}
