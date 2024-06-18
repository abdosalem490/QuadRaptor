#include <math.h>
#include "debug.h"
#include "ch32v20x_rcc.h"
#include "ch32v20x_gpio.h"
#include "ch32v20x_i2c.h"
#include "imu.h"

#define CALIBRATION_ITERATIONS (2000)
#define PI 3.14159265

/* Receiver buffer */
u8 RxData[I2C_Rx_BUFFER_SIZE];

/* Calibration */
float roll_calibration = 0, pitch_calibration = 0, yaw_calibration = 0;

void I2C_init() __attribute__((always_inline));
void I2C_start_transmission(uint8_t receiver_address, uint8_t master_receive) __attribute__((always_inline));
void I2C_write(uint8_t value) __attribute__((always_inline));
void I2C_stop() __attribute__((always_inline));
uint8_t I2C_requestFrom(uint8_t address, uint8_t quantity) __attribute__((always_inline));
uint8_t I2C_read() __attribute__((always_inline));

void mpu6050_gyro_setup();
void mpu6050_accel_setup();
void mpu6050_gyro_read(float* roll_rate, float* pitch_rate, float* yaw_rate);
void mpu6050_accel_read(float* x_acc, float* y_acc, float* z_acc);

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

    while(i < quantity){
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


void mpu6050_gyro_setup()
{
    int16_t calibration_iter = CALIBRATION_ITERATIONS;
    float roll_rate, pitch_rate, yaw_rate;
    float roll_local_calib = 0, pitch_local_calib = 0, yaw_local_calib = 0;
    I2C_init_ch32();
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
    /**
    Register: CONFIG (0x1A = 26)
    * Disables FSYNC
    * Sets the Digital Low Pass filter of BW = 10Hz
    */
    I2C_start_transmission(MPU6050_SLAVE_ADDRESS, MASTER_TRANSMIT_MODE);
    I2C_write(MPU6050_REG_CONFIG);
    I2C_write(0x05);
    I2C_stop();
    /**
    Register: GYRO_CONFIG (0x1B = 27)
    * Doesn't enable gyroscope self test
    * Sets the full scale range to [+-500 deg/s]
    */
    I2C_start_transmission(MPU6050_SLAVE_ADDRESS, MASTER_TRANSMIT_MODE);
    I2C_write(MPU6050_REG_GYRO_CONFIG);
    I2C_write(0x08);
    I2C_stop();

    /**
     * Calibrate the gyroscope
     * Make the sensor aware of its physical reference
    */
    while(calibration_iter--){
        mpu6050_gyro_read(&roll_rate, &pitch_rate, &yaw_rate);
        roll_local_calib += roll_rate;
        pitch_local_calib += pitch_rate;
        yaw_local_calib += yaw_rate;
        Delay_Ms(1);
    }
    roll_calibration = roll_local_calib / CALIBRATION_ITERATIONS;
    pitch_calibration = pitch_local_calib / CALIBRATION_ITERATIONS;
    yaw_calibration = yaw_local_calib / CALIBRATION_ITERATIONS;
}


void mpu6050_gyro_read(float* roll_rate, float* pitch_rate, float* yaw_rate) {
    int16_t GyroX, GyroY, GyroZ;

    /**
    * Registers: Gyroscope measurements (0x43 to 0x48 = 67 to 72)
    */
    I2C_start_transmission(MPU6050_SLAVE_ADDRESS, MASTER_TRANSMIT_MODE);
    I2C_write(MPU6050_REG_GYRO_OUT);
    I2C_stop();

    // Get sensor readings
    I2C_requestFrom(MPU6050_SLAVE_ADDRESS, I2C_Rx_BUFFER_SIZE);

    GyroX= I2C_read()<<8 | I2C_read();
    GyroY= I2C_read()<<8 | I2C_read();
    GyroZ= I2C_read()<<8 | I2C_read();

    *roll_rate=(float)GyroX/MPU6050_LSB_DPS - roll_calibration;
    *pitch_rate=(float)GyroY/MPU6050_LSB_DPS - pitch_calibration;
    *yaw_rate=(float)GyroZ/MPU6050_LSB_DPS - yaw_calibration;

}


void mpu6050_accel_setup()
{
    I2C_init_ch32();
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
    /**
    Register: CONFIG (0x1A = 26)
    * Disables FSYNC
    * Sets the Digital Low Pass filter of BW = 10Hz
    */
    I2C_start_transmission(MPU6050_SLAVE_ADDRESS, MASTER_TRANSMIT_MODE);
    I2C_write(MPU6050_REG_CONFIG);
    I2C_write(0x05);
    I2C_stop();
    /**
    Register: ACCEL_CONFIG (0x1C = 28)
    * Doesn't enable accelerometer self test
    * Sets the full scale range to [+- 8g]
    */
    I2C_start_transmission(MPU6050_SLAVE_ADDRESS, MASTER_TRANSMIT_MODE);
    I2C_write(MPU6050_REG_ACCEL_CONFIG);
    I2C_write(0x10);
    I2C_stop();
}


void mpu6050_accel_read(float* x_acc, float* y_acc, float* z_acc)
{
    int16_t x_reg, y_reg, z_reg;

    /**
    * Registers: Accelerometer measurements (0x3B to 0x40 = 59 to 64)
    */
    I2C_start_transmission(MPU6050_SLAVE_ADDRESS, MASTER_TRANSMIT_MODE);
    I2C_write(MPU6050_REG_ACCEL_OUT);
    I2C_stop();

    // Get sensor readings
    I2C_requestFrom(MPU6050_SLAVE_ADDRESS, I2C_Rx_BUFFER_SIZE);

    x_reg= I2C_read()<<8 | I2C_read();
    y_reg= I2C_read()<<8 | I2C_read();
    z_reg= I2C_read()<<8 | I2C_read();

    *x_acc=(float)x_reg/MPU6050_LSB_G;
    *y_acc=(float)y_reg/MPU6050_LSB_G;
    *z_acc=(float)z_reg/MPU6050_LSB_G;
}

//                                                                                                                              GYR                 ACCEL
void kalman_filter(float * KalmanState, float * KalmanUncertainty, float KalmanInput, float KalmanMeasurement, float Ts, float process_noise, float measure_covar)
{
    float KalmanGain;
    *KalmanState = *KalmanState + Ts*KalmanInput;
    *KalmanUncertainty = *KalmanUncertainty + Ts*Ts * process_noise*process_noise;
    KalmanGain = *KalmanUncertainty * 1/(1*(*KalmanUncertainty) + measure_covar*measure_covar);
    *KalmanState = *KalmanState + KalmanGain*(KalmanMeasurement-*KalmanState);
    *KalmanUncertainty = (1-KalmanGain) * (*KalmanUncertainty);
}


void mpu6050_init()
{
    mpu6050_gyro_setup();
    mpu6050_accel_setup();
}


void mpu6050_read(mpu6050_packet* data)
{
    mpu6050_gyro_read(&(data->angle_rates[ROLL]), &(data->angle_rates[PITCH]), &(data->angle_rates[YAW]));
    mpu6050_accel_read(&(data->accel[X_AXIS]), &(data->accel[Y_AXIS]), &(data->accel[Z_AXIS]));
}




void hmc5883l_init()
{
    I2C_init_ch32();

    #if GY87_AUXILIARY != 0
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

    #endif


    /**
    Register: MODE_REG (0x02)
    *  Sets the measurement mode
    **/
    I2C_start_transmission(HMC5883L_SLAVE_ADDRESS, MASTER_TRANSMIT_MODE);
    I2C_write(HMC5883L_REG_MODE);
    I2C_write(HMC5883L_CONTINUOUS_MODE);
    I2C_stop();

    /**
    Register: CONFIG_A (0x00)
    *  Sets the samples per measurement output to 8
    *  Sets the output data rate to 15Hz
    **/
    I2C_start_transmission(HMC5883L_SLAVE_ADDRESS, MASTER_TRANSMIT_MODE);
    I2C_write(HMC5883L_REG_CONFIG_A);
    I2C_write(HMC5883L_SAMPLES_1 | HMC5883L_OUTPUT_RATE_15);
    I2C_stop();

    /**
    Register: CONFIG_B (0x01)
    *  Sets the sensor field range to 1.3 Ga
    **/
    I2C_start_transmission(HMC5883L_SLAVE_ADDRESS, MASTER_TRANSMIT_MODE);
    I2C_write(HMC5883L_REG_CONFIG_B);
    I2C_write(HMC5883L_RANGE_1_3);
    I2C_stop();


}

void compute_azimuth(hmc5883l_packet* data)
{
    float declination_angle, heading;
    // Declination angle
    declination_angle = (DECLINATION_DEGREE + (DECLINATION_MINUTE / 60.0)) / (180 / PI);
    // Calculate heading
    heading = atan2(data->calibrated[Y_AXIS], data->calibrated[X_AXIS]);
    heading += declination_angle;

    if(heading < 0)
        heading += 2*PI;
    if(heading > 2*PI)
        heading -= 2*PI;

    data->azimuth = heading * (180/PI);
}

void hmc5883l_normalize(hmc5883l_packet* data)
{
    data->calibrated[X_AXIS] = (data->raw[X_AXIS] - X_OFFSET) / SCALE;
    data->calibrated[Y_AXIS] = (data->raw[Y_AXIS] - Y_OFFSET) / SCALE;
}

void hmc5883l_read(hmc5883l_packet* data)
{
    /**
    * Registers: Magnetometer measurements (0x03 to 0x08)
    */
    I2C_start_transmission(HMC5883L_SLAVE_ADDRESS, MASTER_TRANSMIT_MODE);
    I2C_write(HMC5883L_REG_DATA);
    I2C_stop();

    // Get sensor readings
    I2C_requestFrom(HMC5883L_SLAVE_ADDRESS, I2C_Rx_BUFFER_SIZE);

    data->raw[X_AXIS] = (I2C_read()<<8 | I2C_read());
    data->raw[Z_AXIS] = (I2C_read()<<8 | I2C_read());
    data->raw[Y_AXIS] = (I2C_read()<<8 | I2C_read());

    hmc5883l_normalize(data);
    compute_azimuth(data);

}

void imu_init()
{
    mpu6050_init();
    hmc5883l_init();
}

void imu_read(imu_data* data)
{
    float roll_rad, pitch_rad;
    float mag_x, mag_y, mag_z;
    float measured_roll, measured_pitch, measured_yaw;

    mpu6050_read(&(data->mpu6050));
    hmc5883l_read(&(data->hmc5883l));

    roll_rad = atan(data->mpu6050.accel[Y_AXIS]/sqrt(data->mpu6050.accel[X_AXIS]*data->mpu6050.accel[X_AXIS] + data->mpu6050.accel[Z_AXIS]*data->mpu6050.accel[Z_AXIS]));
    pitch_rad = -atan(data->mpu6050.accel[X_AXIS]/sqrt(data->mpu6050.accel[Y_AXIS]*data->mpu6050.accel[Y_AXIS] + data->mpu6050.accel[Z_AXIS]*data->mpu6050.accel[Z_AXIS]));

    measured_roll  = roll_rad  * (180/PI);
    measured_pitch = pitch_rad * (180/PI);

    kalman_filter(&(data->kalman_angles[ROLL]), &(data->kalman_uncertainty[ROLL]), data->mpu6050.angle_rates[ROLL], measured_roll, 1, STD_DEV_GYR, STD_DEV_ACC);
    kalman_filter(&(data->kalman_angles[PITCH]), &(data->kalman_uncertainty[PITCH]), data->mpu6050.angle_rates[PITCH], measured_pitch, 1, STD_DEV_GYR, STD_DEV_ACC);

    // Yaw angle
    roll_rad = data->kalman_angles[ROLL] * (PI/180);
    pitch_rad = data->kalman_angles[PITCH] * (PI/180);

    mag_x = data->hmc5883l.calibrated[X_AXIS];
    mag_y = data->hmc5883l.calibrated[Y_AXIS];
    mag_z = data->hmc5883l.calibrated[Z_AXIS];

    mag_x = mag_x*cos(roll_rad);
    mag_y = mag_y*cos(pitch_rad);

//    measured_yaw = atan2(mag_y, mag_x) * (180/PI);
    data->hmc5883l.calibrated[X_AXIS] = mag_x;
    data->hmc5883l.calibrated[Y_AXIS] = mag_y;
    compute_azimuth(&(data->hmc5883l));
    measured_yaw = data->hmc5883l.azimuth;

    kalman_filter(&(data->kalman_angles[YAW]), &(data->kalman_uncertainty[YAW]), data->mpu6050.angle_rates[YAW], measured_yaw, 1, STD_DEV_GYR, STD_DEV_MAG);


}