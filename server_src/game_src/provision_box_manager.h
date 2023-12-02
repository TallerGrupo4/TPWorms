#include "provisionBox.h"
#include <box2d/box2d.h>

#ifndef BOX_MANAGER_H
#define BOX_MANAGER_H

class BoxManager {
private:
    std::list<std::shared_ptr<ProvisionBox>> boxes;
    int box_id;

    public:

    BoxManager();

    std::shared_ptr<ProvisionBox> get_random_box_type(b2Body* body);

    bool has_boxes();

    void add_box(b2Body* body);

    void reap_boxes(b2World& world);

    bool position_is_free(b2Vec2 position, b2World& world);

    std::vector<ProvisionBoxSnapshot> get_boxes_snapshot();

    

    ~BoxManager();

};

#endif //BOX_MANAGER_H