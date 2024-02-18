#include <SPI.h>  
#include "RF24.h"

RF24 myRadio (7, 8);

/**
* @brief: defines the data to be sent over nrf module
*/
// defines the type of the data to be sent over the air
typedef enum {
  DATA_TYPE_MOVE,   // from remote to drone
  DATA_TYPE_EXTRAS, // from remote to drone
  DATA_TYPE_INFO,   // from drone to remote
}DATA_TYPE_t;

// struct defines data that holds: yaw, roll, pitch, thurst commands
typedef struct{
  int8_t roll;
  int8_t pitch;
  int8_t thurst;
  int8_t yaw;
  bool turnOnLeds;
  bool playMusic;
}move_command_t;


// struct defines data that holds info coming from the drone like temperature, battery charge, etc...
typedef struct{
  float distanceToOrigin;
  float altitude;
  float temperature;
  uint8_t batteryCharge;
}drone_info_t;

// the struct that to be sent over the air
typedef struct{
  DATA_TYPE_t type;

  union {
    move_command_t move;
    drone_info_t info;
  } data;

} data_t;

data_t data; // the variable through which we will send and recieve data
byte addresses[][6] = {"RtoD", "DtoR"};
unsigned long int infoTime = 0;

void setup() 
{
  Serial.begin(115200);
  delay(1000);
  myRadio.begin(); 
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_1MBPS ) ; 
  myRadio.openWritingPipe( addresses[1]);
  myRadio.openReadingPipe(1, addresses[0]);

  infoTime = millis();
}

void loop()  
{
  if (millis() - infoTime >= 1000) 
  {
    infoTime = millis();
    data.type = DATA_TYPE_INFO;
    data.data.info.altitude = random(0, 100);
    data.data.info.temperature = random(0, 100);
    data.data.info.distanceToOrigin = random(0, 100);
    data.data.info.batteryCharge = random(0, 100);
    myRadio.stopListening();
    
    while(myRadio.write(&data, sizeof(data)));
    myRadio.startListening();
  }

  // read incoming traffic if any
  if(myRadio.available())
  {
    myRadio.read(&data, sizeof(data));

    char buff[100];
    sprintf(buff, "yaw = %d, thurst= %d, roll= %d, pitch=%d", data.data.move.yaw, data.data.move.thurst, data.data.move.roll, data.data.move.pitch);
    Serial.println(buff);
  }

}