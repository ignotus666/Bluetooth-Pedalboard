void debounce()
{
  //Switch states for debouncing:
  for (int swSt = 0; swSt < 24; swSt++)                      //There should be 3 different readings of newSwitchState for each switch read by digitalRead().
  {
    int pSt = swSt / 3;                                      //Dividing the newSwitchState reading by 3 using an int gives the correct increments for pressed[].
    newSwitchState[swSt] = mux.read(pressed[pSt]);
  }

  for (int swSt = 0, oSwSt = 0; (swSt < 24) && (oSwSt < 8); swSt += 3, oSwSt++) //Increment switchState by 3 every loop and oldSwitchState by 1.
  {
    if ((newSwitchState[swSt] == newSwitchState[swSt + 1]) && (newSwitchState[swSt + 1] == newSwitchState[swSt + 2]))
    {
      if (newSwitchState[swSt] != oldSwitchState[oSwSt])
      {
        if (newSwitchState[swSt] == LOW)
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

void debounce2()
{
  for (int swSt2 = 0; swSt2 < 6; swSt2++)
  {
    int pSt2 = swSt2 / 3;
    newSwitchState2[swSt2] = digitalRead(pressed2[pSt2]);
  }

  for (int swSt2 = 0, oSwSt2 = 0; (swSt2 < 6) && (oSwSt2 < 2); swSt2 += 3, oSwSt2++) //Increment switchState by 3 every loop and oldSwitchState by 1.
  {
    if ((newSwitchState2[swSt2] == newSwitchState2[swSt2 + 1]) && (newSwitchState2[swSt2 + 1] == newSwitchState2[swSt2 + 2]))
    {
      if (newSwitchState2[swSt2] != oldSwitchState2[oSwSt2])
      {
        if (newSwitchState2[swSt2] == LOW)
        {
          keyPressed2[oSwSt2] = true;
        }
        else
        {
          keyPressed2[oSwSt2] =  false;
        }
        oldSwitchState2[oSwSt2] = newSwitchState2[swSt2];
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
      debounce2();
      lastDebounceTime = currentDebounceTime;
    }
  }
