#include "World.h"

// Used to display the world in an OLED screen.
byte World::getByte(int row, int col) {
    Entity &entity = entities[row][col / 8];
    return entity.getFace()[col % 8];
}

// Applies an event to the world.
void World::apply(Event &event) {
    event.apply(entities);
}

// Cleans up dead entities.
void World::cleanup() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 16; j++) {
            Entity &entity = entities[i][j];
            if (entity.isDead()) entity.empty();
        }
    }
}

