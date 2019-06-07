//LED SEQUENCE:

void ledSequence()
{
  digitalWrite(Led1, HIGH);
  delay(40);
  digitalWrite(Led1, LOW);
  digitalWrite(Led2, HIGH);
  delay(40);
  digitalWrite(Led2, LOW);
  digitalWrite(Led3, HIGH);
  delay(40);
  digitalWrite(Led3, LOW);
  digitalWrite(Led6, HIGH);
  delay(40);
  digitalWrite(Led6, LOW);
  digitalWrite(Led5, HIGH);
  delay(40);
  digitalWrite(Led5, LOW);
  digitalWrite(Led4, HIGH);
  delay(40);
  digitalWrite(Led4, LOW);
}

//BOOT SEQUENCE:

void bootSequence()

{
  tft.setFont(Arial_bold_14);

  bootTextSequence();

  // LED light sequence at boot:

  if ( fHasLooped == false )
  {
    for ( int x = 0; x < 3; x++ ) //Loop 3 times.
    {
      ledSequence();
    }

    fHasLooped = true;
  }

  delay(3000);

  tft.fillScreen(ILI9341_BLACK);

  tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
  tft.setTextScale(2);
  tft.printAlignedOffseted("Choose a Preset", gTextAlignMiddleCenter, 0, -65);

  tft.setTextColor(ILI9341_HOTPINK, ILI9341_BLACK);
  tft.setTextScale(2);
  tft.printAt("BANK 1", 1, 152);

  tft.setTextColor(ILI9341_CYAN, ILI9341_BLACK);
  tft.setTextScale(1);
  tft.printAt("Batt:", 11, 223);

  tft.setTextColor(ILI9341_BLUE, ILI9341_BLACK);
  tft.setTextScale(1);
  tft.printAt("Vol", 147, 223);

  tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
  tft.setTextScale(1);
  tft.printAt("Wah", 280, 223);

  //Draw arc outlines:

  tft.fillArc(25, 200, 21, 1, 0, 78, ILI9341_LIGHTBLUE);//Voltage.
  tft.fillArc(25, 200, 12, 1, 0, 78, ILI9341_LIGHTBLUE);

  tft.fillArc(295, 200, 21, 1, 0, 78, ILI9341_HOTPINK);//Wah.
  tft.fillArc(295, 200, 12, 1, 0, 78, ILI9341_HOTPINK);

  tft.fillArc(160, 200, 21, 1, 0, 78, ILI9341_HOTPINK);//Volume.
  tft.fillArc(160, 200, 12, 1, 0, 78, ILI9341_HOTPINK);

  tft.fillRoundRect(195, 155, 115, 18, 3, ILI9341_GREEN);
  tft.drawRoundRect(194, 154, 117, 20, 3, ILI9341_RED);
  tft.setFontMode(gTextFontModeTransparent);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextScale(1);
  tft.printAt("PRESET MODE", 200, 158);

  //Draw volume arc at boot and give it 50% value:
  volBar = 39;
  tft.setFont(SystemFont5x7);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextScale(1);
  tft.printAt("50", 155, 197);
  tft.fillArc(160, 200, 20, 8, 0 + (volBar), 78, (100, 100, 100));

  tft.fillArc(160, 200, 20, 8, 0, (volBar), ILI9341_BLUE);
}

void bootTextSequence()
{
  tft.fillScreen(ILI9341_BLACK);

  tft.drawImage(logo1, 112, 20, logo1Width, logo1Height);//MEGA
  tft.drawImage(logo2, 50, 60, logo2Width, logo2Height);//Pedalboard
  tft.drawImage(logo3, 140, 120, logo3Width, logo3Height);//By
  tft.drawImage(logo4, 113, 150, logo4Width, logo4Height);//Daryl H.

  tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
  tft.setTextScale(1);
  tft.printAt("Ver 0.80", 120, 210);

  tft.drawImage(guitar, 210, 110, guitarWidth, guitarHeight);
  tft.drawImage(guitar2, 42, 110, guitar2Width, guitar2Height);
}
