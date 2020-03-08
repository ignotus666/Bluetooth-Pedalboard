//BANK FUNCTIONS:

//BANK 1:

void bank1()
{
  for (int k = 0; k < 6; k++)
  {
    if (keyPressed[k] == true)      //Check which button has been pressed.
    {
      MIDI.sendProgramChange(k, 1); //Send a MIDI Program Change message (value, channel).
      midiLed();                    //Flash MIDI LED.

      activeLed = k;
      toggleLeds();                 //Turn LEDs on/off for footswitch 1 active.
      bank1Presets();               //Reset preset names to blue
      presetChanged = 0;

      activePreset = (k + 1);       //The preset to return to later if preset mode is exited.
      return2ActivePreset();        //Print active set of preset names with appropriate one highlighted in red.
      keyPressed[k] = false;        //Return button state to false for debounce code.
    }
  }
}

//BANK 2:

void bank2()
{
  for (int k = 0; k < 6; k++)
  {
    if (keyPressed[k] == true)
    {
      MIDI.sendProgramChange(k+6, 1);
      midiLed();

      activeLed = k;
      toggleLeds();
      bank2Presets();
      presetChanged = 0;

      activePreset = (k + 7);
      return2ActivePreset();
      keyPressed[k] = false;
    }
  }
}

//BANK 3:

void bank3()
{
  for (int k = 0; k < 6; k++)
  {
    if (keyPressed[k] == true)
    {
      MIDI.sendProgramChange(k+12, 1);
      midiLed();

      activeLed = k;
      toggleLeds();
      bank3Presets();
      presetChanged = 0;

      activePreset = (k+13);
      return2ActivePreset();
      keyPressed[k] = false;
    }
  }
}

//BANK 4:

void bank4()
{
  for (int k = 0; k < 6; k++)
  {
    if (keyPressed[k] == true)
    {
      MIDI.sendProgramChange(k+18, 1);
      midiLed();

      activeLed = k;
      toggleLeds();
      bank4Presets();
      presetChanged = 0;

      activePreset = (k+19);
      return2ActivePreset();
      keyPressed[k] = false;
    }
  }
}

//BANK 5:

void bank5()
{
  for (int k = 0; k < 6; k++)
  {
    if (keyPressed[k] == true)
    {
      MIDI.sendProgramChange(k+24, 1);
      midiLed();

      activeLed = k;
      toggleLeds();
      bank5Presets();
      presetChanged = 0;

      activePreset = (k+25);
      return2ActivePreset();
      keyPressed[k] = false;
    }
  }
}
