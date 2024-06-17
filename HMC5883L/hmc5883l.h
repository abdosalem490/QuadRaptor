#ifndef HMC5883L__H
#define HMC5883L__H
/* I2C master mode flag */
#define MASTER_TRANSMIT_MODE 0
#define MASTER_RECEIVER_MODE 1

/* Receiver buffer size */
#define I2C_Rx_BUFFER_SIZE   6

/* HMC5883L Constants */
#define HMC5883L_SLAVE_ADDRESS   (0x1E)
#define HMC5883L_REG_DATA        (0x03)
#define HMC5883L_REG_ID          (0x0A)

#define HMC5883L_REG_MODE        (0x02)
#define HMC5883L_CONTINUOUS_MODE (0x00)
#define HMC5883L_SINGLE_MODE     (0x01)

#define HMC5883L_REG_CONFIG_A    (0x00)
#define HMC5883L_SAMPLES_1       (0x00)
#define HMC5883L_SAMPLES_8       (0x60)
#define HMC5883L_OUTPUT_RATE_15  (0x10)

#define HMC5883L_REG_CONFIG_B    (0x01)
#define HMC5883L_RANGE_1_3       (0x20)
#define HMC5883L_GAIN            (1090.0)

/* MPU6050 auxiliary options*/
#define GY87_AUXILIARY           (1)
#define MPU6050_SLAVE_ADDRESS    (0x68)
#define MPU6050_REG_USER_CTRL    (0x6A)
#define MPU6050_DISABLE_MASTER   (0x00)
#define MPU6050_REG_BYPASS       (0x37)
#define MPU6050_ENABLE_BYPASS    (0x02)
#define MPU6050_REG_PWR_MGMT_1   (0x6B)

/* Packet Constants */
#define X_AXIS      (0)
#define Y_AXIS      (1)
#define Z_AXIS      (2)

/* Declination angle */
#define DECLINATION_DEGREE 4
#define DECLINATION_MINUTE 51

/* Calibration Results */
#define X_OFFSET 259.0
#define Y_OFFSET -163.0
#define SCALE 385.0

struct packet{
    short raw[3];
    float calibrated[3];
    float azimuth;
};
typedef struct packet hmc5883l_packet;

/*
 * Initialize magnetometer
 * Only called once
 */
void hmc5883l_init();

/*
 * Get magnetometer measurements
 * Note: hmc5883l_init must be called once in the
 *       program before using this function
 */
void hmc5883l_read(hmc5883l_packet* data);

void getIDs(char*, char*, char*);
#endif
