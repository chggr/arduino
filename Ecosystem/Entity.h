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
        int stren;
        int intel;
        int dext;
        int cons;

    public:
        Entity() { empty(); };

        void empty();
        bool isEmpty() { return face == FACE_EMPTY; };

        void die() { face = FACE_DEAD; };
        bool isDead() { return face == FACE_DEAD; };

        bool isAlive() { return !isEmpty() && !isDead(); };

        void setFace(byte* value) { face = value; };
        void setStren(int value) { stren = value; };
        void setIntel(int value) { intel = value; };
        void setDext(int value) { dext = value; };
        void setCons(int value) { cons = value; };

        byte* getFace() { return face; };

        void fight(Entity& other);
};

#endif // ENTITY_H

