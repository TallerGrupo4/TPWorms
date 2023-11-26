#ifndef MATCH_H
#define MATCH_H

#include <map>
#include <chrono>

#include <SDL2pp/SDL2pp.hh>

#include "../common_src/snapshot.h"
#include "worm.h"
#include "camera.h"
#include "constantes_cliente.h"
#include "background.h"
#include "surfaces.h"

class Match {
private:
    std::shared_ptr<Background> bkgrnd;
    std::map<char, std::shared_ptr<Worm>> worms_map;
    Camera camera;
    char my_army_id;
    char worm_turn_id;
    uint turn_time;

    bool get_next_target(Target& new_target);

public:
    explicit Match(Snapshot snpsht, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer);
    explicit Match();
    void update_from_snapshot(Snapshot& snpsht);
    void update_from_iter(int iter);
    void update_camera(int camera_offset_x = 0, int camera_offset_y = 0,
                       bool center_camera = false, bool player_activated = false,
                       bool need_to_be_player_activated = false);
    void render(SDL2pp::Renderer& renderer);
    int get_turn_worm_x();
    int get_turn_worm_y();
    bool turn_worm_facing_left();
    char get_turn_worm_id();
    bool is_turn_worm_in_my_army();
};

#endif  // MATCH_H