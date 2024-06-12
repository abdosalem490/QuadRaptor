/*
 * hmc5883l.c
 *
 *  Created on: Jun 11, 2024
 *      Author: mohab
 */

#include <math.h>
#include "debug.h"
#include "ch32v20x_rcc.h"
#include "ch32v20x_gpio.h"
#include "ch32v20x_i2c.h"
#include "hmc5883l.h"

/* Receiver buffer */
u8 RxData[I2C_Rx_BUFFER_SIZE];

void I2C_init() __attribute__((always_inline));
void I2C_start_transmission(uint8_t receiver_address, uint8_t master_receive) __attribute__((always_inline));
void I2C_write(uint8_t value) __attribute__((always_inline));
void I2C_stop() __attribute__((always_inline));
uint8_t I2C_requestFrom(uint8_t address, uint8_t quantity) __attribute__((always_inline));
uint8_t I2C_read() __attribute__((always_inline));

inline void I2C_start_transmission(uint8_t receiver_address, uint8_t master_receive){
    uint8_t i2c_dir = I2C_Direction_Transmitter;
    uint32_t i2c_event = I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED;

    if(master_receive){
        i2c_dir = I2C_Direction_Receiver;
        i2c_event = I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED;
    }

    while( I2C_GetFlagStatus( I2C2, I2C_FLAG_BUSY ) != RESET );


    I2C_GenerateSTART(I2C2, ENABLE);
    while( !I2C_CheckEvent( I2C2, I2C_EVENT_MASTER_MODE_SELECT ) );


    I2C_Send7bitAddress(I2C2, receiver_address << 1, i2c_dir);
    while( !I2C_CheckEvent( I2C2, i2c_event ) );
}

inline void I2C_write(uint8_t value){
    while(I2C_GetFlagStatus(I2C2, I2C_FLAG_TXE)!=SET);
    I2C_SendData(I2C2, value);
}

inline void I2C_stop(){
    while(I2C_GetFlagStatus(I2C2, I2C_FLAG_TXE)!=SET);
    I2C_GenerateSTOP(I2C2, ENABLE);
}

inline uint8_t I2C_read(){
    static uint8_t i = 0;
    uint8_t result = RxData[i];
    i = (i+1) % I2C_Rx_BUFFER_SIZE;
    return result;
}

inline uint8_t I2C_requestFrom(uint8_t address, uint8_t quantity){
    uint8_t i = 0;

    I2C_start_transmission(address, MASTER_RECEIVER_MODE);

    while(i < I2C_Rx_BUFFER_SIZE){
        if( I2C_GetFlagStatus( I2C2, I2C_FLAG_RXNE ) !=  RESET ){
            RxData[i] = I2C_ReceiveData( I2C2 );
            i++;
        }
        if(i == I2C_Rx_BUFFER_SIZE-1) I2C_NACKPositionConfig(I2C2, I2C_NACKPosition_Next);
    }

    while(I2C_GetFlagStatus(I2C2, I2C_FLAG_RXNE)!=SET);
    I2C_GenerateSTOP(I2C2, ENABLE);

    return i;
}

void I2C_init_ch32()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);

    GPIO_InitTypeDef gpioConfig;
    gpioConfig.GPIO_Mode = GPIO_Mode_AF_OD;
    gpioConfig.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    gpioConfig.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOB, &gpioConfig);


    // I2C code
    I2C_InitTypeDef I2CConfig;
    I2CConfig.I2C_ClockSpeed = 400000;
    I2CConfig.I2C_Mode = I2C_Mode_I2C;
    I2CConfig.I2C_DutyCycle = I2C_DutyCycle_2;
    I2CConfig.I2C_OwnAddress1 = 0x2F;
    I2CConfig.I2C_Ack = I2C_Ack_Enable;
    I2CConfig.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Init(I2C2, &I2CConfig);
}

inline void I2C_init(){
    I2C_init_ch32();
}


void hmc5883l_init()
{
    I2C_init_ch32();

    #if GY86_AUXILIARY != 0
    /**
    Register: USER_CTRL (0x6A)
    *  Disable the MPU6050 master mode. This is a prerequisite for the next step
    **/
    I2C_start_transmission(MPU6050_SLAVE_ADDRESS, MASTER_TRANSMIT_MODE);
    I2C_write(MPU6050_REG_USER_CTRL);
    I2C_write(MPU6050_DISABLE_MASTER);
    I2C_stop();

    /**
    Register: BYPASS_CTRL (0x37)
    *  Enables bypass mode. This connects the main I2C bus to the auxiliary one.
    **/
    I2C_start_transmission(MPU6050_SLAVE_ADDRESS, MASTER_TRANSMIT_MODE);
    I2C_write(MPU6050_REG_BYPASS);
    I2C_write(MPU6050_ENABLE_BYPASS);
    I2C_stop();

    /**
    Register: PWR_MGMT_1 (0x6B = 107)
    *  Selects the clock source: 8MHz oscillator
    *  Disables the following bits: Reset, Sleep, Cycle
    *  Does not disable Temperature sensor.
    **/
    I2C_start_transmission(MPU6050_SLAVE_ADDRESS, MASTER_TRANSMIT_MODE);
    I2C_write(MPU6050_REG_PWR_MGMT_1);
    I2C_write(0);
    I2C_stop();

    printf("BYPASS ENABLED\r\n");
    #endif


    /**
    Register: CONFIG_A (0x00)
    *  Sets the samples per measurement output to 8
    *  Sets the output data rate to 30Hz
    **/
    I2C_start_transmission(HMC5883L_SLAVE_ADDRESS, MASTER_TRANSMIT_MODE);
    I2C_write(HMC5883L_REG_CONFIG_A);
    I2C_write(HMC5883L_SAMPLES_8 | HMC5883L_OUTPUT_RATE);
    I2C_stop();

    /**
    Register: CONFIG_B (0x00)
    *  Sets the sensor field range to 1.3 Ga
    **/
    I2C_start_transmission(HMC5883L_SLAVE_ADDRESS, MASTER_TRANSMIT_MODE);
    I2C_write(HMC5883L_REG_CONFIG_B);
    I2C_write(HMC5883L_RANGE_1_3);
    I2C_stop();

    /**
    Register: MODE_REG (0x02)
    *  Sets the measurement mode to continuous measurement mode
    **/
    I2C_start_transmission(HMC5883L_SLAVE_ADDRESS, MASTER_TRANSMIT_MODE);
    I2C_write(HMC5883L_REG_MODE);
    I2C_write(HMC5883L_CONTINUOUS_MODE);
    I2C_stop();

}


void hmc5883l_read(hmc5883l_packet* data)
{
    // Get sensor readings
    I2C_requestFrom(HMC5883L_SLAVE_ADDRESS, I2C_Rx_BUFFER_SIZE);

    data->magnetometer_raw[X_AXIS] = (I2C_read()<<8 | I2C_read()) / HMC5883L_GAIN;
    data->magnetometer_raw[Y_AXIS] = (I2C_read()<<8 | I2C_read()) / HMC5883L_GAIN;
    data->magnetometer_raw[Z_AXIS] = (I2C_read()<<8 | I2C_read()) / HMC5883L_GAIN;

}

