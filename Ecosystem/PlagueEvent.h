#ifndef PLAGUE_EVENT_H
#define PLAGUE_EVENT_H

#include "Arduino.h"
#include "Entity.h"
#include "Event.h"

// An event that involves the death of multiple entities in the world. The
// plague will affect multiple positions picked at random. If those positions
// are occupied, the entities that occupy them die.

class PlagueEvent : public Event {

    public:
        void apply(Entity entities[8][16]) {
            int victims = random(8 * 16);
            for (int i = 0; i < victims; i++) {
                Entity &entity = entities[random(8)][random(16)];
                if (entity.isAlive()) entity.die();
            }
        }
};

#endif // PLAGUE_EVENT_H

