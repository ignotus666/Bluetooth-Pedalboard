//Return LEDs to last state before toggling looper/stomp and preset mode.

void toggleLeds()
{
  digitalWrite(led[lastLed], LOW);
  digitalWrite(led[activeLed], HIGH);

  clearLargeName();
}

void loopLeds()
{
  for (int i = 0; i < 6; i++)
  {
    digitalWrite(led[i], LOW);
  }
  digitalWrite(led[loopLed], HIGH);

  clearLargeName();
}

void ledFlash()
{
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(led[i], HIGH);
    delay(15);
    digitalWrite(led[i], LOW);
  }
}

//MIDI ACTIVITY LEDS:
void midiLedOn()
{
  midiLedTime = millis();
  digitalWrite(led[8], HIGH);
}

void midiLedOff()
{
  if (millis() - midiLedTime >= 5 && millis() - midiLedTime <= 200) //Turn off MIDI LED.
  {

    digitalWrite(led[8], LOW);
  }
}
