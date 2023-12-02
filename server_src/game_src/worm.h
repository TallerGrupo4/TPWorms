#ifndef WORM_H
#define WORM_H

#include <vector>
#include <unordered_map>
#include <box2d/box2d.h>

#include "../../common_src/constants.h"
#include "../../common_src/snapshot.h"
#include "game_constants.h"
#include "tool.h"
#include "projectile_manager.h"
#include "../config.h"
#include "entity.h"

#define WORM_SPEED ConfigSingleton::getInstance().get_worm_speed()
#define WORM_JUMP_SPEED ConfigSingleton::getInstance().get_worm_jump_speed()
#define WORM_JUMP_HOR_SPEED ConfigSingleton::getInstance().get_worm_jump_hor_speed()
#define WORM_BACKFLIP_SPEED ConfigSingleton::getInstance().get_worm_backflip_speed()
#define WORM_BACKFLIP_HOR_SPEED ConfigSingleton::getInstance().get_worm_backflip_hor_speed()
#define START_LIFE ConfigSingleton::getInstance().get_start_life()
#define NULL_STATE ConfigSingleton::getInstance().get_null_state()
#define INITIAL_WORMS_TURN ConfigSingleton::getInstance().get_initial_worms_turn()
#define TURN_TIME ConfigSingleton::getInstance().get_turn_time()




//INCLUDES DE ARMAS
#include "weapon_bazooka.h"
#include "weapon_mortar.h"
#include "weapon_green_grenade.h"
#include "weapon_red_grenade.h"
#include "weapon_banana.h"
#include "weapon_holy_grenade.h"
#include "weapon_dynamite.h"
#include "tool_bat.h"
#include "weapon_airstrike.h"
#include "tool_teleport.h"


class WormNotFound: public std::exception {
    const char* what() const noexcept override {
        return "The worm body is a null pointer";
    }
};


class Worm: public Entity {
    friend class WormComprobator;
    friend class Game;
    std::vector<std::shared_ptr<Tool>> tools;
    char id;
    int life;
    int state;
    int curr_tool;
    int act_dir;
    float last_still_angle;
    float last_y;
    int number_contacts;
    char team_id;
    float aiming_angle;
    bool has_used_tool;




public:
    Worm(b2Body* body, char id, char team_id);
    
    int get_id();

    int get_angle();

    void move(int dir);

    void jump (int dir);

    bool use_tool(int power, float x, float y, int tool, ProjectileManager& projectiles);

    void stop_aiming();

    void aim(int angle_inc, int direction);

    void change_tool(int scroll_direction);

    void store_tool();

    bool in_contact();

    int get_number_contacts();

    void add_contact();

    void remove_contact();
    
    void set_used_tool(bool value);

    WormSnapshot get_snapshot();

    int get_state();

    void set_state(int new_state);

    void set_last_still_angle(float angle);

    float last_angle();

    float get_last_y();

    void set_last_y(float y);

    void set_curr_tool(int new_tool);

    void apply_damage(int damage);

    void add_ammo(int ammo , TOOLS tool);

    void add_health(int health);
};

#endif  // WORM_H