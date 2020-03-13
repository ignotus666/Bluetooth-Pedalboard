//Set the mode the bank buttons are in, pressing expression pedal and the bank/preset down button:
void bankMode()
{
  if (keyPressed[6] == HIGH && loopStatus == false && stompStatus == false && wahVal < 100)
  {
    bankButtonState++;
    clearBankMode();
    bankButtons();
    presetChanged = true;     //Reset counter to store preset or bank changes.

    ledFlashOn();
    ledFlashOff();
  }

  switch (bankButtonState)
  {
    case 0:
      pedalboardBank();   //To scroll through pedalboard banks.
      break;

    case 1:
      softwareBank();     //Send MIDI to change banks in software.
      break;

    case 2:
      softwarePreset();   //Send MIDI to change presets in software.
      break;
  }

  //Press buttons 3 and 4 simultaneously in preset mode to start calibration:
  if (keyPressed[2] == HIGH && keyPressed[3] == HIGH && stompStatus == false && loopStatus == false)
  {
    calibrate();
  }
}

void bankButtons()  //Determine what text to print ("BANK", "PRES" or nothing), depending on what mode the bank buttons are in.
{
  if (bankButtonState > 2)
  {
    bankButtonState = 0;
  }

  if (bankButtonState == 0)
  {
    lastBankButton = 0;
  }

  if (bankButtonState == 1)
  {
    tft.setTextColor(ILI9341_YELLOWGREEN, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAt("<<BANK", 1, 130);

    tft.setTextColor(ILI9341_YELLOWGREEN, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAt("BANK>>", 90, 130);

    lastBankButton = 1;
  }

  if (bankButtonState == 2)
  {
    tft.setTextColor(ILI9341_YELLOWGREEN, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAt("<<PRES", 1, 130);

    tft.setTextColor(ILI9341_YELLOWGREEN, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAt("PRES>>", 90, 130);

    lastBankButton = 2;

    return2lastBank();
  }
  keyPressed[6] = false;
}

void pedalboardBank()
{
  if (keyPressed[7] && loopStatus == false && stompStatus == false && wahVal > 100) //If in Preset Mode button 8 is pressed.
  {
    bankNumber++;
    presetChanged = true;                                                                   //Move to next bank.
    keyPressed[7] = false;

    if (bankNumber != oldBankNumber)                                                   //If banks change, reset preset names and last LED to -1.
    {
      activePreset = -1;
      lastLed = -1;
    }
  }

  if (keyPressed[6] && loopStatus == false && stompStatus == false && wahVal > 100) //Move to previous bank with button 7.
  {
    bankNumber--;
    presetChanged = true;
    keyPressed[6] = false;

    if (bankNumber != oldBankNumber)
    {
      activePreset = -1;
      lastLed = -1;
    }
  }

  if (bankNumber > 4)                                                                //Bank 5 (zero indexed) loops back to 1. Increase number for more banks.
  {
    bankNumber = 0;
  }

  if (bankNumber < 0)
  {
    bankNumber = 4;                                                                  //Increase number for more banks.
  }
}

void softwareBank()
{
  if (keyPressed[7] && loopStatus == false && stompStatus == false && wahVal > 100)  //If in software bank change mode send MIDI notes for bank up/down in software.
  {
    MIDI.sendControlChange(22, 127, 1);
    stompTime = millis();
    presetChanged++;

    ledFlashOn();
    ledFlashOff();

    clearLargeName();
    bankNames();
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("NEXT BANK", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAt("BANK>>", 90, 130);
    keyPressed[7] = false;
  }

  if (keyPressed[6] && loopStatus == false && stompStatus == false && wahVal > 100)
  {
    MIDI.sendControlChange(21, 127, 1);
    stompTime = millis();
    presetChanged++;

    ledFlashOn();
    ledFlashOff();

    clearLargeName();
    bankNames();
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("PREV. BANK", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAt("<<BANK", 1, 130);
    keyPressed[6] = false;
  }

  if (millis() - stompTime > 600 && millis() - stompTime < 700)                    //After some time, return the red names to yellow and erase large central text.
  {
    clearLargeName();
    bankButtonNames();
  }
}

void softwarePreset()
{
  if (keyPressed[7] && loopStatus == false && stompStatus == false && wahVal > 100) //If in software preset change mode send MIDI notes for preset up/down in software.
  {
    MIDI.sendControlChange(24, 127, 1);
    stompTime = millis();
    presetChanged++;

    ledFlashOn();
    ledFlashOff();

    clearLargeName();
    bankNames();
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("NEXT PRESET", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAt("PRES>>", 90, 130);

    keyPressed[7] = false;
  }

  if (keyPressed[6] && loopStatus == false && stompStatus == false && wahVal > 100)
  {
    MIDI.sendControlChange(23, 127, 1);
    stompTime = millis();
    presetChanged++;

    ledFlashOn();
    ledFlashOff();

    clearLargeName();
    bankNames();
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("PREV. PRESET", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAt("<<PRES", 1, 130);

    keyPressed[6] = false;
  }

  if (millis() - stompTime > 600 && millis() - stompTime < 700)
  {
    clearLargeName();
    bankButtonNames();
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
