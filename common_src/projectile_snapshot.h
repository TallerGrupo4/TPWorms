#ifndef __PROJECTILE_SNAPSHOT_H__
#define __PROJECTILE_SNAPSHOT_H__

class ProjectileSnapshot {
    public:
    char type;
    float pos_x;
    float pos_y;
    float angle;
    int direction;
    int state;
    char id;
    int explosion_type;
    float radius;
    int width;
    int height;

    ProjectileSnapshot(int type, float pos_x, float pos_y, float angle, int direction, float radius , int state, char id, int explosion_type, int width = 0, int height = 0):
            type(type), pos_x(pos_x), pos_y(pos_y), angle(angle), direction(direction), state(state), id(id), explosion_type(explosion_type), radius(radius), width(width), height(height) {};

};

#endif //__PROJECTILE_SNAPSHOT_H__
