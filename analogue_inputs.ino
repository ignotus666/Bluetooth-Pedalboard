//ANALOG INPUTS CODE (WAH, VOLTAGE METER):

void wah()
{
  tft.setFontMode(gTextFontModeSolid);

  //Hall-effect wah pedal code:
  wahWah.update();
  wahRead = wahWah.getValue();
  wahVal = wahRead;                         //Assign A0 value to wahVal.
  wahVal = map(wahVal, 310, 470, 0, 127);   //Map the range of the hall sensor to a range of 0-127 for MIDI.
  wahVal = constrain(wahVal, 0, 127);       //Prevent wahVal value from escaping from range permitted by MIDI protocol.

  String sensorVal = String(wahVal);        //Print MIDI value.
  String oldSensorVal = String(lastwahVal); 

  //convert the reading to a char array
  sensorVal.toCharArray(sensorPrintout, 4);
  oldSensorVal.toCharArray(oldSensorPrintout, 4);

  if (wahVal != lastwahVal)                   // If value has changed...
  {
    if (millis() > 6000)                      //Dirty hack that prevents analog inputs from sending unwanted MIDI data right after booting.
    {
      MIDI.sendControlChange(1, wahVal, 1);   // Send MIDI CC message (control number, controller value, channel).
      midiLed();
    }

    tft.setFont(Arial_bold_14);
    tft.setTextScale(1);
    tft.setFontMode(gTextFontModeSolid);
    //tft.printAt("    ", 255, 222);
    tft.setTextColor(ILI9341_BLACK, ILI9341_BLACK);
    tft.printAt(oldSensorPrintout, 255, 222);
    tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
    tft.printAt(sensorPrintout, 255, 222);
  }
  lastwahVal = wahVal;                        //Assign wahVal value to lastwahVal at the end of each cycle.
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

  unsigned int color = 0;

  if (voltagePerc != lastVoltagePerc)
  {
    tft.setTextScale(1);
    tft.fillRoundRect(22, 187, 49, 21, 3, ILI9341_BLACK);

    if (voltage >= 3.85)
    {
      color = ILI9341_GREEN;
    }

    if (voltage >= 3.50 && voltage <= 3.84)
    {
      color = ILI9341_YELLOW;
    }

    if (voltage >= 3.35 && voltage <= 3.49)
    {
      color = ILI9341_ORANGE;
    }

    if (voltage <= 3.34)
    {
      color = ILI9341_RED;
    }

    tft.fillRoundRect(22, 187, 0 + (voltageBar), 21, 3, (color));

    String voltageVal = String(voltage);

    //convert the reading to a char array
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
    tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
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

    if (voltage < 3.34)
    {
      digitalWrite(31, HIGH);//Low battery indicator LED.
    }
    if (voltage > 3.34)
    {
      digitalWrite(31, LOW);
    }
  }
  lastVoltagePerc = voltagePerc;
}
