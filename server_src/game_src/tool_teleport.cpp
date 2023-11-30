#include "tool_teleport.h"
#include "tool_teleport_callback.h"


Teleporter::Teleporter(): Tool(TELEPORTATION, -1, false, -1) {}

bool Teleporter::validate_teleport(float x , float y, b2World* world){
    for (int i =0 ; i < 32 ; i++){
        float angle = (i/(float)32) * 360 * DEGTORAD;
        b2Vec2 direction = b2Vec2(sin(angle), cos(angle));
        b2Vec2 endPos = b2Vec2(x + 1* direction.x, y + 1 * direction.y);

        TeleportRaycastCallback callback;
        world->RayCast(&callback, b2Vec2(x, y), endPos);
        if (callback.hit){
            return false;
            }
    }
    return true;
}

void Teleporter::use(b2Body* worm, int direction, float angle, int time , int power , float x , float y, std::unordered_set<std::shared_ptr<Projectile>>& projectiles){
        printf("Teleporting\n");
        printf("x: %f, y: %f\n", x, y);
        if (!validate_teleport(x, y +PLAT_HEIGHT+0.2, worm->GetWorld() ) && !validate_teleport(x, y - PLAT_HEIGHT - 0.2, worm->GetWorld())){
            return;
        }
        printf("Teleporting for real\n");
        worm->SetTransform(b2Vec2(x, y), 0);
        worm->SetAwake(true);
        worm->SetLinearVelocity(b2Vec2(0, 0));
        worm->SetAngularVelocity(0);
}

Teleporter::~Teleporter() {}