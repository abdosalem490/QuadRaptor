/**
 * --------------------------------------------------------------------------------------------------------------------------------------
 * |    @title          :   source code file for NRF2401                                                                                |
 * |    @file           :   nrf_config.h                                                                                                |
 * |    @author         :   Ahmed Fawzy                                                                                                 |
 * |    @origin_date    :   18/06/2024                                                                                                  |
 * |    @version        :   1.0.0                                                                                                       |
 * |    @tool_chain     :   RISC-V Cross GCC                                                                                            |
 * |    @compiler       :   GCC                                                                                                         |
 * |    @C_standard     :   ISO C99 (-std=c99)                                                                                          |
 * |    @target         :   CH32V203C8T6                                                                                                |
 * |    @notes          :   None                                                                                                        |
 * |    @license        :   MIT License                                                                                                 |
 * |    @brief          :   this source file contains some function to deal with NRF2401                                                |
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
 * |    18/06/2023      1.0.0           Ahmed Fawzy                     Interface Created.                                              |
 * --------------------------------------------------------------------------------------------------------------------------------------
 */


/******************************************************************************
 * Includes
 *******************************************************************************/

/**
 * 
 */
#include "stdint.h"

/**
 * 
 */
#include "nrf_config.h"


/**
 * 
 */
#include "nrf24L01.h"

/**
 * 
 */
#include "nrf.h"

/**
 * 
 */
#include "MCAL_wrapper.h"


/**
 * 
 */
#include "Service_RTOS_wrapper.h"


/**
 * @brief: Write a value to an NRF register
 */
uint8_t NRF_write_register(uint8_t reg, uint8_t value) {
    uint8_t status = 0;
    CSN_LOW();
    status = SPI_transfer(WRITE_REG | (reg & 0x1F));
    SPI_transfer(value);
    CSN_HIGH();
    return status;
}

/**
 * @brief: Write a buffer to an NRF register
 */
void NRF_write_data_register(uint8_t reg, const uint8_t *buf, uint8_t len) {
    CSN_LOW();
    SPI_transfer(WRITE_REG | (reg & 0x1F));
    while (len--) {
        SPI_transfer(*buf++);
    }
    CSN_HIGH();
}

/**
 * @brief: Send a command to the NRF module
 */
uint8_t NRF_send_command(uint8_t command) {
    CSN_LOW();
    uint8_t status = SPI_transfer(WRITE_REG | command);
    CSN_HIGH();
    return status;
}

/**
 * @brief: Get the status of the NRF module
 */
uint8_t get_status() {
    return NRF_send_command(0xFF);
}

/**
 * @brief: Read a value from an NRF register
 */
uint8_t NRF_read_register(uint8_t reg) {
	CSN_LOW();
    SPI_transfer(READ_REG | (reg & 0x1F));
    uint8_t value = SPI_transfer(NOP);
    CSN_HIGH();
    return value;
}

/**
 * @brief: Write data to the NRF module
 */
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
    SERVICE_RTOS_BlockFor(5);
    CE_LOW();

    //uint8_t status = NRF_write_register(STATUS, SHIFT_LEFT(6) | SHIFT_LEFT(5) | SHIFT_LEFT(4));
   /* if (status & SHIFT_LEFT(4)) {
        NRF_send_command(FLUSH_TX);
        return 0;
    }*/
    return ;
}

/**
 * @brief: Open a writing pipe with a specific address
 */
void NRF_openWritingPipe(const uint8_t *address) {
    NRF_write_data_register(RX_ADDR_P0, address, 5);
    NRF_write_data_register(TX_ADDR, address, 5);
}

// 
/**
 * @brief: Open a reading pipe with a specific address
 */
void NRF_openReadingPipe(uint8_t child, const uint8_t *address) {
    NRF_write_data_register(PIPE_ADDRESS_1, address, 5);
    uint8_t en_rxaddr = NRF_read_register(EN_RXADDR);
    NRF_write_register(EN_RXADDR, en_rxaddr | SHIFT_LEFT(PIPE_ENABLE_1));
}

/**
 * @brief: Initialize the NRF module
 */
void NRF_init() {

    MCAL_WRAPPER_DelayUS(110000); // Delay to ensure the NRF module is properly reset

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
    MCAL_WRAPPER_DelayUS(5000000);
}


/**
 * @brief: Start listening for incoming data
 */
void NRF_start_listening() {
    uint8_t config_value = NRF_read_register(CONFIG);
    config_value |= SHIFT_LEFT(0);

    NRF_write_register(CONFIG, config_value);
    NRF_write_register(STATUS, (SHIFT_LEFT(4) | SHIFT_LEFT(5) | SHIFT_LEFT(6)));

    CE_HIGH();
    NRF_write_register(EN_RXADDR, (NRF_read_register(EN_RXADDR) & ~SHIFT_LEFT(0)));

    // delay for allowing NRF to detect if anything received
    SERVICE_RTOS_BlockFor(20);
}

/**
 * @brief: Stop listening for incoming data
 */
void NRF_stop_listening() {
    CE_LOW();
    MCAL_WRAPPER_DelayUS(100);
    NRF_write_register(CONFIG, (NRF_read_register(CONFIG) & ~(0x01)));
    NRF_write_register(EN_RXADDR, (NRF_read_register(EN_RXADDR) | SHIFT_LEFT(0)));
}

/**
 * @brief: Read data from an NRF register into a buffer
 */
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


/**
 * @brief: Read payload data from the NRF module
 */
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

/**
 * @brief: Read data from the NRF module into a buffer
 */
void NRF_read(void *buf, uint8_t len) {
    NRF_read_payload(buf, len);
    NRF_write_register(STATUS, SHIFT_LEFT(6));
}

/**
 * @brief: Check if data is available in the NRF module
 */
uint8_t NRF_data_available() {
    if (NRF_read_register(FIFO_STATUS) & 1) {
        return 0;
    }
    return 1;
}

/*************** END OF FUNCTIONS ***************************************************************************/

