
/**
* @brief: include needed libraries, RF24 and SPI are for transceiver module, ssd1306 and nano_gfx are for LCD module, 
*/
#include <SPI.h>  
#include "RF24.h"
#include "ssd1306.h"
#include "nano_gfx.h"
#include <stdio.h>
#include "math.h"


/**
* @brief: needed global defines 
*/
#define RIGHT_JOYSTICK_X_PIN A3 
#define RIGHT_JOYSTICK_Y_PIN A2 
#define RIGHT_JOYSTICK_SW_PIN 2 

#define LEFT_JOYSTICK_X_PIN A0 
#define LEFT_JOYSTICK_Y_PIN A1 
#define LEFT_JOYSTICK_SW_PIN 7 

#define LEFT_POT_PIN A7 
#define RIGHT_POT_PIN A6 
#define GENERAL_SW_PIN 6

// status of the remote control
#define FLYING_MODE_SELECTION 0
#define FLYING_MODE_STABLE 1
#define FLYING_MODE_RETURN_HOME 2
#define FLYING_MODE_LANDING 3
#define FLYING_MODE_STATUS 4



#define CONACTENATE(first, second) first second

// global variables
SAppMenu mainMenu;
SAppMenu appMenu;
SAppMenu flyModesMenu;
SAppMenu *currentMenu;

RF24 myRadio (9, 10);
unsigned long menuTime;
unsigned long statusTime;
unsigned long commandTime;


uint8_t flyingMode = FLYING_MODE_SELECTION;
uint8_t rightJoyStickSWState = HIGH;
uint8_t leftJoyStickSWState = HIGH;
uint8_t generalSWState = HIGH;
uint8_t rightJoyStickSWStateRC = HIGH;
uint8_t leftJoyStickSWStateRC = HIGH;

uint8_t rightJoyStickPressed = 0;
uint8_t leftJoyStickPressed = 0;
uint8_t generalPressed = 0;


unsigned long currentFlyingSessionInSeconds = 0;
float distanceToOrigin = 0;
float altitude = 0;
float temperature = 0;
uint8_t batteryCharge = 0;


/*
 * Celsius image below is defined directly in flash memory.
 * This reduces SRAM consumption.
 * The image is defined from bottom to top (bits), from left to
 * right (bytes).
 */
const PROGMEM uint8_t celsius_circle[8] =
{
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000010,
    0B00000101,
    0B00000010
};

// address for the pipes
byte addresses[][6] = {"RtoD", "DtoR"};

/**
* @brief: contains elements of main menu
*/
const char *mainMenuItems[] =
{
    "1. Status",
    "2. Fly Modes",
    "3. run an app",
};

/**
* @brief: contains elements of application menus
*/
const char *appMenuItems[] =
{
    "1. Return Home",
    "2. Land Now",
};

/**
* @brief: contains elements of fly modes menus
*/
const char *flyMenuItems[] =
{
    "1. Stable Mode",
};

/**
* @brief: defines the data to be sent over nrf module
*/
// defines the type of the data to be sent over the air
typedef enum {
  DATA_TYPE_MOVE,   // from remote to drone
  DATA_TYPE_EXTRAS, // from remote to drone
  DATA_TYPE_INFO,   // from drone to remote
} DATA_TYPE_t;

// struct defines data that holds: yaw, roll, pitch, thurst commands
typedef struct __attribute__((packed)){
  int8_t roll;
  int8_t pitch;
  int8_t thurst;
  int8_t yaw;
  bool turnOnLeds;
  bool playMusic;
} move_command_t;


// struct defines data that holds info coming from the drone like temperature, battery charge, etc...
typedef struct __attribute__((packed)){
  float distanceToOrigin;
  float altitude;
  float temperature;
  uint8_t batteryCharge;
}drone_info_t;

// the struct that to be sent over the air
typedef struct __attribute__((packed)){
  uint8_t type;

  union {
    move_command_t move;
    drone_info_t info;
  } data;

} data_t;

data_t data; // the variable through which we will send and recieve data

/**
* @brief: global counter to count how many sample reading we get from the buttons
*/
uint32_t global_u32Counter = 0;

/**
* @brief: repesents the current state of the flight
*/
typedef enum {
  FLIGHT_STATUS_MONITOR,
  FLIGHT_STATUS_FLYING,
  FLIGHT_STATUS_LANDING,
  FLIGHT_STATUS_ARMING,
  FLIGHT_STATUS_DE_ARMING,   
  FLIGHT_STATUS_RETURNING_HOME,   
}FLIGHT_STATUS_t;

const char *flight_status[] =
{
  [FLIGHT_STATUS_MONITOR] = "monitoring",
  [FLIGHT_STATUS_FLYING] = "flying",
  [FLIGHT_STATUS_LANDING] = "landing",
  [FLIGHT_STATUS_ARMING] = "arming",
  [FLIGHT_STATUS_DE_ARMING] = "de-arming",
  [FLIGHT_STATUS_RETURNING_HOME] = "return home"
};


/**
* @brief: used to draw the status page
*/
static void drawStatus(float distanceToOrigin, float altitude, float temperature, uint8_t batteryCharge, const char* status)
{

  char buff[50] = "Status:      ";
  strcat(buff, status);

  ssd1306_printFixed(0,  0,  "Dist to Ogn:       m", STYLE_NORMAL);
  ssd1306_printFixed(0,  8,  "Altitude:          m", STYLE_NORMAL);
  ssd1306_printFixed(0,  16, buff, STYLE_NORMAL);
  ssd1306_printFixed(0,  24, "Temperature:       C", STYLE_NORMAL);
  SPRITE sprite = ssd1306_createSprite(106, 24, sizeof(celsius_circle), celsius_circle );
  sprite.draw();
  ssd1306_printFixed(0,  32, "Battery:       %", STYLE_NORMAL);
  ssd1306_printFixed(0,  40, "Flying Time:", STYLE_NORMAL);
  updateStatus(distanceToOrigin, altitude, temperature, batteryCharge, 0);

}

/**
* @brief: used to update status page without redrawing whole page
*/
static void updateStatus(float distanceToOrigin, float altitude, float temperature, uint8_t batteryCharge, uint16_t flyingTimeInSeconds)
{
  char buff[7] = "test";  
  float percent = (batteryCharge / 100.0) * 25 + 100;

  // write distance to origin
  dtostrf(distanceToOrigin, 4, 2, buff);
  ssd1306_setCursor(78, 0);
  ssd1306_print(buff);

  // write Altitude
  dtostrf(altitude, 4, 2, buff);
  ssd1306_setCursor(78, 8);
  ssd1306_print(buff);

  // write temperature
  dtostrf(temperature, 4, 2, buff);
  ssd1306_setCursor(78, 24);
  ssd1306_print(buff);

  // write battery charge
  sprintf(buff, "%d", batteryCharge);
  ssd1306_setCursor(78, 32);
  ssd1306_print(buff);

  ssd1306_drawRect(100, 32, 125, 40);
  ssd1306_fillRect(100, 32, (uint8_t)percent, 40);

  // write flying Time
  sprintf(buff, "%02d:%02d", flyingTimeInSeconds / 60, flyingTimeInSeconds % 60);
  ssd1306_setCursor(78, 40);
  ssd1306_print(buff);
}


static void textDemo()
{
    ssd1306_setFixedFont(ssd1306xled_font6x8);
    ssd1306_clearScreen();
    ssd1306_printFixed(0,  8, "Normal text", STYLE_NORMAL);
    ssd1306_printFixed(0, 16, "Bold text", STYLE_BOLD);
    ssd1306_printFixed(0, 24, "Italic text", STYLE_ITALIC);
    ssd1306_negativeMode();
    ssd1306_printFixed(0, 32, "Inverted bold", STYLE_BOLD);
    ssd1306_positiveMode();
    delay(3000);
}



/**
* @brief: used to get a god state of button
*/
uint8_t getAverageReadings(uint32_t numOfReadings, uint8_t PinNumber)
{
  float avg = 0;
  for(uint32_t i = 0; i < numOfReadings; i++)
  {
    avg += digitalRead(PinNumber);
  }
  avg /= numOfReadings;
  return avg >= 0.5;
}

void setup()
{
  Serial.begin(115200);
  delay(1000);


  /* Select the font to use with menu and all font functions */
  ssd1306_setFixedFont(ssd1306xled_font6x8);
  ssd1306_128x64_i2c_init();
  ssd1306_clearScreen();

  ssd1306_createMenu( &mainMenu, mainMenuItems, sizeof(mainMenuItems) / sizeof(char *) );
  ssd1306_createMenu( &appMenu, appMenuItems, sizeof(appMenuItems) / sizeof(char *) );
  ssd1306_createMenu( &flyModesMenu, flyMenuItems, sizeof(flyMenuItems) / sizeof(char *) );
  
  ssd1306_showMenu( &mainMenu );

  pinMode(RIGHT_JOYSTICK_SW_PIN, INPUT_PULLUP);
  pinMode(LEFT_JOYSTICK_SW_PIN, INPUT_PULLUP);
  pinMode(GENERAL_SW_PIN, INPUT_PULLUP);

  currentMenu = &mainMenu;

  // intialize nrf24l01
  myRadio.begin();  
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_1MBPS ); 
  myRadio.openWritingPipe(addresses[0]);
  myRadio.openReadingPipe(1, addresses[1]);

  delay(1000);

  menuTime = millis();
  statusTime = millis();
  commandTime = millis();
}

uint8_t readingsTaken = 0;
uint8_t after_readings = 0;



void loop()
{
  if(millis() % 5 == 0)
  {
      rightJoyStickSWState = getAverageReadings(50, RIGHT_JOYSTICK_SW_PIN);
      leftJoyStickSWState = getAverageReadings(50, LEFT_JOYSTICK_SW_PIN);
      generalSWState = getAverageReadings(50, GENERAL_SW_PIN);
  }

  // check if 250ms passed (for change of selection of the menu)
  if(flyingMode == FLYING_MODE_SELECTION)
  {
    if(millis() - menuTime >= 250){
      uint16_t dir = analogRead(A2);
      menuTime = millis();
      
      // navigate between menu items
      if(dir > 800){
        ssd1306_menuDown(currentMenu);
      }
      else if(dir < 300) {
        ssd1306_menuUp(currentMenu);
      }
      ssd1306_updateMenu(currentMenu);
    }

    // check if some menu item is selected
    if(rightJoyStickSWState == HIGH && digitalRead(RIGHT_JOYSTICK_SW_PIN) == LOW) {
      delay(50);
      rightJoyStickSWState = LOW;

      uint8_t selected_item = ssd1306_menuSelection(currentMenu); 
      ssd1306_clearScreen();

      // main menu have: 1. Status , 2. Fly Modes , 3. run app
      if(currentMenu == &mainMenu)
      {
        // show status option is selected 
        if(selected_item == 0)
        {
          flyingMode = FLYING_MODE_STATUS;
          drawStatus(distanceToOrigin, altitude, temperature, batteryCharge, flight_status[FLIGHT_STATUS_MONITOR]);
        }
        // fly modes option is selected
        else if(selected_item == 1)
        { 
          currentMenu = &flyModesMenu;
          ssd1306_showMenu( &flyModesMenu );
        }
        // run an app option is selected
        else if(selected_item == 2)
        {
          currentMenu = &appMenu;
          ssd1306_showMenu( &appMenu );
        }
      }
      // fly modes submenu has: 1. Stable Mode
      else if(currentMenu == &flyModesMenu)
      { 
        // Stable Mode is selected 
        if(selected_item == 0)
        {
          flyingMode = FLYING_MODE_STABLE;
          drawStatus(distanceToOrigin, altitude, temperature, batteryCharge, flight_status[FLIGHT_STATUS_ARMING]);
        }
      }
      // run an app has: 1. Return Home , 2. Land Now
      else if(currentMenu == &appMenu)
      {
        // return home option
        if(selected_item == 0)
        {
          flyingMode = FLYING_MODE_RETURN_HOME;
          drawStatus(distanceToOrigin, altitude, temperature, batteryCharge, flight_status[FLIGHT_STATUS_RETURNING_HOME]);
        }
        // land now option
        else if(selected_item == 1)
        { 
          flyingMode = FLYING_MODE_LANDING;
          drawStatus(distanceToOrigin, altitude, temperature, batteryCharge, flight_status[FLIGHT_STATUS_LANDING]);
        }
      }

    }
  }

  // check for return to main menu button
  if(generalSWState == HIGH && digitalRead(GENERAL_SW_PIN) == LOW)
  {
    generalSWState = LOW;
    delay(50);
    ssd1306_clearScreen();
    currentMenu = &mainMenu;
    currentFlyingSessionInSeconds = 0;
    flyingMode = FLYING_MODE_SELECTION;
    ssd1306_showMenu( &mainMenu );
  }

  // update of the shown status every 1 second
  if(flyingMode != FLYING_MODE_SELECTION && millis() - statusTime >= 1000)
  {
    // TODO: receive info from the drone

    statusTime = millis();
    updateStatus(distanceToOrigin, altitude, temperature, batteryCharge, ++currentFlyingSessionInSeconds);
  }

  // send commands to the in case of stable mode fly every 50 ms
  if(flyingMode == FLYING_MODE_STABLE)
  {

    if(millis() - commandTime >= 50)
    {

      // get the current state of buttons being pressed
      uint8_t curretRightReading = getAverageReadings(50, RIGHT_JOYSTICK_SW_PIN);
      uint8_t curretLeftReading = getAverageReadings(50, LEFT_JOYSTICK_SW_PIN);
      
      if(rightJoyStickSWStateRC == HIGH && curretRightReading == LOW)
      {
        rightJoyStickPressed = 1;
      }
      else
      {
        rightJoyStickPressed = 0;
      }

      if(leftJoyStickSWStateRC == HIGH && curretLeftReading == LOW)
      {
        leftJoyStickPressed = 1;
      }
      else
      {
        leftJoyStickPressed = 0;
      }

      commandTime = millis();
      data.type = DATA_TYPE_MOVE;
      data.data.move.yaw = -((analogRead(LEFT_JOYSTICK_X_PIN) >> 3) - 64);
      data.data.move.thurst = -((analogRead(LEFT_JOYSTICK_Y_PIN) >> 3) - 64);
      data.data.move.roll = -((analogRead(RIGHT_JOYSTICK_X_PIN) >> 3) - 64);
      data.data.move.pitch = -((analogRead(RIGHT_JOYSTICK_Y_PIN) >> 3) - 63);
      // data.data.move.turnOnLeds = rightJoyStickSWState == HIGH && digitalRead(RIGHT_JOYSTICK_SW_PIN) == LOW;
      // data.data.move.playMusic = leftJoyStickSWState == HIGH && digitalRead(LEFT_JOYSTICK_SW_PIN) == LOW;
      data.data.move.turnOnLeds = rightJoyStickPressed;
      data.data.move.playMusic = leftJoyStickPressed;

      readingsTaken = 0;

      char buff[100];
      sprintf(buff, "left = %d, right= %d", leftJoyStickPressed, rightJoyStickPressed);
      Serial.println(buff);

      // char buff[100];
      // sprintf(buff, "yaw = %d, thurst= %d, roll= %d, pitch=%d, test=%d", data.data.move.yaw, data.data.move.thurst, data.data.move.roll, data.data.move.pitch, analogRead(RIGHT_JOYSTICK_Y_PIN));
      // Serial.println(buff);
      
      myRadio.stopListening();
      while(myRadio.write(&data, sizeof(data)));
      myRadio.startListening(); 
    }
    else if(millis() - commandTime >= 25 && !readingsTaken)
    {
      // always get the readings
      rightJoyStickSWStateRC = getAverageReadings(50, RIGHT_JOYSTICK_SW_PIN);
      leftJoyStickSWStateRC = getAverageReadings(50, LEFT_JOYSTICK_SW_PIN);
      readingsTaken = 1;

    }

   
  }

  // read incoming traffic if any
  if(myRadio.available())
  {
    myRadio.read(&data, sizeof(data));

    // update current state
    temperature = data.data.info.temperature;
    batteryCharge = data.data.info.batteryCharge;
    altitude = data.data.info.altitude;
    distanceToOrigin = data.data.info.distanceToOrigin;
  }


}