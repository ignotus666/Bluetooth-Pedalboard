void bankMode()
{
  if (keyPressed[6] == HIGH && loopStatus == false && stompStatus == false && wahVal < 100) //Pressing button 7 while also pressing wah to change bank mode.
  {
    bankButtonState++;
    clearBankMode();
    bankButtons();
    presetChanged = 0;     //Reset counter to store preset or bank changes.

    ledFlashOn();
    ledFlashOff();
  }

  switch (bankButtonState)
  {
    case 1:
      pedalboardBank();
      break;

    case 2:
      softwareBank();
      break;

    case 3:
      softwarePreset();
      break;
  }
  
//Press buttons 3 and 4 in preset mode to start calibration:
  if (keyPressed[2] == HIGH && keyPressed[3] == HIGH && stompStatus == false && loopStatus == false)
  {
    calibrate();
  }
}

void bankButtons()
{
  if (bankButtonState > 3)
  {
    bankButtonState = 1;
  }

  if (bankButtonState == 1)
  {
    lastBankButton = 1;
  }

  if (bankButtonState == 2)
  {
    tft.setTextColor(ILI9341_YELLOWGREEN, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAt("<<BANK", 1, 130);

    tft.setTextColor(ILI9341_YELLOWGREEN, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAt("BANK>>", 90, 130);

    lastBankButton = 2;
  }

  if (bankButtonState == 3)
  {
    tft.setTextColor(ILI9341_YELLOWGREEN, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAt("<<PRES", 1, 130);

    tft.setTextColor(ILI9341_YELLOWGREEN, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAt("PRES>>", 90, 130);

    lastBankButton = 3;

    return2lastBank();
  }
  keyPressed[6] = false;
}

void pedalboardBank()
{
  if (keyPressed[7] && loopStatus == false && stompStatus == false && wahVal > 100) //If in Preset Mode button 8 is pressed.
  {
    bankNumber++;                                                                //Move to next bank.
    keyPressed[7] = false;
  }

  if (keyPressed[6] && loopStatus == false && stompStatus == false && wahVal > 100) //Move to previous bank with button 7.
  {
    bankNumber--;
    keyPressed[6] = false;
  }

  if (bankNumber > 5)                                                             //Bank 5 loops back to 1.
  {
    bankNumber = 1;
  }

  if (bankNumber < 1)
  {
    bankNumber = 5;
  }

  if (bankNumber != oldBankNumber)                                                //If banks change, reset preset names and last LED to 0.
  {
    activePreset = 0;
    lastLed = 0;
  }
}

void softwareBank()
{
  if (keyPressed[7] && loopStatus == false && stompStatus == false && wahVal > 100) //If in software bank change mode send MIDI notes for bank up/down in software.
  {
    MIDI.sendControlChange(22, 127, 1);
    stompTime = millis();
    presetChanged++;

    ledFlashOn();
    ledFlashOff();

    clearLargeName();
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
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("PREV. BANK", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAt("<<BANK", 1, 130);
    keyPressed[6] = false;
  }

  if (millis() - stompTime > 600 && millis() - stompTime < 700)
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
  if (lastBankButton == 2)
  {
    tft.setTextColor(ILI9341_YELLOWGREEN, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAt("<<BANK", 1, 130);

    tft.setTextColor(ILI9341_YELLOWGREEN, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAt("BANK>>", 90, 130);
  }

  else if (lastBankButton == 3)
  {
    tft.setTextColor(ILI9341_YELLOWGREEN, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAt("<<PRES", 1, 130);

    tft.setTextColor(ILI9341_YELLOWGREEN, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAt("PRES>>", 90, 130);
  }
}
