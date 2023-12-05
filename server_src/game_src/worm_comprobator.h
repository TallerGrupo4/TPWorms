#include <list>
#include <memory>

#include "worm.h"

#ifndef WORM_COMPROBATOR_H
#define WORM_COMPROBATOR_H

class WormComprobator {

    void check_angles(Worm& w);

    void check_states(Worm& w, int& turn_time, const int& current_turn_player_id);

    void check_velocities(Worm& w);

    bool check_out_of_map_worm(Worm& w, int& turn_time, const int& current_turn_player_id,
                               const int& height, const int& width, const int& water_level);

public:
    WormComprobator();

    void check_during_game(const std::list<std::shared_ptr<Worm>>& worms, int& time,
                           const int& current_id, const int& height, const int& width,
                           const int& water_level);

    std::list<char> check_post_game(std::list<std::shared_ptr<Worm>>& worms, b2World& world);

    bool have_worm_finished_turn(std::list<std::shared_ptr<Worm>>& worms, int& cleaning_time);


    ~WormComprobator();
};

#endif  // WORM_COMPROBATOR_H
