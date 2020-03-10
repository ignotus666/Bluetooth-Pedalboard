void loopActive()
{
  loopStatus = !loopStatus;

  loopTime = millis();                 //Start counting, to clear some messages off the screen after a couple of seconds.

  for (int l = 0; l < 6; l++)          //Set loopStates to true.
  {
    loopState[l] = true;
  }

  if (loopStatus == true)
  {
    for ( int x = 0; x < 2; x++ )
    {
      ledFlashOn();
      ledFlashOff();
    }

    digitalWrite(led[7], HIGH);

    for (int l = 0; l < 6; l++)
    {
      ledOn[l] = false;
    }

    clearTopHalf();
    clearMode();

    loopNames();

    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
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
    for ( int x = 0; x < 2; x++ )
    {
      ledFlashOn();
      ledFlashOff();
    }

    clearTopHalf();
    clearMode();

    return2lastBank();

    if (bankButtonState == 1 || presetChanged == 0) //If next/prev preset or next/prev bank have been pressed, it's presumed the last active preset is no longer active; if not, it's still active.
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

  //Footswitch 1:
  if (keyPressed[0] == true)
  {
    MIDI.sendControlChange(12, 127, 1);     //(control number, controller value, channel). Send the same message whenever the switch is pressed.
    midiLed();
    loopNames();
    loopLed = 0;
    loopLeds();
    for (int l = 0; l < 6; l++)
    {
      if (l != (loopLed))                  //Set all ledOn states to false but don't change the state of the current led used (I just use the loopLed number as a handy reference).
      {
        ledOn[l] = false;
      }
    }
    // turn on or turn off the blinking LED
    if ( ledOn[0] == false)
    {
      ledOn[0] = true;
    }
    else
    {
      ledOn[0] = false;

      tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
      tft.setTextScale(2);
      tft.printAlignedOffseted("PLAY", gTextAlignMiddleCenter, 0, -65);

      tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
      tft.setTextScale(1);
      tft.printAt("PLAY", 281, 90);
      digitalWrite(led[2], HIGH);

      ledStatus[0] = LOW;
      digitalWrite(led[0], ledStatus[0]);
    }
    keyPressed[0] = false;
  }

  //See if it is time to blink the LED:
  if ( ledOn[0] == true )
  {
    timeNow = millis();
    if (timeNow - timePrev >= timeWait )
    {
      timePrev = timeNow;
      if (ledStatus[0] == LOW)
      {
        ledStatus[0] = HIGH;
        tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
        tft.setTextScale(1);
        tft.printAt("MULTI", 1, 90);

        tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
        tft.setTextScale(2);
        tft.printAlignedOffseted("MULTIPLY", gTextAlignMiddleCenter, 0, -65);
      }
      else
      {
        ledStatus[0] = LOW;
        tft.setTextColor(ILI9341_CYAN, ILI9341_BLACK);
        tft.setTextScale(1);
        tft.printAt("MULTI", 1, 90);

        tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
        tft.setTextScale(2);
        tft.printAlignedOffseted("MULTIPLY", gTextAlignMiddleCenter, 0, -65);
      }
      digitalWrite(led[0], ledStatus[0]);
    }
  }

  //Footswitch 2:

  if (keyPressed[1] == true)
  {
    MIDI.sendControlChange(13, 127, 1);
    midiLed();
    loopNames();
    loopLed = 1;
    loopLeds();
    for (int l = 0; l < 6; l++)
    {
      if (l != (loopLed))
      {
        ledOn[l] = false;
      }
    }

    if ( ledOn[1] == false)
    {
      ledOn[1] = true;
    }
    else
    {
      ledOn[1] = false;

      tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
      tft.setTextScale(2);
      tft.printAlignedOffseted("PLAY", gTextAlignMiddleCenter, 0, -65);

      tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
      tft.setTextScale(1);
      tft.printAt("PLAY", 281, 90);
      digitalWrite(led[2], HIGH);

      ledStatus[1] = LOW;
      digitalWrite(led[1], ledStatus[1]);
    }
    keyPressed[1] = false;
  }

  if ( ledOn[1] == true )
  {
    timeNow = millis();
    if (timeNow - timePrev >= timeWait )
    {
      timePrev = timeNow;
      if (ledStatus[1] == LOW)
      {
        ledStatus[1] = HIGH;
        tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
        tft.setTextScale(1);
        tft.printAt("OVERDUB", 120, 90);

        tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
        tft.setTextScale(2);
        tft.printAlignedOffseted("OVERDUB", gTextAlignMiddleCenter, 0, -65);
      }
      else
      {
        ledStatus[1] = LOW;
        tft.setTextColor(ILI9341_CYAN, ILI9341_BLACK);
        tft.setTextScale(1);
        tft.printAt("OVERDUB", 120, 90);

        tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
        tft.setTextScale(2);
        tft.printAlignedOffseted("OVERDUB", gTextAlignMiddleCenter, 0, -65);
      }
      digitalWrite(led[1], ledStatus[1]);
    }
  }

  //Footswitch 3:

  if (keyPressed[2] == true)
  {
    MIDI.sendControlChange(14, 127, 1);
    midiLed();
    loopNames();
    loopLed = 2;
    loopLeds();
    for (int l = 0; l < 6; l++)
    {
      if (l != (loopLed))
      {
        ledOn[l] = false;
      }
    }

    if ( ledOn[2] == false)
    {
      ledOn[2] = true;
    }
    else
    {
      ledOn[2] = false;

      tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
      tft.setTextScale(2);
      tft.printAlignedOffseted("PLAY", gTextAlignMiddleCenter, 0, -65);

      tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
      tft.setTextScale(1);
      tft.printAt("PLAY", 281, 90);

      ledStatus[2] = LOW;
      digitalWrite(led[2], HIGH);
    }
    keyPressed[2] = false;
  }

  if ( ledOn[2] == true )
  {
    timeNow = millis();
    if (timeNow - timePrev >= timeWait )
    {
      timePrev = timeNow;
      if (ledStatus[2] == LOW)
      {
        ledStatus[2] = HIGH;
        tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
        tft.setTextScale(1);
        tft.printAt("REC", 245, 90);

        tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
        tft.setTextScale(2);
        tft.printAlignedOffseted("RECORD", gTextAlignMiddleCenter, 0, -65);
      }
      else
      {
        ledStatus[2] = LOW;
        tft.setTextColor(ILI9341_CYAN, ILI9341_BLACK);
        tft.setTextScale(1);
        tft.printAt("REC", 245, 90);

        tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
        tft.setTextScale(2);
        tft.printAlignedOffseted("RECORD", gTextAlignMiddleCenter, 0, -65);
      }
      digitalWrite(led[2], ledStatus[2]);
    }
  }

  //Footswitch 4:

  if (keyPressed[3] == true)
  {
    MIDI.sendControlChange(15, 127, 1);
    midiLed();
    loopNames();
    loopLed = 3;
    loopLeds();
    for (int l = 0; l < 6; l++)
    {
      if (l != (loopLed))
      {
        ledOn[l] = false;
      }
    }

    if ( ledOn[3] == false)
    {
      ledOn[3] = true;
    }
    else
    {
      ledOn[3] = false;

      tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
      tft.setTextScale(2);
      tft.printAlignedOffseted("PLAY", gTextAlignMiddleCenter, 0, -65);

      tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
      tft.setTextScale(1);
      tft.printAt("PLAY", 281, 90);
      digitalWrite(led[2], HIGH);

      ledStatus[3] = LOW;
      digitalWrite(led[3], ledStatus[3]);
    }
    keyPressed[3] = false;
  }

  if ( ledOn[3] == true )
  {
    timeNow = millis();
    if (timeNow - timePrev >= timeWait )
    {
      timePrev = timeNow;
      if (ledStatus[3] == LOW)
      {
        ledStatus[3] = HIGH;
        tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
        tft.setTextScale(1);
        tft.printAligned("INSERT", gTextAlignTopLeft);

        tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
        tft.setTextScale(2);
        tft.printAlignedOffseted("INSERT", gTextAlignMiddleCenter, 0, -65);
      }
      else
      {
        ledStatus[3] = LOW;
        tft.setTextColor(ILI9341_CYAN, ILI9341_BLACK);
        tft.setTextScale(1);
        tft.printAligned("INSERT", gTextAlignTopLeft);

        tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
        tft.setTextScale(2);
        tft.printAlignedOffseted("INSERT", gTextAlignMiddleCenter, 0, -65);
      }
      digitalWrite(led[3], ledStatus[3]);
    }
  }

  //Footswitch 5:

  if (keyPressed[4] == true)
  {
    MIDI.sendControlChange(16, 127, 1);
    midiLed();
    loopNames();
    loopLed = 4;
    loopLeds();
    for (int l = 0; l < 6; l++)
    {
      if (l != (loopLed))
      {
        ledOn[l] = false;
      }
    }

    if ( ledOn[4] == false)
    {
      ledOn[4] = true;
    }
    else
    {
      ledOn[4] = false;

      tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
      tft.setTextScale(2);
      tft.printAlignedOffseted("PLAY", gTextAlignMiddleCenter, 0, -65);

      tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
      tft.setTextScale(1);
      tft.printAt("PLAY", 281, 90);
      digitalWrite(led[2], HIGH);

      ledStatus[4] = LOW;
      digitalWrite(led[4], ledStatus[4]);
    }
    keyPressed[4] = false;
  }

  if ( ledOn[4] == true )
  {
    timeNow = millis();
    if (timeNow - timePrev >= timeWait )
    {
      timePrev = timeNow;
      if (ledStatus[4] == LOW)
      {
        ledStatus[4] = HIGH;
        tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
        tft.setTextScale(1);
        tft.printAligned("REPLACE", gTextAlignTopCenter);

        tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
        tft.setTextScale(2);
        tft.printAlignedOffseted("REPLACE", gTextAlignMiddleCenter, 0, -65);
      }
      else
      {
        ledStatus[4] = LOW;
        tft.setTextColor(ILI9341_CYAN, ILI9341_BLACK);
        tft.setTextScale(1);
        tft.printAligned("REPLACE", gTextAlignTopCenter);

        tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
        tft.setTextScale(2);
        tft.printAlignedOffseted("REPLACE", gTextAlignMiddleCenter, 0, -65);
      }
      digitalWrite(led[4], ledStatus[4]);
    }
  }

  //Footswitch 6:

  if (keyPressed[5] == true)
  {
    MIDI.sendControlChange(17, 127, 1);
    midiLed();
    loopNames();
    loopLed = 5;
    loopLeds();
    for (int l = 0; l < 6; l++)
    {
      if (l != (loopLed))
      {
        ledOn[l] = false;
      }
    }

    if ( ledOn[5] == false)
    {
      ledOn[5] = true;
    }
    else
    {
      ledOn[5] = false;

      tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
      tft.setTextScale(2);
      tft.printAlignedOffseted("PLAY", gTextAlignMiddleCenter, 0, -65);

      tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
      tft.setTextScale(1);
      tft.printAt("PLAY", 281, 90);
      digitalWrite(led[2], HIGH);

      ledStatus[5] = LOW;
      digitalWrite(led[5], ledStatus[5]);
    }
    keyPressed[5] = false;
  }

  if ( ledOn[5] == true )
  {
    timeNow = millis();
    if (timeNow - timePrev >= timeWait )
    {
      timePrev = timeNow;
      if (ledStatus[5] == LOW)
      {
        ledStatus[5] = HIGH;
        tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
        tft.setTextScale(1);
        tft.printAligned("PAUSE", gTextAlignTopRight);

        tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
        tft.setTextScale(2);
        tft.printAlignedOffseted("PAUSE", gTextAlignMiddleCenter, 0, -65);
      }
      else
      {
        ledStatus[5] = LOW;
        tft.setTextColor(ILI9341_CYAN, ILI9341_BLACK);
        tft.setTextScale(1);
        tft.printAligned("PAUSE", gTextAlignTopRight);

        tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
        tft.setTextScale(2);
        tft.printAlignedOffseted("PAUSE", gTextAlignMiddleCenter, 0, -65);
      }
      digitalWrite(led[5], ledStatus[5]);
    }
  }

  //For footswitch 7:
  if (keyPressed[6] == true && loopStatus == true)
  {
    MIDI.sendControlChange(18, 127, 1);
    loopTime = millis();
    midiLed();
    digitalWrite(led[lastLed], LOW);

    for (int l = 0; l < 6; l++)
    {
      ledOn[l] = false;
    }

    loopNames();

    clearLargeName();

    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
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
    midiLed();
    digitalWrite(led[lastLed], LOW);

    for (int l = 0; l < 6; l++)
    {
      ledOn[l] = false;
    }

    loopNames();

    clearLargeName();

    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
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
