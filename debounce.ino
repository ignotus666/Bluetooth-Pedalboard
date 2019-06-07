void debounce1()
{
  if (  (newSwitch1State1 == newSwitch1State2) && (newSwitch1State1 == newSwitch1State3) )
  {
    if ( newSwitch1State1 != oldSwitch1State )
    {
      if ( newSwitch1State1 == HIGH )
      {
        key1Pressed = true;
      }
      else
      {
        key1Pressed =  false;
      }
      oldSwitch1State = newSwitch1State1;
      delay(50);
    }
  }
}

void debounce2()
{
  if (  (newSwitch2State1 == newSwitch2State2) && (newSwitch2State2 == newSwitch2State3) )
  {
    if ( newSwitch2State1 != oldSwitch2State )
    {
      if ( newSwitch2State1 == HIGH )
      {
        key2Pressed = true;
      }
      else
      {
        key2Pressed =  false;
      }
      oldSwitch2State = newSwitch2State1;
      delay(50);
    }
  }
}

void debounce3()
{
  if (  (newSwitch3State1 == newSwitch3State2) && (newSwitch3State2 == newSwitch3State3) )
  {
    if ( newSwitch3State1 != oldSwitch3State )
    {
      if ( newSwitch3State1 == HIGH )
      {
        key3Pressed = true;
      }
      else
      {
        key3Pressed =  false;
      }
      oldSwitch3State = newSwitch3State1;
      delay(50);
    }
  }
}

void debounce4()
{
   if (  (newSwitch4State1 == newSwitch4State2) && (newSwitch4State2 == newSwitch4State3) )
  {
    if ( newSwitch4State1 != oldSwitch4State )
    {
      if ( newSwitch4State1 == HIGH )
      {
        key4Pressed = true;
      }
      else
      {
        key4Pressed =  false;
      }
      oldSwitch4State = newSwitch4State1;
      delay(50);
    }
  }
}

void debounce5()
{
  if (  (newSwitch5State1 == newSwitch5State2) && (newSwitch5State2 == newSwitch5State3) )
  {
    if ( newSwitch5State1 != oldSwitch5State )
    {
      if ( newSwitch5State1 == HIGH )
      {
        key5Pressed = true;
      }
      else
      {
        key5Pressed =  false;
      }
      oldSwitch5State = newSwitch5State1;
      delay(50);
    }
  }
}

void debounce6()
{
  if (  (newSwitch6State1 == newSwitch6State2) && (newSwitch6State2 == newSwitch6State3) )
  {
    if ( newSwitch6State1 != oldSwitch6State )
    {
      if ( newSwitch6State1 == HIGH )
      {
        key6Pressed = true;
      }
      else
      {
        key6Pressed =  false;
      }
      oldSwitch6State = newSwitch6State1;
      delay(50);
    }
  }
}

void debounce7()
{
  if (  (newSwitch7State1 == newSwitch7State2) && (newSwitch7State2 == newSwitch7State3) )
  {
    if ( newSwitch7State1 != oldSwitch7State )
    {
      if ( newSwitch7State1 == HIGH )
      {
        key7Pressed = true;
      }
      else
      {
        key7Pressed =  false;
      }
      oldSwitch7State = newSwitch7State1;
      delay(50);
    }
  }
}

void debounce8()
{
  if (  (newSwitch8State1 == newSwitch8State2) && (newSwitch8State2 == newSwitch8State3) )
  {
    if ( newSwitch8State1 != oldSwitch8State )
    {
      if ( newSwitch8State1 == HIGH )
      {
        key8Pressed = true;
      }
      else
      {
        key8Pressed =  false;
      }
      oldSwitch8State = newSwitch8State1;
      delay(50);
    }
  }
}

void debounce9()
{
  if (  (newSwitch9State1 == newSwitch9State2) && (newSwitch9State2 == newSwitch9State3) )
  {
    if ( newSwitch9State1 != oldSwitch9State )
    {
      if ( newSwitch9State1 == HIGH )
      {
        key9Pressed = true;
      }
      else
      {
        key9Pressed =  false;
      }
      oldSwitch9State = newSwitch9State1;
      delay(50);
    }
  }
}

void debounce10()
{
  if (  (newSwitch10State1 == newSwitch10State2) && (newSwitch10State2 == newSwitch10State3) )
  {
    if ( newSwitch10State1 != oldSwitch10State )
    {
      if ( newSwitch10State1 == HIGH )
      {
        key10Pressed = true;
      }
      else
      {
        key10Pressed =  false;
      }
      oldSwitch10State = newSwitch10State1;
      delay(50);
    }
  }
}

void debounceStates()
{
    //Switch states for debouncing:

  newSwitch1State1 = pressed1;
  newSwitch1State2 = pressed1;
  newSwitch1State3 = pressed1;
  
  newSwitch2State1 = pressed2;
  newSwitch2State2 = pressed2;
  newSwitch2State3 = pressed2;
  
  newSwitch3State1 = pressed3;
  newSwitch3State2 = pressed3;
  newSwitch3State3 = pressed3;
  
  newSwitch4State1 = pressed4;
  newSwitch4State2 = pressed4;
  newSwitch4State3 = pressed4;
  
  newSwitch5State1 = pressed5;
  newSwitch5State2 = pressed5;
  newSwitch5State3 = pressed5;
  
  newSwitch6State1 = pressed6;
  newSwitch6State2 = pressed6;
  newSwitch6State3 = pressed6;
  
  newSwitch7State1 = bankDown;
  newSwitch7State2 = bankDown;
  newSwitch7State3 = bankDown;
  
  newSwitch8State1 = bankUp;
  newSwitch8State2 = bankUp;
  newSwitch8State3 = bankUp;
  
  newSwitch9State1 = stompOn;
  newSwitch9State2 = stompOn;
  newSwitch9State3 = stompOn;
  
  newSwitch10State1 = loopOn;
  newSwitch10State2 = loopOn;
  newSwitch10State3 = loopOn;
  
  debounce1();
  debounce2();
  debounce3();
  debounce4();
  debounce5();
  debounce6();
  debounce7();
  debounce8();
  debounce9();
  debounce10();
}
