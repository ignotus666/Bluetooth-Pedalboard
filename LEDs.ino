//Return LEDs to last state before toggling looper/stomp and preset mode.

void foot1()
{
  for (int i = 0; i < 6; i++)
  {
    digitalWrite(led[i], LOW);
  }
  digitalWrite(led[0], HIGH);

  lastLed = led[0];

  clearLargeName();
}

void foot2()
{
  for (int i = 0; i < 6; i++)
  {
    digitalWrite(led[i], LOW);
  }
  digitalWrite(led[1], HIGH);

  lastLed = led[1];

  clearLargeName();
}

void foot3()
{
  for (int i = 0; i < 6; i++)
  {
    digitalWrite(led[i], LOW);
  }
  digitalWrite(led[2], HIGH);

  lastLed = led[2];

  clearLargeName();
}

void foot4()
{
  for (int i = 0; i < 6; i++)
  {
    digitalWrite(led[i], LOW);
  }
  digitalWrite(led[3], HIGH);

  lastLed = led[3];

  clearLargeName();
}

void foot5()
{
  for (int i = 0; i < 6; i++)
  {
    digitalWrite(led[i], LOW);
  }
  digitalWrite(led[4], HIGH);

  lastLed = led[4];

  clearLargeName();
}

void foot6()
{
  for (int i = 0; i < 6; i++)
  {
    digitalWrite(led[i], LOW);
  }
  digitalWrite(led[5], HIGH);

  lastLed = led[5];

  clearLargeName();
}

void loopFoot1()
{
  for (int i = 0; i < 6; i++)
  {
    digitalWrite(led[i], LOW);
  }
  digitalWrite(led[0], HIGH);

  clearLargeName();
}

void loopFoot2()
{
  for (int i = 0; i < 6; i++)
  {
    digitalWrite(led[i], LOW);
  }
  digitalWrite(led[1], HIGH);

  clearLargeName();
}

void loopFoot3()
{
  for (int i = 0; i < 6; i++)
  {
    digitalWrite(led[i], LOW);
  }
  digitalWrite(led[2], HIGH);

  clearLargeName();
}

void loopFoot4()
{
  for (int i = 0; i < 6; i++)
  {
    digitalWrite(led[i], LOW);
  }
  digitalWrite(led[3], HIGH);

  clearLargeName();
}

void loopFoot5()
{
  for (int i = 0; i < 6; i++)
  {
    digitalWrite(led[i], LOW);
  }
  digitalWrite(led[4], HIGH);

  clearLargeName();
}

void loopFoot6()
{
  for (int i = 0; i < 6; i++)
  {
    digitalWrite(led[i], LOW);
  }
  digitalWrite(led[5], HIGH);

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

  if (stompStatus == HIGH)
  {
    digitalWrite(led[7], HIGH);
  }
}
