#ifndef BIRTH_EVENT_H
#define BIRTH_EVENT_H

#include "Arduino.h"
#include "Entity.h"
#include "Event.h"

// An event that involves the birth of a new entity in the world. A position in
// the world is picked up at random and, if empty, a new entity is initialized
// using random attribute values

class BirthEvent : public Event {

    public:
        void apply(Entity entities[8][16]) {
            Entity &entity = entities[random(8)][random(16)];
            if (! entity.isEmpty()) return;

            entity.setFace(FACES[random(FACES_LEN)]);
            entity.setStren(random(100));
            entity.setIntel(random(100));
            entity.setDext(random(100));
            entity.setCons(random(100));
        }
};

#endif // BIRTH_EVENT_H

