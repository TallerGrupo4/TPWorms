#include "effects_sounds.h"

EffectsSounds::EffectsSounds(SDL2pp::Mixer& mixer) : mixer(mixer),
                /*PICKUP BOX*/
                pickup_box_sound(PICKUP_BOX_SOUND_PATH),
                /*FINNISHED*/
                match_winner_sound(MATCH_WINNER_SOUND_PATH),
                match_loser_sound(MATCH_LOSER_SOUND_PATH),
                /*EXPLOSION SOUNDS*/
                big_explosion_sound(BIG_EXPLOSION_SOUND_PATH),
                small_explosion_sound(SMALL_EXPLOSION_SOUND_PATH),
                holy_grenade_explosion_sound(HOLY_GRENADE_EXPLOSION_SOUND_PATH),
                /*WEAPON USE SOUNDS*/
                powerup(POWERUP_SOUND_PATH),
                bazooka_shoot(BAZOOKA_SHOOT_SOUND_PATH),
                dynamite_active_sound(DYNAMITE_ACTIVE_SOUND_PATH),
                holy_grenade_active_sound(HOLY_GRENADE_ACTIVE_SOUND_PATH),
                airstrike_active_sound(AIRSTRIKE_ACTIVE_SOUND_PATH),
                teleport_sound(TELEPORT_SOUND_PATH),
                baseball_bat_active_sound(BASEBALL_BAT_ACTIVE_SOUND_PATH),
                /*WORM SOUNDS*/
                worm_jump_sound(WORM_JUMP_SOUND_PATH),
                worm_impact_sound(WORM_IMPACT_SOUND_PATH),
                worm_death_sound(WORM_DEATH_SOUND_PATH) {

}

void EffectsSounds::play_pickup_box_sound() {
    mixer.PlayChannel(-1, pickup_box_sound, 0);
}

void EffectsSounds::play_match_winner_sound() {
    mixer.PlayChannel(-1, match_winner_sound, -1);
}

void EffectsSounds::play_match_loser_sound() {
    mixer.PlayChannel(-1, match_loser_sound, -1);
}

void EffectsSounds::play_big_explosion_sound() {
    mixer.PlayChannel(-1, big_explosion_sound, 0);
}

void EffectsSounds::play_small_explosion_sound() {
    mixer.PlayChannel(-1, small_explosion_sound, 0);
}

void EffectsSounds::play_holy_grenade_explosion_sound() {
    mixer.PlayChannel(-1, holy_grenade_explosion_sound, 0);
}

void EffectsSounds::play_powerup_sound() {
    mixer.PlayChannel(-1, powerup, 0);
}

void EffectsSounds::play_bazooka_shoot_sound() {
    mixer.PlayChannel(-1, bazooka_shoot, 0);
}

void EffectsSounds::play_dynamite_active_sound() {
    mixer.PlayChannel(SPECIAL_EXPLOSIONS_CHANNEL, dynamite_active_sound, -1);
}

void EffectsSounds::play_holy_grenade_active_sound() {
    mixer.PlayChannel(SPECIAL_EXPLOSIONS_CHANNEL, holy_grenade_active_sound, 0);
}

void EffectsSounds::play_airstrike_active_sound() {
    mixer.PlayChannel(-1, airstrike_active_sound, 0);
}

void EffectsSounds::play_teleport_sound() {
    mixer.PlayChannel(-1, teleport_sound, 0);
}

void EffectsSounds::play_baseball_bat_sound() {
    mixer.PlayChannel(-1, baseball_bat_active_sound, 0);
}

void EffectsSounds::play_worm_jump_sound() {
    mixer.PlayChannel(WORM_SOUNDS_CHANNEL, worm_jump_sound, 0);
}

void EffectsSounds::play_worm_impact_sound() {
    mixer.PlayChannel(WORM_SOUNDS_CHANNEL, worm_impact_sound, 0);
}

void EffectsSounds::play_worm_death_sound() {
    mixer.PlayChannel(WORM_SOUNDS_CHANNEL, worm_death_sound, 0);
}

void EffectsSounds::stop_dynamite_fuse_sound() {
    mixer.HaltChannel(SPECIAL_EXPLOSIONS_CHANNEL);
}