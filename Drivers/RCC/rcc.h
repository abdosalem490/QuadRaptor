#ifndef RCC_PERIPHERAL_RCC_H_
#define RCC_PERIPHERAL_RCC_H_

/**
 * @brief Define peripheral reset bit positions for RCC_APB2RSTR register
 */
#define RCC_APB2_AFIO   ((uint32_t)(1 << 0))  ///< Alternate Function I/O reset
#define RCC_APB2_IOPA   ((uint32_t)(1 << 2))  ///< IO port A reset
#define RCC_APB2_IOPB   ((uint32_t)(1 << 3))  ///< IO port B reset
#define RCC_APB2_TIM1   ((uint32_t)(1 << 11)) ///< Timer 1 reset
#define RCC_APB2_SPI1   ((uint32_t)(1 << 12)) ///< SPI 1 reset
#define RCC_APB2_USART1 ((uint32_t)(1 << 14)) ///< USART 1 reset

/**
 * @brief Define peripheral reset bit positions for RCC_APB1RSTR register
 */
#define RCC_APB1_TIM2    ((uint32_t)(1 << 0))  ///< Timer 2 reset
#define RCC_APB1_TIM4    ((uint32_t)(1 << 2))  ///< Timer 4 reset
#define RCC_APB1_SPI2    ((uint32_t)(1 << 14)) ///< SPI 2 reset
#define RCC_APB1_USART3  ((uint32_t)(1 << 18)) ///< USART 3 reset
#define RCC_APB1_I2C1    ((uint32_t)(1 << 21)) ///< I2C 1 reset
#define RCC_APB1_I2C2    ((uint32_t)(1 << 22)) ///< I2C 2 reset

/**
 * @brief Resets the specified APB2 peripheral.
 * @param peripheral: The peripheral to reset, specified using the defined bit positions (e.g., RCC_APB2_AFIO).
 * @param reset: 1 to reset the peripheral, 0 to release the reset.
 */
void RCC_APB2_Reset(uint32_t peripheral, uint8_t reset);

/**
 * @brief Resets the specified APB1 peripheral.
 * @param peripheral: The peripheral to reset, specified using the defined bit positions (e.g., RCC_APB1_TIM2).
 * @param reset: 1 to reset the peripheral, 0 to release the reset.
 */
void RCC_APB1_Reset(uint32_t peripheral, uint8_t reset);

/**
 * @brief Enables or disables the clock for the specified APB2 peripheral.
 * @param peripheral: The peripheral for which to enable or disable the clock, specified using the defined bit positions (e.g., RCC_APB2_AFIO).
 * @param enable: 1 to enable the clock, 0 to disable the clock.
 */
void RCC_APB2_EnableClock(uint32_t peripheral, uint8_t enable);

/**
 * @brief Enables or disables the clock for the specified APB1 peripheral.
 * @param peripheral: The peripheral for which to enable or disable the clock, specified using the defined bit positions (e.g., RCC_APB1_TIM2).
 * @param enable: 1 to enable the clock, 0 to disable the clock.
 */
void RCC_APB1_EnableClock(uint32_t peripheral, uint8_t enable);

#endif /* RCC_PERIPHERAL_RCC_H_ */
