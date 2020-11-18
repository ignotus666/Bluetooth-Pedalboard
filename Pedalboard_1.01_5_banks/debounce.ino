void debounce()
{
  //Switch states for debouncing:
  for (int swSt = 0; swSt < 30; swSt++)                                          //There should be 3 different readings of newSwitchState for each switch read by digitalRead().
  {
    int pSt = swSt / 3;                                                          //Dividing the newSwitchState reading by 3 using an int gives the correct increments for pressed[].
    newSwitchState[swSt] = digitalRead(pressed[pSt]);
  }

  for (int swSt = 0, oSwSt = 0; (swSt < 30) && (oSwSt < 10); swSt += 3, oSwSt++) //Increment switchState by 3 every loop and oldSwitchState by 1. 
  {
    if ((newSwitchState[swSt] == newSwitchState[swSt + 1]) && (newSwitchState[swSt + 1] == newSwitchState[swSt + 2]))
    {
      if (newSwitchState[swSt] != oldSwitchState[oSwSt])
      {
        if (newSwitchState[swSt] == HIGH)
        {
          keyPressed[oSwSt] = true;
        }
        else
        {
          keyPressed[oSwSt] =  false;
        }
        oldSwitchState[oSwSt] = newSwitchState[swSt];
      }
    }
  }
}

//Run debounce code every 50 ms. To avoid use of delay():
void debounceTime()                         
{
  if (millis() - lastDebounceTime >= 50)
  {
    debounce();
    lastDebounceTime = currentDebounceTime;
  }
}
