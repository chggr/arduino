#include "Arduino.h"
#include "BirthEvent.h"
#include "DeathEvent.h"
#include "Event.h"
#include "EventGenerator.h"
#include "PlagueEvent.h"
#include "WarEvent.h"

Event* EventGenerator::generate() {
    byte temp = random(100);

    if (temp < 40) {
        return new BirthEvent();
    } else if (temp < 80) {
        return new DeathEvent();
    } else if (temp < 95) {
        return new WarEvent();
    } else {
        return new PlagueEvent();
    }
}

