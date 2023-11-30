#ifndef WORM_SNAPSHOT_H
#define WORM_SNAPSHOT_H

class WormSnapshot {
public:
    char id;
    float pos_x;
    float pos_y;
    int angle;
    int max_health;
    int health;
    char direction;
    int weapon;
    int state;
    char team_id;
    int aiming_angle;


    WormSnapshot(char id, float pos_x, float pos_y, int angle, int max_health, int health, char direction, int weapon,
                 int state, char team_id, int aiming_angle):
            id(id),
            pos_x(pos_x),
            pos_y(pos_y),
            angle(angle),
            max_health(max_health),
            health(health),
            direction(direction),
            weapon(weapon),
            state(state), 
            team_id(team_id),
            aiming_angle(aiming_angle) {};
    ~WormSnapshot(){};
};

#endif //WORM_SNAPSHOT_H
