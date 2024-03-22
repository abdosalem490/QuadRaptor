/* I2C master mode flag */
#define MASTER_TRANSMIT_MODE 0
#define MASTER_RECEIVER_MODE 1

/* Receiver buffer size */
#define I2C_Rx_BUFFER_SIZE   6

/* MPU6050 Constants */
#define MPU6050_SLAVE_ADDRESS   (0x68)
#define MPU6050_REG_PWR_MGMT_1  (0x6B)
#define MPU6050_REG_CONFIG      (0x1A)
#define MPU6050_REG_GYRO_CONFIG (0x1B)
#define MPU6050_REG_GYRO_OUT    (0x43)
#define MPU6050_LSB_DPS         (65.5)


/*
 * Initialize gyroscope
 * Only called once
 */
void mpu6050_gyro_setup();

/*
 * Get gyroscope measurements
 * Note: gyro_setup must be called once in the 
 *       program before using this function
 */
void mpu6050_gyro_read(float* roll_rate, float* pitch_rate, float* yaw_rate);
