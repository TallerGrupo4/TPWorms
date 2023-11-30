#ifndef MATCH_H
#define MATCH_H

#include <map>
#include <list>
#include <chrono>

#include <SDL2pp/SDL2pp.hh>

#include "../common_src/snapshot.h"
#include "worm.h"
#include "projectile.h"
#include "camera.h"
#include "constantes_cliente.h"
#include "action.h"
#include "background.h"
#include "surfaces.h"

class Match {
private:
    std::shared_ptr<Background> bkgrnd;
    std::map<char, std::shared_ptr<Worm>> worms_map;
    std::map<char, std::shared_ptr<Projectile>> projectiles_map;
    char my_army_id;
    char worm_turn_id;
    uint turn_time;
    Camera camera;
    uint charge_for_weapon;

    bool get_next_target(Target& new_target);

public:
    explicit Match(Snapshot snpsht, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer);
    explicit Match();
    void update_from_snapshot(Snapshot& snpsht, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer);
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
    bool is_turn_worm_still();
    bool turn_worm_has_dynamite();
    bool turn_worm_has_weapon();
    bool turn_worm_has_weapon_to_aim();
    bool turn_worm_has_charging_weapon();
    bool turn_worm_has_guided_weapon();
    bool is_turn_worm_aiming_weapon();
    bool handle_left_button(std::shared_ptr<Action>& action);
    bool handle_right_button(std::shared_ptr<Action>& action);
    bool handle_up_button(std::shared_ptr<Action>& action);
    bool handle_down_button(std::shared_ptr<Action>& action);
    bool handle_space_button_pressed(std::shared_ptr<Action>& action);
    bool handle_space_button_release(std::shared_ptr<Action>& action);
    void handle_mouse_left_click(int mouse_x, int mouse_y);
    bool handle_mouse_right_click(std::shared_ptr<Action>& action, int mouse_x, int mouse_y);
    bool handle_mouse_scroll_up(std::shared_ptr<Action>& action);
    bool handle_mouse_scroll_down(std::shared_ptr<Action>& action);
    void handle_mouse_motion(int mouse_x, int mouse_y);
    bool handle_enter_button(std::shared_ptr<Action>& action);
    bool handle_backspace_button(std::shared_ptr<Action>& action);
};

#endif  // MATCH_H