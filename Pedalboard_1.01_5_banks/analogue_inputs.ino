//ANALOG INPUTS CODE (WAH, VOLTAGE METER):

void wah()
{
  tft.setFontMode(gTextFontModeSolid);

  //Hall-effect wah pedal code:
  pedal.update();
  pedalRead = pedal.getValue();                                    //Get the smoothed analog value.
  pedalRead = constrain(pedalRead, pedalMin, pedalMax);

  //Multimap values to make MIDI and pedalBar output more linear:
  int pedalRange = pedalMax - pedalMin;

  int midi_out[] = {0, 16, 32, 48, 64, 80, 96, 112, 127};

   int bar_out[] = {1, 10, 19, 24, 33, 42, 51, 60, 69};

  //Slightly padded max and min values to keep them within range.
  int hall_in[] = {pedalMin + 20, pedalMin + (pedalRange * 0.30), pedalMin + (pedalRange * 0.50),
                   pedalMin + (pedalRange * 0.65), pedalMin + (pedalRange * 0.75), pedalMin + (pedalRange * 0.83),
                   pedalMin + (pedalRange * 0.89), pedalMin + (pedalRange * 0.94), pedalMax - 7
                  };
  //Non-padded max and min values to stop pedalBar misbehaving.
  int hall_in_2[] = {pedalMin - 5, pedalMin + (pedalRange * 0.30), pedalMin + (pedalRange * 0.50),
                   pedalMin + (pedalRange * 0.65), pedalMin + (pedalRange * 0.75), pedalMin + (pedalRange * 0.83),
                   pedalMin + (pedalRange * 0.89), pedalMin + (pedalRange * 0.94), pedalMax + 5
                  };

  pedalVal = multiMap(pedalRead, hall_in, midi_out, 9);             //Map to range of 0-127 for MIDI. multiMap(val, _in, _out, no. of values).
  pedalVal = constrain(pedalVal, 0, 127);                           //Prevent pedalVal value from escaping from range permitted by MIDI protocol.
  pedalBar = multiMap(pedalRead, hall_in_2, bar_out, 9);
  pedalBar = constrain(pedalBar, 1, 69);

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

// Code to make pedal output more linear. Note: the _in array should have increasing values
int multiMap(int val, int* _in, int* _out, uint8_t size)
{
  // take care the value is within range
  // val = constrain(val, _in[0], _in[size-1]);
  if (val <= _in[0]) return _out[0];
  if (val >= _in[size-1]) return _out[size-1];

  // search right interval
  uint8_t pos = 1;  // _in[0] allready tested
  while(val > _in[pos]) pos++;

  // this will handle all exact "points" in the _in array
  if (val == _in[pos]) return _out[pos];

  // interpolate in the right segment for the rest
  return (val - _in[pos-1]) * (_out[pos] - _out[pos-1]) / (_in[pos] - _in[pos-1]) + _out[pos-1];
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
