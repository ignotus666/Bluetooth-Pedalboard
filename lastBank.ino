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
    bank6Status = false;
    bank7Status = false;
    bank8Status = false;
    bank9Status = false;
    bank10Status = false;
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
    bank6Status = false;
    bank7Status = false;
    bank8Status = false;
    bank9Status = false;
    bank10Status = false;
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
    bank6Status = false;
    bank7Status = false;
    bank8Status = false;
    bank9Status = false;
    bank10Status = false;
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
    bank6Status = false;
    bank7Status = false;
    bank8Status = false;
    bank9Status = false;
    bank10Status = false;
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
    bank6Status = false;
    bank7Status = false;
    bank8Status = false;
    bank9Status = false;
    bank10Status = false;
    stompStatus = false;
    
    bank5Presets();
  }

  if (lastBank == 6)
  {
    bank6Status = true;

    bank1Status = false;
    bank2Status = false;
    bank3Status = false;
    bank4Status = false;
    bank5Status = false;
    bank7Status = false;
    bank8Status = false;
    bank9Status = false;
    bank10Status = false;
    stompStatus = false;
    
    bank6Presets();
  }

  if (lastBank == 7)
  {
    bank7Status = true;

    bank1Status = false;
    bank2Status = false;
    bank3Status = false;
    bank4Status = false;
    bank5Status = false;
    bank6Status = false;
    bank8Status = false;
    bank9Status = false;
    bank10Status = false;
    stompStatus = false;
    
    bank7Presets();
  }

  if (lastBank == 8)
  {
    bank8Status = true;

    bank1Status = false;
    bank2Status = false;
    bank3Status = false;
    bank4Status = false;
    bank5Status = false;
    bank6Status = false;
    bank7Status = false;
    bank9Status = false;
    bank10Status = false;
    stompStatus = false;
    
    bank8Presets();
  }

  if (lastBank == 9)
  {
    bank9Status = true;

    bank1Status = false;
    bank2Status = false;
    bank3Status = false;
    bank4Status = false;
    bank5Status = false;
    bank6Status = false;
    bank7Status = false;
    bank8Status = false;
    bank10Status = false;
    stompStatus = false;
    
    bank9Presets();
  }

  if (lastBank == 10)
  {
    bank10Status = true;

    bank1Status = false;
    bank2Status = false;
    bank3Status = false;
    bank4Status = false;
    bank5Status = false;
    bank6Status = false;
    bank7Status = false;
    bank8Status = false;
    bank9Status = false;
    stompStatus = false;
    
    bank10Presets();
  }
}
