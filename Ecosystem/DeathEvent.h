#ifndef DEATH_EVENT_H
#define DEATH_EVENT_H

#include "Arduino.h"
#include "Entity.h"
#include "Event.h"

// An event that involves the death of an entity in the world. A position is
// picked up at random and, if occupied, the entity that occupies it dies.

class DeathEvent : public Event {

    public:
        void apply(Entity entities[8][16]) {
            Entity &entity = entities[random(8)][random(16)];
            if (entity.isAlive()) entity.die();
        }
};

#endif // DEATH_EVENT_H

