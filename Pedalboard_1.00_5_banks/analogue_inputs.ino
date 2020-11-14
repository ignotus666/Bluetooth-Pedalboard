//ANALOG INPUTS CODE (WAH, VOLTAGE METER):

void wah()
{
  tft.setFontMode(gTextFontModeSolid);

  //Hall-effect wah pedal code:
  pedal.update();
  pedalRead = pedal.getValue();                                    //Get the smoothed analog value.
  pedalRead = constrain(pedalRead, pedalMin, pedalMax);
  pedalVal = pedalRead;                                            //Assign A0 value to pedalVal.
  pedalVal = map(pedalVal, pedalMin + 20, pedalMax - 7, 0, 127);   //Map to range of 0-127 for MIDI. Slightly padded max and min values to keep them within range.
  pedalVal = constrain(pedalVal, 0, 127);                          //Prevent pedalVal value from escaping from range permitted by MIDI protocol.
  pedalBar = pedalRead;
  pedalBar = map(pedalBar, pedalMin, pedalMax, 0, 67);
  pedalBar = constrain(pedalBar, 0, 67);

  String sensorVal = String(pedalVal);                             //Print MIDI value.
  String oldSensorVal = String(lastPedalVal);

  //convert the reading to a char array:
  sensorVal.toCharArray(sensorPrintout, 4);
  oldSensorVal.toCharArray(oldSensorPrintout, 4);

  if (pedalVal != lastPedalVal)                                    // If value has changed...
  {
    if (millis() > 6000)                                           //Dirty hack preventing unwanted MIDI data sent right after booting.
    {
      MIDI.sendControlChange(pedalControlNum, pedalVal, 1);        // Send MIDI CC message (control number, controller value, channel).
      midiLedOn();
    }

    tft.setFont(Arial_bold_14);
    tft.setTextScale(1);
    tft.setFontMode(gTextFontModeSolid);
    tft.setTextColor(ILI9341_BLACK, ILI9341_BLACK);
    tft.printAt(oldSensorPrintout, 273, 223);                      //Print old sensor value in black to erase it before printing new one.
    tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
    tft.printAt(sensorPrintout, 273, 223);

    unsigned int pedalBarColour = 0;

    if (pedalState == 0)
    {
      pedalBarColour = ILI9341_GREEN;
    }

    else
    {
      pedalBarColour = ILI9341_YELLOW;
    }

    tft.fillRoundRect(230, 216, pedalBar, 3, 1, pedalBarColour);
    tft.fillRoundRect(230 + pedalBar, 216, 67 - pedalBar, 3, 1, ILI9341_BLACK);

  }
  lastPedalVal = pedalVal;                                         //Assign pedalVal value to lastPedalVal at the end of each cycle.
}

void batteryIndicator()
{
  voltageBar = battRead;
  voltagePerc = battRead;
  float voltage = battRead * (5 / 1023.0);
  voltageBar = map(voltageBar, 640, 838, 0, 49);//Map bar to 3.1v - 4.1v.
  voltageBar = constrain(voltageBar, 0, 49);
  voltagePerc = map(voltagePerc, 640, 838, 0, 100);
  voltagePerc = constrain(voltagePerc, 0, 100);

  unsigned int colour = 0;

  if (voltagePerc != lastVoltagePerc)           //If voltage percentage has changed, write new value and apply appropriate colour.
  {
    tft.setTextScale(1);
    tft.fillRoundRect(22, 187, 49, 21, 3, ILI9341_BLACK);

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

    tft.fillRoundRect(22, 187, 0 + (voltageBar), 21, 3, (colour));

    String voltageVal = String(voltage);

    voltageVal.toCharArray(voltagePrintout, 5);

    tft.setFont(Arial_bold_14);
    tft.setTextColor(ILI9341_CYAN, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.setFontMode(gTextFontModeSolid);
    tft.fillRect(42, 223, 32, 16, ILI9341_BLACK);
    tft.printAt(voltagePrintout, 42, 223);
    tft.printAt("v", 75, 223);

    String voltageVal2 = String(voltagePerc);

    voltageVal2.toCharArray(volPercPrintout, 4);

    //tft.setFont(SystemFont5x7);

    if (colour == ILI9341_YELLOW || colour == ILI9341_ORANGE)
    {
      tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    }

    if (colour == ILI9341_GREEN || colour == ILI9341_RED)
    {
      tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
    }

    //tft.setTextScale(1);
    tft.setFontMode(gTextFontModeTransparent);
    if (voltagePerc >= 100)
    {
      tft.printAt(volPercPrintout, 28, 191);
    }

    if (voltagePerc < 100 && voltagePerc > 9)
    {
      tft.printAt(volPercPrintout, 35, 191);
    }

    if (voltagePerc < 10)
    {
      tft.printAt(volPercPrintout, 41, 191);
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
