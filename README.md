# Bluetooth-Pedalboard
MIDI Pedalboard with Bluetooth communication.
Essentially the same project as in https://github.com/ignotus666/midi-pedalboard but with bluetooth capability added and all pots removed. I found that it's not at all practical to have to bend over to turn knobs... The code is almost the same, with the potentiometer code removed and some added for measuring the battery voltage and displaying it on the screen. There is no need for bluetooth-specific code. The main difference is in the hardware, with the addition of 2 bluetooth modules and a receiver circuit.

The bluetooth modules used are the HC-05; one for the transmitter and another for the receiver. In the pedalboard, the Tx output of the Arduino is fed to the Rx pin of a HC-05 (using a voltage divider to bring the 5v down to around 3.3v), bypassing the MIDI-USB circuit, which can now be left out or used for the receiver. The receiver consists of the MIDI-USB circuit used in the MIDI Pedalboard that is fed the serial data coming from a second HC-05 module (module Tx -> PIC18F2550 Rx, no voltage divider needed). The pedalboard is powered by an 18650 li-ion battery which has a charge/protection circuit and a DC-DC booster module to output a constant 5v for the Arduino. The battery + terminal is wired to an analog input in order to read its voltage and print the value on the screen, to know when it needs charging. This reading is smoothed using the AnalogSmooth library as otherwise it's quite erratic.

The signal path is as follows:

Arduino Tx -> Rx HC-05 emitter (slave) -> (((BT signal))) -> HC-05 receiver (master) Tx -> Rx PIC18F2550 (MIDI USB) -> PC

In order for the MIDI-bluetooth communication to work, a series of software changes need to made to the bluetooth modules, the PIC firmware and the MIDI library.

A small guide is included on what changes need to be made to the bluetooth modules and how to do them. Also included is the modified firmware for the PIC18F2550 in the receiver. Instructions on how to upload this firmware to the PIC if you don't have a programmer are included in the bluetooth_files folder. The other change needed is to the baud rate in the MIDI library. Open the 'midi_settings.h' file (in my case it's in /home/*username*/Arduino/libraries/arduino_midi_library-master/src/midi_settings.h) and in line 73 change the baudrate to 115200.

When the pedalboard is powered off, the line going from the battery + terminal to the analog pin should be cut off. I use a 2PDT switch to switch off power and also this line.

Li-ion batteries can be dangerous and should be handled with care. I take NO responsibility for anything bad happening. An alternative is to just use a small power bank to power the pedalboard and then you can leave out all the battery code and circuitry.
