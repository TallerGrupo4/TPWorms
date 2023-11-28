#include "tool.h"

#ifndef TELEPORTER_H
#define TELEPORTER_H

class Teleporter: public Tool {
    bool validate_teleport(float x , float y, b2World* world);

    public:
    Teleporter();

    void use(b2Body* worm, int direction, float angle, int time , int power , float x , float y, std::unordered_set<std::shared_ptr<Projectile>>& projectiles);

    ~Teleporter();

};

#endif  // TELEPORTER_H
