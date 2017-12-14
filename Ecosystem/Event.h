#ifndef EVENT_H
#define EVENT_H

#include "Entity.h"

// Abstract class that should be implemented by concrete events that could
// happen in the ecosystem. Contains only a single method, to apply the event
// to the entities that exist in the world.

class Event {

    public:
        virtual void apply(Entity entities[8][16]) = 0;
};

#endif // EVENT_H

