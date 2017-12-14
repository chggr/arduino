#include "World.h"

byte World::getByte(int row, int col) {
    Entity &entity = entities[row][col / 8];
    return entity.getFace()[col % 8];
}

void World::apply(Event &event) {
    event.apply(entities);
}

