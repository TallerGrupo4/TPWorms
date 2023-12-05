#ifndef MATCH_H
#define MATCH_H

#include <map>
#include <memory>
#include <utility>

#include <SDL2pp/SDL2pp.hh>

#include "../common_src/snapshot.h"

#include "actions.h"
#include "background.h"
#include "camera.h"
#include "client_constants.h"
#include "effects_animations.h"
#include "effects_sounds.h"
#include "projectile.h"
#include "provision_box.h"
#include "surfaces.h"
#include "worm.h"

// Class that represents a match
class Match {
private:
    std::shared_ptr<Background> bkgrnd;
    std::shared_ptr<EffectsAnimations> effects_an;
    std::shared_ptr<EffectsSounds> effects_sound;
    std::map<char, std::shared_ptr<Worm>> worms_map;
    std::map<char, std::shared_ptr<Projectile>> projectiles_map;
    std::map<char, std::shared_ptr<ProvisionBox>> provision_boxes_map;
    char my_army_id;
    char worm_turn_id;
    uint turn_time;
    Camera camera;
    uint charge_for_weapon;
    uint timer_for_weapon;
    bool already_shot_charged_weapon;

    void update_camera_for_less_priority_targets(int camera_offset_x, int camera_offset_y,
                                                 bool center_camera);
    bool get_next_target(Target& new_target);
    bool turn_worm_facing_left();
    char get_turn_worm_id();
    bool is_turn_worm_in_my_army();
    bool is_turn_worm_still();
    bool turn_worm_has_dynamite();
    bool turn_worm_has_weapon();
    bool turn_worm_has_weapon_to_aim();
    bool turn_worm_has_charging_weapon();
    bool turn_worm_has_timer_weapon();
    bool turn_worm_has_guided_weapon();
    bool is_turn_worm_aiming_weapon();

public:
    /**
     * @brief Construct a new Match object
     * @param snpsht Snapshot of the match received from the server
     * @param surfaces Surfaces of the match
     * @param renderer Renderer of the match
     * @param mixer Music mixer of the match
     */
    explicit Match(Snapshot snpsht, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer,
                   SDL2pp::Mixer& mixer);
    Match();
    /**
     * @brief Updates the match from a snapshot received from the server
     * @param snpsht Snapshot of the match received from the server
     * @param surfaces Surfaces of the match
     * @param renderer Renderer of the match
     */
    void update_from_snapshot(Snapshot& snpsht, MatchSurfaces& surfaces,
                              SDL2pp::Renderer& renderer);
    /**
     * @brief Updates the match from the ticks of the match
     * @param iter Iterations needed to update all the ticks
     */
    void update_from_iter(int iter);
    /**
     * @brief Updates the camera of the match
     * @param camera_offset_x Offset of the camera in the x axis
     * @param camera_offset_y Offset of the camera in the y axis
     * @param center_camera True if the camera needs to be centered, false otherwise
     * @param player_activated True if the player activated, false otherwise
     * @param need_to_be_player_activated True if the player needs to be activated, false otherwise
     * @param window Window of the match
     * @param pos_x_to_warp_mouse X coordinate of the position to warp the mouse
     * @param pos_y_to_warp_mouse Y coordinate of the position to warp the mouse
     */
    void update_camera(int camera_offset_x = 0, int camera_offset_y = 0, bool center_camera = false,
                       bool player_activated = false, bool need_to_be_player_activated = false,
                       SDL2pp::Window* window = nullptr, int pos_x_to_warp_mouse = 0,
                       int pos_y_to_warp_mouse = 0);
    /**
     * @brief Renders the match
     * @param renderer Renderer of the match
     */
    void render(SDL2pp::Renderer& renderer);
    int get_turn_worm_x();
    int get_turn_worm_y();
    bool handle_left_button(std::shared_ptr<Action>& action);
    bool handle_right_button(std::shared_ptr<Action>& action);
    bool handle_up_button(std::shared_ptr<Action>& action);
    bool handle_down_button(std::shared_ptr<Action>& action);
    bool handle_space_button_pressed(std::shared_ptr<Action>& action, bool first_time_pressed);
    bool handle_space_button_release(std::shared_ptr<Action>& action, SDL2pp::Renderer& renderer);
    void handle_1_button();
    void handle_2_button();
    void handle_3_button();
    void handle_4_button();
    void handle_5_button();
    bool handle_cheat_1(std::shared_ptr<Action>& action);
    bool handle_cheat_2(std::shared_ptr<Action>& action);
    bool handle_cheat_3(std::shared_ptr<Action>& action);
    bool handle_cheat_4(std::shared_ptr<Action>& action);
    void handle_mouse_left_click(int mouse_x, int mouse_y);
    bool handle_mouse_right_click(std::shared_ptr<Action>& action, int mouse_x, int mouse_y);
    bool handle_mouse_scroll_up(std::shared_ptr<Action>& action);
    bool handle_mouse_scroll_down(std::shared_ptr<Action>& action);
    void handle_mouse_motion(int mouse_x, int mouse_y);
    bool handle_enter_button(std::shared_ptr<Action>& action);
    bool handle_backspace_button(std::shared_ptr<Action>& action);
};

#endif  // MATCH_H
