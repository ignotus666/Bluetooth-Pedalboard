//Sets of preset names for each bank:

void bank1Presets()
{
  tft.setTextColor(ILI9341_CYAN, ILI9341_BLACK);
  tft.setTextScale(1);
  tft.printAlignedOffseted("MAST. PUP", gTextAlignMiddleLeft, 0, -20);
  
  tft.printAlignedOffseted("B in BLACK", gTextAlignMiddleCenter, 0, -20);

  tft.printAlignedOffseted("STONER", gTextAlignMiddleRight, 0, -20);

  tft.printAligned("CLEAN", gTextAlignTopLeft);

  tft.printAligned("CLEANw/EFF", gTextAlignTopCenter);

  tft.printAligned("ECHOEY", gTextAlignTopRight);
}

void bank2Presets()
{
  tft.setTextColor(ILI9341_CYAN, ILI9341_BLACK);
  tft.setTextScale(1);
  tft.printAlignedOffseted("TOOL", gTextAlignMiddleLeft, 0, -20);

  tft.printAlignedOffseted("KYUSS", gTextAlignMiddleCenter, 0, -20);

  tft.printAlignedOffseted("CYCO", gTextAlignMiddleRight, 0, -20);

  tft.printAligned("OCTA", gTextAlignTopLeft);

  tft.printAligned("SANDMAN", gTextAlignTopCenter);

  tft.printAligned("NEUROSIS", gTextAlignTopRight);
}

void bank3Presets()
{
  tft.setTextColor(ILI9341_CYAN, ILI9341_BLACK);
  tft.setTextScale(1);
  tft.printAlignedOffseted("TRIP.DEL", gTextAlignMiddleLeft, 0, -20);

  tft.printAlignedOffseted("CRUNCH", gTextAlignMiddleCenter, 0, -20);

  tft.printAlignedOffseted("FUZZY", gTextAlignMiddleRight, 0, -20);

  tft.printAligned("EXTREME", gTextAlignTopLeft);

  tft.printAligned("SLUDGE", gTextAlignTopCenter);

  tft.printAligned("DOOM", gTextAlignTopRight);
}

void bank4Presets()
{
  tft.setTextColor(ILI9341_CYAN, ILI9341_BLACK);
  tft.setTextScale(1);
  tft.printAlignedOffseted("PRES.19", gTextAlignMiddleLeft, 0, -20);

  tft.printAlignedOffseted("PRES.20", gTextAlignMiddleCenter, 0, -20);

  tft.printAlignedOffseted("PRES.21", gTextAlignMiddleRight, 0, -20);

  tft.printAligned("PRES.22", gTextAlignTopLeft);

  tft.printAligned("PRES.23", gTextAlignTopCenter);

  tft.printAligned("PRES.24", gTextAlignTopRight);
}

void bank5Presets()
{
  tft.setTextColor(ILI9341_CYAN, ILI9341_BLACK);
  tft.setTextScale(1);
  tft.printAlignedOffseted("PRES.25", gTextAlignMiddleLeft, 0, -20);

  tft.printAlignedOffseted("PRES.26", gTextAlignMiddleCenter, 0, -20);

  tft.printAlignedOffseted("PRES.27", gTextAlignMiddleRight, 0, -20);

  tft.printAligned("PRES.28", gTextAlignTopLeft);

  tft.printAligned("PRES.29", gTextAlignTopCenter);

  tft.printAligned("PRES.30", gTextAlignTopRight);
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
