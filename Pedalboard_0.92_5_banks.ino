
/******************************************************************************
    Copyright (C) 2019  Daryl Hanlon (ignotus666@hotmail.com)

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
#include <images.h>
#include <ILI9341_due_config.h>
#include <SystemFont5x7.h>
#include <ILI9341_due.h>
#include <fonts/Arial_bold_14.h>
#include <EEPROM.h>
#include <SPI.h>
#include <MIDI.h>
#include <AnalogSmooth.h>
#include <ResponsiveAnalogRead.h>


// Pin definitions and wiring for TFT:
#define TFT_CS   53
#define TFT_DC   49
#define TFT_RST  48 //Can also be connected to reset on Arduino board.
/*Hardware MOSI and SCK pins for MEGA (can't be freely assigned):
  MOSI -> pin 51
  SCK -> pin 52.
  LED & VCC -> 3.3v
  GND -> GND.
  SCK, MOSI, DC and CS pins must go through 5v -> 3.3v level shifter.
  MISO can be left disconnected if not using SD card.*/

// Create instance of TFT library:
ILI9341_due tft = ILI9341_due(TFT_CS, TFT_DC, TFT_RST);

//LED pin array:
const byte led[8] = {24, 25, 22, 23, 20, 21, 18, 19};
const byte ledCnt = 8;

long unsigned midiLedTime = 0;

//Button arrays and pins:
const byte pressed[10] = {5, 4, 7, 6, 9, 8, 36, 37, 11, 10};
const byte pressCount = 10;

//Wah variables:
const int wahPin = A0;
ResponsiveAnalogRead wahWah(wahPin, true, 0.01);
int wahVal = 0;
int lastwahVal = 0;   //Initial wah values. One for the first value and another to test if there's been a change.
int wahRead = 0;
int pedalMin = 1023;    // Reference minimum pedal value for calibration.
int pedalMax = 0;       // Maximum pedal value for calibration.
long unsigned calibrateTime = 0;
//eeprom address locations:
#define ADDR_MIN_VAL         0 //Starts at address zero.
#define ADDR_MAX_VAL         ADDR_MIN_VAL + sizeof(pedalMin) // Use the next free space.
//#define ADDR_X  ADDR_MAX_VAL + sizeof(pedalMax)            // For hypothetical use of more eeprom for something else.

//Digital volume:
int volVal = 64;
int lastVolVal = 0;
int volBar = 0;
int volPerc = 0;

//Battery stuff:
int battPin = 15; //Analog pin to read battery voltage.
AnalogSmooth as200 = AnalogSmooth(200); //Average value of 200 readings (library modified).
float battRead = 0;
char sensorPrintout[4]; //Char array to print wah values.
char oldSensorPrintout[4]; //Char array to print wah values.
char voltagePrintout[5];//Char array for battery voltage.
char volPercPrintout[4];//Char array for battery percentage.
int voltageBar = 0;
int voltagePerc = 0;
int lastVoltagePerc = 0;
long unsigned lastReading = -30000;
long unsigned currentReading = 0;
bool usbOn = false;

bool fHasLooped  = false; //For boot LED sequence.

//Variables for bank changes:
bool statusBank[5] = {true, false, false, false, false};

byte bankNumber = 1;
byte oldBankNumber = 0;

byte bankButtonState = 1;
byte lastBankButton = 1;

byte presetChanged = 0;

byte lastBank = 1; //Variable to enable returning to last bank active before leaving preset mode.

//Pedalboard mode variable:
bool stompStatus = false;

//Variables to toggle stomp buttons:
bool stompState[6] = {true, true, true, true, true, true};

long unsigned stompTime = 0;

//Variable to toggle loop mode:
bool loopStatus = false;

long unsigned loopTime = 0;

//Char strings for loop mode:
char *loopStringBig[] = {"PLAY", "MULTIPLY", "OVERDUB", "RECORD", "INSERT", "REPLACE", "PAUSE"};
char *loopStringSmall[] = {"MULTI", "OVERDUB", "REC", "INSERT", "REPLACE", "PAUSE"};
char *loopNamePosition[] = {"gTextAlignMiddleLeft", "gTextAlignMiddleCenter", "gTextAlignMiddleRight", "gTextAlignTopLeft", "gTextAlignTopCenter", "gTextAlignTopRight"};

//Variables to toggle loop buttons:
bool loopState[6] = {true, true, true, true, true, true};

// variables used to control blinking LEDs:
bool ledOn[6] = {false, false, false, false, false, false};
bool ledStatus[6] = {LOW, LOW, LOW, LOW, LOW, LOW};

byte loopLed = 0;

// variables to hold the new and old switch states for debouncing:
bool newSwitchState[30] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};

bool oldSwitchState[10] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};

long unsigned currentDebounceTime = 0;
long unsigned lastDebounceTime = 0;

//Switch states for debouncing:
bool keyPressed[10] = {false, false, false, false, false, false, false, false, false, false};

// variables to hold the times for blinking LEDs:
unsigned long timeNow = 0;
unsigned long timePrev = 0;
unsigned int timeWait = 400;

byte activeLed = 0; //Currently active LED.
byte lastLed = 0;   //LED to turn off when another one becomes active.
byte activePreset = 0; //To return to the last preset active before leaving preset mode.

byte presetNumber = 0;

MIDI_CREATE_DEFAULT_INSTANCE(); //Set up MIDI communication.

void setup()
{
  for (int p = 0; p < ledCnt; p++)
  {
    pinMode(led[p], OUTPUT);
  }

  for (int b = 0; b < pressCount; b++)
  {
    pinMode(pressed[b], INPUT);
  }

  tft.begin(); //Initialise TFT;

  tft.setRotation(iliRotation270); //Flip screen upside down because of interfering wires.

  bootSequence();

  MIDI.begin();           //Set up MIDI output.
  //Serial.begin(115200); //For debugging.

  pedalMin = EEPROM.get(ADDR_MIN_VAL, pedalMin);
  delay(100);
  pedalMax = EEPROM.get(ADDR_MAX_VAL, pedalMax);
  delay(100);


  if (analogRead(A15) <= 613) //If it reads under 613 (3.0v) it's on USB power.
  {
    tft.fillRect(1, 223, 35, 16, ILI9341_BLACK);
    tft.setFont(Arial_bold_14);
    tft.setTextColor(ILI9341_CYAN);
    tft.setTextScale(1);
    tft.printAt("USB", 33, 200);
    tft.printAt("POWER", 20, 219);
    usbOn = true;
  }

  else
  {
    tft.drawRoundRect(20, 185, 53, 25, 3, ILI9341_WHITE); //Draw battery
    tft.drawRoundRect(21, 186, 51, 23, 3, ILI9341_WHITE);
    tft.fillRect(73, 193, 4, 8, ILI9341_WHITE);
  }
}

void loop()
{
  currentDebounceTime = millis();
  debounceTime();
  wah();

  float analogSmooth200 = as200.analogReadSmooth(battPin); //Every 200 readings of the analog pin connected to the battery's + terminal, average them.
  battRead = analogSmooth200;

  //Print averaged battery voltage every 30 seconds:
  currentReading = millis();
  readBattery();

  tft.setFont(Arial_bold_14);

  //See which mode is active for bank buttons 7 & 8). Press wah and button 7 to cycle through controller bank change mode (no MIDI), and bank & preset up/down in software (MIDI sent).

  bankMode();

  //What happens when cycling through preset banks (not software banks):

  presetBanks();

  //Determine which bank is active:

  presetBankStatus();

  //Check if pedalboard mode has been activated:

  if (keyPressed[8])
  {
    stompActive();
    keyPressed[8] = false;
  }

  //Check if loop mode has been activated:

  if (keyPressed[9])
  {
    loopActive();
    keyPressed[9] = false;
  }

  midiLedOff();

  if (loopStatus == false)
  {
    lastLed = activeLed;
  }
}

//END OF LOOP().


//CLEAR SPACES:
void clearSmallPresets() //Clear small preset names but leave large one.
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
  tft.fillRect(1, 152, 185, 22, ILI9341_BLACK);
}

void clearMode() //Clear loop/stomp/preset mode on message.
{
  tft.fillRect(194, 154, 120, 20, ILI9341_BLACK);
}

void clearBankMode() //Bank up/down buttons' status space.
{
  tft.fillRect(1, 130, 190, 20, ILI9341_BLACK);
}
