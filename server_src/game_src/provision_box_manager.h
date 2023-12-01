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

    BoxType get_random_box_type();

    bool has_boxes();

    void add_box(BoxType type, b2Vec2 position);

    void reap_boxes();

    // std::vector<BoxSnapshot> get_boxes_snapshot();

    

    ~BoxManager();

};

#endif //BOX_MANAGER_H