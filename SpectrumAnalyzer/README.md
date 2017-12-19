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

The LM358P chip contains two Operational Amplifiers that will be used to
amplify the biased AC signal from both right and left channels. This gain
stage is required in order to achieve much better and accurate sampling and
analog to digital conversion later on. Each OpAmp has been configured as a
non-inverting amplifier, to ensure that the signal at the output of this stage
is amplified but not inverted. The biased AC signals from both channels are fed
to the positive inputs of the OpAmps (pins 3 and 5) and two 10 kOhm variable
resistors are connected between the outputs (pins 1 and 7), the negative inputs
(pins 2 and 6) and GND. This allows users to vary the gain of this stage
independently for each channel by adjusting the corresponding potentiometer.

The biased and amplified AC signals are then fed to the Arduino Nano pins A0
and A1 for sampling and ADC (Analog to Digital Conversion). The small 128x64
SSD1306 OLED display uses the I2C protocol (Inter-Integrated Circuit) to
receive data from the Arduino via just two pins: SDA for data and SCL for the
clock. This screen has four pins in total that are connected as follows: Vcc to
5V, GND to GND, SDA to A4 and SCL to A5. Finally a small tactile switch is
connected between D12 and GND. This will be used to switch between the two
available modes: spectrum plot or wave plot.



### Software

The Arduino Nano continuously samples both right and left channels and uses
these samples to plot either a graph of the signal itself or a bar chart of
its frequency contents. The ATmega328 analog to digital converter (ADC) is
initialized so that the prescaler is set to 16. The micro controller's clock
speed is 16 MHz and a single AD conversion takes 13 clock cycles. This means
that the overall sampling frequency is 16 MHZ / (13 * 16) = 76923 KHz. This
sampling rate should be enough according to the Nyquist / Shannon theorem to
capture all frequencies within the human hearing range (20 Hz to 20 KHz).

Higher sampling rate allows capturing higher frequency content and also causes
the input buffer to fill up faster, thus helping achieve almost real-time
performance. Unfortunately prescaler values less than 16 should not be used,
as lower values (8, 4 and 2) are known to lead to significant analog to digital
conversion inaccuracies. Therefore the prescaler value chosen (16) is the best
compromise between high sampling rate but also accurate AD conversion.

The OledDisplay.cpp class is the driver for the SSD1306 OLED screen. It can be
used to initialize the display by sending all necessary commands according to
the initialization sequence described in the data sheet. Additionally the class
can be used to display either a plot of the samples that have been obtained for
each channel, or a bar chart of the frequency contents of the signal. The number
of columns and spacing between them is configurable.

The users can dynamically select which plot type they would like to display on
the OLED screen by pressing the tactile switch to alternate between modes of
operation. In every loop, the software will first take samples of both right
and left channels. According to the mode selected, it will either display a
plot of the samples themselves or a bar chart of the spectrum present in the
signal. A simple DFT (Discrete Fourier Transform) algorithm is used to
calculate each frequency component. This algorithm is easy to understand and
implement, but its runtime complexity is O(N^2). If this is not performant
enough, we can susbtitute DFT with FFT (Fast Fourier Transform). The later is
much more complex but significantly faster, with O(NlogN) runtime complexity.



### Gallery

Pictures to follow...

