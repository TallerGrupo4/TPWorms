#include "provision_box_callback.h"  
    
bool ProvisionBoxCallback::ReportFixture(b2Fixture* fixture){
    Entity* entity = reinterpret_cast<Entity*>(fixture->GetBody()->GetUserData().pointer);
    if (entity->get_type() == WORM || entity->get_type() == PROVISION_BOX){
        count++;
    }
    return true;
}

ProvisionBoxCallback::~ProvisionBoxCallback(){}