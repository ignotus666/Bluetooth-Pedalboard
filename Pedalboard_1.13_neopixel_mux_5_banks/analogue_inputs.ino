//ANALOG INPUTS CODE (WAH, VOLTAGE METER):

void wah()
{
  tft.setFontMode(gTextFontModeSolid);

  //Hall-effect wah pedal code:
  pedal.update();
  pedalRead = pedal.getValue();                                    //Get the smoothed analog value.
  pedalRead = constrain(pedalRead, pedalMin, pedalMax);
  pedalVal = pedalRead; 
  pedalVal = map(pedalVal, pedalMin+10, pedalMax-5, 0, 127);        //Map to range of 0-127.
  pedalVal = constrain(pedalVal, 0, 127);                           //Prevent pedalVal value from escaping from range permitted by MIDI protocol.
  pedalBar = pedalRead;
  pedalBar = map(pedalBar, pedalMin, pedalMax, 0, 67);
  pedalBar = constrain(pedalBar, 0, 67);

  String sensorVal = String(pedalVal);                             //Print MIDI value.
  String oldSensorVal = String(lastPedalVal);

  //convert the reading to a char array:
  sensorVal.toCharArray(sensorPrintout, 4);
  oldSensorVal.toCharArray(oldSensorPrintout, 4);

  if (pedalVal != lastPedalVal)                                    //If value has changed...
  {
    if (millis() > 6000)                                           //Dirty hack preventing unwanted MIDI data sent right after booting.
    {
      MIDI.sendControlChange(pedalControlNum, pedalVal, 1);        //Send MIDI CC message (control number, controller value, channel).
      if (pedalVal > 126)
      {
        leds[8] = CRGB::Black;
      }
      else
      {
        leds[8] = CRGB((255 - (pedalVal * 2)), 0, (0 + (pedalVal * 2)));
      }
      FastLED.show();
    }

    tft.setFont(Arial_bold_14);
    tft.setTextScale(1);
    tft.setFontMode(gTextFontModeSolid);
    tft.setTextColor(ILI9341_BLACK, ILI9341_BLACK);
    tft.printAt(oldSensorPrintout, 283, 223);                      //Print old sensor value in black to erase it before printing new one.
    tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
    tft.printAt(sensorPrintout, 283, 223);

    unsigned int pedalBarColour = 0;

    if (pedalState == 0)
    {
      pedalBarColour = ILI9341_GREEN;
    }

    else
    {
      pedalBarColour = ILI9341_YELLOW;
    }

    tft.fillRoundRect(240, 216, pedalBar, 3, 1, pedalBarColour);
    tft.fillRoundRect(240 + pedalBar, 216, 67 - pedalBar, 3, 1, ILI9341_BLACK);

  }
  lastPedalVal = pedalVal;                                         //Assign pedalVal value to lastPedalVal at the end of each cycle.


  //Press buttons 1 and 6 to reset battery time counter:
  if (keyPressed[0] == true && keyPressed[5] == true && usbOn == false)
  {
    minuteCounter = 0;
    printUptime();
    keyPressed[0] = false;
    keyPressed[5] = false;
  }
}

void batteryIndicator()
{
  float voltage = ((battRead * (3.3 / 1023.0)) * 3.29);  //Multiply by the ratio due to voltage divider.
  float voltageBar = mapFloat(voltage, 3.0, 4.15, 0, 49);//Map bar to 3.1v - 4.1v.
  voltageBar = constrain(voltageBar, 0, 49);
  float perc = mapFloat(voltage, 3.0, 4.15, 0, 100);
  int voltagePerc = (int) perc;                          //Cast float to int.
  voltagePerc = constrain(voltagePerc, 0, 100);

  unsigned int colour = 0;

  if (voltagePerc != lastVoltagePerc)                    //If voltage percentage has changed, write new value and apply appropriate colour.
  {
    tft.setTextScale(1);
    tft.fillRoundRect(3, 187, 49, 21, 3, ILI9341_BLACK);

    if (voltagePerc >= 60)
    {
      colour = ILI9341_GREEN;
    }

    if (voltagePerc >= 46 && voltagePerc <= 59)
    {
      colour = ILI9341_YELLOW;
    }

    if (voltagePerc >= 26 && voltagePerc <= 45)
    {
      colour = ILI9341_ORANGE;
    }

    if (voltagePerc <= 25 && voltagePerc >= 0)
    {
      colour = ILI9341_RED;
    }

    tft.fillRoundRect(3, 187, voltageBar, 21, 3, (colour));

    String voltageVal = String(voltage);

    voltageVal.toCharArray(voltagePrintout, 5);

    tft.setFont(Arial_bold_14);
    tft.setTextColor(ILI9341_CYAN, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.setFontMode(gTextFontModeSolid);
    tft.fillRect(42, 214, 32, 16, ILI9341_BLACK);
    tft.printAt(voltagePrintout, 42, 214);
    tft.printAt("v", 75, 214);

    String voltageVal2 = String(voltagePerc);

    voltageVal2.toCharArray(volPercPrintout, 4);

    if (colour == ILI9341_YELLOW || colour == ILI9341_ORANGE)
    {
      tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    }

    if (colour == ILI9341_GREEN || colour == ILI9341_RED)
    {
      tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
    }

    tft.setFontMode(gTextFontModeTransparent);
    if (voltagePerc >= 100)
    {
      tft.printAt(volPercPrintout, 9, 191);
      //tft.print(" %");
    }

    if (voltagePerc < 100 && voltagePerc > 9)
    {
      tft.printAt(volPercPrintout, 16, 191);
      //tft.print(" %");
    }

    if (voltagePerc < 10)
    {
      tft.printAt(volPercPrintout, 22, 191);
      //tft.print(" %");
    }
    tft.print(" %");
  }
  lastVoltagePerc = voltagePerc;
}

void readBattery()
{

  if (millis() - lastReading >= 30000 && usbOn == false)
  {
    batteryIndicator();
    lastReading = currentReading;
  }
}

void batteryLife()
{
  if (millis() - countBatteryTime >= 60000)
  {
    minuteCounter++;
    eepromSaveCounter++;
    countBatteryTime = millis();

    if (eepromSaveCounter == 2)            //Save to eeprom every 2 minutes.
    {
      EEPROM.put(timeCount, minuteCounter);
      eepromSaveCounter = 0;
    }

    printUptime();
  }
}

void printUptime()
{
  tft.fillRect(50, 230, 50, 8, ILI9341_BLACK);
  tft.setFont(SystemFont5x7);
  tft.setTextScale(1);
  hoursNum = minuteCounter / 60;
  minutesNum = minuteCounter - (hoursNum * 60);
  String minuteVal = String(minutesNum);
  minuteVal.toCharArray(minutePrintout, 3);
  String hourVal = String(hoursNum);
  hourVal.toCharArray(hourPrintout, 3);
  tft.setTextColor(ILI9341_HOTPINK, ILI9341_BLACK);
  tft.printAt(hourPrintout, 50, 230);
  tft.setTextColor(ILI9341_BLUE, ILI9341_BLACK);
  tft.print("h ");
  tft.setTextColor(ILI9341_HOTPINK, ILI9341_BLACK);
  tft.print(minutePrintout);
  tft.setTextColor(ILI9341_BLUE, ILI9341_BLACK);
  tft.print("m");
}
