//BANK FUNCTIONS:

//BANK 1:

void bank1()
{
  //Footswitch code:

  //Footswitch 1:
  if (key1Pressed)  // Check if button has been pressed.
  {
    MIDI.sendProgramChange(0, 1); // send a MIDI Program Change message (value, channel).
    midiLed();

    foot1();//Turn LEDs on/off for footswitch 1 active.
    bank1Presets();  //Reset preset names to blue

    activePreset = 1;
    return2ActivePreset();//Print active set of preset names with appropriate one highlighted in red.
    key1Pressed = false;
  }

  //For footswitch 2:
  if (key2Pressed)
  {
    MIDI.sendProgramChange(1, 1); //see above
    midiLed();

    foot2();
    bank1Presets();

    activePreset = 2;
    return2ActivePreset();
    key2Pressed = false;
  }

  //Footswitch 3:
  if (key3Pressed)
  {
    MIDI.sendProgramChange(2, 1); //etc...
    midiLed();

    foot3();
    bank1Presets();

    activePreset = 3;
    return2ActivePreset();
    key3Pressed = false;
  }

  //For footswitch 4:
  if (key4Pressed)
  {
    MIDI.sendProgramChange(3, 1);
    midiLed();

    foot4();
    bank1Presets();

    activePreset = 4;
    return2ActivePreset();
    key4Pressed = false;
  }

  //For footswitch 5:
  if (key5Pressed)
  {
    MIDI.sendProgramChange(4, 1);
    midiLed();

    foot5();

    bank1Presets();
    activePreset = 5;
    return2ActivePreset();
    key5Pressed = false;
  }

  //For footswitch 6:
  if (key6Pressed)
  {
    MIDI.sendProgramChange(5, 1);
    midiLed();

    foot6();
    bank1Presets();

    activePreset = 6;
    return2ActivePreset();
    key6Pressed = false;
  }
}

//BANK 2:

void bank2()
{
  if (key1Pressed)
  {
    MIDI.sendProgramChange(6, 1);
    midiLed();

    foot1();
    bank2Presets();

    activePreset = 7;
    return2ActivePreset();
    key1Pressed = false;
  }

  if (key2Pressed)
  {
    MIDI.sendProgramChange(7, 1);
    midiLed();

    foot2();
    bank2Presets();

    activePreset = 8;
    return2ActivePreset();
    key2Pressed = false;
  }

  if (key3Pressed)
  {
    MIDI.sendProgramChange(8, 1);
    midiLed();

    foot3();
    bank2Presets();

    activePreset = 9;
    return2ActivePreset();
    key3Pressed = false;
  }

  if (key4Pressed)
  {
    MIDI.sendProgramChange(9, 1);
    midiLed();

    foot4();
    bank2Presets();

    activePreset = 10;
    return2ActivePreset();
    key4Pressed = false;
  }

  if (key5Pressed)
  {
    MIDI.sendProgramChange(10, 1);
    midiLed();

    foot5();
    bank2Presets();
    activePreset = 11;
    return2ActivePreset();
    key5Pressed = false;
  }

  if (key6Pressed)
  {
    MIDI.sendProgramChange(11, 1);
    midiLed();

    foot6();
    bank2Presets();

    activePreset = 12;
    return2ActivePreset();
    key6Pressed = false;
  }
}

//BANK 3:

void bank3()
{
  if (key1Pressed)
  {
    MIDI.sendProgramChange(12, 1);
    midiLed();

    foot1();
    bank3Presets();

    activePreset = 13;
    return2ActivePreset();
    key1Pressed = false;
  }

  if (key2Pressed)
  {
    MIDI.sendProgramChange(13, 1);
    midiLed();

    foot2();
    bank3Presets();

    activePreset = 14;
    return2ActivePreset();
    key2Pressed = false;
  }

  if (key3Pressed)
  {
    MIDI.sendProgramChange(14, 1);
    midiLed();

    foot3();
    bank3Presets();

    activePreset = 15;
    return2ActivePreset();
    key3Pressed = false;
  }

  if (key4Pressed)
  {
    MIDI.sendProgramChange(15, 1);
    midiLed();

    foot4();
    bank3Presets();

    activePreset = 16;
    return2ActivePreset();
    key4Pressed = false;
  }

  if (key5Pressed)
  {
    MIDI.sendProgramChange(16, 1);
    midiLed();

    foot5();
    bank3Presets();

    activePreset = 17;
    return2ActivePreset();
    key5Pressed = false;
  }

  if (key6Pressed)
  {
    MIDI.sendProgramChange(17, 1);
    midiLed();

    foot6();
    bank3Presets();

    activePreset = 18;
    return2ActivePreset();
    key6Pressed = false;
  }
}

//BANK 4:

void bank4()
{
  if (key1Pressed)
  {
    MIDI.sendProgramChange(18, 1);
    midiLed();

    foot1();
    bank4Presets();

    activePreset = 19;
    return2ActivePreset();
    key1Pressed = false;
  }

  if (key2Pressed)
  {
    MIDI.sendProgramChange(19, 1);
    midiLed();

    foot2();
    bank4Presets();

    activePreset = 20;
    return2ActivePreset();
    key2Pressed = false;
  }

  if (key3Pressed)
  {
    MIDI.sendProgramChange(20, 1);
    midiLed();

    foot3();
    bank4Presets();

    activePreset = 21;
    return2ActivePreset();
    key3Pressed = false;
  }

  if (key4Pressed)
  {
    MIDI.sendProgramChange(21, 1);
    midiLed();

    foot4();
    bank4Presets();

    activePreset = 22;
    return2ActivePreset();
    key4Pressed = false;
  }

  if (key5Pressed)
  {
    MIDI.sendProgramChange(22, 1);
    midiLed();

    foot5();
    bank4Presets();

    activePreset = 23;
    return2ActivePreset();
    key5Pressed = false;
  }

  if (key6Pressed)
  {
    MIDI.sendProgramChange(23, 1);
    midiLed();

    foot6();
    bank4Presets();

    activePreset = 24;
    return2ActivePreset();
    key6Pressed = false;
  }
}

//BANK 5:

void bank5()
{
  if (key1Pressed)
  {
    MIDI.sendProgramChange(24, 1);
    midiLed();

    foot1();
    bank5Presets();

    activePreset = 25;
    return2ActivePreset();
    key1Pressed = false;
  }

  if (key2Pressed)
  {
    MIDI.sendProgramChange(25, 1);
    midiLed();

    foot2();
    bank5Presets();

    activePreset = 26;
    return2ActivePreset();
    key2Pressed = false;
  }

  if (key3Pressed)
  {
    MIDI.sendProgramChange(26, 1);
    midiLed();

    foot3();
    bank5Presets();

    activePreset = 27;
    return2ActivePreset();
    key3Pressed = false;
  }

  if (key4Pressed)
  {
    MIDI.sendProgramChange(27, 1);
    midiLed();

    foot4();
    bank5Presets();

    activePreset = 28;
    return2ActivePreset();
    key4Pressed = false;
  }

  if (key5Pressed)
  {
    MIDI.sendProgramChange(28, 1);
    midiLed();

    foot5();
    bank5Presets();

    activePreset = 29;
    return2ActivePreset();
    key5Pressed = false;
  }

  if (key6Pressed)
  {
    MIDI.sendProgramChange(29, 1);
    midiLed();

    foot6();
    bank5Presets();

    activePreset = 30;
    return2ActivePreset();
    key6Pressed = false;
  }
}
