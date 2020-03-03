void loopActive()
{
  loopStatus = !loopStatus;

  loopTime = millis();//Start counting, to clear some messages off the screen after a couple of seconds.

  loop1State = true;
  loop2State = true;
  loop3State = true;
  loop4State = true;
  loop5State = true;
  loop6State = true;

  if (loopStatus == true)
  {
    for ( int x = 0; x < 2; x++ )
    {
      ledFlashOn();
      ledFlashOff();
    }

    digitalWrite(led[7], HIGH);
    
    led1On = false;
    led2On = false;
    led3On = false;
    led4On = false;
    led5On = false;
    led6On = false;

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

    bank1Status = false;
    bank2Status = false;
    bank3Status = false;
    bank4Status = false;
    bank5Status = false;
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
    return2ActivePreset();
    bankButtonNames();

    tft.fillRoundRect(195, 155, 115, 18, 3, ILI9341_GREEN);
    tft.drawRoundRect(194, 154, 117, 20, 3, ILI9341_RED);
    tft.setFontMode(gTextFontModeTransparent);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextScale(1);
    tft.printAt("PRESET MODE", 200, 158);

    digitalWrite(lastLed, HIGH);
    digitalWrite(led[7], LOW);
  }
}

//LOOP MODE:

void loopMode()
{
  //Footswitch code:

  //Footswitch 1:
  if (key1Pressed)
  {
    MIDI.sendControlChange(12, 127, 1);     //(control number, controller value, channel).Send the same message whenever the switch is pressed.
    midiLed();
    loopNames();
    loopFoot1();
    led2On = false;
    led3On = false;
    led4On = false;
    led5On = false;
    led6On = false;
    // turn on or turn off the blinking LED
    if ( led1On == false)
    {
      led1On = true;
    }
    else
    {
      led1On = false;

      tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
      tft.setTextScale(2);
      tft.printAlignedOffseted("PLAY", gTextAlignMiddleCenter, 0, -65);

      tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
      tft.setTextScale(1);
      tft.printAt("PLAY", 281, 90);
      digitalWrite(led[2], HIGH);

      led1Status = LOW;
      digitalWrite(led[0], led1Status);
    }
    key1Pressed = false;
  }

  //See if it is time to blink the LED:
  if ( led1On == true )
  {
    timeNow = millis();
    if (timeNow - timePrev >= timeWait )
    {
      timePrev = timeNow;
      if (led1Status == LOW)
      {
        led1Status = HIGH;
        tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
        tft.setTextScale(1);
        tft.printAt("MULTI", 1, 90);

        tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
        tft.setTextScale(2);
        tft.printAlignedOffseted("MULTIPLY", gTextAlignMiddleCenter, 0, -65);
      }
      else
      {
        led1Status = LOW;
        tft.setTextColor(ILI9341_CYAN, ILI9341_BLACK);
        tft.setTextScale(1);
        tft.printAt("MULTI", 1, 90);

        tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
        tft.setTextScale(2);
        tft.printAlignedOffseted("MULTIPLY", gTextAlignMiddleCenter, 0, -65);
      }
      digitalWrite(led[0], led1Status);
    }
  }

  //Footswitch 2:

  if (key2Pressed)
  {
    MIDI.sendControlChange(13, 127, 1);
    midiLed();
    loopNames();
    loopFoot2();
    led1On = false;
    led3On = false;
    led4On = false;
    led5On = false;
    led6On = false;

    if ( led2On == false)
    {
      led2On = true;
    }
    else
    {
      led2On = false;

      tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
      tft.setTextScale(2);
      tft.printAlignedOffseted("PLAY", gTextAlignMiddleCenter, 0, -65);

      tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
      tft.setTextScale(1);
      tft.printAt("PLAY", 281, 90);
      digitalWrite(led[2], HIGH);

      led2Status = LOW;
      digitalWrite(led[1], led2Status);
    }
    key2Pressed = false;
  }

  if ( led2On == true )
  {
    timeNow = millis();
    if (timeNow - timePrev >= timeWait )
    {
      timePrev = timeNow;
      if (led2Status == LOW)
      {
        led2Status = HIGH;
        tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
        tft.setTextScale(1);
        tft.printAt("OVERDUB", 120, 90);

        tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
        tft.setTextScale(2);
        tft.printAlignedOffseted("OVERDUB", gTextAlignMiddleCenter, 0, -65);
      }
      else
      {
        led2Status = LOW;
        tft.setTextColor(ILI9341_CYAN, ILI9341_BLACK);
        tft.setTextScale(1);
        tft.printAt("OVERDUB", 120, 90);

        tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
        tft.setTextScale(2);
        tft.printAlignedOffseted("OVERDUB", gTextAlignMiddleCenter, 0, -65);
      }
      digitalWrite(led[1], led2Status);
    }
  }

  //Footswitch 3:

  if (key3Pressed)
  {
    MIDI.sendControlChange(14, 127, 1);
    midiLed();
    loopNames();
    loopFoot3();
    led1On = false;
    led2On = false;
    led4On = false;
    led5On = false;
    led6On = false;

    if ( led3On == false)
    {
      led3On = true;
    }
    else
    {
      led3On = false;

      tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
      tft.setTextScale(2);
      tft.printAlignedOffseted("PLAY", gTextAlignMiddleCenter, 0, -65);

      tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
      tft.setTextScale(1);
      tft.printAt("PLAY", 281, 90);

      led3Status = LOW;
      digitalWrite(led[2], HIGH);
    }
    key3Pressed = false;
  }

  if ( led3On == true )
  {
    timeNow = millis();
    if (timeNow - timePrev >= timeWait )
    {
      timePrev = timeNow;
      if (led3Status == LOW)
      {
        led3Status = HIGH;
        tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
        tft.setTextScale(1);
        tft.printAt("REC", 245, 90);

        tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
        tft.setTextScale(2);
        tft.printAlignedOffseted("RECORD", gTextAlignMiddleCenter, 0, -65);
      }
      else
      {
        led3Status = LOW;
        tft.setTextColor(ILI9341_CYAN, ILI9341_BLACK);
        tft.setTextScale(1);
        tft.printAt("REC", 245, 90);

        tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
        tft.setTextScale(2);
        tft.printAlignedOffseted("RECORD", gTextAlignMiddleCenter, 0, -65);
      }
      digitalWrite(led[2], led3Status);
    }
  }

  //Footswitch 4:

  if (key4Pressed)
  {
    MIDI.sendControlChange(15, 127, 1);
    midiLed();
    loopNames();
    loopFoot4();
    led1On = false;
    led2On = false;
    led3On = false;
    led5On = false;
    led6On = false;

    if ( led4On == false)
    {
      led4On = true;
    }
    else
    {
      led4On = false;

      tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
      tft.setTextScale(2);
      tft.printAlignedOffseted("PLAY", gTextAlignMiddleCenter, 0, -65);

      tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
      tft.setTextScale(1);
      tft.printAt("PLAY", 281, 90);
      digitalWrite(led[2], HIGH);

      led4Status = LOW;
      digitalWrite(led[3], led4Status);
    }
    key4Pressed = false;
  }

  if ( led4On == true )
  {
    timeNow = millis();
    if (timeNow - timePrev >= timeWait )
    {
      timePrev = timeNow;
      if (led4Status == LOW)
      {
        led4Status = HIGH;
        tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
        tft.setTextScale(1);
        tft.printAligned("INSERT", gTextAlignTopLeft);

        tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
        tft.setTextScale(2);
        tft.printAlignedOffseted("INSERT", gTextAlignMiddleCenter, 0, -65);
      }
      else
      {
        led4Status = LOW;
        tft.setTextColor(ILI9341_CYAN, ILI9341_BLACK);
        tft.setTextScale(1);
        tft.printAligned("INSERT", gTextAlignTopLeft);

        tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
        tft.setTextScale(2);
        tft.printAlignedOffseted("INSERT", gTextAlignMiddleCenter, 0, -65);
      }
      digitalWrite(led[3], led4Status);
    }
  }

  //Footswitch 5:

  if (key5Pressed)
  {
    MIDI.sendControlChange(16, 127, 1);
    midiLed();
    loopNames();
    loopFoot5();
    led1On = false;
    led2On = false;
    led3On = false;
    led4On = false;
    led6On = false;

    if ( led5On == false)
    {
      led5On = true;
    }
    else
    {
      led5On = false;

      tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
      tft.setTextScale(2);
      tft.printAlignedOffseted("PLAY", gTextAlignMiddleCenter, 0, -65);

      tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
      tft.setTextScale(1);
      tft.printAt("PLAY", 281, 90);
      digitalWrite(led[2], HIGH);

      led5Status = LOW;
      digitalWrite(led[4], led5Status);
    }
    key5Pressed = false;
  }

  if ( led5On == true )
  {
    timeNow = millis();
    if (timeNow - timePrev >= timeWait )
    {
      timePrev = timeNow;
      if (led5Status == LOW)
      {
        led5Status = HIGH;
        tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
        tft.setTextScale(1);
        tft.printAligned("REPLACE", gTextAlignTopCenter);

        tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
        tft.setTextScale(2);
        tft.printAlignedOffseted("REPLACE", gTextAlignMiddleCenter, 0, -65);
      }
      else
      {
        led5Status = LOW;
        tft.setTextColor(ILI9341_CYAN, ILI9341_BLACK);
        tft.setTextScale(1);
        tft.printAligned("REPLACE", gTextAlignTopCenter);

        tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
        tft.setTextScale(2);
        tft.printAlignedOffseted("REPLACE", gTextAlignMiddleCenter, 0, -65);
      }
      digitalWrite(led[4], led5Status);
    }
  }

  //Footswitch 6:

  if (key6Pressed)
  {
    MIDI.sendControlChange(17, 127, 1);
    midiLed();
    loopNames();
    loopFoot6();
    led1On = false;
    led2On = false;
    led3On = false;
    led4On = false;
    led5On = false;

    if ( led6On == false)
    {
      led6On = true;
    }
    else
    {
      led6On = false;

      tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
      tft.setTextScale(2);
      tft.printAlignedOffseted("PLAY", gTextAlignMiddleCenter, 0, -65);

      tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
      tft.setTextScale(1);
      tft.printAt("PLAY", 281, 90);
      digitalWrite(led[2], HIGH);

      led6Status = LOW;
      digitalWrite(led[5], led6Status);
    }
    key6Pressed = false;
  }

  if ( led6On == true )
  {
    timeNow = millis();
    if (timeNow - timePrev >= timeWait )
    {
      timePrev = timeNow;
      if (led6Status == LOW)
      {
        led6Status = HIGH;
        tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
        tft.setTextScale(1);
        tft.printAligned("PAUSE", gTextAlignTopRight);

        tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
        tft.setTextScale(2);
        tft.printAlignedOffseted("PAUSE", gTextAlignMiddleCenter, 0, -65);
      }
      else
      {
        led6Status = LOW;
        tft.setTextColor(ILI9341_CYAN, ILI9341_BLACK);
        tft.setTextScale(1);
        tft.printAligned("PAUSE", gTextAlignTopRight);

        tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
        tft.setTextScale(2);
        tft.printAlignedOffseted("PAUSE", gTextAlignMiddleCenter, 0, -65);
      }
      digitalWrite(led[5], led6Status);
    }
  }

  //For footswitch 7:
  if (key7Pressed && loopStatus == true)
  {
    MIDI.sendControlChange(18, 127, 1);
    loopTime = millis();
    midiLed();
    digitalWrite(led[0,1,2,3,4,5], LOW);
    led1On = false;
    led2On = false;
    led3On = false;
    led4On = false;
    led5On = false;
    led6On = false;

    loopNames();

    clearLargeName();

    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("UNDO", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAt("UNDO", 1, 130);
    key7Pressed = false;
  }

  //For footswitch 8:
  if (key8Pressed && loopStatus == true)
  {
    MIDI.sendControlChange(19, 127, 1);
    loopTime = millis();
    midiLed();
    digitalWrite(led[0,1,2,3,4,5], LOW);
    led1On = false;
    led2On = false;
    led3On = false;
    led4On = false;
    led5On = false;
    led6On = false;

    loopNames();

    clearLargeName();

    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("REDO", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAt("REDO", 80, 130);
    key8Pressed = false;
  }

  if (millis() - loopTime > 1000 && millis() - loopTime < 1050)
  {
    clearLargeName();
    loopNames();
  }
}
