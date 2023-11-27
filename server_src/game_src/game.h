#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <box2d/box2d.h>
#include "../../common_src/snapshot.h"
#include "../map.h"
#include "gamebuilder.h"
#include "worm.h"
#include "listeners.h"
#include "filter.h"
#include "team.h"
#include "projectile.h"



#ifndef GAME_H
#define GAME_H

class Game {
    float water_level;
    b2World world;
    GameBuilder builder;
    MyListener listener;
    MyFilter filter;
    std::vector<b2Vec2> spawn_points;
    std::map<uint8_t, Team> teams;
    std::unordered_set<std::shared_ptr<Projectile>> projectiles;
    int current_turn_player_id;
    int turn_time;
    int team_turn;
    bool turn_cleaning;
    int cleaning_time;

    void check_angles(Worm& w);

    void check_states(Worm& w);

    void check_velocities(Worm& w);

    void worm_comprobations();

    void projectiles_comprobations(int it);

    void manage_turn();

    void turn_clean_up();



public:
    Game();

    Snapshot start_and_send(Map& map, int number_of_players, std::map<char, std::vector<char>>& match_teams);

    void add_player(int current_id, int team_id , std::vector<b2Vec2>& spawn_points);

    void move_player(int id, int direction);

    void jump_player(int id , int direction);

    void player_use_tool(int id, int potency, float pos_x , float pos_y);

    void player_aim(int id, int increment, int direction);

    void player_change_tool(int id, int direction);

    void remove_army(char army_id);

    void print_current_state();

    void game_post_cleanup();

    void step(int it);

    Snapshot get_game_snapshot();

    ~Game();
};

#endif  // GAME_H