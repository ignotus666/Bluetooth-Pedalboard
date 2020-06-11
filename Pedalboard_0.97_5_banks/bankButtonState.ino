//Set the mode the bank buttons are in, using long press on BANK DOWN button:
void bankMode()
{
  if (keyPressed[6] == HIGH && loopStatus == false && stompStatus == false)    //Only switch 7 (keyPressed[6]) has the long/short press function.
  {
    if (buttonActive == false)
    {
      buttonActive = true;
      buttonTimer = millis();
    }

    if ((millis() - buttonTimer > longPressTime) && (longPressActive == false)) //Long press.
    {
      longPressActive = true;

      bankButtonState++;

      if (bankButtonState > 2)
      {
        bankButtonState = 0;
      }

      clearBankMode();
      bankButtons();

      ledFlash();
      digitalWrite(led[lastLed], HIGH);
    }
  }

  else
  {
    if (buttonActive == true)                                                  //Short press.
    {
      if (longPressActive == true)
      {
        longPressActive = false;
      }

      switch (bankButtonState)                                                 //Short press does different things depending on mode (bankButtonState) the bank buttons are in.
      {
        case 0:                                                                //Pedalboard banks (no MIDI).
          bankNumber--;

          if (bankNumber < 0)
          {
            bankNumber = 4;                                                    //Increase number for more banks.
          }

          presetChanged = true;
          keyPressed[6] = false;

          if (bankNumber != oldBankNumber)
          {
            activePreset = -1;
            activeLed = -1;
          }
          break;

        case 1:                                                                //Software bank change (MIDI sent).
          MIDI.sendControlChange(21, 127, 1);
          clearNameTime = millis();
          presetChanged = true;

          ledFlash();

          clearLargeName();
          printBluePreset();
          tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
          tft.setTextScale(2);
          tft.printAlignedOffseted("PREV. BANK", gTextAlignMiddleCenter, 0, -65);

          tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
          tft.setTextScale(1);
          tft.printAt("<<BANK", 1, 130);
          keyPressed[6] = false;
          activePreset = -1;
          activeLed = -1;
          break;

        case 2:                                                                //Software preset change (MIDI sent).
          MIDI.sendControlChange(23, 127, 1);
          clearNameTime = millis();
          presetChanged = true;

          ledFlash();

          clearLargeName();
          printBluePreset();
          tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
          tft.setTextScale(2);
          tft.printAlignedOffseted("PREV. PRESET", gTextAlignMiddleCenter, 0, -65);

          tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
          tft.setTextScale(1);
          tft.printAt("<<PRES", 1, 130);

          keyPressed[6] = false;
          activePreset = -1;
          activeLed = -1;
          break;
      }
      buttonActive = false;
    }
  }
  if (keyPressed[7] && loopStatus == false && stompStatus == false)            //Switch 8 operates normally (no long/short press).
  {
    switch (bankButtonState)
    {
      case 0:
        bankNumber++;

        if (bankNumber > 4)
        {
          bankNumber = 0;
        }

        presetChanged = true;
        keyPressed[7] = false;

        if (bankNumber != oldBankNumber)                                       //If banks change, reset preset names and last LED to -1.
        {
          activePreset = -1;
          activeLed = -1;
        }
        break;

      case 1:
        MIDI.sendControlChange(22, 127, 1);
        clearNameTime = millis();
        presetChanged = true;

        ledFlash();

        clearLargeName();
        printBluePreset();
        tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
        tft.setTextScale(2);
        tft.printAlignedOffseted("NEXT BANK", gTextAlignMiddleCenter, 0, -65);

        tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
        tft.setTextScale(1);
        tft.printAt("BANK>>", 90, 130);
        keyPressed[7] = false;
        activePreset = -1;
        activeLed = -1;
        break;

      case 2:
        MIDI.sendControlChange(24, 127, 1);
        clearNameTime = millis();
        presetChanged = true;

        ledFlash();

        clearLargeName();
        printBluePreset();
        tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
        tft.setTextScale(2);
        tft.printAlignedOffseted("NEXT PRESET", gTextAlignMiddleCenter, 0, -65);

        tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
        tft.setTextScale(1);
        tft.printAt("PRES>>", 90, 130);

        keyPressed[7] = false;
        activePreset = -1;
        activeLed = -1;
        break;
    }
  }

  if (bankButtonState == 1 || bankButtonState == 2)
  {
    if (millis() - clearNameTime > 600 && millis() - clearNameTime < 700)      //After some time, return the red names to yellow and erase large central text.
    {
      clearLargeName();
      bankButtonNames();
    }
  }
}

//Determine what text to print ("BANK", "PRES" or nothing), depending on what mode the bank buttons are in:
void bankButtons()
{
  if (bankButtonState == 0)
  {
    lastBankButton = 0;
  }

  else if (bankButtonState == 1)
  {
    tft.setTextColor(ILI9341_YELLOWGREEN, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAt("<<BANK", 1, 130);

    tft.setTextColor(ILI9341_YELLOWGREEN, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAt("BANK>>", 90, 130);

    lastBankButton = 1;
  }

  else
  {
    tft.setTextColor(ILI9341_YELLOWGREEN, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAt("<<PRES", 1, 130);

    tft.setTextColor(ILI9341_YELLOWGREEN, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAt("PRES>>", 90, 130);

    lastBankButton = 2;
  }
  keyPressed[6] = false;
}

void bankButtonNames()
{
  if (lastBankButton == 1)
  {
    tft.setTextColor(ILI9341_YELLOWGREEN, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAt("<<BANK", 1, 130);

    tft.setTextColor(ILI9341_YELLOWGREEN, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAt("BANK>>", 90, 130);
  }

  else if (lastBankButton == 2)
  {
    tft.setTextColor(ILI9341_YELLOWGREEN, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAt("<<PRES", 1, 130);

    tft.setTextColor(ILI9341_YELLOWGREEN, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAt("PRES>>", 90, 130);
  }
}
