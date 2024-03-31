/* I2C master mode flag */
#define MASTER_TRANSMIT_MODE 0
#define MASTER_RECEIVER_MODE 1

/* Receiver buffer size */
#define I2C_Rx_BUFFER_SIZE   6

/* MPU6050 Constants */
#define MPU6050_SLAVE_ADDRESS    (0x68)
#define MPU6050_REG_PWR_MGMT_1   (0x6B)
#define MPU6050_REG_CONFIG       (0x1A)
#define MPU6050_REG_GYRO_CONFIG  (0x1B)
#define MPU6050_REG_GYRO_OUT     (0x43)
#define MPU6050_LSB_DPS          (65.5)
#define MPU6050_REG_ACCEL_CONFIG (0x1C)
#define MPU6050_REG_ACCEL_OUT    (0x3B)
#define MPU6050_LSB_G            (4096)

/* Packet Constants */
#define ROLL        (0)
#define PITCH       (1)
#define YAW         (2)
#define X_AXIS      (0)
#define Y_AXIS      (1)
#define Z_AXIS      (2)



struct packet{
    float angle_rates[3];
    float accel[3];
};
typedef struct packet mpu6050_packet;

/*
 * Initialize gyroscope and accelerometer
 * Only called once
 */
void mpu6050_init();

/*
 * Get gyroscope and accelerometer measurements
 * Note: mpu6050_init must be called once in the 
 *       program before using this function
 */
void mpu6050_read(mpu6050_packet* data);
