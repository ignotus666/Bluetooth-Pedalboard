//Activate the appropriate bank number (determined in pedalboardBank()) or if loop or stomp mode are active:
void presetBankStatus()
{
  for (int b = 0; b < 5; b++)        //Increase number for more banks.
  {
    if (statusBank[b] == true)       //b is bankNumber.
    {
      banks();
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

//Change statuses of non-active banks and modes and print bank numbers and ranges:
void presetBanks()                  
{
  const char *bank[] = {"BANK 1", "BANK 2", "BANK 3", "BANK 4", "BANK 5"};        //Add more banks and ranges if increasing number of banks.
  const char *bankRange[] = {"(1-6)", "(7-12)", "(13-18)", "(19-24)", "(25-30)"};

  if (bankNumber != oldBankNumber)
  {
    statusBank[bankNumber] = true;

    clearSmallPresets();

    bankNames();

    statusBank[bankNumber + 1] = false; //Only adjacent bank numbers need to be changed to 'false'.
    statusBank[bankNumber - 1] = false;
    stompStatus = false;
    loopStatus = false;

    ledFlash();

    clearBankSpace();

    tft.setTextColor(ILI9341_HOTPINK);
    tft.setTextScale(2);
    tft.printAt(bank[bankNumber], 1, 152);

    tft.setTextColor(ILI9341_WHITE);
    tft.setTextScale(1);
    tft.printAt(bankRange[bankNumber], 125, 160);
    lastBank = bankNumber;
  }
  oldBankNumber = bankNumber;
}
