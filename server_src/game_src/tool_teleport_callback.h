#include <box2d/box2d.h>

#ifndef TELEPORT_RAYCAST_CALLBACK_H
#define TELEPORT_RAYCAST_CALLBACK_H
class TeleportRaycastCallback: public b2RayCastCallback {
    friend class Teleporter;
    bool hit = false;

    float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal,
                        float fraction);

    ~TeleportRaycastCallback();
};

#endif  // TELEPORT_RAYCAST_CALLBACK_H
