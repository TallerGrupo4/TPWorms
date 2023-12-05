#ifndef PLATFORM_SNAPSHOT_H
#define PLATFORM_SNAPSHOT_H

#include "../server_src/config.h"
#include "../server_src/game_src/game_constants.h"
#include "./constants.h"


class PlatformSnapshot {
public:
    BeamType type;
    float pos_x;
    float pos_y;
    float width;
    float height;

    PlatformSnapshot(BeamType type, float pos_x, float pos_y, float width, float height):
            type(type), pos_x(pos_x), pos_y(pos_y), width(width), height(height) {}


    PlatformSnapshot(BeamType type, float pos_x, float pos_y):
            type(type), pos_x(pos_x), pos_y(pos_y), width(PLAT_SMALL), height(PLAT_HEIGHT) {
        if (type <= 8) {
            width = PLAT_BIG;
        }
        if (type == LargeVertical || type == LargeVerticalFlipped || type == ShortVertical ||
            type == ShortVerticalFlipped) {
            height = PLAT_SMALL;
            width = PLAT_HEIGHT;
        }
    }
    ~PlatformSnapshot() {}
};

#endif  // PLATFORM_SNAPSHOT_H
