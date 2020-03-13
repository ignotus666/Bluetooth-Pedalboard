//Sets of preset names to be printed for each bank:

void bankNames()
{
  b = bankNumber;
  const char *bankNames[5][6] = 
  {   
    {"MAST. PUP", "B in BLACK", "STONER", "CLEAN", "CLEANw/EFF", "ECHOEY"},  //Bank 1.
    {"TOOL", "KYUSS","CYCO", "OCTA", "SANDMAN", "NEUROSIS"},                 //Bank 2.
    {"TRIP.DEL", "CRUNCH", "FUZZY", "EXTREME","SLUDGE", "DOOM"},             //3
    {"PRES.19", "PRES.20", "PRES.21", "PRES.22", "PRES.23", "PRES.24"},      //4
    {"PRES.25", "PRES.26", "PRES.27", "PRES.28", "PRES.29", "PRES.30"}       //5
  };                                                                         //If increasing no. of banks, add more sets and reflect no. in first parameter after bankNames.

  tft.setTextColor(ILI9341_CYAN, ILI9341_BLACK);
  tft.setTextScale(1);
  tft.printAlignedOffseted(bankNames[b][0], gTextAlignMiddleLeft, 0, -20);
  
  tft.printAlignedOffseted(bankNames[b][1], gTextAlignMiddleCenter, 0, -20);

  tft.printAlignedOffseted(bankNames[b][2], gTextAlignMiddleRight, 0, -20);

  tft.printAligned(bankNames[b][3], gTextAlignTopLeft);

  tft.printAligned(bankNames[b][4], gTextAlignTopCenter);

  tft.printAligned(bankNames[b][5], gTextAlignTopRight);
}

void loopNames()
{
  tft.setTextColor(ILI9341_CYAN, ILI9341_BLACK);
  tft.setTextScale(1);
  tft.printAligned("INSERT", gTextAlignTopLeft);

  tft.printAt("OVERDUB", 120, 90);

  tft.printAt("REC/PLAY", 245, 90);

  tft.printAt("MULTI", 1, 90);

  tft.printAligned("REPLACE", gTextAlignTopCenter);

  tft.printAligned("PAUSE", gTextAlignTopRight);
  
  tft.printAt("UNDO", 1, 130);
  
  tft.printAt("REDO", 80, 130);
}

//Small reset names printed in red and large names in green when active. Also used when returning to preset mode from stomp or loop mode:
void return2ActivePreset()
{
  b = bankNumber;
  const char *bigNames[] =                                                              //Large name printed in centre.
  { "MASTER OF PUPPETS", "BACK IN BLACK", "STONER", "CLEAN", "CLEAN w/EFF", "ECHOEY",   //Bank 1. These differ from the arrays above in that here individual names are printed, not sets.
    "TOOL", "KYUSS", "CYCO", "OCTA", "SANDMAN", "NEUROSIS",                             //Bank 2.
    "TRIPLE DELAY", "CRUNCH", "FUZZY", "EXTREME", "SLUDGE", "DOOM",                     //3
    "PRESET 19", "PRESET 20", "PRESET 21", "PRESET 22", "PRESET 23", "PRESET 24",       //4
    "PRESET 25", "PRESET 26", "PRESET 27", "PRESET 28", "PRESET 29", "PRESET 30"        //5
  };                                                                                    //Add more names if increasing no. of banks. 

  const char *smallNames[] =
  { "MAST. PUP", "B in BLACK", "STONER", "CLEAN", "CLEANw/EFF", "ECHOEY",   //Bank 1.
    "TOOL", "KYUSS", "CYCO", "OCTA", "SANDMAN", "NEUROSIS",                 //Bank 2.
    "TRIP.DEL", "CRUNCH", "FUZZY", "EXTREME", "SLUDGE", "DOOM",             //3
    "PRES.19", "PRES.20", "PRES.21", "PRES.22", "PRES.23", "PRES.24",       //4
    "PRES.25", "PRES.26", "PRES.27", "PRES.28", "PRES.29", "PRES.30"        //5
  };                                                                        //Add more names if increasing no. of banks. 


  tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
  tft.setTextScale(2);
  tft.printAlignedOffseted(bigNames[activePreset], gTextAlignMiddleCenter, 0, -65); //Large preset name, offset 55 px upwards from centre.

  tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
  tft.setTextScale(1);

  if (activePreset == (b * 6))
  {
    tft.printAlignedOffseted(smallNames[b * 6], gTextAlignMiddleLeft, 0, -20);
  }

  else if (activePreset == (b * 6) + 1)
  {
    tft.printAlignedOffseted(smallNames[(b * 6) + 1], gTextAlignMiddleCenter, 0, -20);
  }

  else if (activePreset == (b * 6) + 2)
  {
    tft.printAlignedOffseted(smallNames[(b * 6) + 2], gTextAlignMiddleRight, 0, -20);
  }
  
  else if (activePreset == (b * 6) + 3)
  {
    tft.printAligned(smallNames[(b * 6) + 3], gTextAlignTopLeft);
  }

  else if (activePreset == (b * 6) + 4)
  {
    tft.printAligned(smallNames[(b * 6) + 4], gTextAlignTopCenter);
  }

  else if (activePreset == (b * 6) + 5)
  {
    tft.printAligned(smallNames[(b * 6) + 5], gTextAlignTopRight);
  }
}
