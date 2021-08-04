//Return LEDs to last state before toggling looper/stomp and preset mode.
void toggleLeds()
{
  leds[lastLed] = CRGB(0, 255, 255);
  leds[lastLed].nscale8(15);
  FastLED.show();
  leds[activeLed] = CRGB::Red;
  FastLED.show();

  clearLargeName();
}

//LED states in preset mode:
void presetModeLeds()
{
  for (int i = 0; i < 6; i++)
  {
    leds[i] = CRGB(0, 255, 255);
    leds[6] = CRGB::Green;
    leds[7] = CRGB(196, 67, 247);
    leds[i].nscale8(15);
    leds[6].nscale8(15);
    leds[7].nscale8(15);
    FastLED.show();
  }
}

void loopLeds()
{
  for (int i = 0; i < 6; i++)
  {
    leds[i] = CRGB(135, 56, 245);
    leds[i].nscale8(15);
    FastLED.show();
  }
  leds[loopLed] = CRGB::Red;
  FastLED.show();

  clearLargeName();
}

void ledFlash()
{
  for (int i = 0; i < 8; i++)
  {
    leds[i] = CRGB::White;
    FastLED.show();
    delay(15);
    leds[i] = CRGB::Black;
    FastLED.show();
  }
}

//MIDI ACTIVITY LEDS:
void midiLedOn()
{
  midiLedTime = millis();
  leds[8] = CRGB::Green;
  FastLED.show();
}

void midiLedOff()
{
  if (millis() - midiLedTime >= 5 && millis() - midiLedTime <= 200) //Turn off MIDI LED.
  {
    leds[8] = CRGB::Black;
    FastLED.show();
  }
}
