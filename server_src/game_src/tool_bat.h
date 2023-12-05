#include "tool.h"

#ifndef BAT_H
#define BAT_H

class Bat: public Tool {
    int damage;

public:
    Bat();
    bool use(b2Body* worm, int direction, float angle, int time, int power, float x, float y,
             ProjectileManager& projectiles) override;
    ~Bat();
};

#endif  // BAT_H
