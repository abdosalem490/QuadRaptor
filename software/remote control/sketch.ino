
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

// RF24 myRadio (7, 8);
unsigned long menuTime;
unsigned long statusTime;

uint8_t flyingMode = FLYING_MODE_SELECTION;
uint8_t rightJoyStickSWState = HIGH;
uint8_t leftJoyStickSWState = HIGH;
uint8_t generalSWState = HIGH;


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



/**
* @brief: needed struct for transceiver
*/
typedef struct 
{
  int id=1;
  float temperature = 18.3;
  char  text[100] = "Text to be transmitted";
} Package_t;
Package_t data;

byte addresses[][6] = {"0"};

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
  ssd1306_fillRect(100, 32, (int)percent, 40);
  ssd1306_drawRect(100, 32, 125, 40);


  ssd1306_setCursor(78, 32);
  ssd1306_print(buff);

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

  /*myRadio.begin();  
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openWritingPipe( addresses[0]);
  delay(1000);*/

  menuTime = millis();
  statusTime = millis();
}

void loop()
{

  if(millis() % 5 == 0)
  {
    rightJoyStickSWState = digitalRead(RIGHT_JOYSTICK_SW_PIN);
    leftJoyStickSWState = digitalRead(LEFT_JOYSTICK_SW_PIN);
    generalSWState = digitalRead(GENERAL_SW_PIN);

    Serial.println(rightJoyStickSWState);
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

      if(currentMenu == &mainMenu)
      {
        // show status option is selected 
        if(selected_item == 0)
        {
          flyingMode = FLYING_MODE_STATUS;
          drawStatus(distanceToOrigin, altitude, temperature, batteryCharge, flight_status[FLIGHT_STATUS_MONITOR]);
        }
        else if(selected_item == 1)
        { 
          currentMenu = &flyModesMenu;
          ssd1306_showMenu( &flyModesMenu );
        }
        else if(selected_item == 2)
        {
          currentMenu = &appMenu;
          ssd1306_showMenu( &appMenu );
        }
      }
      else if(currentMenu == &flyModesMenu)
      { 
        if(selected_item == 0)
        {
          flyingMode = FLYING_MODE_STABLE;
          drawStatus(distanceToOrigin, altitude, temperature, batteryCharge, flight_status[FLIGHT_STATUS_ARMING]);
        }
      }
      else if(currentMenu == &appMenu)
      {
        if(selected_item == 0)
        {
          flyingMode = FLYING_MODE_RETURN_HOME;
          drawStatus(distanceToOrigin, altitude, temperature, batteryCharge, flight_status[FLIGHT_STATUS_RETURNING_HOME]);
        }
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


  if(flyingMode != FLYING_MODE_SELECTION && millis() - statusTime >= 1000)
  {
    statusTime = millis();
    updateStatus(distanceToOrigin, altitude, temperature, batteryCharge, ++currentFlyingSessionInSeconds);
  }


  /*myRadio.write(&data, sizeof(data)); 
  Serial.print("\nPackage:");
  Serial.print(data.id);
  Serial.print("\n");
  Serial.println(data.temperature);
  Serial.println(data.text);
  data.id = data.id + 1;
  data.temperature = data.temperature+0.1;
  delay(1000);*/
}