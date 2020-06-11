//ANALOG INPUTS CODE (WAH, VOLTAGE METER):

void wah()
{
  tft.setFontMode(gTextFontModeSolid);

  //Hall-effect wah pedal code:
  wahWah.update();
  wahRead = wahWah.getValue();                                 //Get the smoothed analog value.
  wahRead = constrain(wahRead, pedalMin, pedalMax);
  wahVal = wahRead;                                            //Assign A0 value to wahVal.
  wahVal = map(wahVal, pedalMin + 20, pedalMax - 5, 0, 127);  //Map to range of 0-127 for MIDI. Slightly padded max and min values to keep them within range.
  wahVal = constrain(wahVal, 0, 127);                          //Prevent wahVal value from escaping from range permitted by MIDI protocol.

  String sensorVal = String(wahVal);                           //Print MIDI value.
  String oldSensorVal = String(lastWahVal);

  //convert the reading to a char array:
  sensorVal.toCharArray(sensorPrintout, 4);
  oldSensorVal.toCharArray(oldSensorPrintout, 4);

  if (wahVal != lastWahVal)                                    // If value has changed...
  {
    if (millis() > 6000)                                       //Dirty hack preventing unwanted MIDI data sent right after booting.
    {
      MIDI.sendControlChange(0, wahVal, 1);                    // Send MIDI CC message (control number, controller value, channel).
      midiLedOn();
    }

    tft.setFont(Arial_bold_14);
    tft.setTextScale(1);
    tft.setFontMode(gTextFontModeSolid);
    tft.setTextColor(ILI9341_BLACK, ILI9341_BLACK);
    tft.printAt(oldSensorPrintout, 255, 222);                 //Print old sensor value in black to erase it before printing new one.
    tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
    tft.printAt(sensorPrintout, 255, 222);
  }
  lastWahVal = wahVal;                                        //Assign wahVal value to lastWahVal at the end of each cycle.
}

void batteryIndicator()
{
  int battery = battRead;
  voltageBar = battRead;
  voltagePerc = battRead;
  float voltage = battery * (5 / 1023.0);
  voltageBar = map(voltageBar, 640, 838, 0, 49);//Map bar to 3.1v - 4.1v.
  voltageBar = constrain(voltageBar, 0, 49);
  voltagePerc = map(voltagePerc, 640, 838, 0, 100);
  voltagePerc = constrain(voltagePerc, 0, 100);

  unsigned int colour = 0;

  if (voltagePerc != lastVoltagePerc)                  //If voltage percentage has changed, write new value and apply appropriate colour.
  {
    tft.setTextScale(1);
    tft.fillRoundRect(22, 187, 49, 21, 3, ILI9341_BLACK);

    if (voltagePerc >= 75)
    {
      colour = ILI9341_GREEN;
    }

    if (voltagePerc >= 56 && voltagePerc <= 74)
    {
      colour = ILI9341_YELLOW;
    }

    if (voltagePerc >= 31 && voltagePerc <= 55)
    {
      colour = ILI9341_ORANGE;
    }

    if (voltagePerc <= 30)
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

    tft.setFont(SystemFont5x7);
    
    if (colour == ILI9341_YELLOW || colour == ILI9341_ORANGE)
    {
      tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    }
    
    if (colour == ILI9341_GREEN || colour == ILI9341_RED)
    {
      tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
    }
    
    tft.setTextScale(1);
    tft.setFontMode(gTextFontModeTransparent);
    if (voltagePerc >= 100)
    {
      tft.printAt(volPercPrintout, 34, 194);
    }

    if (voltagePerc < 100 && voltagePerc > 9)
    {
      tft.printAt(volPercPrintout, 38, 194);
    }

    if (voltagePerc < 10)
    {
      tft.printAt(volPercPrintout, 41, 194);
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
