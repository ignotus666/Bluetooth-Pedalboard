void calibrate()
{
  pedalMin = 1023;          //Reset them to 0 before calibrating in case previous calibrations conflict.
  pedalMax = 0;
  calibrateTime = millis();
  clearLargeName();

  tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
  tft.setTextScale(2);
  tft.printAlignedOffseted("CALIBRATING", gTextAlignMiddleCenter, -30, -65);

  // Calibrate during five seconds
  while (millis() - calibrateTime < 5000)
  {
    wahWah.update();
    wahRead = wahWah.getValue();

    //Record the maximum sensor value:
    if (wahRead > pedalMax)
    {
      pedalMax = wahRead;
    }

    //Record the minimum sensor value:
    if (wahRead < pedalMin)
    {
      pedalMin = wahRead;
    }
    
    //Count down 5 seconds:
    if (millis() - calibrateTime > 1 && millis() - calibrateTime < 100)
    {
      tft.printAlignedOffseted("5", gTextAlignMiddleCenter, 130, -65);
    }

    else if (millis() - calibrateTime > 1000 && millis() - calibrateTime < 1050)
    {
      tft.setTextColor(ILI9341_BLACK);
      tft.printAlignedOffseted("5", gTextAlignMiddleCenter, 130, -65);
      tft.setTextColor(ILI9341_GREEN);
      tft.printAlignedOffseted("4", gTextAlignMiddleCenter, 130, -65);
    }
    else if (millis() - calibrateTime > 2000 && millis() - calibrateTime < 2050)
    {
      tft.setTextColor(ILI9341_BLACK);
      tft.printAlignedOffseted("4", gTextAlignMiddleCenter, 130, -65);
      tft.setTextColor(ILI9341_GREEN);
      tft.printAlignedOffseted("3", gTextAlignMiddleCenter, 130, -65);
    }
    else if (millis() - calibrateTime > 3000 && millis() - calibrateTime < 3050)
    {
      tft.setTextColor(ILI9341_BLACK);
      tft.printAlignedOffseted("3", gTextAlignMiddleCenter, 130, -65);
      tft.setTextColor(ILI9341_GREEN);
      tft.printAlignedOffseted("2", gTextAlignMiddleCenter, 130, -65);
    }
    else if (millis() - calibrateTime > 4000 && millis() - calibrateTime < 4050)
    {
      tft.setTextColor(ILI9341_BLACK);
      tft.printAlignedOffseted("2", gTextAlignMiddleCenter, 130, -65);
      tft.setTextColor(ILI9341_GREEN);
      tft.printAlignedOffseted("1", gTextAlignMiddleCenter, 130, -65);
    }

    //Serial.println(wahRead); //Serial readings for debugging.
  }
  //Serial.println(pedalMin);
  //Serial.println(pedalMax);

  EEPROM.put(ADDR_MIN_VAL, pedalMin); //Write min and max values to eeprom.
  delay(100);
  EEPROM.put(ADDR_MAX_VAL, pedalMax);
  delay(100);

  clearLargeName();
  tft.setTextColor(ILI9341_BLACK);
  tft.printAlignedOffseted("1", gTextAlignMiddleCenter, 130, -65);
  tft.setTextColor(ILI9341_GREEN);
  tft.printAlignedOffseted("DONE", gTextAlignMiddleCenter, 0, -65);
  delay(1500);
  printActivePreset();
}
