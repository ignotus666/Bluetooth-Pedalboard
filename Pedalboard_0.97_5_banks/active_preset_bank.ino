//5 BANKS:

void banks()
{
  b = bankNumber;
  for (int k = 0; k < 6; k++)
  {
    if (keyPressed[k] == true && wahVal > 100)              //Check which button has been pressed. Don't change if wah pressed (for calibration).
    {
      MIDI.sendProgramChange(k + (b*6), 1);                 //Send a MIDI Program Change message (value, channel). Multiply bank No. by 6 (no. of preset footswitches) and add to k to get note.
      midiLedOn();                                          //Flash MIDI LED.

      activeLed = k;
      toggleLeds();                                         //Turn LEDs on/off for footswitch 1 active.
      printBluePreset();                                    //Reset preset names to blue
      presetChanged = false;

      activePreset = (k + (b*6));                           //The preset to return to later if preset mode is exited.
      printActivePreset();                                //Print active set of preset names with appropriate one highlighted in red.
      keyPressed[k] = false;                                //Return button state to false for debounce code.
    }
    lastActivePreset = activePreset;
  }
}

//Function to return to last active bank when toggling between looper/stomp and preset mode:

void return2lastBank()
{
  for (int b = 1; b < 5; b++)       //Increase number of banks here (optional)
  {
    if (b !=  (lastBank))
    {
      statusBank[b] = false;
      statusBank[lastBank] = true;
    }
  }
  stompStatus = false;

  bankNames();
}
