#include "Arduino.h"
#include "OledDisplay.h"
#include "World.h"

World world;
OledDisplay oled;

void setup() {
    oled.init();
}

void loop() {
    oled.display(world);
    delay(10000);
}

