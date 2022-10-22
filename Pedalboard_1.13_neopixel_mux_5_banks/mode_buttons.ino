void modeButtons()
{ 
  int l = 0;
  
  //Short press: Stomp mode. Long: PC note for tuner.
  if (keyPressed[6])
  {
    if (button7Active == false)
    {
      button7Active = true;
      buttonTimer = millis();
    }

    if ((millis() - buttonTimer > longPressTime) && (longPress7Active == false))  //Long press.
    {
      MIDI.sendControlChange(120, 127, 1);
      tunerOn = !tunerOn;
      longPress7Active = true;
      ledFlash();

      if ((loopModeStatus == false) && (stompModeStatus == false))
      {
        presetModeLeds();

        if (presetChanged == false) //If bank buttons have been pressed, it's presumed the last active preset is no longer active; if not, it's still active.
        {
          leds[lastLed] = CRGB::Red;
          FastLED.show();
        }
      }

      if (stompModeStatus == true)
      {
        for (l = 0; l < 6; l++)
        {
          leds[l] = CRGB::Green;
          leds[l].nscale8(15);
          leds[7] = CRGB(196, 67, 247);
          leds[7].nscale8(15);
          FastLED.show();
        }
        leds[6] = CRGB::Blue;
        FastLED.show();

        for (int s = 0; s < 6; s++)
        {
          if (stompButtonState[s] == true)
          {
            leds[s] = CRGB::DarkMagenta;
            FastLED.show();
          }
        }
      }

      if (loopModeStatus == true)
      {
        for (l = 0; l < 6; l++)
        {
          leds[l] = CRGB::DarkViolet;
          leds[l].nscale8(15);
          leds[6] = CRGB::Green;
          leds[6].nscale8(15);
          FastLED.show();
        }
        leds[7] = CRGB::Blue;
        FastLED.show();

        if (ledStatus[2] = CRGB::Green)
        {
          leds[2] = ledStatus[2];
          FastLED.show();
        }
      }

      if (tunerOn == true)
      {
        tft.drawImage(tuner, 195, 192, tunerWidth, tunerHeight);
      }

      if (tunerOn == false)
      {
        tft.fillRect(195, 192, 25, 27, ILI9341_BLACK);
      }
    }
  }

  else
  {
    if (button7Active == true)
    {
      if (longPress7Active == true)
      {
        longPress7Active = false;
      }

      else
      {
        stompActive();                                                    //Short. Toggle between preset/stomp modes.
      }

      button7Active = false;
    }
  }

  
  //Short press: looper mode. Long = PC note for mute/unmute.  
  
  if (keyPressed[7])
  {
    if (button8Active == false)
    {
      button8Active = true;
      buttonTimer = millis();
    }

    if ((millis() - buttonTimer > longPressTime) && (longPress8Active == false)) //Long press. Only works in preset mode.
    {
      MIDI.sendControlChange(121, 127, 1);
      muteOn = !muteOn;
      longPress8Active = true;
      ledFlash();

      if ((loopModeStatus == false) && (stompModeStatus == false))
      {
        presetModeLeds();

        if (presetChanged == false) //If bank buttons have been pressed, it's presumed the last active preset is no longer active; if not, it's still active.
        {
          leds[lastLed] = CRGB::Red;
          FastLED.show();
        }
      }

      if (stompModeStatus == true)
      {
        for (l = 0; l < 6; l++)
        {
          leds[l] = CRGB::Green;
          leds[l].nscale8(15);
          leds[7] = CRGB(196, 67, 247);
          leds[7].nscale8(15);
          FastLED.show();
        }
        leds[6] = CRGB::Blue;
        FastLED.show();

        for (int s = 0; s < 6; s++)
        {
          if (stompButtonState[s] == true)
          {
            leds[s] = CRGB::DarkMagenta;
            FastLED.show();
          }
        }
      }

      if (loopModeStatus == true)
      {
        for (l = 0; l < 6; l++)
        {
          leds[l] = CRGB::DarkViolet;
          leds[l].nscale8(15);
          leds[6] = CRGB::Green;
          leds[6].nscale8(15);
          FastLED.show();
        }
        leds[7] = CRGB::Blue;
        FastLED.show();

        if (playLedOn == true && loopModeStateInit == true)
        {
          leds[2] = CRGB::Green;
          FastLED.show();
        }
      }

      if (muteOn == true)
      {
        tft.fillRoundRect(73, 189, 50, 18, 3, ILI9341_RED);
        tft.drawRoundRect(72, 188, 52, 20, 3, ILI9341_WHITE);
        tft.setFontMode(gTextFontModeTransparent);
        tft.setTextColor(ILI9341_WHITE);
        tft.setTextScale(1);
        tft.printAt("MUTE", 78, 192);
      }

      if (muteOn == false)
      {
        tft.fillRect(72, 188, 52, 20, ILI9341_BLACK);
      }
    }
  }

  else
  {
    if (button8Active == true)
    {
      if (longPress8Active == true)
      {
        longPress8Active = false;
      }

      else
      {
        loopActive();                                                    //Short. Toggle between preset/looper modes.
      }
      button8Active = false;
    }
  }
}
