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

The World class represents the place where entities are born, live and
eventually die. It is implemented as a simple 16x8 matrix of entities. Each
entity requires an 8x8 pixel block to be displayed, thus the world can contain
a maximum of (128 / 8) * (64 / 8) = 16 * 8 = 128 entities. Various types of
events can be applied to the world that cause entities to be born, to fight each
other and die. After each event, the cleanup() method needs to be called to
ensure any dead entities are removed from the world.

Each entity has a face and four attributes (strength, intelligence, dexterity
and constitution) that affect how successful it will be when fighting others.
There are ten possible faces (defined in Faces.h) and two additional faces to
represent empty space in the world (FACE\_EMPTY) and a dead entity (FACE\_DEAD).
A face is assigned to each entity at random upon birth. When an entity dies,
its face automatically changes to FACE\_DEAD.

There currently four events that can affect the entities living in the world:
1. **Birth**: A new entity is born at a random position, its face and
attributes are randomly chosen.
2. **Death**: Death strikes at a random position, causing any entity that
occupies it to die immediately.
3. **War**: War affects multiple positions in the world. Entities in those
positions attempt to fight with one of their neighbours. At the end of each
fight the weakest entity dies.
4. **Plague**: Plague affects multiple positions and causes any entities that
occupy them to die immediately.

Of course more events like these can be added in the future, to make the
simulation more interesting. The EventGenerator.cpp class is responsible for
generating these events at random and controlling the frequency of each event
type.

Finally, the OledDisplay.ccp class is the driver for the SSD1306 OLED display.
It sends all necessary commands to initialize the screen as per data sheet. It
is also used to display the world and the faces of all entities living within
it.



### Gallery

Pictures to follow...

