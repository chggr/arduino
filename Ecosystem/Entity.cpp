#include "Entity.h"

// Empties this entity, setting everything to default values.
void Entity::empty() {
    face = FACE_EMPTY;
    stren = 0;
    intel = 0;
    dext = 0;
    cons = 0;
}

// This entity fights another entity. The winner is the entity that has the
// best attributes. The loser will die as a result of the battle.
void Entity::fight(Entity &other) {
    int score = 0;
    score += stren - other.stren;
    score += intel - other.intel;
    score += dext - other.dext;
    score += cons - other.cons;

    if (score > 0) other.die();
    else if (score < 0) die();
}

