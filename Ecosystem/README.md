# Ecosystem

In this project we are building a small electronic ecosystem within an Arduino
board and use an OLED screen to display its status. The world comprises of
multiple entities / species that are independently born and fight both each
other and the elements to survive.



### Hardware

The hardware build is very straight forward and involves soldering together
an Arduino Nano and a small 128x64 SSD1306 OLED display. This display uses
the I2C protocol (Inter-Integrated Circuit) to receive data from the Arduino
board via just two pins: SDA for data and SCL for the clock. The OLED screen
has four pins in total that need to be connected as follows: VCC to 5V, GND to
GND, SDA to A4 and SCL to A5. That's it, there are no further components
required for this build.



### Software

The software is a bit more challenging and consists of multiple C++ classes
that are used to model various concepts within the ecosystem. The entry point
is Ecosystem.cpp, which contains the Arduino setup() and loop() methods. It
also creates three main objects: the world, a random event generator and the
OLED screen driver. Read on for more details on how these classes work.

The setup() method initiates the random number generator by reading some noise
on analog pin 0 and using it as a seed to the generator. This ensures that each
run of the software will be truly different compared to previous runs. It also
initializes the OLED screen and finally displays the current state of the
world, which at this point is totally empty.

The loop() method generates random events that might affect the world, applies
them onto it and finally displays the new state on the OLED screen. There is an
initial delay of a random amount of time up to one second. Then a random event
is generated and applied to the world. At this point the world has changed and
there might be entities that have been born or have died. Therefore any dead
entities will need to be cleaned up before repeating the loop again.



### Gallery

Pictures to follow...

