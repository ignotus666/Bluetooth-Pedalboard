//Sets of preset names to be printed for each bank:

void bankNames()
{
  b = bankNumber;

  tft.setTextColor(ILI9341_CYAN, ILI9341_BLACK);
  tft.setTextScale(1);
  tft.printAlignedOffseted(presetNames[b][0], gTextAlignMiddleLeft, 0, -20);

  tft.printAlignedOffseted(presetNames[b][1], gTextAlignMiddleCenter, 0, -20);

  tft.printAlignedOffseted(presetNames[b][2], gTextAlignMiddleRight, 0, -20);

  tft.printAligned(presetNames[b][3], gTextAlignTopLeft);

  tft.printAligned(presetNames[b][4], gTextAlignTopCenter);

  tft.printAligned(presetNames[b][5], gTextAlignTopRight);
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

  if (activePreset > -2)              //So it doesn't print wrong preset if entering and leaving stomp/loop mode first thing after booting.
  {
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted(bigNames[activePreset], gTextAlignMiddleCenter, 0, -65); //Large preset name, offset 65 px upwards from centre.
  }

  tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
  tft.setTextScale(1);

  if (activePreset == (b * 6))
  {
    tft.printAlignedOffseted(presetNames[b][0], gTextAlignMiddleLeft, 0, -20);
  }

  else if (activePreset == (b * 6) + 1)
  {
    tft.printAlignedOffseted(presetNames[b][1], gTextAlignMiddleCenter, 0, -20);
  }

  else if (activePreset == (b * 6) + 2)
  {
    tft.printAlignedOffseted(presetNames[b][2], gTextAlignMiddleRight, 0, -20);
  }

  else if (activePreset == (b * 6) + 3)
  {
    tft.printAligned(presetNames[b][3], gTextAlignTopLeft);
  }

  else if (activePreset == (b * 6) + 4)
  {
    tft.printAligned(presetNames[b][4], gTextAlignTopCenter);
  }

  else if (activePreset == (b * 6) + 5)
  {
    tft.printAligned(presetNames[b][5], gTextAlignTopRight);
  }
}
