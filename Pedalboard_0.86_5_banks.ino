
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
#include <Wah.h>
#include <pedals.h>
#include <logo.h>
#include <guitar.h>
#include <ILI9341_due_config.h>
#include <SystemFont5x7.h>
#include <ILI9341_due.h>
#include <fonts/Arial_bold_14.h>
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

//LED pin assignment:
const byte led[8] = {24, 25, 22, 23, 20, 21, 18, 19};
const byte ledCnt = 8;

//Button definitions and pins:
#define pressed1 digitalRead(5)
#define pressed2 digitalRead(4)
#define pressed3 digitalRead(7)
#define pressed4 digitalRead(6)
#define pressed5 digitalRead(9)
#define pressed6 digitalRead(8)
#define bankDown digitalRead(36)
#define bankUp digitalRead(37)
#define stompOn digitalRead(11)
#define loopOn digitalRead(10)

//Wah variables:
const int wahPin = A0;
ResponsiveAnalogRead wahWah(wahPin, true, 0.01);
int wahVal = 0;
int lastwahVal = 0;   //Initial wah values. One for the first value and another to test if there's been a change.
int wahRead = 0;

//Digital volume:

int volVal = 64;
int lastVolVal = 0;
int volBar = 0;
int volPerc = 0;

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
bool bank1Status = true;
bool bank2Status = false;
bool bank3Status = false;
bool bank4Status = false;
bool bank5Status = false;

byte bankNumber = 1;
byte oldBankNumber = 0;

byte bankButtonState = 1;
byte lastBankButton = 1;

byte lastBank = 1; //Variable to enable returning to last bank active before leaving preset mode.

//Pedalboard mode variable:
bool stompStatus = false;

//Variables to toggle stomp buttons:
bool stomp1State = true;
bool stomp2State = true;
bool stomp3State = true;
bool stomp4State = true;
bool stomp5State = true;
bool stomp6State = true;

long unsigned stompTime = 0;

//Variable to toggle loop mode:
bool loopStatus = false;

long unsigned loopTime = 0;

//Variables to toggle loop buttons:
bool loop1State = true;
bool loop2State = true;
bool loop3State = true;
bool loop4State = true;
bool loop5State = true;
bool loop6State = true;

// variables to hold the new and old switch states for debouncing:
bool oldSwitch1State = LOW;
bool newSwitch1State1 = LOW;
bool newSwitch1State2 = LOW;
bool newSwitch1State3 = LOW;

bool oldSwitch2State = LOW;
bool newSwitch2State1 = LOW;
bool newSwitch2State2 = LOW;
bool newSwitch2State3 = LOW;

bool oldSwitch3State = LOW;
bool newSwitch3State1 = LOW;
bool newSwitch3State2 = LOW;
bool newSwitch3State3 = LOW;

bool oldSwitch4State = LOW;
bool newSwitch4State1 = LOW;
bool newSwitch4State2 = LOW;
bool newSwitch4State3 = LOW;

bool oldSwitch5State = LOW;
bool newSwitch5State1 = LOW;
bool newSwitch5State2 = LOW;
bool newSwitch5State3 = LOW;

bool oldSwitch6State = LOW;
bool newSwitch6State1 = LOW;
bool newSwitch6State2 = LOW;
bool newSwitch6State3 = LOW;

bool oldSwitch7State = LOW;
bool newSwitch7State1 = LOW;
bool newSwitch7State2 = LOW;
bool newSwitch7State3 = LOW;

bool oldSwitch8State = LOW;
bool newSwitch8State1 = LOW;
bool newSwitch8State2 = LOW;
bool newSwitch8State3 = LOW;

bool oldSwitch9State = LOW;
bool newSwitch9State1 = LOW;
bool newSwitch9State2 = LOW;
bool newSwitch9State3 = LOW;

bool oldSwitch10State = LOW;
bool newSwitch10State1 = LOW;
bool newSwitch10State2 = LOW;
bool newSwitch10State3 = LOW;

//Switch states for debouncing:
bool key1Pressed = false;
bool key2Pressed = false;
bool key3Pressed = false;
bool key4Pressed = false;
bool key5Pressed = false;
bool key6Pressed = false;
bool key7Pressed = false;
bool key8Pressed = false;
bool key9Pressed = false;
bool key10Pressed = false;

// variables to hold the times for blinking LEDs:
unsigned long timeNow = 0;
unsigned long timePrev = 0;
unsigned int timeWait = 400;

// variables used to control blinking LEDs:
bool led1On = false;
bool led1Status = LOW;

bool led2On = false;
bool led2Status = LOW;

bool led3On = false;
bool led3Status = LOW;

bool led4On = false;
bool led4Status = LOW;

bool led5On = false;
bool led5Status = LOW;

bool led6On = false;
bool led6Status = LOW;

byte lastLed = 0; //To return to the last LED active before leaving preset mode.
byte activePreset = 0; //To return to the last preset active before leaving preset mode.

byte presetNumber = 0;

MIDI_CREATE_DEFAULT_INSTANCE(); //Set up MIDI communication.

void setup()
{
  for(int p=0; p<ledCnt; p++)
   {
       pinMode(led[p], OUTPUT);
   }

  tft.begin(); //Initialise TFT;

  tft.setRotation(iliRotation270); //Flip screen upside down because of interfering wires.

  bootSequence();

  MIDI.begin(); // set up MIDI output.


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
  debounceStates();
  wah();

  float analogSmooth200 = as200.analogReadSmooth(battPin);
  battRead = analogSmooth200;

  //Print averaged battery voltage every 30 seconds:
  currentReading = millis();
  if (millis() - lastReading >= 30000 && usbOn == false)
  {
    batteryIndicator();
    lastReading = currentReading;
  }

  tft.setFont(Arial_bold_14);

  //See which mode is active for bank buttons:

  if (key7Pressed == HIGH && loopStatus == false && stompStatus == false && wahVal < 100)
  {
    bankButtonState++;

    if (bankButtonState > 3)
    {
      bankButtonState = 1;
    }

    ledFlashOn();
    ledFlashOff();
    clearBankMode();

    if (bankButtonState == 1)
    {
      lastBankButton = 1;
    }

    if (bankButtonState == 2)
    {
      tft.setTextColor(ILI9341_YELLOWGREEN, ILI9341_BLACK);
      tft.setTextScale(1);
      tft.printAt("<<BANK", 1, 130);

      tft.setTextColor(ILI9341_YELLOWGREEN, ILI9341_BLACK);
      tft.setTextScale(1);
      tft.printAt("BANK>>", 90, 130);

      lastBankButton = 2;
    }

    if (bankButtonState == 3)
    {
      tft.setTextColor(ILI9341_YELLOWGREEN, ILI9341_BLACK);
      tft.setTextScale(1);
      tft.printAt("<<PRES", 1, 130);

      tft.setTextColor(ILI9341_YELLOWGREEN, ILI9341_BLACK);
      tft.setTextScale(1);
      tft.printAt("PRES>>", 90, 130);

      lastBankButton = 3;
    }
    key7Pressed = false;
  }

  if (bankButtonState == 1)
  {
    pedalboardBank();
  }

  if (bankButtonState == 2)
  {
    softwareBank();
  }

  if (bankButtonState == 3)
  {
    nextPreset();
  }

  // BANK 1:

  if (bankNumber != oldBankNumber && bankNumber == 1)
  {
    bank1Status = true;

    clearSmallPresets();

    bank1Presets();

    bank2Status = false; //Only adjacent bank numbers need to be changed to 'false'
    bank5Status = false;
    stompStatus = false;
    loopStatus = false;

    for ( int x = 0; x < 2; x++ )       //Loop 2 times.
    {
      ledFlashOn();
      ledFlashOff();
    }

    clearBankSpace();

    tft.setTextColor(ILI9341_HOTPINK);
    tft.setTextScale(2);
    tft.printAt("BANK 1", 1, 152);

    tft.setTextColor(ILI9341_WHITE);
    tft.setTextScale(1);
    tft.printAt("(1-6)", 125, 160);
    lastBank = 1;
  }

  // BANK 2:

  if (bankNumber != oldBankNumber && bankNumber == 2)
  {
    bank2Status = true;

    clearSmallPresets();

    bank2Presets();

    bank1Status = false;
    bank3Status = false;
    stompStatus = false;
    loopStatus = false;

    for ( int x = 0; x < 2; x++ )
    {
      ledFlashOn();
      ledFlashOff();
    }

    clearBankSpace();

    tft.setTextColor(ILI9341_HOTPINK);
    tft.setTextScale(2);
    tft.printAt("BANK 2", 1, 152);

    tft.setTextColor(ILI9341_WHITE);
    tft.setTextScale(1);
    tft.printAt("(7-12)", 125, 160);
    lastBank = 2;
  }

  // BANK 3:

  if (bankNumber != oldBankNumber && bankNumber == 3)
  {
    bank3Status = true;

    clearSmallPresets();

    bank3Presets();

    bank2Status = false;
    bank4Status = false;
    stompStatus = false;
    loopStatus = false;

    for ( int x = 0; x < 2; x++ )
    {
      ledFlashOn();
      ledFlashOff();
    }

    clearBankSpace();

    tft.setTextColor(ILI9341_HOTPINK);
    tft.setTextScale(2);
    tft.printAt("BANK 3", 1, 152);

    tft.setTextColor(ILI9341_WHITE);
    tft.setTextScale(1);
    tft.printAt("(13-18)", 125, 160);
    lastBank = 3;
  }

  // BANK 4:

  if (bankNumber != oldBankNumber && bankNumber == 4)
  {
    bank4Status = true;

    clearSmallPresets();

    bank4Presets();

    bank3Status = false;
    bank5Status = false;
    stompStatus = false;
    loopStatus = false;

    for ( int x = 0; x < 2; x++ )
    {
      ledFlashOn();
      ledFlashOff();
    }

    clearBankSpace();

    tft.setTextColor(ILI9341_HOTPINK);
    tft.setTextScale(2);
    tft.printAt("BANK 4", 1, 152);

    tft.setTextColor(ILI9341_WHITE);
    tft.setTextScale(1);
    tft.printAt("(19-24)", 125, 160);
    lastBank = 4;
  }

  // BANK 5:

  if (bankNumber != oldBankNumber && bankNumber == 5)
  {
    bank5Status = true;

    clearSmallPresets();

    bank5Presets();

    bank4Status = false;
    bank1Status = false;
    stompStatus = false;
    loopStatus = false;

    for ( int x = 0; x < 2; x++ )
    {
      ledFlashOn();
      ledFlashOff();
    }

    clearBankSpace();

    tft.setTextColor(ILI9341_HOTPINK);
    tft.setTextScale(2);
    tft.printAt("BANK 5", 1, 152);

    tft.setTextColor(ILI9341_WHITE);
    tft.setTextScale(1);
    tft.printAt("(25-30)", 125, 160);
    lastBank = 5;
  }
  oldBankNumber = bankNumber;

  //Determine which bank is active:

  if (bank1Status == true)
  {
    bank1();
  }

  if (bank2Status == true)
  {
    bank2();
  }

  if (bank3Status == true)
  {
    bank3();
  }

  if (bank4Status == true)
  {
    bank4();
  }

  if (bank5Status == true)
  {
    bank5();
  }

  if (stompStatus == true)
  {
    stompMode();
  }

  if (loopStatus == true)
  {
    loopMode();
  }

  //Check if pedalboard mode has been activated:

  if (key9Pressed)
  {
    stompActive();
    key9Pressed = false;
  }

  //Check if loop mode has been activated:

  if (key10Pressed)
  {
    loopActive();
    key10Pressed = false;
  }

  if (millis() - stompTime > 600 && millis() - stompTime < 700)
  {
    clearLargeName();
    bankButtonNames();
  }
}

//MIDI ACTIVITY LEDS:
void midiLed()
{
  if (stompStatus == LOW)
  {
    digitalWrite(led[6], HIGH);
    delay(5);
    digitalWrite(led[6], LOW);
  }

  if (stompStatus == HIGH)
  {
    digitalWrite(led[7], HIGH);
    delay(5);
    digitalWrite(led[7], LOW);
  }
}

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
