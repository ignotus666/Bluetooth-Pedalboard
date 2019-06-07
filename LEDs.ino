//Return LEDs to last state before toggling looper/stomp and preset mode.

void foot1()
{
  digitalWrite(Led1, HIGH);
  digitalWrite(Led2, LOW);
  digitalWrite(Led3, LOW);
  digitalWrite(Led4, LOW);
  digitalWrite(Led5, LOW);
  digitalWrite(Led6, LOW);

  lastLed = Led1;

  clearLargeName();
}

void foot2()
{
  digitalWrite(Led1, LOW);
  digitalWrite(Led2, HIGH);
  digitalWrite(Led3, LOW);
  digitalWrite(Led4, LOW);
  digitalWrite(Led5, LOW);
  digitalWrite(Led6, LOW);

  lastLed = Led2;

  clearLargeName();
}

void foot3()
{
  digitalWrite(Led1, LOW);
  digitalWrite(Led2, LOW);
  digitalWrite(Led3, HIGH);
  digitalWrite(Led4, LOW);
  digitalWrite(Led5, LOW);
  digitalWrite(Led6, LOW);

  lastLed = Led3;

  clearLargeName();
}

void foot4()
{
  digitalWrite(Led1, LOW);
  digitalWrite(Led2, LOW);
  digitalWrite(Led3, LOW);
  digitalWrite(Led4, HIGH);
  digitalWrite(Led5, LOW);
  digitalWrite(Led6, LOW);

  lastLed = Led4;

  clearLargeName();
}

void foot5()
{
  digitalWrite(Led1, LOW);
  digitalWrite(Led2, LOW);
  digitalWrite(Led3, LOW);
  digitalWrite(Led4, LOW);
  digitalWrite(Led5, HIGH);
  digitalWrite(Led6, LOW);

  lastLed = Led5;

  clearLargeName();
}

void foot6()
{
  digitalWrite(Led1, LOW);
  digitalWrite(Led2, LOW);
  digitalWrite(Led3, LOW);
  digitalWrite(Led4, LOW);
  digitalWrite(Led5, LOW);
  digitalWrite(Led6, HIGH);

  lastLed = Led6;

  clearLargeName();
}

void loopFoot1()
{
  digitalWrite(Led1, HIGH);
  digitalWrite(Led2, LOW);
  digitalWrite(Led3, LOW);
  digitalWrite(Led4, LOW);
  digitalWrite(Led5, LOW);
  digitalWrite(Led6, LOW);

  clearLargeName();
}

void loopFoot2()
{
  digitalWrite(Led1, LOW);
  digitalWrite(Led2, HIGH);
  digitalWrite(Led3, LOW);
  digitalWrite(Led4, LOW);
  digitalWrite(Led5, LOW);
  digitalWrite(Led6, LOW);

  clearLargeName();
}

void loopFoot3()
{
  digitalWrite(Led1, LOW);
  digitalWrite(Led2, LOW);
  digitalWrite(Led3, HIGH);
  digitalWrite(Led4, LOW);
  digitalWrite(Led5, LOW);
  digitalWrite(Led6, LOW);

  clearLargeName();
}

void loopFoot4()
{
  digitalWrite(Led1, LOW);
  digitalWrite(Led2, LOW);
  digitalWrite(Led3, LOW);
  digitalWrite(Led4, HIGH);
  digitalWrite(Led5, LOW);
  digitalWrite(Led6, LOW);

  clearLargeName();
}

void loopFoot5()
{
  digitalWrite(Led1, LOW);
  digitalWrite(Led2, LOW);
  digitalWrite(Led3, LOW);
  digitalWrite(Led4, LOW);
  digitalWrite(Led5, HIGH);
  digitalWrite(Led6, LOW);

  clearLargeName();
}

void loopFoot6()
{
  digitalWrite(Led1, LOW);
  digitalWrite(Led2, LOW);
  digitalWrite(Led3, LOW);
  digitalWrite(Led4, LOW);
  digitalWrite(Led5, LOW);
  digitalWrite(Led6, HIGH);

  clearLargeName();
}
void ledFlashOn()
{
  digitalWrite(Led1, HIGH);
  digitalWrite(Led2, HIGH);
  digitalWrite(Led3, HIGH);
  digitalWrite(Led4, HIGH);
  digitalWrite(Led5, HIGH);
  digitalWrite(Led6, HIGH);
  digitalWrite(Led7, HIGH);
  digitalWrite(Led8, HIGH);

  delay(30);
}

void ledFlashOff()
{
  digitalWrite(Led1, LOW);
  digitalWrite(Led2, LOW);
  digitalWrite(Led3, LOW);
  digitalWrite(Led4, LOW);
  digitalWrite(Led5, LOW);
  digitalWrite(Led6, LOW);
  digitalWrite(Led7, LOW);
  digitalWrite(Led8, LOW);

  delay(30);
}
