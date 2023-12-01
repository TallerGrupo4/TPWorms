// #include "provision_box_manager.h"
// #include "provisionBox_ammo.h"
// #include "provisionBox_heal.h"
// #include "provisionBox_trap.h"

// BoxManager::BoxManager(): box_id(0) {}

// std::shared_ptr<ProvisionBox> BoxManager::get_random_box_type(){
//     int random = rand() % 3;
//     switch (random){
//         case AMMO_BOX:
//             return std::make_shared<AmmoBox>(AmmoBox(box_id));
//         case HEALTH_BOX:
//             return std::shared_ptr<ProvisionBox>(new ProvisionBox(HEALTH_BOX, b2Vec2(0,0), box_id));
//         case TRAP_BOX:
//             return std::shared_ptr<ProvisionBox>(new ProvisionBox(BULLET_BOX, b2Vec2(0,0), box_id));
// }

// bool BoxManager::has_boxes(){
//     return !boxes.empty();

// }

// void BoxManager::add_box(BoxType type, b2Vec2 position){
//     std::shared_ptr<ProvisionBox> box(new ProvisionBox(type, position, box_id));
//     boxes.push_back(box);
//     box_id++;

// }

// void BoxManager::reap_boxes();

//     // std::vector<BoxSnapshot> get_boxes_snapshot();

    

//     ~BoxManager();