//Activate the appropriate bank number or if loop or stomp mode are active:
void presetBankStatus()
{
  for (int b = 0; b < 5; b++)        //Increase number for more banks.
  {
    if (bankStatus[b] == true)       //b is bankNumber.
    {
      banks();
    }
  }

  if (stompModeStatus == true)
  {
    stompMode();                     //Kept these names (stompMode and loopMode) out of the array for the rest of the banks to make it easier to keep track in the code.
  }

  else if (loopModeStatus == true)
  {
    loopMode();
  }
}

//Change statuses of non-active banks and modes and print bank numbers and ranges:
void presetBanks()                  
{
  const char *bank[] = {"1", "2", "3", "4", "5"};        //Add more banks and ranges if increasing number of banks.
  const char *bankRange[] = {"(1-6)", "(7-12)", "(13-18)", "(19-24)", "(25-30)"};

  if (bankNumber != oldBankNumber)
  {
    bankStatus[bankNumber] = true;

    clearSmallPresets();

    bankNames();

    bankStatus[bankNumber + 1] = false; //Only adjacent bank numbers need to be changed to 'false'.
    bankStatus[bankNumber - 1] = false;
    stompModeStatus = false;
    loopModeStatus = false;

    ledFlash();
    presetModeLeds();

    clearBankSpace();

    tft.setTextColor(ILI9341_HOTPINK);
    tft.setTextScale(2);
    tft.printAt(bank[bankNumber], 95, 152);

    tft.setTextColor(ILI9341_WHITE);
    tft.setTextScale(1);
    tft.printAt(bankRange[bankNumber], 125, 160);
    lastBank = bankNumber;
  }
  oldBankNumber = bankNumber;
}
