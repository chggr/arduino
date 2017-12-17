# SpectrumAnalyzer

In this project we are building a device that can be used to visualize the
sound waves that are produced by a sound source before they reach our ears.
The device intercepts the sound signal travelling from a sound source (radio,
mp3 player, PC) to our speakers or headphones, analyzes it and displays its
spectrum or wave plot in an OLED screen.



### Hardware

The hardware for this project consists of the following components: an Arduino
Nano, a small 128x64 SSD1306 OLED screen, an LM358P dual Operational Amplifier
chip, four 10 KOhm variable resistors, two 1 uF electrolytic capacitors, two
3\.5 mm stereo jack connectors and a button.

The two 3\.5 mm stereo jack connectors are connected in parallel, so that the
sound signal that is received as input will be replayed verbatim at the output.
A 1 uF capacitor is connected to the left and right channel so that the device
picks up only the AC part of the signal for further amplification and analysis.

The AC signal will of course vary over time and it can span both positive and
negative voltages. The Operational Amplifier chip that has been chosen (LM358P)
works only with positive voltages and therefore we need to introduce a DC bias
to our AC signal to ensure all of it is on the positive voltage range. Moreover
we need to be able to control the level of DC bias and increase it or decrease
it according to the volume of the sound. This is done by connecting a variable
resistor to Vcc and GND and using its middle pin as the DC bias. The user can
alter the potentiometer for each channel as required to ensure enough DC bias
is present so that the full signal is on the positive voltage range.



### Software



### Gallery

Pictures to follow...

