/*
The contents of this code and instructions are the intellectual property of Carbon Aeronautics. 
The text and figures in this code and instructions are licensed under a Creative Commons Attribution - Noncommercial - ShareAlike 4.0 International Public Licence. 
This license lets you remix, adapt, and build upon your work non-commercially, as long as you credit Carbon Aeronautics 
(but not in any way that suggests that we endorse you or your use of the work) and license your new creations under the identical terms.
This code and instruction is provided "As Is” without any further warranty. Neither Carbon Aeronautics or the author has any liability to any person or entity 
with respect to any loss or damage caused or declared to be caused directly or indirectly by the instructions contained in this code or by 
the software and hardware described in it. As Carbon Aeronautics has no control over the use, setup, assembly, modification or misuse of the hardware, 
software and information described in this manual, no liability shall be assumed nor accepted for any resulting damage or injury. 
By the act of copying, use, setup or assembly, the user accepts all resulting liability.

1.0  5 October 2022 -  initial release
*/

#include <Wire.h>

#define MONITOR 0
#define PLOT 1
#define SERIAL_MODE PLOT

void I2C_setclk(uint32_t freq) __attribute__((always_inline));
void I2C_init() __attribute__((always_inline));
void I2C_start_transmission(uint8_t receiver_address) __attribute__((always_inline));
void I2C_write(uint8_t value) __attribute__((always_inline));
void I2C_end() __attribute__((always_inline));
uint8_t I2C_requestFrom(uint8_t address, uint8_t quantity, uint8_t stop_bool) __attribute__((always_inline));
uint8_t I2C_read() __attribute__((always_inline));

inline void I2C_setclk(uint32_t freq){
  Wire.setClock(freq);
}
inline void I2C_init(){
  Wire.begin();
}
inline void I2C_start_transmission(uint8_t receiver_address){
  Wire.beginTransmission(receiver_address);
}
inline void I2C_write(uint8_t value){
  Wire.write(value);
}
inline void I2C_end(){
  Wire.endTransmission();
}
inline uint8_t I2C_requestFrom(uint8_t address, uint8_t quantity, uint8_t stop_bool = true){
  return Wire.requestFrom(address, quantity, stop_bool);
}
inline uint8_t I2C_read(){
  return Wire.read();
}

float RateRoll, RatePitch, RateYaw;
void gyro_signals(void) {
  I2C_start_transmission(0x68);
  I2C_write(0x1A);
  I2C_write(0x05);
  I2C_end();
  I2C_start_transmission(0x68);
  I2C_write(0x1B);
  I2C_write(0x8);
  I2C_end();
  I2C_start_transmission(0x68);
  I2C_write(0x43);
  I2C_end();
  I2C_requestFrom(0x68, 6);
  int16_t GyroX= I2C_read()<<8 | I2C_read();
  int16_t GyroY= I2C_read()<<8 | I2C_read();
  int16_t GyroZ= I2C_read()<<8 | I2C_read();
  RateRoll=(float)GyroX/65.5;
  RatePitch=(float)GyroY/65.5;
  RateYaw=(float)GyroZ/65.5;
}

void setup() {
  Serial.begin(57600);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  I2C_setclk(400000);
  I2C_init();
  delay(250);
  I2C_start_transmission(0x68);
  I2C_write(0x6B);
  I2C_write(0x00);
  I2C_end();
}
void loop() {
  gyro_signals();
  
  #if SERIAL_MODE == MONITOR
  Serial.print("Roll=");
  Serial.print(RateRoll);
  Serial.print(" ,Pitch=");
  Serial.print(RatePitch);
  Serial.print(" ,Yaw=");
  Serial.println(RateYaw);
  #endif
  
  #if SERIAL_MODE == PLOT
  Serial.print(RateRoll);
  Serial.print(", ");
  Serial.print(RatePitch);
  Serial.print(", ");
  Serial.println(RateYaw);
  #endif
  
  delay(50);
}
