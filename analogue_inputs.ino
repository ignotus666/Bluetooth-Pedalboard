//ANALOG INPUTS CODE (WAH, VOLTAGE METER):

void wah()
{
  tft.setFontMode(gTextFontModeSolid);

  //Hall-effect wah pedal code:
  wahWah.update();
  wahRead = wahWah.getValue();
  wahVal = wahRead;                  //Assign A0 value to wahVal.
  wahBar = wahRead;
  wahPerc = wahRead;

  wahVal = map(wahVal, 303, 470, 0, 127);   //Map the range of the hall sensor to a range of 0-127 for MIDI.
  wahBar = map(wahBar, 303, 470, 0, 78);    //Map sensor range to 0-78 for arc.
  wahPerc = map(wahPerc, 303, 470, 0, 100); //Map sensor range to 0-100 for percentage.

  wahVal = constrain(wahVal, 0, 127);       //Prevent wahVal value from escaping from range permitted by MIDI protocol.
  wahBar = constrain(wahBar, 0, 78);
  wahPerc = constrain(wahPerc, 0, 100);

  String sensorVal = String(wahPerc);//Read value of A0.

  //convert the reading to a char array
  sensorVal.toCharArray(sensorPrintout, 4);

  if (wahVal != lastwahVal)                // If value has changed...
  {
    if (millis() > 6000) //Dirty hack that prevents analog inputs from sending unwanted MIDI data right after booting.
    {
      MIDI.sendControlChange(1, wahVal, 1);   // Send MIDI CC message (control number, controller value, channel).
      midiLed();
    }

    tft.fillArc(295, 200, 20, 8, 0 + (wahBar), 78, (100, 100, 100));

    tft.fillArc(295, 200, 20, 8, 0, (wahBar), ILI9341_RED);

    tft.fillCircle(295, 200, 10, ILI9341_BLACK);//Erase previous percentage value in centre of arc.

    tft.setFont(SystemFont5x7);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextScale(1);

    //Centre the values within the arc:
    if (wahPerc == 100)
    {
      tft.printAt(sensorPrintout, 286, 197);
    }

    if (wahPerc < 100 && wahPerc > 9)
    {
      tft.printAt(sensorPrintout, 290, 197);
    }

    if (wahPerc < 10)
    {
      tft.printAt(sensorPrintout, 293, 197);
    }
  }

  lastwahVal = wahVal; //Assign wahVal value to lastwahVal at the end of each cycle.
}

void batteryIndicator()
{
  int battery = battRead;
  voltageBar = battRead;
  voltagePerc = battRead;
  float voltage = battery * (5 / 1023.0);
  voltageBar = map(voltageBar, 640, 838, 0, 78);//Map bar to 3.1v - 4.1v.
  voltageBar = constrain(voltageBar, 0, 78);
  voltagePerc = map(voltagePerc, 640, 838, 0, 100);
  voltagePerc = constrain(voltagePerc, 0, 100);

  tft.fillArc(25, 200, 20, 8, 0 + (voltageBar), 78, (100, 100, 100));

  if (voltage >= 3.85)
  {
    tft.fillArc(25, 200, 20, 8, 0, (voltageBar), ILI9341_GREEN);
  }

  if (voltage >= 3.50 && voltage <= 3.84)
  {
    tft.fillArc(25, 200, 20, 8, 0, (voltageBar), ILI9341_YELLOW);
  }

  if (voltage >= 3.35 && voltage <= 3.49)
  {
    tft.fillArc(25, 200, 20, 8, 0, (voltageBar), ILI9341_ORANGE);
  }

  if (voltage <= 3.34)
  {
    tft.fillArc(25, 200, 20, 8, 0, (voltageBar), ILI9341_RED);
  }

  String voltageVal = String(voltage);

  //convert the reading to a char array
  voltageVal.toCharArray(voltagePrintout, 5);

  tft.setFont(Arial_bold_14);
  tft.setTextColor(ILI9341_CYAN);
  tft.setTextScale(1);
  tft.fillRect(55, 223, 35, 16, ILI9341_BLACK);
  tft.printAt(voltagePrintout, 52, 223);
  tft.printAt("v", 85, 223);

  String voltageVal2 = String(voltagePerc);

  voltageVal2.toCharArray(volPercPrintout, 4);

  tft.fillCircle(25, 200, 10, ILI9341_BLACK);
  tft.setFont(SystemFont5x7);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextScale(1);
  if (voltagePerc == 100)
  {
    tft.printAt(volPercPrintout, 16, 197);
  }

  if (voltagePerc < 100 && voltagePerc > 9)
  {
    tft.printAt(volPercPrintout, 20, 197);
  }

  if (voltagePerc < 10)
  {
    tft.printAt(volPercPrintout, 23, 197);
  }

  if (voltage < 3.34)
  {
    digitalWrite(31, HIGH);//Low battery indicator LED.
  }
  if (voltage > 3.34)
  {
    digitalWrite(31, LOW);
  }
}
