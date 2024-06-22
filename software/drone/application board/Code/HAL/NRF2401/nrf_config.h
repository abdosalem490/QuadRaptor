/*
 * nrf_config.h
 *
 *  Created on: Jun 18, 2024
 *      Author: DELL
 */

#ifndef USER_NRF_CONFIG_H_
#define USER_NRF_CONFIG_H_

#define NRF_PORT GPIOA // NRF port for both CE and CSN
#define NRF_CE_PIN GPIO_Pin_3 // CE pin number
#define NRF_CSN_PIN GPIO_Pin_4 // CSN pin number
#define SPIx SPI1  // SPI used for communication

#define SHIFT_LEFT(x) (1 << (x))



#endif /* USER_NRF_CONFIG_H_ */
