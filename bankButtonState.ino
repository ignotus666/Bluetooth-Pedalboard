void pedalboardBank()
{
  if (key8Pressed && loopStatus == false && stompStatus == false && wahVal > 100) //If in Preset Mode button 8 is pressed.
  {
    bankNumber++;                                                                 //Move to next bank.
    key8Pressed = false;
  }

  if (key7Pressed && loopStatus == false && stompStatus == false && wahVal > 100) //Move to previous bank with button 7.
  {
    bankNumber--;
    key7Pressed = false;
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
  if (key8Pressed && loopStatus == false && stompStatus == false && wahVal > 100) //If in software bank change mode send MIDI notes for bank up/down in software.
  {
    MIDI.sendControlChange(22, 127, 1);
    stompTime = millis();

    ledFlashOn();
    ledFlashOff();

    clearLargeName();
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("NEXT BANK", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAt("BANK>>", 90, 130);
    key8Pressed = false;
  }

  if (key7Pressed && loopStatus == false && stompStatus == false && wahVal > 100)
  {
    MIDI.sendControlChange(21, 127, 1);
    stompTime = millis();

    ledFlashOn();
    ledFlashOff();

    clearLargeName();
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("PREV. BANK", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAt("<<BANK", 1, 130);
    key7Pressed = false;
  }
}

void softwarePreset()
{
  if (key8Pressed && loopStatus == false && stompStatus == false && wahVal > 100) //If in software preset change mode send MIDI notes for preset up/down in software.
  {
    MIDI.sendControlChange(24, 127, 1);
    stompTime = millis();

    ledFlashOn();
    ledFlashOff();

    clearLargeName();
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("NEXT PRESET", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAt("PRES>>", 90, 130);
    
    key8Pressed = false;
  }

  if (key7Pressed && loopStatus == false && stompStatus == false && wahVal > 100)
  {
    MIDI.sendControlChange(23, 127, 1);
    stompTime = millis();

    ledFlashOn();
    ledFlashOff();

    clearLargeName();
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("PREV. PRESET", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAt("<<PRES", 1, 130);
    
    key7Pressed = false;
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

  if (lastBankButton == 3)
  {
    tft.setTextColor(ILI9341_YELLOWGREEN, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAt("<<PRES", 1, 130);

    tft.setTextColor(ILI9341_YELLOWGREEN, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAt("PRES>>", 90, 130);
  }
}
