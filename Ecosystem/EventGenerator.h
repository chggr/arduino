#ifndef EVENT_GENERATOR_H
#define EVENT_GENERATOR_H

#include "Event.h"

// Generates events that affect the world and the entities within it.

class EventGenerator {

    public:
        Event* generate();
};

#endif // EVENT_GENERATOR_H

