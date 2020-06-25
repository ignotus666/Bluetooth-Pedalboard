# Bluetooth-Pedalboard
MIDI Pedalboard with Bluetooth communication based on an Arduino Mega.
It consists of 10 momentary footswitches, 9 LEDs, a hall-effect sensor (A1302) for the expression pedal, 2 x HC-05 bluetooth modules, a USB-MIDI circuit and a 2.4" ILI9341 TFT screen (with 5v to 3.3v logic level shifter). All switches are connected with external 10k pull down resistors. The Arduino pins for all the connected components are contained in the sketch but are really up to the user (except some TFT pins) and can be changed. I use a neodymium magnet for the A1302 sensor with a usable range of about 3 cm. It can be easily calibrated, explained below.

There is no bluetooth-specific code. There is one bluetooth module attached to the Aruino board and another in the PIC18F2550-based MIDI-USB receiver circuit connected at the PC via USB.

The bluetooth modules used are the HC-05; one for the transmitter and another for the receiver. In the pedalboard, the Tx output of the Arduino is fed to the Rx pin of a HC-05 (the emitter) using a voltage divider to bring the 5v down to around 3.3v. The receiver consists of a MIDI-USB circuit that is fed the serial data coming from a second HC-05 module (module Tx -> PIC18F2550 Rx, no voltage divider needed). The pedalboard is powered by an 18650 li-ion battery which has a charge/protection circuit and a DC-DC booster module to output a constant 5v for the Arduino. The battery + terminal is wired to an analog input in order to read its voltage and print the value on the screen, to know when it needs charging. This reading is smoothed using the AnalogSmooth library as otherwise it's quite erratic.

The signal path is as follows:

Arduino Tx -> Rx HC-05 emitter (slave) -> (((BT signal))) -> HC-05 receiver (master) Tx -> Rx PIC18F2550 (MIDI USB) -> PC

In order for the MIDI-bluetooth communication to work, a series of changes need to made to the bluetooth modules, the PIC firmware and the MIDI library.

A small guide is included on what changes need to be made to the bluetooth modules and how to do them. Also included is the modified firmware for the PIC18F2550 in the receiver. I've also included the zipped AnalogSmooth (modified), Arduino_MIDI (modified), marekburiak-ILI9341_due and ResponsiveAnalogRead libraries in a .zip folder so you just have to open that and then import them using the Arduino IDE. The marekburiak-ILI9341_due library folder has the images.h file included so the sketch picks it up. The MIDI library is the same as the standard available from the library manager but with the name changed so updates don't screw it up and revert it to the standard MIDI baud rate, as it's modified to use 115200.

When the pedalboard is powered off, the line going from the battery + terminal to the analog pin should be cut off. I use a 2PDT switch to switch off power and also this line.

Li-ion batteries can be dangerous and should be handled with care. I take NO responsibility for anything bad happening. An alternative is to just use a small power bank to power the pedalboard and then you can leave out all the battery code and circuitry.

FUNCTIONS:

The functions displayed on the screen are arranged so that they are in a position relative to the physical location of the footswitches, to identify what preset each switch activates, what stomp pedal it toggles or what loop function it operates when in each different mode.

Default mode when booting is 'Preset Mode'. You get 6 presets to choose from using the 'keyPressed[0]' to 'keyPressed[5]' switches. The 'keyPressed[6]' (Bank down) and 'keyPressed[7]' (Bank up) switches scroll through 5 preset banks (more can be added relatively easily; I just don't need that many), each with a set of 6 presets. This mode sends Program Change MIDI messages, each preset with its own note (from 0 to 29, channel 1).

<img src="https://user-images.githubusercontent.com/4263412/84315665-4920f080-ab6a-11ea-848f-3b2405ac3df0.jpg" width="30%"></img>  

When in preset mode, by long-pressing Bank Down (0.7 s) you can scroll through 3 different functions for the bank change buttons. In default mode they scroll through the pedalboard's banks (no MIDI sent). The next function sets them to send MIDI messages for 'Next Bank' and 'Previous Bank'. The last function sends MIDI messages for 'Next Preset' and 'Previous Preset'.

<img src="https://user-images.githubusercontent.com/4263412/84315668-49b98700-ab6a-11ea-80f0-90ec02b944c1.jpg" width="30%"></img> <img src="https://user-images.githubusercontent.com/4263412/84315669-4a521d80-ab6a-11ea-91d7-6fb915765abc.jpg" width="30%"></img>

By long-pressing Bank Up you can toggle between two different control numbers for the expression pedal; 0 for Wah and 1 for Volume. The display will show which is active.

The 'keyPressed[8]' (Stomp Mode) switch activates 'Stomp Mode'. You get 6 pedals that can be turned on and off using the 'keyPressed[0]' to 'keyPressed[5]' switches. When in 'Stomp Mode', the 'Bank up' and 'Bank down' switches can be used to raise and lower the volume. Each pedal switch sends a CC message that alternates between values 127 and 0, to turn pedals on and off.

<img src="https://user-images.githubusercontent.com/4263412/84315671-4aeab400-ab6a-11ea-87f8-3227ffdcc02c.jpg" width="30%"></img> 

The 'keyPressed[9]' (Loop Mode) switch activates 'Looper Mode'. You get 8 looper functions using the 'keyPressed[0]' to 'keyPressed[5]' switches and the 'Bank up' and 'Bank down' switches. These functions are for operating the Sooperlooper software. CC messages are used.

<img src="https://user-images.githubusercontent.com/4263412/84315661-48885a00-ab6a-11ea-8ec7-9e4e71c14083.jpg" width="30%"></img>

Pressing the 'Stomp Mode' or 'Loop Mode' switch again returns it to 'Preset Mode'.

It is possible to calibrate an expression pedal connected to A0 (change accordingly if using another input). By simultaneously pressing 'keyPressed[2]' and 'keyPressed[3]' (switches 3 and 4) it enters calibration mode and you have 5 seconds to move the pedal across its entire range. The min and max levels are stored in eeprom so calibration should only be needed once.

To change preset names, there are 2 arrays of names in the Pedalboard_x.xx_5_banks.ino file, in the global variables. The first array is for the small names printed relative to the button positions; keep these short or abbreviated so they fit. The second array is for the full name of the active preset printed large in the centre of the screen. Names are displayed centred in their position on the screen without the need to enter coordinates.
To increase the number of preset banks, Do a 'Find' (enable 'Search all sketch tabs') typing 'more banks' in the search field. This will take you to the lines that need modifications for more banks.

This video shows most of the functions: https://www.youtube.com/watch?v=eDRC17XOzQg&t=9s. Some aspects of the display have changed since.
