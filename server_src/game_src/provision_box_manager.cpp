#include "provision_box_manager.h"

#include "provision_box_callback.h"

BoxManager::BoxManager(): box_id(0) {}


std::shared_ptr<ProvisionBox> BoxManager::get_random_box_type(b2Body* body) {
    int random = rand() % 3;
    switch (random) {
        case AMMO_BOX:
            return std::make_shared<ProvisionBox>(body, AMMO_BOX, box_id);
            break;

        case HEALTH_BOX:
            return std::make_shared<ProvisionBox>(body, HEALTH_BOX, box_id);
            break;

        default:
            return std::make_shared<ProvisionBox>(body, TRAP_BOX, box_id);
            break;
    }
}


bool BoxManager::has_boxes() { return !boxes.empty(); }


void BoxManager::add_box(b2Body* body) {
    std::shared_ptr<ProvisionBox> box = get_random_box_type(body);
    boxes.push_back(box);
    box_id++;
}

bool BoxManager::position_is_free(b2Vec2 position, b2World& world) {
    b2AABB aabb;
    aabb.lowerBound = b2Vec2(position.x - 2, position.y - 2);
    aabb.upperBound = b2Vec2(position.x + 2, position.y + 2);
    ProvisionBoxCallback callback;
    world.QueryAABB(&callback, aabb);
    return callback.count == 0;
}


void BoxManager::reap_boxes(b2World& world) {
    std::list<std::shared_ptr<ProvisionBox>> boxes_to_reap;
    for (auto it = boxes.begin(); it != boxes.end(); ++it) {
        if ((*it)->get_state() == PICKED) {
            boxes_to_reap.push_back(*it);
        }
    }
    for (auto it = boxes_to_reap.begin(); it != boxes_to_reap.end(); ++it) {
        world.DestroyBody((*it)->get_body());
        boxes.remove(*it);
    }
}

std::vector<ProvisionBoxSnapshot> BoxManager::get_boxes_snapshot() {
    std::vector<ProvisionBoxSnapshot> boxes_snapshot;
    for (auto it = boxes.begin(); it != boxes.end(); ++it) {
        boxes_snapshot.push_back((*it)->get_snapshot());
    }
    return boxes_snapshot;
}


BoxManager::~BoxManager() {}
