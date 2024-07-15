#ifndef UART_UART_H_
#define UART_UART_H_

/**
 * @brief USART Control Register 1 (USART_CR1) bit definitions
 */
#define USART_CR1_UE      (1 << 13) ///< USART enable
#define USART_CR1_TE      (1 << 3)  ///< Transmitter enable
#define USART_CR1_RE      (1 << 2)  ///< Receiver enable
#define USART_CR1_M       (1 << 12) ///< Word length (0: 8 data bits, 1: 9 data bits)
#define USART_CR1_PCE     (1 << 10) ///< Parity control enable
#define USART_CR1_PS      (1 << 9)  ///< Parity selection (0: even parity, 1: odd parity)

/**
 * @brief USART Control Register 2 (USART_CR2) bit definitions
 */
#define USART_CR2_STOP    (3 << 12) ///< STOP bits (2 bits, used to select the number of stop bits)

/**
 * @brief USART Control Register 3 (USART_CR3) bit definitions
 */
#define USART_CR3_RTSE    (1 << 8)  ///< RTS enable
#define USART_CR3_CTSE    (1 << 9)  ///< CTS enable

/**
 * @brief Masks for clearing specific bits in USART control registers
 */
#define CTLR2_STOP_CLEAR_Mask  ((uint16_t)0xCFFF) ///< Mask for clearing STOP bits in USART_CR2
#define CTLR1_CLEAR_Mask       ((uint16_t)0xE9F3) ///< Mask for clearing specific bits in USART_CR1
#define CTLR3_CLEAR_Mask       ((uint16_t)0xFCFF) ///< Mask for clearing specific bits in USART_CR3

/**
 * @brief USART Status Register (USART_SR) bit definitions
 */
#define USART_SR_RXNE     (1 << 5) ///< Read data register not empty
#define USART_SR_TXE      (1 << 7) ///< Transmit data register empty
#define USART_SR_TC       (1 << 6) ///< Transmission complete

/**
 * @brief Initializes the USART peripheral with the specified parameters.
 * @param baudRate: The baud rate for USART communication.
 * @param wordLength: The word length (number of data bits).
 * @param stopBits: The number of stop bits.
 * @param parity: The parity setting (none, even, or odd).
 * @param mode: The mode of operation (transmit, receive, or both).
 * @param hardwareFlowControl: The hardware flow control setting (RTS/CTS).
 */
void USART_initialize(uint32_t baudRate, uint32_t wordLength, uint32_t stopBits, uint32_t parity, uint32_t mode, uint32_t hardwareFlowControl);

/**
 * @brief Writes data to the UART data register.
 * @param data: The data to be sent (9 bits maximum).
 */
void UART_WriteData(uint16_t data);

/**
 * @brief Reads data from the UART data register.
 * @return The received data (9 bits maximum).
 */
uint16_t UART_ReadData(void);

/**
 * @brief Checks the status of a specific UART flag.
 * @param UART4_FLAG: The flag to check.
 * @return The status of the flag (SET or RESET).
 */
FlagStatus UART_CheckFlag(uint16_t UART4_FLAG);

/**
 * @brief Resets a specific UART flag.
 * @param flag: The flag to be reset.
 */
void UART_ResetFlag(uint16_t flag);

#endif /* UART_UART_H_ */
