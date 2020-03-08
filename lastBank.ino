//Function to return to last active bank when toggling between looper/stomp and preset mode:

void return2lastBank()
{
  for (int b = 1; b < 5; b++)
  {
    if (b !=  (lastBank - 1))           //It's lastBank -1 because of the array index starting at 0 but bank numbers starting at 1.
    {
      statusBank[b] = false;
      statusBank[lastBank - 1] = true;
    }
  }
  stompStatus = false;

  switch (lastBank)
  {
    case 1:
      bank1Presets();
      break;

    case 2:
      bank2Presets();
      break;

    case 3:
      bank3Presets();
      break;

    case 4:
      bank4Presets();
      break;

    case 5:
      bank5Presets();
      break;
  }
}
