#IntegerFun

This is an exploratory project to get familiar with the Arduino libraries, the
IDE and Arduino Create web environment. The aim of this project is to generate,
manimpulate and display integers in various ways.



###Hardware

The hardware for this project consists of an Arduino Nano, four 74HC595 8-bit
shift registers, 32 LEDs, 32 330 Ohm resistors and a button to switch among
the various software options. Each output pin of the 74HC595 connects to a 330
Ohm resistor and a LED so that a full 32-bit integer can be displayed.

Digital pins 6 (DATA\_PIN), 5 (LATCH\_PIN) and 4 (CLOCK\_PIN) of the Arduino
have been selected to drive all four 74HC595 serial-in, parallel-out registers.
An additional pin 3 (INPUT\_PIN) is connected to the button and then to ground.



###Software

All functionality is included in the IntegerFun.cpp file, which needs to be
compiled against the Arduino library. Once the Arduino boots up, all
aforementioned pins are set to the right state: OUTPUT for pins connected to
the registers and INPUT\_PULLUP for the pin connected to the button. The
ATmega328 will then continuously execute function loop() and sleep for a second
between successive executions.

