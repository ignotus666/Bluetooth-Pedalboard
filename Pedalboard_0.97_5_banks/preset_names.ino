//Sets of preset names to be printed for each bank:

void bankNames()
{
  b = bankNumber;

  tft.setTextColor(ILI9341_CYAN, ILI9341_BLACK);
  tft.setTextScale(1);
  tft.printAlignedOffseted(smallPresetName[b][0], gTextAlignMiddleLeft, 0, -20);

  tft.printAlignedOffseted(smallPresetName[b][1], gTextAlignMiddleCenter, 0, -20);

  tft.printAlignedOffseted(smallPresetName[b][2], gTextAlignMiddleRight, 0, -20);

  tft.printAligned(smallPresetName[b][3], gTextAlignTopLeft);

  tft.printAligned(smallPresetName[b][4], gTextAlignTopCenter);

  tft.printAligned(smallPresetName[b][5], gTextAlignTopRight);
}

void loopNames()
{
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
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

//Small preset names printed in red and large names in green when active. Also used when returning to preset mode from stomp or loop mode:
void printActivePreset()
{
  b = bankNumber;

  if (activePreset > -2)              //At -2 so it doesn't print wrong preset if entering and leaving stomp/loop mode first thing after booting.
  {
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted(bigPresetName[activePreset], gTextAlignMiddleCenter, 0, -65); //Large preset name, offset 65 px upwards from centre.
  }

  tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
  tft.setTextScale(1);

  if (activePreset == (b * 6))
  {
    tft.printAlignedOffseted(smallPresetName[b][0], gTextAlignMiddleLeft, 0, -20);
  }

  else if (activePreset == (b * 6) + 1)
  {
    tft.printAlignedOffseted(smallPresetName[b][1], gTextAlignMiddleCenter, 0, -20);
  }

  else if (activePreset == (b * 6) + 2)
  {
    tft.printAlignedOffseted(smallPresetName[b][2], gTextAlignMiddleRight, 0, -20);
  }

  else if (activePreset == (b * 6) + 3)
  {
    tft.printAligned(smallPresetName[b][3], gTextAlignTopLeft);
  }

  else if (activePreset == (b * 6) + 4)
  {
    tft.printAligned(smallPresetName[b][4], gTextAlignTopCenter);
  }

  else if (activePreset == (b * 6) + 5)
  {
    tft.printAligned(smallPresetName[b][5], gTextAlignTopRight);
  }
}

void printBluePreset()     //Just print last active preset back to blue instead of printing whole set again.
{
  b = bankNumber;
  
  tft.setTextColor(ILI9341_CYAN, ILI9341_BLACK);
  tft.setTextScale(1);

  if (lastActivePreset == (b * 6))
  {
    tft.printAlignedOffseted(smallPresetName[b][0], gTextAlignMiddleLeft, 0, -20);
  }

  else if (lastActivePreset == (b * 6) + 1)
  {
    tft.printAlignedOffseted(smallPresetName[b][1], gTextAlignMiddleCenter, 0, -20);
  }

  else if (lastActivePreset == (b * 6) + 2)
  {
    tft.printAlignedOffseted(smallPresetName[b][2], gTextAlignMiddleRight, 0, -20);
  }

  else if (lastActivePreset == (b * 6) + 3)
  {
    tft.printAligned(smallPresetName[b][3], gTextAlignTopLeft);
  }

  else if (lastActivePreset == (b * 6) + 4)
  {
    tft.printAligned(smallPresetName[b][4], gTextAlignTopCenter);
  }

  else if (lastActivePreset == (b * 6) + 5)
  {
    tft.printAligned(smallPresetName[b][5], gTextAlignTopRight);
  }
}
