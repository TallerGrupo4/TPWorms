#include "worm.h"

#ifndef WORM_COMPROBATOR_H
#define WORM_COMPROBATOR_H

class WormComprobator{

    void check_angles(Worm& w);

    void check_states(Worm& w, int& turn_time, int& current_turn_player_id);

    void check_velocities(Worm& w);

    void check_out_of_map_worm(Worm& w, int& turn_time, int& current_turn_player_id, int& height , int& width, int& water_level);

    public:

    WormComprobator();

    void check_during_game(std::list<std::shared_ptr<Worm>>& worms, int& time, int& current_id, int& height , int& width, int& water_level);

    std::list<char> check_post_turn(std::list<std::shared_ptr<Worm>>& worms, b2World& world);


    ~WormComprobator();
};

#endif //WORM_COMPROBATOR_H