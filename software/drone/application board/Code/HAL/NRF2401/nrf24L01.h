

#ifndef USER_NRF24L01_H_
#define USER_NRF24L01_H_


/*--------- Instructions ------------*/
#define READ_REG 0x00
#define WRITE_REG 0x20
#define R_RX_PAYLOAD 0x61
#define W_TX_PAYLOAD 0xA0
#define FLUSH_TX 0xE1
#define FLUSH_RX 0xE2
#define NOP 0xFF


/*--------memory map -------------*/
#define CONFIG 0x00
#define EN_AA 0x01
#define EN_RXADDR 0x02
#define SETUP_AW 0x03
#define SETUP_RETR 0x04
#define RF_CH 0x05
#define RF_SETUP 0x06
#define STATUS 0x07
#define RX_ADDR_P0 0x0A
#define RX_ADDR_P1 0x0B
#define RX_ADDR_P2 0x0C
#define RX_ADDR_P3 0x0D
#define RX_ADDR_P4 0x0E
#define RX_ADDR_P5 0x0F
#define ERX_P0 0
#define ERX_P1 1
#define ERX_P2 2
#define TX_ADDR 0x10
#define RX_PW_P0 0x11
#define FIFO_STATUS 0x17
#define DYNPD 0x1C




// Define the macros for the child pipe enable
#define PIPE_ENABLE_0 ERX_P0
#define PIPE_ENABLE_1 ERX_P1


// Define the macros for the child pipe address
#define PIPE_ADDRESS_0 RX_ADDR_P0
#define PIPE_ADDRESS_1 RX_ADDR_P1


#endif /* USER_NRF24L01_H_ */
