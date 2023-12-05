#include <map>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <box2d/box2d.h>

#include "../../common_src/snapshot.h"
#include "../map.h"

#include "filter.h"
#include "gamebuilder.h"
#include "listeners.h"
#include "projectile_manager.h"
#include "provision_box_manager.h"
#include "team.h"
#include "worm.h"
#include "worm_comprobator.h"


#ifndef GAME_H
#define GAME_H

class Game {
    int water_level;
    b2World world;
    int height;
    int width;
    GameBuilder builder;
    MyListener listener;
    MyFilter filter;
    std::vector<b2Vec2> spawn_points;
    std::map<uint8_t, Team> teams;
    BoxManager box_manager;
    ProjectileManager projectile_manager;
    WormComprobator worm_comprobator;
    int current_turn_player_id;
    bool shoot_cheat;
    int turn_time;
    int team_turn;
    bool turn_cleaning;
    int cleaning_time;
    bool game_ended;
    int winner_team_id;

    void worm_comprobations();

    void projectiles_comprobations(int it);

    void manage_turn();

    void turn_clean_up();

    void spawn_provision_box();

    std::shared_ptr<Worm> get_worm_if_can_act(int id);


    std::vector<WormSnapshot> assign_worms_to_teams(const Map& map,
                                                    std::vector<b2Vec2>& current_spawn_points,
                                                    std::map<char, std::vector<char>>& match_teams,
                                                    int number_of_players);


public:
    Game();

    Snapshot start_and_send(const Map& map, int number_of_players,
                            std::map<char, std::vector<char>>& match_teams);

    void add_player(int current_id, int team_id, std::vector<b2Vec2>& spawn_points);

    void move_player(int id, int direction);

    void jump_player(int id, int direction);

    void player_use_tool(int id, int potency, float pos_x, float pos_y, int timer);

    void player_aim(int id, int increment, int direction);

    void player_change_tool(int id, int direction);

    void remove_army(char army_id);

    void game_post_cleanup();

    void step(int it);

    bool check_end_game();

    Snapshot get_game_snapshot();

    Snapshot get_end_game_snapshot();

    void toggle_shoot_cheat(char id);

    void cheat_ammo(char id);

    void cheat_life(char id);

    void cheat_turn_time();

    ~Game();
};

#endif  // GAME_H
