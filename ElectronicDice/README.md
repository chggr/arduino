# ElectronicDice

This is an easy and fun project to make, using Arduino and its random number
generator library to replace physical dice with your own electronic dice. Dice
are used in almost all board games, so this project has many practical uses.



### Hardware

The hardware for this project consists of an Arduino Nano, two 74HC595 8-bit
shift registers, 7 green LEDs, 7 red LEDs, 14 200 Ohm resistors and a button to
trigger rolling the dice.

Each dice consists of 7 LEDs, 7 200 Ohm resistors and one 74HC595 8-bit shift
register. The cathode of all LEDs needs to be connected to ground and the anode
to a 200 Ohm resistor and then to an output pin of the shift register. Only
seven out of eight output pins of 74HC595 are used (Q\_A is left unconnected).

Both dice are controlled by an Arduino Nano. Digital pins 10 (DATA\_PIN\_A), 11
(LATCH\_PIN\_A) and 12 (CLOCK\_PIN\_A) drive the 74HC595 of the first dice and
digital pins 2 (DATA\_PIN\_B), 3 (LATCH\_PIN\_B) and 4 (CLOCK\_PIN\_B) drive the
74HC595 of the second dice. An additional pin 5 (INPUT\_PIN) is connected to the
button and then to ground.

 

### Software

The logic is quite simple and is included in the ElectronicDice.cpp file, which
needs to be compiled against the Arduino library. Once the Arduino boots up,
all aforementioned pins are set to the correct state: OUTPUT for digital pins
connected to the registers and INPUT\_PULLUP for the pin connected to the
button. Additionally the random number generator is seeded with noise picked up
by reading analog pin 0. This step is necessary to ensure that rolling the dice
is as random as possible and the same numbers are not repeated after the micro
controller reboots. Finally all dice LEDs are initialized to remain switched
off and ready for first use.

In each loop execution, ATmega328 will check whether the user has pressed the
button to roll the dice. If the button has not been pressed, no action is
required and thus the micro controller sleeps for 100 ms. On the contrary, if
the input button is pressed, the micro controller needs to roll the dice. At
first, a random number between 30 and 50 inclusive is generated. This controls
how many times the dice values are going to change before settling on the final
number. The micro controller sleeps for 100 ms after each value change, which
produces a nice visual effect to the user. For three to five seconds the dice
rapidly and randomly change before settling to a final number.

