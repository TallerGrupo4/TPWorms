#include "hud.h"

#include <string>

Hud::Hud():
        target(),
        marker_an(nullptr),
        /*TEXTS*/
        wind_velocity_text(nullptr),
        turn_time_text(nullptr),
        ammo_text(nullptr),
        timer_text(nullptr),
        charging_text(nullptr),
        turn_army_text(nullptr),
        end_game_text(nullptr),
        /*WEAPON ICONS*/
        bazooka_icon_on(nullptr),
        bazooka_icon_off(nullptr),
        mortar_icon_on(nullptr),
        mortar_icon_off(nullptr),
        green_grenade_icon_on(nullptr),
        green_grenade_icon_off(nullptr),
        red_grenade_icon_on(nullptr),
        red_grenade_icon_off(nullptr),
        banana_icon_on(nullptr),
        banana_icon_off(nullptr),
        holy_icon_on(nullptr),
        holy_icon_off(nullptr),
        air_strike_icon_on(nullptr),
        air_strike_icon_off(nullptr),
        dynamite_icon_on(nullptr),
        dynamite_icon_off(nullptr),
        teleport_icon_on(nullptr),
        teleport_icon_off(nullptr),
        baseball_bat_icon_on(nullptr),
        baseball_bat_icon_off(nullptr),
        my_army_id(-1),
        my_army_color(WHITE),
        turn_worm_weapon(TOOLS::NO_TOOL),
        marker_following_mouse(false),
        marker_set(false),
        is_end_game(false),
        marker_x(0),
        marker_y(0) {}

Hud::Hud(SDL2pp::Renderer& renderer, MatchSurfaces& surfaces, Target target, uint turn_time,
         char my_army_id):
        target(target),
        marker_an(nullptr),
        /*TEXTS*/
        wind_velocity_text(std::make_shared<SDL2pp::Surface>(
                SDL2pp::Font(WORMS_FONT_PATH, 16)
                        .RenderText_Blended(std::string("Wind Speed: "), WHITE))),
        turn_time_text(std::make_shared<SDL2pp::Surface>(
                SDL2pp::Font(WORMS_FONT_PATH, 16)
                        .RenderText_Blended(std::string("Turn Time: " + std::to_string(turn_time)),
                                            WHITE))),
        ammo_text(std::make_shared<SDL2pp::Surface>(
                SDL2pp::Font(WORMS_FONT_PATH, 16)
                        .RenderText_Blended(std::string("Weapon Ammo: "), WHITE))),
        timer_text(std::make_shared<SDL2pp::Surface>(
                SDL2pp::Font(WORMS_FONT_PATH, 16)
                        .RenderText_Blended(std::string("Grenade Timer: "), WHITE))),
        charging_text(std::make_shared<SDL2pp::Surface>(
                SDL2pp::Font(WORMS_FONT_PATH, 16)
                        .RenderText_Blended(std::string("Weapon Charge: "), WHITE))),
        turn_army_text(std::make_shared<SDL2pp::Surface>(
                SDL2pp::Font(WORMS_FONT_PATH, 16)
                        .RenderText_Blended(std::string("WAITING TURN TO START"), WHITE))),
        end_game_text(std::make_shared<SDL2pp::Surface>(
                SDL2pp::Font(WORMS_FONT_PATH, 64)
                        .RenderText_Blended(std::string("PLACEHOLDER TEXT END GAME"), WHITE))),
        /*WEAPON ICONS*/
        bazooka_icon_on(std::make_shared<SDL2pp::Texture>(renderer, surfaces.bazooka_icon_on)),
        bazooka_icon_off(std::make_shared<SDL2pp::Texture>(renderer, surfaces.bazooka_icon_off)),
        mortar_icon_on(std::make_shared<SDL2pp::Texture>(renderer, surfaces.mortar_icon_on)),
        mortar_icon_off(std::make_shared<SDL2pp::Texture>(renderer, surfaces.mortar_icon_off)),
        green_grenade_icon_on(
                std::make_shared<SDL2pp::Texture>(renderer, surfaces.green_grenade_icon_on)),
        green_grenade_icon_off(
                std::make_shared<SDL2pp::Texture>(renderer, surfaces.green_grenade_icon_off)),
        red_grenade_icon_on(
                std::make_shared<SDL2pp::Texture>(renderer, surfaces.red_grenade_icon_on)),
        red_grenade_icon_off(
                std::make_shared<SDL2pp::Texture>(renderer, surfaces.red_grenade_icon_off)),
        banana_icon_on(std::make_shared<SDL2pp::Texture>(renderer, surfaces.banana_icon_on)),
        banana_icon_off(std::make_shared<SDL2pp::Texture>(renderer, surfaces.banana_icon_off)),
        holy_icon_on(std::make_shared<SDL2pp::Texture>(renderer, surfaces.holy_icon_on)),
        holy_icon_off(std::make_shared<SDL2pp::Texture>(renderer, surfaces.holy_icon_off)),
        air_strike_icon_on(
                std::make_shared<SDL2pp::Texture>(renderer, surfaces.air_strike_icon_on)),
        air_strike_icon_off(
                std::make_shared<SDL2pp::Texture>(renderer, surfaces.air_strike_icon_off)),
        dynamite_icon_on(std::make_shared<SDL2pp::Texture>(renderer, surfaces.dynamite_icon_on)),
        dynamite_icon_off(std::make_shared<SDL2pp::Texture>(renderer, surfaces.dynamite_icon_off)),
        teleport_icon_on(std::make_shared<SDL2pp::Texture>(renderer, surfaces.teleport_icon_on)),
        teleport_icon_off(std::make_shared<SDL2pp::Texture>(renderer, surfaces.teleport_icon_off)),
        baseball_bat_icon_on(
                std::make_shared<SDL2pp::Texture>(renderer, surfaces.baseball_bat_icon_on)),
        baseball_bat_icon_off(
                std::make_shared<SDL2pp::Texture>(renderer, surfaces.baseball_bat_icon_off)),
        my_army_id(my_army_id),
        my_army_color(WHITE),
        turn_worm_weapon(TOOLS::NO_TOOL),
        marker_following_mouse(false),
        marker_set(false),
        is_end_game(false),
        marker_x(0),
        marker_y(0) {

    switch (my_army_id) {
        case 0:
            marker_an = std::make_unique<Animation>(renderer, surfaces.marker_blue,
                                                    MILISECS_FOR_MARKER_SPRITES, false, true);
            my_army_color = BLUE;
            break;
        case 1:
            marker_an = std::make_unique<Animation>(renderer, surfaces.marker_red,
                                                    MILISECS_FOR_MARKER_SPRITES, false, true);
            my_army_color = RED;
            break;
        case 2:
            marker_an = std::make_unique<Animation>(renderer, surfaces.marker_yellow,
                                                    MILISECS_FOR_MARKER_SPRITES, false, true);
            my_army_color = YELLOW;
            break;
        case 3:
            marker_an = std::make_unique<Animation>(renderer, surfaces.marker_green,
                                                    MILISECS_FOR_MARKER_SPRITES, false, true);
            my_army_color = GREEN;
            break;
        default:
            marker_an = std::make_unique<Animation>(renderer, surfaces.marker_purple,
                                                    MILISECS_FOR_MARKER_SPRITES, false, true);
            my_army_color = ORANGE;
            break;
    }
}

void Hud::render_armies_health(SDL2pp::Renderer& renderer, int army_health_pos_y) {
    int gap = 10;
    int health_pos_x = gap;
    int health_pos_y = army_health_pos_y;
    for (const auto& pair: this->armies_health_texts) {
        SDL2pp::Texture army_health_text_texture(renderer, *pair.second);
        renderer.Copy(army_health_text_texture, SDL2pp::NullOpt,
                      SDL2pp::Rect(health_pos_x, health_pos_y, army_health_text_texture.GetWidth(),
                                   army_health_text_texture.GetHeight()));
        health_pos_y += army_health_text_texture.GetHeight() + gap;
    }
}

void Hud::render_weapon_icons(SDL2pp::Renderer& renderer) {
    int gap = 10;
    int icons_pos_x = renderer.GetLogicalWidth() - gap - (*this->teleport_icon_on).GetWidth();
    int teleport_pos_y = gap;
    int air_strike_pos_y = teleport_pos_y + (*this->teleport_icon_on).GetHeight() + gap;
    int baseball_bat_pos_y = air_strike_pos_y + (*this->air_strike_icon_on).GetHeight() + gap;
    int dynamite_pos_y = baseball_bat_pos_y + (*this->baseball_bat_icon_on).GetHeight() + gap;
    int holy_pos_y = dynamite_pos_y + (*this->dynamite_icon_on).GetHeight() + gap;
    int banana_pos_y = holy_pos_y + (*this->holy_icon_on).GetHeight() + gap;
    int red_grenade_pos_y = banana_pos_y + (*this->banana_icon_on).GetHeight() + gap;
    int green_grenade_pos_y = red_grenade_pos_y + (*this->red_grenade_icon_on).GetHeight() + gap;
    int mortar_pos_y = green_grenade_pos_y + (*this->green_grenade_icon_on).GetHeight() + gap;
    int bazooka_pos_y = mortar_pos_y + (*this->mortar_icon_on).GetHeight() + gap;

    renderer.Copy(*this->bazooka_icon_off, SDL2pp::NullOpt,
                  SDL2pp::Rect(icons_pos_x, bazooka_pos_y, (*this->bazooka_icon_off).GetWidth(),
                               (*this->bazooka_icon_off).GetHeight()));
    renderer.Copy(*this->mortar_icon_off, SDL2pp::NullOpt,
                  SDL2pp::Rect(icons_pos_x, mortar_pos_y, (*this->mortar_icon_off).GetWidth(),
                               (*this->mortar_icon_off).GetHeight()));
    renderer.Copy(*this->green_grenade_icon_off, SDL2pp::NullOpt,
                  SDL2pp::Rect(icons_pos_x, green_grenade_pos_y,
                               (*this->green_grenade_icon_off).GetWidth(),
                               (*this->green_grenade_icon_off).GetHeight()));
    renderer.Copy(
            *this->red_grenade_icon_off, SDL2pp::NullOpt,
            SDL2pp::Rect(icons_pos_x, red_grenade_pos_y, (*this->red_grenade_icon_off).GetWidth(),
                         (*this->red_grenade_icon_off).GetHeight()));
    renderer.Copy(*this->banana_icon_off, SDL2pp::NullOpt,
                  SDL2pp::Rect(icons_pos_x, banana_pos_y, (*this->banana_icon_off).GetWidth(),
                               (*this->banana_icon_off).GetHeight()));
    renderer.Copy(*this->holy_icon_off, SDL2pp::NullOpt,
                  SDL2pp::Rect(icons_pos_x, holy_pos_y, (*this->holy_icon_off).GetWidth(),
                               (*this->holy_icon_off).GetHeight()));
    renderer.Copy(*this->dynamite_icon_off, SDL2pp::NullOpt,
                  SDL2pp::Rect(icons_pos_x, dynamite_pos_y, (*this->dynamite_icon_off).GetWidth(),
                               (*this->dynamite_icon_off).GetHeight()));
    renderer.Copy(
            *this->baseball_bat_icon_off, SDL2pp::NullOpt,
            SDL2pp::Rect(icons_pos_x, baseball_bat_pos_y, (*this->baseball_bat_icon_off).GetWidth(),
                         (*this->baseball_bat_icon_off).GetHeight()));
    renderer.Copy(
            *this->air_strike_icon_off, SDL2pp::NullOpt,
            SDL2pp::Rect(icons_pos_x, air_strike_pos_y, (*this->air_strike_icon_off).GetWidth(),
                         (*this->air_strike_icon_off).GetHeight()));
    renderer.Copy(*this->teleport_icon_off, SDL2pp::NullOpt,
                  SDL2pp::Rect(icons_pos_x, teleport_pos_y, (*this->teleport_icon_off).GetWidth(),
                               (*this->teleport_icon_off).GetHeight()));

    switch (this->turn_worm_weapon) {
        case TOOLS::BAZOOKA:
            renderer.SetDrawColor(BLUE);
            renderer.FillRect(SDL2pp::Rect(icons_pos_x - (gap / 2), bazooka_pos_y - (gap / 2),
                                           (*this->bazooka_icon_on).GetWidth() + gap,
                                           (*this->bazooka_icon_on).GetHeight() + gap));
            renderer.SetDrawColor(WHITE);
            renderer.Copy(
                    *this->bazooka_icon_on, SDL2pp::NullOpt,
                    SDL2pp::Rect(icons_pos_x, bazooka_pos_y, (*this->bazooka_icon_on).GetWidth(),
                                 (*this->bazooka_icon_on).GetHeight()));
            break;
        case TOOLS::MORTAR:
            renderer.SetDrawColor(BLUE);
            renderer.FillRect(SDL2pp::Rect(icons_pos_x - (gap / 2), mortar_pos_y - (gap / 2),
                                           (*this->mortar_icon_on).GetWidth() + gap,
                                           (*this->mortar_icon_on).GetHeight() + gap));
            renderer.SetDrawColor(WHITE);
            renderer.Copy(
                    *this->mortar_icon_on, SDL2pp::NullOpt,
                    SDL2pp::Rect(icons_pos_x, mortar_pos_y, (*this->mortar_icon_on).GetWidth(),
                                 (*this->mortar_icon_on).GetHeight()));
            break;
        case TOOLS::GREEN_GRENADE:
            renderer.SetDrawColor(BLUE);
            renderer.FillRect(SDL2pp::Rect(icons_pos_x - (gap / 2), green_grenade_pos_y - (gap / 2),
                                           (*this->green_grenade_icon_on).GetWidth() + gap,
                                           (*this->green_grenade_icon_on).GetHeight() + gap));
            renderer.SetDrawColor(WHITE);
            renderer.Copy(*this->green_grenade_icon_on, SDL2pp::NullOpt,
                          SDL2pp::Rect(icons_pos_x, green_grenade_pos_y,
                                       (*this->green_grenade_icon_on).GetWidth(),
                                       (*this->green_grenade_icon_on).GetHeight()));
            break;
        case TOOLS::RED_GRENADE:
            renderer.SetDrawColor(BLUE);
            renderer.FillRect(SDL2pp::Rect(icons_pos_x - (gap / 2), red_grenade_pos_y - (gap / 2),
                                           (*this->red_grenade_icon_on).GetWidth() + gap,
                                           (*this->red_grenade_icon_on).GetHeight() + gap));
            renderer.SetDrawColor(WHITE);
            renderer.Copy(*this->red_grenade_icon_on, SDL2pp::NullOpt,
                          SDL2pp::Rect(icons_pos_x, red_grenade_pos_y,
                                       (*this->red_grenade_icon_on).GetWidth(),
                                       (*this->red_grenade_icon_on).GetHeight()));
            break;
        case TOOLS::BANANA:
            renderer.SetDrawColor(BLUE);
            renderer.FillRect(SDL2pp::Rect(icons_pos_x - (gap / 2), banana_pos_y - (gap / 2),
                                           (*this->banana_icon_on).GetWidth() + gap,
                                           (*this->banana_icon_on).GetHeight() + gap));
            renderer.SetDrawColor(WHITE);
            renderer.Copy(
                    *this->banana_icon_on, SDL2pp::NullOpt,
                    SDL2pp::Rect(icons_pos_x, banana_pos_y, (*this->banana_icon_on).GetWidth(),
                                 (*this->banana_icon_on).GetHeight()));
            break;
        case TOOLS::HOLY_GRENADE:
            renderer.SetDrawColor(BLUE);
            renderer.FillRect(SDL2pp::Rect(icons_pos_x - (gap / 2), holy_pos_y - (gap / 2),
                                           (*this->holy_icon_on).GetWidth() + gap,
                                           (*this->holy_icon_on).GetHeight() + gap));
            renderer.SetDrawColor(WHITE);
            renderer.Copy(*this->holy_icon_on, SDL2pp::NullOpt,
                          SDL2pp::Rect(icons_pos_x, holy_pos_y, (*this->holy_icon_on).GetWidth(),
                                       (*this->holy_icon_on).GetHeight()));
            break;
        case TOOLS::DYNAMITE:
            renderer.SetDrawColor(BLUE);
            renderer.FillRect(SDL2pp::Rect(icons_pos_x - (gap / 2), dynamite_pos_y - (gap / 2),
                                           (*this->dynamite_icon_on).GetWidth() + gap,
                                           (*this->dynamite_icon_on).GetHeight() + gap));
            renderer.SetDrawColor(WHITE);
            renderer.Copy(
                    *this->dynamite_icon_on, SDL2pp::NullOpt,
                    SDL2pp::Rect(icons_pos_x, dynamite_pos_y, (*this->dynamite_icon_on).GetWidth(),
                                 (*this->dynamite_icon_on).GetHeight()));
            break;
        case TOOLS::BASEBALL_BAT:
            renderer.SetDrawColor(BLUE);
            renderer.FillRect(SDL2pp::Rect(icons_pos_x - (gap / 2), baseball_bat_pos_y - (gap / 2),
                                           (*this->baseball_bat_icon_on).GetWidth() + gap,
                                           (*this->baseball_bat_icon_on).GetHeight() + gap));
            renderer.SetDrawColor(WHITE);
            renderer.Copy(*this->baseball_bat_icon_on, SDL2pp::NullOpt,
                          SDL2pp::Rect(icons_pos_x, baseball_bat_pos_y,
                                       (*this->baseball_bat_icon_on).GetWidth(),
                                       (*this->baseball_bat_icon_on).GetHeight()));
            break;
        case TOOLS::AIRSTRIKE:
            renderer.SetDrawColor(BLUE);
            renderer.FillRect(SDL2pp::Rect(icons_pos_x - (gap / 2), air_strike_pos_y - (gap / 2),
                                           (*this->air_strike_icon_on).GetWidth() + gap,
                                           (*this->air_strike_icon_on).GetHeight() + gap));
            renderer.SetDrawColor(WHITE);
            renderer.Copy(*this->air_strike_icon_on, SDL2pp::NullOpt,
                          SDL2pp::Rect(icons_pos_x, air_strike_pos_y,
                                       (*this->air_strike_icon_on).GetWidth(),
                                       (*this->air_strike_icon_on).GetHeight()));
            break;
        case TOOLS::TELEPORTATION:
            renderer.SetDrawColor(BLUE);
            renderer.FillRect(SDL2pp::Rect(icons_pos_x - (gap / 2), teleport_pos_y - (gap / 2),
                                           (*this->teleport_icon_on).GetWidth() + gap,
                                           (*this->teleport_icon_on).GetHeight() + gap));
            renderer.SetDrawColor(WHITE);
            renderer.Copy(
                    *this->teleport_icon_on, SDL2pp::NullOpt,
                    SDL2pp::Rect(icons_pos_x, teleport_pos_y, (*this->teleport_icon_on).GetWidth(),
                                 (*this->teleport_icon_on).GetHeight()));
            break;
        default:
            break;
    }
}

void Hud::render(SDL2pp::Renderer& renderer) {
    if (is_end_game) {
        SDL2pp::Texture end_game_text_texture(renderer, *this->end_game_text);
        renderer.Copy(
                end_game_text_texture, SDL2pp::NullOpt,
                SDL2pp::Rect(
                        (renderer.GetLogicalWidth() / 2) - ((*this->end_game_text).GetWidth() / 2),
                        (renderer.GetLogicalHeight() / 2) -
                                ((*this->end_game_text).GetHeight() / 2),
                        (*this->end_game_text).GetWidth(), (*this->end_game_text).GetHeight()));
    } else {
        if (marker_following_mouse) {
            SDL_RendererFlip flip = SDL_FLIP_NONE;
            marker_an->render(
                    renderer,
                    SDL2pp::Rect(marker_x - marker_an->get_frame_size() / 2,
                                 marker_y - marker_an->get_frame_size() / 2,
                                 marker_an->get_frame_size(), marker_an->get_frame_size()),
                    flip);
        } else if (marker_set) {
            SDL_RendererFlip flip = SDL_FLIP_NONE;
            marker_an->render(
                    renderer,
                    SDL2pp::Rect(marker_x - this->target.x_offset - marker_an->get_frame_size() / 2,
                                 marker_y - this->target.y_offset - marker_an->get_frame_size() / 2,
                                 marker_an->get_frame_size(), marker_an->get_frame_size()),
                    flip);
        }
        int gap = 10;
        int wind_velocity_pos_y =
                renderer.GetLogicalHeight() - gap - wind_velocity_text->GetHeight();
        int wind_velocity_pos_x = renderer.GetLogicalWidth() - gap - wind_velocity_text->GetWidth();
        int turn_time_pos_y = gap;
        int turn_army_pos_y = turn_time_pos_y + turn_time_text->GetHeight() + gap;
        int timer_pos_y = renderer.GetLogicalHeight() - gap - (*this->timer_text).GetHeight();
        int weapon_ammo_pos_y = timer_pos_y - gap - (*this->ammo_text).GetHeight();
        int charging_pos_y = weapon_ammo_pos_y - gap - (*this->charging_text).GetHeight();

        switch (target.type_of_target) {
            case TargetType::WormType: {
                SDL2pp::Texture timer_text_texture(renderer, *this->timer_text);
                renderer.Copy(timer_text_texture, SDL2pp::NullOpt,
                              SDL2pp::Rect(gap, timer_pos_y, (*this->timer_text).GetWidth(),
                                           (*this->timer_text).GetHeight()));
                SDL2pp::Texture ammo_text_texture(renderer, *this->ammo_text);
                renderer.Copy(ammo_text_texture, SDL2pp::NullOpt,
                              SDL2pp::Rect(gap, weapon_ammo_pos_y, (*this->ammo_text).GetWidth(),
                                           (*this->ammo_text).GetHeight()));
                SDL2pp::Texture charging_text_texture(renderer, *this->charging_text);
                renderer.Copy(charging_text_texture, SDL2pp::NullOpt,
                              SDL2pp::Rect(gap, charging_pos_y, (*this->charging_text).GetWidth(),
                                           (*this->charging_text).GetHeight()));
                render_weapon_icons(renderer);
            }
            case TargetType::ProjectileType: {
                SDL2pp::Texture velocity_text_texture(renderer, *this->wind_velocity_text);
                renderer.Copy(velocity_text_texture, SDL2pp::NullOpt,
                              SDL2pp::Rect(wind_velocity_pos_x, wind_velocity_pos_y,
                                           this->wind_velocity_text->GetWidth(),
                                           this->wind_velocity_text->GetHeight()));
            }
            case TargetType::PlayerType: {
                SDL2pp::Texture turn_time_text_texture(renderer, *this->turn_time_text);
                renderer.Copy(turn_time_text_texture, SDL2pp::NullOpt,
                              SDL2pp::Rect(gap, turn_time_pos_y, (*this->turn_time_text).GetWidth(),
                                           (*this->turn_time_text).GetHeight()));
                SDL2pp::Texture turn_army_text_texture(renderer, *this->turn_army_text);
                renderer.Copy(turn_army_text_texture, SDL2pp::NullOpt,
                              SDL2pp::Rect(gap, turn_army_pos_y, (*this->turn_army_text).GetWidth(),
                                           (*this->turn_army_text).GetHeight()));
                render_armies_health(
                        renderer, turn_army_pos_y + (*this->turn_army_text).GetHeight() + gap * 3);
            } break;
            case TargetType::NoneType:
                break;
        }
    }
}

void Hud::update_target(Target target) { this->target = target; }

void Hud::update_turn_weapon(TOOLS turn_worm_weapon) { this->turn_worm_weapon = turn_worm_weapon; }

void Hud::update_turn_weapon_ammo(int turn_worm_weapon_ammo) {
    std::string ammo_count;
    if (turn_worm_weapon_ammo == -1) {
        ammo_count = "Inf";
    } else {
        ammo_count = std::to_string(turn_worm_weapon_ammo);
    }
    std::string ammo_text_str = "Weapon Ammo: " + ammo_count;
    *this->ammo_text = SDL2pp::Font(WORMS_FONT_PATH, 16).RenderText_Blended(ammo_text_str, WHITE);
}

void Hud::update_wind_velocity(int wind_velocity) {
    std::string wind_speed_direction_str;
    if (wind_velocity < 0) {
        wind_speed_direction_str = " W";
    } else if (wind_velocity > 0) {
        wind_speed_direction_str = " E";
    }
    std::string wind_speed_str =
            "Wind Speed: " + std::to_string(std::abs(wind_velocity)) + wind_speed_direction_str;
    *this->wind_velocity_text =
            SDL2pp::Font(WORMS_FONT_PATH, 16).RenderText_Blended(wind_speed_str, WHITE);
}

void Hud::update_armies_health(const std::map<char, int>& armies_health) {
    for (const auto& pair: armies_health) {
        char army_id = pair.first;
        int army_health = pair.second;
        SDL2pp::Color army_color = WHITE;
        std::string army_health_text_str;
        if (army_id == this->my_army_id) {
            army_health_text_str = "My Army Health: " + std::to_string(army_health);
            army_color = my_army_color;
        } else {
            army_health_text_str = "Player " + std::to_string(army_id + 1) +
                                   " Army Health: " + std::to_string(army_health);
            switch (army_id) {
                case 0:
                    army_color = BLUE;
                    break;
                case 1:
                    army_color = RED;
                    break;
                case 2:
                    army_color = YELLOW;
                    break;
                case 3:
                    army_color = GREEN;
                    break;
                default:
                    army_color = ORANGE;
                    break;
            }
        }
        if (this->armies_health_texts.find(army_id) == this->armies_health_texts.end()) {
            this->armies_health_texts[army_id] = std::make_shared<SDL2pp::Surface>(
                    SDL2pp::Font(WORMS_FONT_PATH, 12)
                            .RenderText_Blended(army_health_text_str, army_color));
        } else {
            *this->armies_health_texts[army_id] =
                    SDL2pp::Font(WORMS_FONT_PATH, 12)
                            .RenderText_Blended(army_health_text_str, army_color);
        }
    }
}

void Hud::update_from_iter() {
    if (marker_following_mouse or marker_set) {
        this->marker_an->update_once();
    }
}

void Hud::update_marker(int x, int y) {
    if (marker_following_mouse) {
        this->marker_x = x;
        this->marker_y = y;
    }
}

void Hud::follow_mouse_with_marker(int mouse_x, int mouse_y) {
    this->marker_an->reset();
    this->marker_set = false;
    this->marker_following_mouse = true;
    this->marker_x = mouse_x;
    this->marker_y = mouse_y;
}

void Hud::set_army_turn(char worm_turn_army_id) {
    if (this->my_army_id == worm_turn_army_id) {
        std::string turn_army_text_str = "My Turn";
        *this->turn_army_text = SDL2pp::Font(WORMS_FONT_PATH, 16)
                                        .RenderText_Blended(turn_army_text_str, my_army_color);
    } else {
        SDL_Color turn_color;
        switch (worm_turn_army_id) {
            case 0:
                turn_color = BLUE;
                break;
            case 1:
                turn_color = RED;
                break;
            case 2:
                turn_color = YELLOW;
                break;
            case 3:
                turn_color = GREEN;
                break;
            default:
                turn_color = ORANGE;
                break;
        }
        std::string turn_army_text_str =
                "Player " + std::to_string(worm_turn_army_id + 1) + " Turn";
        *this->turn_army_text = SDL2pp::Font(WORMS_FONT_PATH, 16)
                                        .RenderText_Blended(turn_army_text_str, turn_color);
    }
}

void Hud::set_marker_position(int x, int y) {
    if (not marker_set) {
        this->marker_an->reset();
        this->marker_following_mouse = false;
        this->marker_set = true;
        this->marker_x = x + this->target.x_offset;
        this->marker_y = y + this->target.y_offset;
    } else {
        this->marker_an->reset();
        this->marker_x = x + this->target.x_offset;
        this->marker_y = y + this->target.y_offset;
    }
}

void Hud::set_charging_value(int charge) {
    std::string charging_text_str = "Weapon Charge: " + std::to_string(charge);
    *this->charging_text =
            SDL2pp::Font(WORMS_FONT_PATH, 16).RenderText_Blended(charging_text_str, WHITE);
}

void Hud::clear_charging_value() {
    std::string charging_text_str = "Weapon Charge: ";
    *this->charging_text =
            SDL2pp::Font(WORMS_FONT_PATH, 16).RenderText_Blended(charging_text_str, WHITE);
}

void Hud::set_timer(int timer) {
    std::string timer_text_str = "Grenade Timer: " + std::to_string(timer);
    *this->timer_text = SDL2pp::Font(WORMS_FONT_PATH, 16).RenderText_Blended(timer_text_str, WHITE);
}

void Hud::clear_timer_value() {
    std::string timer_text_str = "Grenade Timer: ";
    *this->timer_text = SDL2pp::Font(WORMS_FONT_PATH, 16).RenderText_Blended(timer_text_str, WHITE);
}

void Hud::set_end_game(char winner_team_id) {
    this->is_end_game = true;
    if (this->my_army_id == winner_team_id) {
        std::string end_game_text_str = "Congratulations! You Won!";
        *this->end_game_text = SDL2pp::Font(WORMS_FONT_PATH, 32)
                                       .RenderText_Blended(end_game_text_str, my_army_color);
    } else {
        SDL_Color winner_color;
        switch (winner_team_id) {
            case 0:
                winner_color = BLUE;
                break;
            case 1:
                winner_color = RED;
                break;
            case 2:
                winner_color = YELLOW;
                break;
            case 3:
                winner_color = GREEN;
                break;
            default:
                winner_color = ORANGE;
                break;
        }
        std::string end_game_text_str =
                "Bad Luck! Player " + std::to_string(winner_team_id + 1) + " Won!";
        *this->end_game_text = SDL2pp::Font(WORMS_FONT_PATH, 32)
                                       .RenderText_Blended(end_game_text_str, winner_color);
    }
}

void Hud::take_out_marker() {
    this->marker_following_mouse = false;
    this->marker_set = false;
    this->marker_x = 0;
    this->marker_y = 0;
}

int Hud::get_marker_x() { return this->marker_x; }

int Hud::get_marker_y() { return this->marker_y; }

void Hud::update_turn_time_text(uint turn_time) {
    std::string turn_time_text_str = "Turn Time: " + std::to_string(turn_time);
    *this->turn_time_text =
            SDL2pp::Font(WORMS_FONT_PATH, 16).RenderText_Blended(turn_time_text_str, WHITE);
}

bool Hud::is_marker_set() { return this->marker_set; }

bool Hud::is_marker_active() { return (this->marker_set or this->marker_following_mouse); }
