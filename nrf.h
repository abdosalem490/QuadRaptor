#ifndef USER_NRF_H_
#define USER_NRF_H_

/**
 * @brief Sets the CSN pin low.
 */
void CSN_LOW();

/**
 * @brief Sets the CSN pin high.
 */
void CSN_HIGH();

/**
 * @brief Sets the CE pin low.
 */
void CE_LOW();

/**
 * @brief Sets the CE pin high.
 */
void CE_HIGH();

/**
 * @brief Initializes the SPI interface.
 *
 * @param GPIOx The GPIO port to use.
 * @param SPI_SCK_Pin The SCK pin.
 * @param SPI_MISO_Pin The MISO pin.
 * @param SPI_MOSI_Pin The MOSI pin.
 */
void SPI_init(GPIO_TypeDef* GPIOx, uint16_t SPI_SCK_Pin, uint16_t SPI_MISO_Pin, uint16_t SPI_MOSI_Pin);

/**
 * @brief Gets the status of the NRF module.
 *
 * @return The status byte.
 */
uint8_t get_status();

/**
 * @brief Sends a command to the NRF module.
 *
 * @param command The command byte to send.
 * @return The status byte returned by the NRF module.
 */
uint8_t NRF_send_command(uint8_t command);

/**
 * @brief Transfers a byte over SPI.
 *
 * @param data The byte to transfer.
 * @return The byte received from the SPI transfer.
 */
uint8_t SPI_transfer(uint8_t data);

/**
 * @brief Writes a value to an NRF register.
 *
 * @param reg The register to write to.
 * @param value The value to write.
 * @return The status byte returned by the NRF module.
 */
uint8_t NRF_write_register(uint8_t reg, uint8_t value);

/**
 * @brief Writes a buffer to an NRF register.
 *
 * @param reg The register to write to.
 * @param buf The buffer containing the data to write.
 * @param len The length of the buffer.
 */
void NRF_write_data_register(uint8_t reg, const uint8_t *buf, uint8_t len);

/**
 * @brief Reads a value from an NRF register.
 *
 * @param reg The register to read from.
 * @return The value read from the register.
 */
uint8_t NRF_read_register(uint8_t reg);

/**
 * @brief Writes data to the NRF module.
 *
 * @param buf The buffer containing the data to write.
 * @param data_len The length of the data.
 * @return True if the write was successful, false otherwise.
 */
void NRF_write(const void* buf, uint8_t data_len);

/**
 * @brief Initializes the NRF module.
 */
void NRF_init();

/**
 * @brief Starts listening for incoming data.
 */
void NRF_start_listening();

/**
 * @brief Stops listening for incoming data.
 */
void NRF_stop_listening();

/**
 * @brief Reads data from an NRF register into a buffer.
 *
 * @param reg The register to read from.
 * @param buf The buffer to store the data.
 * @param len The length of the buffer.
 * @return The status byte returned by the NRF module.
 */
uint8_t NRF_read_data_register(uint8_t reg, uint8_t *buf, uint8_t len);

/**
 * @brief Opens a writing pipe with a specific address.
 *
 * @param address The address of the writing pipe.
 */
void NRF_openWritingPipe(const uint8_t *address);

/**
 * @brief Opens a reading pipe with a specific address.
 *
 * @param child The child pipe number.
 * @param address The address of the reading pipe.
 */
void NRF_openReadingPipe(uint8_t child, const uint8_t *address);

/**
 * @brief Reads payload data from the NRF module.
 *
 * @param buf The buffer to store the data.
 * @param len The length of the buffer.
 * @return The status byte returned by the NRF module.
 */
uint8_t NRF_read_payload(void *buf, uint8_t len);

/**
 * @brief Reads data from the NRF module into a buffer.
 *
 * @param buf The buffer to store the data.
 * @param len The length of the buffer.
 */
void NRF_read(void *buf, uint8_t len);

/**
 * @brief Checks if data is available in the NRF module.
 *
 * @return True if data is available, false otherwise.
 */
uint8_t NRF_data_available();

#endif /* USER_NRF_H_ */
