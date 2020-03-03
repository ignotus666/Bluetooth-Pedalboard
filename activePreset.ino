void return2ActivePreset()
{
  if (activePreset == 1)
  {
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("MASTER OF PUPPETS", gTextAlignMiddleCenter, 0, -65); //Large preset name, offset 55 px upwards from centre.

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAlignedOffseted("MAST. PUP", gTextAlignMiddleLeft, 0, -20);
  }

  if (activePreset == 2)
  {
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("BACK IN BLACK",gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAlignedOffseted("B in BLACK", gTextAlignMiddleCenter, 0, -20);
  }

  if (activePreset == 3)
  {
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("STONER", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAlignedOffseted("STONER", gTextAlignMiddleRight, 0, -20);
  }

  if (activePreset == 4)
  {
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("CLEAN", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAligned("CLEAN", gTextAlignTopLeft);
  }

  if (activePreset == 5)
  {
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("CLEAN w/EFF", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAligned("CLEANw/EFF", gTextAlignTopCenter);
  }

  if (activePreset == 6)
  {
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("ECHOEY", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAligned("ECHOEY", gTextAlignTopRight);
  }

  if (activePreset == 7)
  {
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("TOOL", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAlignedOffseted("TOOL", gTextAlignMiddleLeft, 0, -20);
  }

  if (activePreset == 8)
  {
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("KYUSS", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAlignedOffseted("KYUSS", gTextAlignMiddleCenter, 0, -20);
  }

  if (activePreset == 9)
  {
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("CYCO", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAlignedOffseted("CYCO", gTextAlignMiddleRight, 0, -20);
  }

  if (activePreset == 10)
  {
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("OCTA", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAligned("OCTA", gTextAlignTopLeft);
  }

  if (activePreset == 11)
  {
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("SANDMAN", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAligned("SANDMAN", gTextAlignTopCenter);
  }

  if (activePreset == 12)
  {
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("NEUROSIS", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAligned("NEUROSIS", gTextAlignTopRight);
  }

  if (activePreset == 13)
  {
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("TRIPLE DELAY", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAlignedOffseted("TRIP.DEL", gTextAlignMiddleLeft, 0, -20);
  }

  if (activePreset == 14)
  {
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("CRUNCH", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAlignedOffseted("CRUNCH", gTextAlignMiddleCenter, 0, -20);
  }

  if (activePreset == 15)
  {
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("FUZZY", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAlignedOffseted("FUZZY", gTextAlignMiddleRight, 0, -20);
  }

  if (activePreset == 16)
  {
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("EXTREME", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAligned("EXTREME", gTextAlignTopLeft);
  }

  if (activePreset == 17)
  {
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("SLUDGE", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAligned("SLUDGE", gTextAlignTopCenter);
  }

  if (activePreset == 18)
  {
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("DOOM", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAligned("DOOM", gTextAlignTopRight);
  }

  if (activePreset == 19)
  {
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("PRESET 19", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAlignedOffseted("PRES.19", gTextAlignMiddleLeft, 0, -20);
  }

  if (activePreset == 20)
  {
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("PRESET 20", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAlignedOffseted("PRES.20", gTextAlignMiddleCenter, 0, -20);
  }

  if (activePreset == 21)
  {
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("PRESET 21", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAlignedOffseted("PRES.21", gTextAlignMiddleRight, 0, -20);
  }

  if (activePreset == 22)
  {
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("PRESET 22", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAligned("PRES.22", gTextAlignTopLeft);
  }

  if (activePreset == 23)
  {
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("PRESET 23", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAligned("PRES.23", gTextAlignTopCenter);
  }

  if (activePreset == 24)
  {
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("PRESET 24", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAligned("PRES.24", gTextAlignTopRight);
  }

  if (activePreset == 25)
  {
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("PRESET 25", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAlignedOffseted("PRES.25", gTextAlignMiddleLeft, 0, -20);
  }

  if (activePreset == 26)
  {
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("PRESET 26", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAlignedOffseted("PRES.26", gTextAlignMiddleCenter, 0, -20);
  }

  if (activePreset == 27)
  {
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("PRESET 27", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAlignedOffseted("PRES.27", gTextAlignMiddleRight, 0, -20);
  }

  if (activePreset == 28)
  {
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("PRESET 28", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAligned("PRES.28", gTextAlignTopLeft);
  }

  if (activePreset == 29)
  {
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("PRESET 29", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAligned("PRES.29", gTextAlignTopCenter);
  }

  if (activePreset == 30)
  {
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.setTextScale(2);
    tft.printAlignedOffseted("PRESET 30", gTextAlignMiddleCenter, 0, -65);

    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setTextScale(1);
    tft.printAligned("PRES.30", gTextAlignTopRight);
  }
}
