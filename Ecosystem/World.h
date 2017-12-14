#ifndef WORLD_H
#define WORLD_H

#include "Entity.h"
#include "Event.h"
#include "Faces.h"

// A class to represent the world, which basically comprises of an array of
// entities. Various events can happen that affect the entities in the world.

class World {

    private:
        Entity entities[8][16];

    public:
        byte getByte(int row, int col);
        void apply(Event &event);
};

#endif // WORLD_H

