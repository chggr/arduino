#include "Arduino.h"
#include "Event.h"
#include "EventGenerator.h"
#include "OledDisplay.h"
#include "World.h"

World world;
OledDisplay oled;
EventGenerator generator;

void setup() {
    randomSeed(analogRead(0));

    oled.init();
    oled.display(world);
}

void loop() {
    delay(random(1000));

    Event* event = generator.generate();
    world.apply(&event);
    delete event;
    oled.display(world);

    delay(200);
    world.cleanup();
    oled.display(world);
}

