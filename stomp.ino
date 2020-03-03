//STOMP ACTIVE/INACTIVE:

void stompActive()
{
  stompStatus = !stompStatus;

  presetNumber = 0; //Reset preset number to 0.

  stomp1State = true;
  stomp2State = true;
  stomp3State = true;
  stomp4State = true;
  stomp5State = true;
  stomp6State = true;

  if (stompStatus == true)
  {
    for ( int x = 0; x < 2; x++ )
    {
      ledFlashOn();
      ledFlashOff();
    }

    digitalWrite(led[6], HIGH);

    clearMode();

    clearTopHalf();//Clear all the way down to 'BANK X'.

    tft.fillRoundRect(195, 155, 110, 18, 3, ILI9341_BLUE);
    tft.drawRoundRect(194, 154, 112, 20, 3, ILI9341_WHITE);
    tft.setFontMode(gTextFontModeTransparent);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextScale(1);
    tft.printAt("STOMP MODE", 200, 158);

    //Draw pedals:
    tft.drawImage(pedal1, 4, 80, pedal1Width, pedal1Height);
    tft.drawImage(pedal2, 143, 80, pedal2Width, pedal2Height);
    tft.drawImage(pedal3, 279, 80, pedal3Width, pedal3Height);
    tft.drawImage(pedal4, 4, 3, pedal4Width, pedal4Height);
    tft.drawImage(pedal5, 143, 3, pedal5Width, pedal5Height);
    tft.drawImage(pedal6, 279, 3, pedal6Width, pedal6Height);

    //Print numbers in each pedal:
    tft.setFontMode(gTextFontModeTransparent);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextScale(1);
    tft.printAt("1", 20, 128);

    tft.setTextColor(ILI9341_WHITE);
    tft.setTextScale(1);
    tft.printAt("2", 158, 128);

    tft.setTextColor(ILI9341_WHITE);
    tft.setTextScale(1);
    tft.printAt("3", 295, 128);

    tft.setTextColor(ILI9341_WHITE);
    tft.setTextScale(1);
    tft.printAt("4", 20, 52);

    tft.setTextColor(ILI9341_WHITE);
    tft.setTextScale(1);
    tft.printAt("5", 158, 52);

    tft.setTextColor(ILI9341_WHITE);
    tft.setTextScale(1);
    tft.printAt("6", 295, 52);

    bank1Status = false;
    bank2Status = false;
    bank3Status = false;
    bank4Status = false;
    bank5Status = false;
    loopStatus = false;
  }

  else
  {
    for ( int x = 0; x < 2; x++ )
    {
      ledFlashOn();
      ledFlashOff();
    }

    loopStatus = false;

    clearTopHalf();
    clearMode();

    return2lastBank();
    return2ActivePreset();
    bankButtonNames();

    tft.fillRoundRect(195, 155, 115, 18, 3, ILI9341_GREEN);
    tft.drawRoundRect(194, 154, 117, 20, 3, ILI9341_RED);
    tft.setFontMode(gTextFontModeTransparent);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextScale(1);
    tft.printAt("PRESET MODE", 200, 158);

    digitalWrite(lastLed, HIGH);

    digitalWrite(led[6], LOW);
  }
}

//STOMP MODE:

void stompMode()
{
  tft.setFontMode(gTextFontModeTransparent);
  //Footswitch code:

  //For footswitch 1:
  if (key1Pressed)
  {
    stomp1State = !stomp1State;

    if (stomp1State == true)
    {
      MIDI.sendControlChange(2, 0, 1);
      midiLed();

      digitalWrite(led[0], LOW);

      //Erase red outline:
      tft.drawRoundRect(3, 79, 40, 72, 5, ILI9341_BLACK);
      tft.drawRoundRect(2, 78, 42, 74, 5, ILI9341_BLACK);

      //Revert number to white:
      tft.setTextColor(ILI9341_WHITE);
      tft.setTextScale(1);
      tft.printAt("1", 20, 128);
    }

    if (stomp1State == false)
    {
      MIDI.sendControlChange(2, 127, 1);
      midiLed();

      digitalWrite(led[0], HIGH);

      //Outline pedals in red:
      tft.drawRoundRect(3, 79, 40, 72, 5, ILI9341_RED);
      tft.drawRoundRect(2, 78, 42, 74, 5, ILI9341_RED);

      //Turn number in pedal red:
      tft.setTextColor(ILI9341_RED);
      tft.setTextScale(1);
      tft.printAt("1", 20, 128);
    }
    key1Pressed = false;
  }

  //For footswitch 2:
  if (key2Pressed)
  {
    stomp2State = !stomp2State;

    if (stomp2State == true)
    {
      MIDI.sendControlChange(3, 0, 1);
      midiLed();

      digitalWrite(led[1], LOW);

      tft.drawRoundRect(142, 79, 40, 72, 5, ILI9341_BLACK);
      tft.drawRoundRect(141, 78, 42, 74, 5, ILI9341_BLACK);

      tft.setTextColor(ILI9341_WHITE);
      tft.setTextScale(1);
      tft.printAt("2", 158, 128);
    }

    if (stomp2State == false)
    {
      MIDI.sendControlChange(3, 127, 1);
      midiLed();

      digitalWrite(led[1], HIGH);

      tft.drawRoundRect(142, 79, 40, 72, 5, ILI9341_RED);
      tft.drawRoundRect(141, 78, 42, 74, 5, ILI9341_RED);

      tft.setTextColor(ILI9341_RED);
      tft.setTextScale(1);
      tft.printAt("2", 158, 128);
    }
    key2Pressed = false;
  }

  //For footswitch 3:
  if (key3Pressed)
  {
    stomp3State = !stomp3State;

    if (stomp3State == true)
    {
      MIDI.sendControlChange(4, 0, 1);
      midiLed();

      digitalWrite(led[2], LOW);

      tft.drawRoundRect(278, 79, 40, 72, 5, ILI9341_BLACK);
      tft.drawRoundRect(277, 78, 42, 74, 5, ILI9341_BLACK);

      tft.setTextColor(ILI9341_WHITE);
      tft.setTextScale(1);
      tft.printAt("3", 295, 128);
    }

    if (stomp3State == false)
    {
      MIDI.sendControlChange(4, 127, 1);
      midiLed();

      digitalWrite(led[2], HIGH);

      tft.drawRoundRect(278, 79, 40, 72, 5, ILI9341_RED);
      tft.drawRoundRect(277, 78, 42, 74, 5, ILI9341_RED);

      tft.setTextColor(ILI9341_RED);
      tft.setTextScale(1);
      tft.printAt("3", 295, 128);
    }
    key3Pressed = false;
  }

  //For footswitch 4:
  if (key4Pressed)
  {
    stomp4State = !stomp4State;

    if (stomp4State == true)
    {
      MIDI.sendControlChange(5, 0, 1);
      midiLed();

      digitalWrite(led[3], LOW);

      tft.drawRoundRect(3, 2, 40, 72, 5, ILI9341_BLACK);
      tft.drawRoundRect(2, 1, 42, 74, 5, ILI9341_BLACK);

      tft.setTextColor(ILI9341_WHITE);
      tft.setTextScale(1);
      tft.printAt("4", 20, 52);
    }

    if (stomp4State == false)
    {
      MIDI.sendControlChange(5, 127, 1);
      midiLed();

      digitalWrite(led[3], HIGH);

      tft.drawRoundRect(3, 2, 40, 72, 5, ILI9341_RED);
      tft.drawRoundRect(2, 1, 42, 74, 5, ILI9341_RED);

      tft.setTextColor(ILI9341_RED);
      tft.setTextScale(1);
      tft.printAt("4", 20, 52);
    }
    key4Pressed = false;
  }

  //For footswitch 5:
  if (key5Pressed)
  {
    stomp5State = !stomp5State;

    if (stomp5State == true)
    {
      MIDI.sendControlChange(6, 0, 1);
      midiLed();

      digitalWrite(led[4], LOW);

      tft.drawRoundRect(142, 2, 40, 72, 5, ILI9341_BLACK);
      tft.drawRoundRect(141, 1, 42, 74, 5, ILI9341_BLACK);

      tft.setTextColor(ILI9341_WHITE);
      tft.setTextScale(1);
      tft.printAt("5", 158, 52);
    }

    if (stomp5State == false)
    {
      MIDI.sendControlChange(6, 127, 1);
      midiLed();

      digitalWrite(led[4], HIGH);

      tft.drawRoundRect(142, 2, 40, 72, 5, ILI9341_RED);
      tft.drawRoundRect(141, 1, 42, 74, 5, ILI9341_RED);

      tft.setTextColor(ILI9341_RED);
      tft.setTextScale(1);
      tft.printAt("5", 158, 52);
    }
    key5Pressed = false;
  }

  //For footswitch 6:
  if (key6Pressed)
  {
    stomp6State = !stomp6State;

    if (stomp6State == true)
    {
      MIDI.sendControlChange(7, 0, 1);
      midiLed();

      digitalWrite(led[5], LOW);

      tft.drawRoundRect(278, 2, 40, 72, 5, ILI9341_BLACK);
      tft.drawRoundRect(277, 1, 42, 74, 5, ILI9341_BLACK);

      tft.setTextColor(ILI9341_WHITE);
      tft.setTextScale(1);
      tft.printAt("6", 295, 52);
    }

    if (stomp6State == false)
    {
      MIDI.sendControlChange(7, 127, 1);
      midiLed();

      digitalWrite(led[5], HIGH);

      tft.drawRoundRect(278, 2, 40, 72, 5, ILI9341_RED);
      tft.drawRoundRect(277, 1, 42, 74, 5, ILI9341_RED);

      tft.setTextColor(ILI9341_RED);
      tft.setTextScale(1);
      tft.printAt("6", 295, 52);
    }
    key6Pressed = false;
  }

  //Switches 7 & 8 control volume when stomp mode is active:

  //For footswitch 7 (volume down):
  if (bankDown && stompStatus == true)
  {
    lastVolVal = volVal - 4; //Change by increments of 4.

    if (lastVolVal <= 0)
    {
      lastVolVal = 0;
    }

    MIDI.sendControlChange(0, lastVolVal, 1);
    midiLed();

    volBar = lastVolVal;
    volBar = map(volBar, 0, 127, 0, 78);
    volBar = constrain(volBar, 0, 78);
    volPerc = lastVolVal;
    volPerc = map(volPerc, 0, 127, 0, 100);
    volPerc = constrain(volPerc, 0, 100);

    String sensorVal7 = String(volPerc);

    // convert the reading to a char array
    sensorVal7.toCharArray(sensorPrintout, 4);

    tft.fillArc(155, 200, 20, 8, 0 + (volBar), 78, ILI9341_BLACK);

    tft.fillArc(155, 200, 20, 8, 0, (volBar), ILI9341_RED);

    tft.fillCircle(155, 200, 10, ILI9341_BLACK);

    tft.setFont(SystemFont5x7);
    tft.setFontMode(gTextFontModeSolid);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextScale(1);

    if (volPerc == 100)
    {
      tft.printAt(sensorPrintout, 146, 197);
    }

    if (volPerc < 100 && volPerc > 9)
    {
      tft.printAt(sensorPrintout, 150, 197);
    }

    if (volPerc < 10)
    {
      tft.printAt(sensorPrintout, 153, 197);
    }

    volVal = lastVolVal;

    delay(60); //Delay for increments while holding switch down.
  }

  //For footswitch 8 (volume up):
  if (bankUp && stompStatus == true)
  {
    lastVolVal = volVal + 4;

    if (lastVolVal >= 127)
    {
      lastVolVal = 127;
    }

    MIDI.sendControlChange(0, lastVolVal, 1);
    midiLed();

    volBar = lastVolVal;
    volBar = map(volBar, 0, 127, 0, 78);
    volBar = constrain(volBar, 0, 78);
    volPerc = lastVolVal;
    volPerc = map(volPerc, 0, 127, 0, 100);
    volPerc = constrain(volPerc, 0, 100);

    String sensorVal7 = String(volPerc);

    // convert the reading to a char array
    sensorVal7.toCharArray(sensorPrintout, 4);

    tft.fillArc(155, 200, 20, 8, 0 + (volBar), 78, ILI9341_BLACK);

    tft.fillArc(155, 200, 20, 8, 0, (volBar), ILI9341_RED);

    tft.fillCircle(155, 200, 10, ILI9341_BLACK);

    tft.setFont(SystemFont5x7);
    tft.setFontMode(gTextFontModeSolid);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextScale(1);

    if (volPerc == 100)
    {
      tft.printAt(sensorPrintout, 146, 197);
    }

    if (volPerc < 100 && volPerc > 9)
    {
      tft.printAt(sensorPrintout, 150, 197);
    }

    if (volPerc < 10)
    {
      tft.printAt(sensorPrintout, 153, 197);
    }

    volVal = lastVolVal;

    delay(60);
  }
}
