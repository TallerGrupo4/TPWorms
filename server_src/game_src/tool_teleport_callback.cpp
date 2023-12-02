#include "tool_teleport_callback.h"


float TeleportRaycastCallback::ReportFixture(b2Fixture* fixture , const b2Vec2& point , const b2Vec2& normal , float fraction){
    b2Body* body = fixture->GetBody();
    if (body->GetType() == b2_staticBody){
        hit = true;
    }
    return 1;
}

TeleportRaycastCallback::~TeleportRaycastCallback(){}

