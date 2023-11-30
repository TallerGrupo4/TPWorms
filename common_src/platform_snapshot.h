#ifndef PLATFORM_SNAPSHOT_H
#define PLATFORM_SNAPSHOT_H

#include "./constants.h"
#include "../server_src/config.h"
#define WORM_WIDTH ConfigSingleton::getInstance().get_worm_width()
#define WORM_HEIGHT ConfigSingleton::getInstance().get_worm_height()
#define PLAT_SMALL ConfigSingleton::getInstance().get_plat_small()
#define PLAT_HEIGHT ConfigSingleton::getInstance().get_plat_height()

class PlatformSnapshot {
public:
    BeamType type;
    float pos_x;
    float pos_y;
    float width;
    float height;


    PlatformSnapshot(BeamType type, float pos_x, float pos_y, float width = PLAT_SMALL, float height = PLAT_HEIGHT):
            type(type), pos_x(pos_x), pos_y(pos_y), width(width), height(height) {};
    ~PlatformSnapshot(){};
};

#endif //PLATFORM_SNAPSHOT_H
