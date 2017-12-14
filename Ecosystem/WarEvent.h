#ifndef WAR_EVENT_H
#define WAR_EVENT_H

#include "Arduino.h"
#include "Entity.h"
#include "Event.h"

// An event that involves entities fighting their neighbours in the world. War
// affects multiple positions picked at random. If those positions are occupied
// the entities that occupy them attempt to fight with their neighbours at west,
// east, north and south of the map.

class WarEvent : public Event {

    public:
        void apply(Entity entities[8][16]) {
            int battles = random(8 * 16);
            for (int i = 0; i < battles; i++) {

                int row = random(8);
                int col = random(16);
                Entity &fighter = entities[row][col];

                // West
                if (col > 0) {
                    Entity &enemy = entities[row][col - 1];
                    if (enemy.isAlive()) {
                        fighter.fight(enemy);
                        continue;
                    }
                }

                // East
                if (col < 15) {
                    Entity &enemy = entities[row][col + 1];
                    if (enemy.isAlive()) {
                        fighter.fight(enemy);
                        continue;
                    }
                }

                // North
                if (row > 0) {
                    Entity &enemy = entities[row - 1][col];
                    if (enemy.isAlive()) {
                        fighter.fight(enemy);
                        continue;
                    }
                }

                // South
                if (row < 7) {
                    Entity &enemy = entities[row + 1][col];
                    if (enemy.isAlive()) {
                        fighter.fight(enemy);
                        continue;
                    }
                }
            }
        }
};

#endif // WAR_EVENT_H

