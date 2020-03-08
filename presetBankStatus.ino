void presetBankStatus()
{
  for (int b = 0; b < 5; b++)
  {
    if (statusBank[b] == true)
    {
      switch (b)
      {
      case 0:
      bank1();
      break;
      
      case 1:
      bank2();
      break;
      
      case 2:
      bank3();
      break;
      
      case 3:
      bank4();
      break;
      
      case 4:
      bank5();
      break;
      }      
    }
  }

  if (stompStatus == true)
  {
    stompMode();                     //Kept these names (stompMode and loopMode) out of the array for the rest of the banks to make it easier to keep track in the code.
  }

  else if (loopStatus == true)
  {
    loopMode();
  }
}

void presetBanks()
{
    // BANK 1:

  if (bankNumber != oldBankNumber && bankNumber == 1)
  {
    statusBank[0] = true;

    clearSmallPresets();

    bank1Presets();

    statusBank[1] = false; //Only adjacent bank numbers need to be changed to 'false'.
    statusBank[4] = false;
    stompStatus = false;
    loopStatus = false;

    for ( int x = 0; x < 2; x++ )       //Loop 2 times.
    {
      ledFlashOn();
      ledFlashOff();
    }

    clearBankSpace();

    tft.setTextColor(ILI9341_HOTPINK);
    tft.setTextScale(2);
    tft.printAt("BANK 1", 1, 152);

    tft.setTextColor(ILI9341_WHITE);
    tft.setTextScale(1);
    tft.printAt("(1-6)", 125, 160);
    lastBank = 1;
  }

  // BANK 2:

  else if (bankNumber != oldBankNumber && bankNumber == 2)
  {
    statusBank[1] = true;

    clearSmallPresets();

    bank2Presets();

    statusBank[0] = false;
    statusBank[2] = false;
    stompStatus = false;
    loopStatus = false;

    for ( int x = 0; x < 2; x++ )
    {
      ledFlashOn();
      ledFlashOff();
    }

    clearBankSpace();

    tft.setTextColor(ILI9341_HOTPINK);
    tft.setTextScale(2);
    tft.printAt("BANK 2", 1, 152);

    tft.setTextColor(ILI9341_WHITE);
    tft.setTextScale(1);
    tft.printAt("(7-12)", 125, 160);
    lastBank = 2;
  }

  // BANK 3:

  else if (bankNumber != oldBankNumber && bankNumber == 3)
  {
    statusBank[2] = true;

    clearSmallPresets();

    bank3Presets();

    statusBank[1] = false;
    statusBank[3] = false;
    stompStatus = false;
    loopStatus = false;

    for ( int x = 0; x < 2; x++ )
    {
      ledFlashOn();
      ledFlashOff();
    }

    clearBankSpace();

    tft.setTextColor(ILI9341_HOTPINK);
    tft.setTextScale(2);
    tft.printAt("BANK 3", 1, 152);

    tft.setTextColor(ILI9341_WHITE);
    tft.setTextScale(1);
    tft.printAt("(13-18)", 125, 160);
    lastBank = 3;
  }

  // BANK 4:

  else if (bankNumber != oldBankNumber && bankNumber == 4)
  {
    statusBank[3] = true;

    clearSmallPresets();

    bank4Presets();

    statusBank[2] = false;
    statusBank[4] = false;
    stompStatus = false;
    loopStatus = false;

    for ( int x = 0; x < 2; x++ )
    {
      ledFlashOn();
      ledFlashOff();
    }

    clearBankSpace();

    tft.setTextColor(ILI9341_HOTPINK);
    tft.setTextScale(2);
    tft.printAt("BANK 4", 1, 152);

    tft.setTextColor(ILI9341_WHITE);
    tft.setTextScale(1);
    tft.printAt("(19-24)", 125, 160);
    lastBank = 4;
  }

  // BANK 5:

  else if (bankNumber != oldBankNumber && bankNumber == 5)
  {
    statusBank[4] = true;

    clearSmallPresets();

    bank5Presets();

    statusBank[3] = false;
    statusBank[0] = false;
    stompStatus = false;
    loopStatus = false;

    for ( int x = 0; x < 2; x++ )
    {
      ledFlashOn();
      ledFlashOff();
    }

    clearBankSpace();

    tft.setTextColor(ILI9341_HOTPINK);
    tft.setTextScale(2);
    tft.printAt("BANK 5", 1, 152);

    tft.setTextColor(ILI9341_WHITE);
    tft.setTextScale(1);
    tft.printAt("(25-30)", 125, 160);
    lastBank = 5;
  }
  oldBankNumber = bankNumber;
}
