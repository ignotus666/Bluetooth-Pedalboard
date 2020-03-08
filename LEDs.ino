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
void ledFlashOn()
{
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(led[i], HIGH);
  }

  delay(30);
}

void ledFlashOff()
{
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(led[i], LOW);
  }

  delay(30);
}

//MIDI ACTIVITY LEDS:
void midiLed()
{
  midiLedTime = millis();
  if (stompStatus == LOW)
  {
    digitalWrite(led[6], HIGH);
  }

  else
  {
    digitalWrite(led[7], HIGH);
  }
}

void midiLedOff()
{
  if (millis() - midiLedTime >= 5 && millis() - midiLedTime <= 200) //Turn off MIDI LED.
  {

    if (stompStatus == LOW)
    {
      digitalWrite(led[6], LOW);
    }

    else
    {
      digitalWrite(led[7], LOW);
    }
  }
}
