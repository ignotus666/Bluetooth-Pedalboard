void loopActive()
{
  loopStatus = !loopStatus;

  for (int l = 0; l < 6; l++)          //Set loopStates to true.
  {
    loopState[l] = true;
  }

  if (loopStatus == true)
  {
    ledFlash();

    digitalWrite(led[7], HIGH);

    for (int l = 0; l < 6; l++)
    {
      ledOn[l] = false;
    }

    clearTopHalf();
    clearMode();

    loopNames();

    tft.setTextColor(ILI9341_BLUE, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("LOOPER MODE", gTextAlignMiddleCenter, 0, -65);

    tft.fillRoundRect(195, 155, 117, 18, 3, ILI9341_RED);
    tft.drawRoundRect(194, 154, 119, 20, 3, ILI9341_WHITE);
    tft.setFontMode(gTextFontModeTransparent);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextScale(1);
    tft.printAt("LOOPER MODE", 200, 158);

    for (int b = 0; b < 5; b++)
    {
      statusBank[b] = false;
    }
    stompStatus = false;
  }

  else
  {
    ledFlash();

    clearTopHalf();
    clearMode();

    return2lastBank();

    if (presetChanged == false) //If bank buttons have been pressed, it's presumed the last active preset is no longer active; if not, it's still active.
    {
      return2ActivePreset();
      digitalWrite(led[lastLed], HIGH);
    }
    bankButtonNames();

    tft.fillRoundRect(195, 155, 115, 18, 3, ILI9341_GREEN);
    tft.drawRoundRect(194, 154, 117, 20, 3, ILI9341_RED);
    tft.setFontMode(gTextFontModeTransparent);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextScale(1);
    tft.printAt("PRESET MODE", 200, 158);

    digitalWrite(led[7], LOW);
  }
}

//LOOP MODE:

void loopMode()
{
  //Footswitch code:
  //Char strings for loop mode:
  const char *loopStringBig[] = {"MULTIPLY", "OVERDUB", "RECORD", "INSERT", "REPLACE", "PAUSE"};
  unsigned int smallLoopColour = 0;
  unsigned int bigLoopColour = 0;

  for (int k = 0; k < 6; k++)
  {
    if (keyPressed[k] == true)                //Check which button has been pressed.
    {
      MIDI.sendControlChange(k + 12, 127, 1); //(Control number, controller value, channel). Send the same message whenever the switch is pressed.
      midiLedOn();
      loopNames();
      loopLed = k;
      loopLeds();
      for (int l = 0; l < 6; l++)
      {
        if (l != (loopLed))                   //Set all ledOn states to false but don't change the state of the current led used (I just use the loopLed number as a handy reference).
        {
          ledOn[l] = false;
        }
      }
      // turn on or turn off the blinking LED
      if ( ledOn[k] == false)
      {
        ledOn[k] = true;
      }
      else
      {
        ledOn[k] = false;

        tft.setTextColor(ILI9341_BLUE, ILI9341_BLACK);
        tft.setTextScale(2);
        tft.printAlignedOffseted("PLAY", gTextAlignMiddleCenter, 0, -65);

        tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
        tft.setTextScale(1);
        tft.printAt("PLAY", 281, 90);
        if (k != 2)                          //LED on/off sequence slightly different for REC/PLAY button.
        {
          digitalWrite(led[2], HIGH);
          ledStatus[k] = LOW;
          digitalWrite(led[k], ledStatus[k]);
        }
        else
        {
          ledStatus[2] = LOW;
          digitalWrite(led[2], HIGH);
        }
      }
      keyPressed[k] = false;
    }

    //See if it is time to blink the LED:
    if ( ledOn[k] == true )
    {
      timeNow = millis();
      if (timeNow - timePrev >= timeWait )
      {
        timePrev = timeNow;
        if (ledStatus[k] == LOW)
        {
          smallLoopColour = ILI9341_RED;
          bigLoopColour = ILI9341_BLUE;
          ledStatus[k] = HIGH;
        }

        else //(ledStatus[k] == HIGH)
        {
          smallLoopColour = ILI9341_WHITE;
          bigLoopColour = ILI9341_RED;
          ledStatus[k] = LOW;
        }
        tft.setTextColor(smallLoopColour, ILI9341_BLACK);
        tft.setTextScale(1);
        switch (k)
        {
          case 0:
            tft.printAt("MULTI", 1, 90);
            break;

          case 1:
            tft.printAt("OVERDUB", 120, 90);
            break;

          case 2:
            tft.printAt("REC", 245, 90);
            break;

          case 3:
            tft.printAligned("INSERT", gTextAlignTopLeft);
            break;

          case 4:
            tft.printAligned("REPLACE", gTextAlignTopCenter);
            break;

          case 5:
            tft.printAligned("PAUSE", gTextAlignTopRight);
            break;
        }

        tft.setTextColor(bigLoopColour, ILI9341_BLACK);
        tft.setTextScale(2);
        tft.printAlignedOffseted(loopStringBig[k], gTextAlignMiddleCenter, 0, -65);

        digitalWrite(led[k], ledStatus[k]);
      }
    }
  }


  //For footswitch 7:
  if (keyPressed[6] == true && loopStatus == true)
  {
    MIDI.sendControlChange(18, 127, 1);
    loopTime = millis();
    midiLedOn();
    digitalWrite(led[lastLed], LOW);

    for (int l = 0; l < 6; l++)
    {
      ledOn[l] = false;
    }

    loopNames();

    clearLargeName();

    tft.setTextColor(ILI9341_BLUE, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("UNDO", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAt("UNDO", 1, 130);
    keyPressed[6] = false;
  }

  //For footswitch 8:
  if (keyPressed[7] == true && loopStatus == true)
  {
    MIDI.sendControlChange(19, 127, 1);
    loopTime = millis();
    midiLedOn();
    digitalWrite(led[lastLed], LOW);

    for (int l = 0; l < 6; l++)
    {
      ledOn[l] = false;
    }

    loopNames();

    clearLargeName();

    tft.setTextColor(ILI9341_BLUE, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("REDO", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAt("REDO", 80, 130);
    keyPressed[7] = false;
  }

  if (millis() - loopTime > 1000 && millis() - loopTime < 1050)
  {
    clearLargeName();
    loopNames();
  }
}
