

/******************************************************************************
    Copyright (C) 2020  Daryl Hanlon (ignotus666@hotmail.com)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

*********************************************************************************/
#include <Arduino.h>
#include <images.h>
#include <ILI9341_due_config.h>
#include <SystemFont5x7.h>
#include <ILI9341_due.h>
#include <fonts/Arial_bold_14.h>
#include <EEPROM.h>
#include <SPI.h>
#include <MIDI.h>
#include <ResponsiveAnalogRead.h>
#include <FastLED.h>
#include <Mux.h>
#include <AnalogSmooth.h>
#include <MapFloat.h>

//MCU: Atmega1284

using namespace admux;

// Pin definitions and wiring for TFT:
#define TFT_CS   4
#define TFT_DC   3
#define TFT_RST  2

/*Hardware MOSI and SCK pins for MEGA (can't be freely assigned):
  MOSI -> pin 51 (D5 for 1284)
  SCK -> pin 52. (D7 for 1284)
  LED & VCC -> 3.3v
  GND -> GND.
  SCK, MOSI, DC and CS pins must go through 5v -> 3.3v level shifter.
  MISO can be left disconnected if not using SD card.*/

// Create instance of TFT library:
ILI9341_due tft = ILI9341_due(TFT_CS, TFT_DC, TFT_RST);

//RGB LEDs:
#define NUM_LEDS 100 //Actually 9, but this workaround fixes an annoying flicker.
#define DATA_PIN 15
CRGB leds[NUM_LEDS];
long unsigned midiLedTime = 0;

//Switches:
Mux mux(admux::Pin(19, INPUT_PULLUP, PinType::Digital), Pinset(20, 21, 22)); //Use 'admux::Pin' instead of 'Pin' to resolve conflict with FastLED library.
const byte pressed[8] = {0, 1, 2, 3, 4, 5, 6, 7};                            //These go through the multiplexer.
const byte pressed2[2] = {13, 14};                                           //These go straight to digital inputs.

//Variables to hold the new and old switch states for debouncing:
bool newSwitchState[24] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW,
                           LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW,
                           LOW, LOW, LOW, LOW
                          };

bool oldSwitchState[8] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};

bool newSwitchState2[6] = {LOW, LOW, LOW, LOW, LOW, LOW
                          };

bool oldSwitchState2[2] = {LOW, LOW};
long unsigned currentDebounceTime = 0;
long unsigned lastDebounceTime = 0;

//Switch states for debouncing:
bool keyPressed[8] = {false, false, false, false, false, false, false, false};
bool keyPressed2[2] = {false, false};

//Long press variables:
long buttonTimer = 0;
long longPressTime = 700;

boolean button9Active = false;
boolean longPress9Active = false;
boolean button10Active = false;
boolean longPress10Active = false;
boolean button7Active = false;
boolean longPress7Active = false;
boolean button8Active = false;
boolean longPress8Active = false;

bool tunerOn = false;
bool muteOn = false;

//Expression pedal variables:
byte pedalControlNum = 0;
bool pedalState = 0;
const int pedalPin = A0;
ResponsiveAnalogRead pedal(pedalPin, true, 0.01);
int pedalVal = 0;
int lastPedalVal = 0;   //Initial wah values. One for the first value and another to test if there's been a change.
int pedalRead = 0;
int pedalBar = 0;
char sensorPrintout[4];    //Char array to print wah values.
char oldSensorPrintout[4]; //Char array to print wah values.
int pedalMin = 1023;       // Reference minimum pedal value for calibration.
int pedalMax = 0;          // Maximum pedal value for calibration.
long unsigned calibrateTime = 0;
//eeprom address locations:
#define ADDR_MIN_VAL         0                               //Starts at address zero.
#define ADDR_MAX_VAL         ADDR_MIN_VAL + sizeof(pedalMin) //Use the next free space.

//Digital volume:
int volVal = 64;
int lastVolVal = 0;
int volBar = 0;
int volPerc = 0;

//Battery stuff:
int battPin = A2; //Analog pin to read battery voltage.
AnalogSmooth as200 = AnalogSmooth(200); //Average value of 10 readings.
float battRead = 0;
char voltagePrintout[5];//Char array for battery voltage.
char volPercPrintout[4];//Char array for battery percentage.
int voltageBar = 0;
int voltagePerc = 0;
int lastVoltagePerc = 0;
long unsigned lastReading = -30000;
long unsigned currentReading = 0;
bool usbOn = true;

#define timeCount ADDR_MAX_VAL + sizeof(pedalMax)//Use address after pedal min and max values.
long unsigned countBatteryTime = 0;
int minuteCounter = 0;
byte eepromSaveCounter = 0;
char hourPrintout[3];                            //Char array for battery time on (hours).
char minutePrintout[3];                          //Char array for battery time on (minutes).
byte hoursNum = 0;
byte minutesNum = 0;

//Variables for bank changes:
bool statusBank[5] = {true, false, false, false, false};

int bankNumber = 0;
byte oldBankNumber = 1;

byte bankButtonState = 0;
byte lastBankButton = 0;

byte lastBank = 0; //Variable to enable returning to last bank active before leaving preset mode.
byte b = bankNumber;

const char *smallPresetName[5][6] =
{
  {"MAST. PUP", "B. in BLACK", "STONER", "CLEAN", "CLEANw/EFF", "ECHOEY"}, //Bank 1.
  {"TOOL", "KYUSS", "CYCO", "OCTA", "SANDMAN", "NEUROSIS"},                //Bank 2.
  {"TRIP.DEL", "CRUNCH", "FUZZY", "EXTREME", "SLUDGE", "DOOM"},            //3
  {"PRES.19", "PRES.20", "PRES.21", "PRES.22", "PRES.23", "PRES.24"},      //4
  {"PRES.25", "PRES.26", "PRES.27", "PRES.28", "PRES.29", "PRES.30"}       //5
};                                                                         //For more banks, add more sets (6 per bank) and reflect no. in first parameter after bankNames.

const char *bigPresetName[] =                                                         //Large name printed in centre.
{ "MASTER OF PUPPETS", "BACK IN BLACK", "STONER", "CLEAN", "CLEAN w/EFF", "ECHOEY",   //Bank 1. These differ from the arrays above in that here individual names are printed, not sets.
  "TOOL", "KYUSS", "CYCO", "OCTA", "SANDMAN", "NEUROSIS",                             //Bank 2.
  "TRIPLE DELAY", "CRUNCH", "FUZZY", "EXTREME", "SLUDGE", "DOOM",                     //3
  "PRESET 19", "PRESET 20", "PRESET 21", "PRESET 22", "PRESET 23", "PRESET 24",       //4
  "PRESET 25", "PRESET 26", "PRESET 27", "PRESET 28", "PRESET 29", "PRESET 30"        //5
};                                                                                    //Add more names if adding more banks (6 per bank).

int activeLed = -1;    //Currently active LED. Set at boot to a value not corresponding to any LED.
int lastLed = -1;      //LED to turn off when another one becomes active.
int activePreset = -2; //To return to the last preset active before leaving preset mode. Set to -2 only at boot to stop it printing wrong preset.
int lastActivePreset = 0;
bool presetChanged = false;

//Pedalboard mode variable:
bool stompStatus = false;

//Variables to toggle stomp buttons:
bool stompState[6] = {false, false, false, false, false, false};

long unsigned clearNameTime = 0;

//Variable to toggle loop mode:
bool loopStatus = false;
bool loopStateInit = false;
bool playLedOn =false;

long unsigned loopTime = 0;

//Variables to toggle loop buttons:
bool loopState[6] = {true, true, true, true, true, true};

//Variables used to control blinking LEDs:
bool ledOn[6] = {false, false, false, false, false, false};
uint32_t ledStatus[6] = {CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black};

byte loopLed = 0;

//Variables to hold the times for blinking LEDs:
unsigned long timeNow = 0;
unsigned long timePrev = 0;
unsigned int timeWait = 400;

//Set up MIDI communication:
MIDI_CREATE_DEFAULT_INSTANCE();

void setup()
{
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);

  //Initialise TFT:
  tft.begin();

  pinMode(13, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);


  tft.setRotation(iliRotation270); //Flip screen upside down because of interfering wires.

  bootSequence();

  MIDI.begin();           //Set up MIDI output.
  //Serial.begin(115200); //For debugging.

  pedalMin = EEPROM.get(ADDR_MIN_VAL, pedalMin); //Load pedal min and max values from eeprom.
  delay(100);
  pedalMax = EEPROM.get(ADDR_MAX_VAL, pedalMax);
  delay(100);
  minuteCounter = EEPROM.get(timeCount, minuteCounter);
  delay(100);
  //Serial.println(pedalMin);
  //Serial.println(pedalMax);

  tft.setFont(Arial_bold_14);
}

void loop()
{
  currentDebounceTime = millis();
  debounceTime();
  wah();

  //Every 200 readings of the analog pin connected to the battery's + terminal, average them:
  float analogSmooth200 = as200.analogReadSmooth(battPin);
  battRead = analogSmooth200;

  if (millis() > 10000 && millis() < 10100)    //Give input time to stabilise and then determine whether it's on USB or battery power.
  {
    if (battRead < 250) //If it reads less than 3v it's on USB power.
    {
      tft.fillRect(1, 223, 35, 16, ILI9341_BLACK);
      tft.setFont(Arial_bold_14);
      tft.setTextColor(ILI9341_CYAN);
      tft.setTextScale(1);
      tft.printAt("USB", 18, 190);
      tft.printAt("POWER", 5, 209);
    }

    else
    {
      tft.drawRoundRect(1, 185, 53, 25, 3, ILI9341_WHITE); //Draw battery
      tft.drawRoundRect(2, 186, 51, 23, 3, ILI9341_WHITE);
      tft.fillRect(54, 193, 4, 8, ILI9341_WHITE);

      tft.setTextColor(ILI9341_CYAN, ILI9341_BLACK);
      tft.setTextScale(1);
      tft.printAt("Batt:", 1, 214);

      usbOn = false;
      tft.setFont(SystemFont5x7);
      tft.setTextScale(1);
      tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
      tft.printAt("UpTime: ", 1, 230);
      printUptime();
    }
  }
  //If on battery power, count minutes it's on for:
  if (usbOn == false)
  {
    batteryLife();
  }

  //Print averaged battery voltage every 30 seconds:
  currentReading = millis();
  readBattery();

  tft.setFont(Arial_bold_14);

  //See which mode is active for bank buttons 9 & 10. Long-press 9 to cycle through controller bank change mode (no MIDI), and bank & preset up/down in software (MIDI sent):
  bankMode();

  //What happens when cycling through preset banks (not software banks):
  presetBanks();

  //Determine which bank is active:
  presetBankStatus();

  //Check mode change buttons:
  modeButtons();

  //Turn MIDI LED off if it's on:
  midiLedOff();

  if (loopStatus == false)
  {
    lastLed = activeLed;
  }
}

//END OF LOOP().


//CLEAR SPACES:
void clearSmallPresets()   //Clear small preset names but leave large one.
{
  tft.fillRect(1, 1, 320, 16, ILI9341_BLACK);
  tft.fillRect(1, 90, 320, 16, ILI9341_BLACK);
}

void clearTopHalf()
{
  tft.fillRect(0, 1, 320, 152, ILI9341_BLACK);
}

void clearLargeName()     //Clear large preset name.
{
  tft.fillRect(1, 40, 320, 40, ILI9341_BLACK);
}

void clearBankSpace()     //Clear bank number space.
{
  tft.fillRect(95, 152, 85, 22, ILI9341_BLACK);
}

void clearMode()          //Clear loop/stomp/preset mode on message.
{
  tft.fillRect(194, 154, 120, 20, ILI9341_BLACK);
}

void clearBankMode()      //Bank up/down buttons' status space.
{
  tft.fillRect(1, 130, 160, 14, ILI9341_BLACK);
}

void clearPedalName()
{
  tft.fillRect(240, 222, 40, 18, ILI9341_BLACK);
}
