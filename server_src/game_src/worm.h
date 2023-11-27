#ifndef WORM_H
#define WORM_H

#include <vector>
#include <unordered_map>
#include <box2d/box2d.h>

#include "../../common_src/constants.h"
#include "../../common_src/snapshot.h"
#include "game_constants.h"
#include "tool.h"

//INCLUDES DE ARMAS
#include "weapon_bazooka.h"


class WormNotFound: public std::exception {
    const char* what() const noexcept override {
        return "The worm body is a null pointer";
    }
};


class Worm {
    friend class Game;
    b2Body* body;
    std::vector<std::shared_ptr<Tool>> tools;
    char id;
    int life;
    int state;
    int curr_tool;
    int act_dir;
    float last_still_angle;
    float last_y;
    int number_contacts;
    int type;
    char team_id;
    int aiming_angle;
    int time_for_curr_tool;
    bool has_used_tool;




public:
    Worm(b2Body* body, char id, char team_id);
    
    int get_id();

    int get_angle();

    void move(int dir);

    void jump (int dir);

    void use_tool(int power, float x, float y, std::unordered_set<std::shared_ptr<Projectile>>& projectiles);

    void aim(int angle_inc, int direction);

    void change_tool(int scroll_direction);

    void store_tool();

    bool in_contact();

    void add_contact();

    void remove_contact();
    
    void set_used_tool(bool value);

    WormSnapshot get_snapshot();

    int get_state();

    void set_state(int new_state);

    void set_last_still_angle(float angle);

    float last_angle();

    int get_type();

    float get_last_y();

    void set_last_y(float y);

    void set_curr_tool(int new_tool);

    void apply_damage(int damage);
};

#endif  // WORM_H