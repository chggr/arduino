#ifndef ENTITY_H
#define ENTITY_H

#include "Faces.h"

// A class that represents an entity in the Ecosystem. Each entity has a face,
// defined in Faces.h, and the following attributes: strength, intelligence,
// dexterity and constitution. All these attributes are stored as integers and
// will be used to determine which entity wins a fight. An entity can be in
// three states: empty, alive or dead.

class Entity {

    private:
        byte* face;
        byte stren;
        byte intel;
        byte dext;
        byte cons;

    public:
        Entity() { empty(); };

        void empty();
        bool isEmpty() { return face == FACE_EMPTY; };

        void die() { face = FACE_DEAD; };
        bool isDead() { return face == FACE_DEAD; };

        bool isAlive() { return !isEmpty() && !isDead(); };

        void setFace(byte* value) { face = value; };
        void setStren(byte value) { stren = value; };
        void setIntel(byte value) { intel = value; };
        void setDext(byte value) { dext = value; };
        void setCons(byte value) { cons = value; };

        byte* getFace() { return face; };

        void fight(Entity& other);
};

#endif // ENTITY_H

