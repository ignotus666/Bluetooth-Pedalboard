//Set the mode the bank buttons are in, using long press on BANK DOWN button:
void bankMode()
//Long press to scroll through bank button functions: (pedal banks / software banks / software next/prev preset).
//Short press: 'prev' within each function.
{
  if (keyPressed[6] && loopStatus == false && stompStatus == false)             
  { 
    if (button6Active == false)
    {
      button6Active = true;
      buttonTimer = millis();
    }

    if ((millis() - buttonTimer > longPressTime) && (longPress6Active == false)) //Long press.
    {
      longPress6Active = true;
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
    if (button6Active == true)                                                    //Short press.
    {
      if (longPress6Active == true)
      {
        longPress6Active = false;
      }

      else

        switch (bankButtonState)                                                 //Short press does different things depending on mode (bankButtonState) the bank buttons are in.
        {
          case 0:                                                                //Pedalboard banks (no MIDI).
            bankNumber--;

            if (bankNumber < 0)
            {
              bankNumber = 4;                                                    //Increase number for more banks (zero-indexed so 4 actually = 5).
            }

            presetChanged = true;

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

            activePreset = -1;
            activeLed = -1;
            break;
        }
      button6Active = false;
    }
  }

//Long press: toggle between wah and vol functions. Short press: 'next' within each function.
  if (keyPressed[7] && loopStatus == false && stompStatus == false)            
  {
    if (button7Active == false)
    {
      button7Active = true;
      buttonTimer = millis();
    }

    if ((millis() - buttonTimer > longPressTime) && (longPress7Active == false)) //Long press.
    {
      longPress7Active = true;
      pedalState = !pedalState;
      clearPedalName();
      ledFlash();

      if (pedalState == 0)
      {
        pedalControlNum = 0;
        tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
        tft.printAt("Wah:", 230, 223);
      }

      else
      {
        pedalControlNum = 1;
        tft.setTextColor(ILI9341_YELLOW, ILI9341_BLACK);
        tft.printAt("Vol:", 230, 223);
      }
    }
  }

  else
  {
    if (button7Active == true)                                                    //Short press.
    {
      if (longPress7Active == true)
      {
        longPress7Active = false;
      }

      else
        switch (bankButtonState)
        {
          case 0:
            bankNumber++;

            if (bankNumber > 4)                                                    //Increase for more banks.
            {
              bankNumber = 0;
            }

            presetChanged = true;

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

            activePreset = -1;
            activeLed = -1;
            break;
        }
      button7Active = false;
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
