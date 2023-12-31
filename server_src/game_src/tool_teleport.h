#include "tool.h"

#ifndef TELEPORTER_H
#define TELEPORTER_H

class Teleporter: public Tool {
    bool validate_teleport(float x, float y, b2World* world);

public:
    Teleporter();

    bool use(b2Body* worm, int direction, float angle, int time, int power, float x, float y,
             ProjectileManager& projectiles) override;

    ~Teleporter();
};

#endif  // TELEPORTER_H
