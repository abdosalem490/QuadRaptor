#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>
#include "debug.h"
#include "nrf_config.h"
#include "nrf24L01.h"
#include "nrf.h"

typedef enum {
    DATA_TYPE_MOVE,
    DATA_TYPE_EXTRAS,
    DATA_TYPE_INFO,
} DATA_TYPE_t;

typedef struct __attribute__((packed)){
    int8_t roll;
    int8_t pitch;
    int8_t thurst;
    int8_t yaw;
    bool turnOnLeds;
    bool playMusic;
} move_command_t;

typedef struct __attribute__((packed)){
    float distanceToOrigin;
    float altitude;
    float temperature;
    uint8_t batteryCharge;
} drone_info_t;

typedef struct __attribute__((packed)){
    uint8_t type;
    union {
        move_command_t move;
        drone_info_t info;
    } data;
} data_t;

data_t data;
uint8_t addresses[][6] = {"RtoD", "DtoR"};

static uint32_t seed = 1;

void srand(uint32_t s) {
    seed = s;
}

int random(int min, int max) {
    seed = (214013 * seed + 2531011);
    return min + (seed ^ seed >> 15) % (max - min + 1);
}



void USART_SendString(char *str) {
    while (*str) {
        USART_SendData(USART1, *str++);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
    }
}

void USART_SendFormattedString(const char *format, ...) {
    char buffer[128];
    va_list args;
    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);
    USART_SendString(buffer);
}


void sys_setup() {
    SystemCoreClockUpdate();
    Delay_Init();
    USART_Printf_Init(115200);
    Delay_Ms(1000);
    USART_SendString("Initializing..........\r\n");
    srand(1);
}


void NRF_setup()
{
	SPI_init( GPIOA, GPIO_Pin_5, GPIO_Pin_6, GPIO_Pin_7);
	NRF_init();
	NRF_openWritingPipe(addresses[1]);
	NRF_openReadingPipe(1, addresses[0]);
}

int main() {

	sys_setup();
	NRF_setup();

	    while (1) {
	        // Main loop can handle other tasks
            NRF_start_listening();
            if (NRF_data_available()) {

            	            NRF_read(&data, sizeof(data));

            	            USART_SendFormattedString("Received data type: %d\r\n", data.type);
            	            if (data.type == DATA_TYPE_MOVE) {
            	                USART_SendFormattedString("Roll: %d, Pitch: %d, Thrust: %d, Yaw: %d, LEDs: %d, Music: %d\r\n",
            	                                          data.data.move.roll, data.data.move.pitch, data.data.move.thurst,
            	                                          data.data.move.yaw, data.data.move.turnOnLeds, data.data.move.playMusic);
            	            } else if (data.type == DATA_TYPE_INFO) {
            	                USART_SendFormattedString("Distance: %.2f, Altitude: %.2f, Temperature: %.2f, Battery: %d%%\r\n",
            	                                          data.data.info.distanceToOrigin, data.data.info.altitude,
            	                                          data.data.info.temperature, data.data.info.batteryCharge);
            	            } else {
            	                USART_SendString("Unknown data type received\r\n");
            	            }
            	        }

            Delay_Ms(5);
	    	// Prepare the data

	    	        data.type = DATA_TYPE_INFO;
	    	        data.data.info.altitude = random(0, 100);
	    	        data.data.info.temperature = random(0, 100);
	    	        data.data.info.distanceToOrigin = random(0, 100);
	    	        data.data.info.batteryCharge = random(0, 100);

	    	        NRF_stop_listening();
	    	        NRF_write(&data, sizeof(data));



	    }
}


