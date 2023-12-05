#ifndef WORM_H
#define WORM_H

#include <map>
#include <memory>

#include <SDL2pp/SDL2pp.hh>

#include "../common_src/constants.h"
#include "../common_src/snapshot.h"

#include "Animation.h"
#include "client_constants.h"
#include "colordependentwidgets.h"
#include "effects_animations.h"
#include "effects_sounds.h"
#include "surfaces.h"
#include "worm_animations.h"
#include "worm_widgets.h"

class Worm {
public:
    Worm(const WormSnapshot& worm_snpsht, int worm_width, int worm_height,
         std::shared_ptr<EffectsAnimations>& effects_an,
         std::shared_ptr<EffectsSounds>& effects_sound, ArmyColorDependentWidgets widgets,
         MatchSurfaces& surfaces, SDL2pp::Renderer& renderer);
    ~Worm();
    void update_from_snapshot(SDL2pp::Renderer& renderer, WormSnapshot& worm_snpsht);
    void update_from_iter(int iter);
    void render(SDL2pp::Renderer& renderer, int camera_offset_x, int camera_offset_y);
    void render_texts_and_widgets(SDL2pp::Renderer& renderer, int camera_offset_x,
                                  int camera_offset_y);
    void moveRigth();
    void moveLeft();
    void stopMoving();
    int get_worm_state();
    int get_worm_x();
    int get_worm_y();
    TOOLS get_weapon();
    int get_weapon_ammo();
    bool has_weapon();
    bool has_dynamite();
    bool has_weapon_to_aim();
    bool has_charging_weapon();
    bool has_timer_weapon();
    bool has_guided_weapon();
    bool worm_facing_left();
    char get_army_id();

private:
    void handleShootedState(SDL2pp::Renderer& renderer, TOOLS old_weapon);

    std::shared_ptr<EffectsAnimations> effects_an;
    std::shared_ptr<EffectsSounds> effects_sound;
    bool facing_left;
    bool moving;
    int angle;
    char id;
    int health_points;
    int max_health;
    int state;
    TOOLS weapon;
    int weapon_ammo;
    int aiming_angle;
    int x;
    int y;
    int width;
    int height;
    char army_id;
    WormAnimations worm_an;
    WormWidgets worm_texts;
};

#endif  // WORM_H
