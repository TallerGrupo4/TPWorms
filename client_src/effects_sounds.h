#ifndef EFFECTS_SOUNDS_H
#define EFFECTS_SOUNDS_H

#include <memory>
#include <list>

#include <SDL2pp/SDL2pp.hh>

#include "constantes_cliente.h"

class EffectsSounds {
public:
    explicit EffectsSounds(SDL2pp::Mixer& mixer);
    void play_pickup_box_sound();
    void play_match_winner_sound();
    void play_match_loser_sound();
    void play_big_explosion_sound();
    void play_small_explosion_sound();
    void play_holy_grenade_explosion_sound();
    void play_powerup_sound();
    void play_bazooka_shoot_sound();
    void play_dynamite_active_sound();
    void play_holy_grenade_active_sound();
    void play_airstrike_active_sound();
    void play_teleport_sound();
    void play_baseball_bat_sound();
    void play_worm_jump_sound();
    void play_worm_impact_sound();
    void play_worm_death_sound();
    void stop_dynamite_fuse_sound();
private:
    SDL2pp::Mixer& mixer;
    /*PICKUP BOX*/
    SDL2pp::Chunk pickup_box_sound;
    /*FINNISHED*/
    SDL2pp::Chunk match_winner_sound;
    SDL2pp::Chunk match_loser_sound;
    /*EXPLOSION SOUNDS*/
    SDL2pp::Chunk big_explosion_sound; //explosion 2
    SDL2pp::Chunk small_explosion_sound; //explosion 3
    SDL2pp::Chunk holy_grenade_explosion_sound; //explosion 1
    /*WEAPON USE SOUNDS*/
    SDL2pp::Chunk powerup; //rocketpowerup
    SDL2pp::Chunk bazooka_shoot; //rocketrelease
    SDL2pp::Chunk dynamite_active_sound; //fuse
    SDL2pp::Chunk holy_grenade_active_sound; //holygrenade
    SDL2pp::Chunk airstrike_active_sound; //airstrike
    SDL2pp::Chunk teleport_sound; //teleport
    SDL2pp::Chunk baseball_bat_active_sound; //baseballbatrelease
    /*WORM SOUNDS*/
    SDL2pp::Chunk worm_jump_sound; //wormspring
    SDL2pp::Chunk worm_impact_sound; //wormimpact
    SDL2pp::Chunk worm_death_sound; //cough5
};

#endif  // EFFECTS_SOUNDS_H