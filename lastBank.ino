//Function to return to last active bank when toggling between looper/stomp and preset mode:

void return2lastBank()
{
  if (lastBank == 1)
  {
    bank1Status = true;

    bank2Status = false;
    bank3Status = false;
    bank4Status = false;
    bank5Status = false;
    stompStatus = false;
    
    bank1Presets();
  }

  if (lastBank == 2)
  {
    bank2Status = true;

    bank1Status = false;
    bank3Status = false;
    bank4Status = false;
    bank5Status = false;
    stompStatus = false;
    
    bank2Presets();
  }

  if (lastBank == 3)
  {
    bank3Status = true;

    bank1Status = false;
    bank2Status = false;
    bank4Status = false;
    bank5Status = false;
    stompStatus = false;
    
    bank3Presets();
  }

  if (lastBank == 4)
  {
    bank4Status = true;

    bank1Status = false;
    bank2Status = false;
    bank3Status = false;
    bank5Status = false;
    stompStatus = false;
    
    bank4Presets();
  }

  if (lastBank == 5)
  {
    bank5Status = true;

    bank1Status = false;
    bank2Status = false;
    bank3Status = false;
    bank4Status = false;
    stompStatus = false;
    
    bank5Presets();
  }
}
