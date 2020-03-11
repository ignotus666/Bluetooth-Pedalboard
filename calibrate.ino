void calibrate()
{
  pedalMin = 1023;          //Reset them to 0 before calibrating in case previous calibrations conflict.
  pedalMax = 0;
  calibrateTime = millis();
  clearLargeName();

  tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
  tft.setTextScale(2);
  tft.printAlignedOffseted("CALIBRATING", gTextAlignMiddleCenter, 0, -65);

  // Calibrate during five seconds
  while (millis() - calibrateTime < 5000)
  {
    wahWah.update();
    wahRead = wahWah.getValue();

    // record the maximum sensor value
    if (wahRead > pedalMax)
    {
      pedalMax = wahRead;
    }

    // record the minimum sensor value
    if (wahRead < pedalMin)
    {
      pedalMin = wahRead;
    }
    //Serial.println(wahRead); //Serial readings for debugging.
  }
  //Serial.println(pedalMin);
  //Serial.println(pedalMax);

  EEPROM.put(ADDR_MIN_VAL, pedalMin);
  delay(100);
  EEPROM.put(ADDR_MAX_VAL, pedalMax);
  delay(100);

  clearLargeName();
  tft.printAlignedOffseted("DONE", gTextAlignMiddleCenter, 0, -65);
  delay(1000);
}
