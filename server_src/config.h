#ifndef CONFIG_SINGLETON_H
#define CONFIG_SINGLETON_H

#include <yaml-cpp/yaml.h>
#include <iostream>

class ConfigSingleton {
public:
    static ConfigSingleton& getInstance() {
        static ConfigSingleton instance;
        return instance;
    }

    int get_extra_health() const {
        return extra_health;
    }

    int get_max_players() const {
        return max_players;
    }

    int get_plat_small() const {
        return plat_small;
    }

    int get_plat_big() const {
        return plat_big;
    }

    float get_plat_height() const {
        return plat_height;
    }

    float get_plat_friction() const {
        return plat_friction;
    }

    float get_worm_width() const {
        return worm_width;
    }

    float get_worm_height() const {
        return worm_height;
    }

    float get_worm_friction() const {
        return worm_friction;
    }

    int get_start_life() const {
        return start_life;
    }

    int get_null_state() const {
        return null_state;
    }

    int get_initial_worms_turn() const {
        return initial_worms_turn;
    }

    int get_turn_time() const {
        return turn_time;
    }

    float get_worm_speed() const {
        return worm_speed;
    }

    float get_worm_jump_speed() const {
        return worm_jump_speed;
    }

    float get_worm_jump_hor_speed() const {
        return worm_jump_hor_speed;
    }

    float get_worm_backflip_speed() const {
        return worm_backflip_speed;
    }

    float get_worm_backflip_hor_speed() const {
        return worm_backflip_hor_speed;
    }

    float get_explosion_power() const {
        return explosion_power;
    }
    
    float get_explosion_fragment_power() const {
        return explosion_fragment_power;
    }

    float get_projectile_potency() const {
        return projectile_potency;
    }

    int get_bazooka_damage() const {
        return bazooka_damage;
    }

    int get_bazooka_radius() const {
        return bazooka_radius;
    }

    float get_bazooka_misile_restitution() const {
        return bazooka_misile_restitution;
    }

    float get_bazooka_misile_density() const {
        return bazooka_misile_density;
    }

    int get_mortar_damage() const {
        return mortar_damage;
    }

    int get_mortar_radius() const {
        return mortar_radius;
    }
    
    int get_mortar_fragments() const {
        return mortar_fragments;
    }

    float get_mortar_misile_restitution() const {
        return mortar_misile_restitution;
    }

    float get_mortar_misile_density() const {
        return mortar_misile_density;
    }

    float get_mortar_max_ammo() const {
        return mortar_max_ammo;
    }

    int get_green_grenade_damage() const {
        return green_grenade_damage;
    }

    int get_green_grenade_radius() const {
        return green_grenade_radius;
    }

    float get_green_grenade_restitution() const {
        return green_grenade_restitution;
    }

    float get_green_grenade_density() const {
        return green_grenade_density;
    }

    int get_red_grenade_damage() const {
        return red_grenade_damage;
    }

    int get_red_grenade_radius() const {
        return red_grenade_radius;
    }

    int get_red_grenade_fragments() const {
        return red_grenade_fragments;
    }

    int get_red_grenade_max_ammo() const {
        return red_grenade_max_ammo;
    }

    float get_red_grenade_restitution() const {
        return red_grenade_restitution;
    }

    float get_red_grenade_density() const {
        return red_grenade_density;
    }

    int get_banana_damage() const {
        return banana_damage;
    }

    int get_banana_radius() const {
        return banana_radius;
    }

    float get_banana_restitution() const {
        return banana_restitution;
    }

    float get_banana_density() const {
        return banana_density;
    }

    int get_banana_max_ammo() const {
        return banana_max_ammo;
    }

    int get_holy_grenade_damage() const {
        return holy_grenade_damage;
    }

    int get_holy_grenade_radius() const {
        return holy_grenade_radius;
    }

    float get_holy_grenade_restitution() const {
        return holy_grenade_restitution;
    }

    float get_holy_grenade_density() const {
        return holy_grenade_density;
    }

    int get_holy_grenade_max_ammo() const {
        return holy_grenade_max_ammo;
    }

    int get_dynamite_damage() const {
        return dynamite_damage;
    }

    int get_dynamite_radius() const {
        return dynamite_radius;
    }

    int get_dynamite_restitution() const {
        return dynamite_restitution;
    }

    int get_dynamite_density() const {
        return dynamite_density;
    }

    int get_dynamite_max_ammo() const {
        return dynamite_max_ammo;
    }

    int get_baseball_bat_damage() const {
        return baseball_bat_damage;
    }

    int get_airstrike_damage() const {
        return airstrike_damage;
    }

    int get_airstrike_radius() const {
        return airstrike_radius;
    }

    int get_airstrike_max_ammo() const{
        return airstrike_max_ammo;
    }

    int get_fragment_damage() const {
        return fragment_damage;
    }

    int get_fragment_radius() const {
        return fragment_radius;
    }

    ~ConfigSingleton() {}

    ConfigSingleton(ConfigSingleton const&) = delete;
    void operator=(ConfigSingleton const&) = delete;



private:
    ConfigSingleton() {
        readConfigFromFile();
    }

    void readConfigFromFile() {
        try {
            std::cout << "Reading config file..." << std::endl;
            YAML::Node config = YAML::LoadFile("../external/config/config.yaml");
            max_players = config["max_players"].as<int>();
            // Platforms
            plat_small = config["plat_small"].as<int>();
            plat_big = config["plat_big"].as<int>();
            plat_height = config["plat_height"].as<float>();
            plat_friction = config["plat_friction"].as<float>();
            // Worms
            worm_width = config["worm_width"].as<float>();
            worm_height = config["worm_height"].as<float>();
            worm_friction = config["worm_friction"].as<float>();
            // World
            start_life = config["start_life"].as<int>();
            extra_health = config["extra_health"].as<int>();
            null_state = config["null_state"].as<int>();
            initial_worms_turn = config["initial_worms_turn"].as<int>();
            turn_time = config["turn_time"].as<int>();
            turn_time = turn_time *  30; // 30 is the fps of the game
            // Physics
            worm_speed = config["worm_speed"].as<float>();
            worm_jump_speed = config["worm_jump_speed"].as<float>();
            worm_jump_hor_speed = config["worm_jump_hor_speed"].as<float>();
            worm_backflip_speed = config["worm_backflip_speed"].as<float>();
            worm_backflip_hor_speed = config["worm_backflip_hor_speed"].as<float>();
            explosion_power = config["explosion_power"].as<float>();
            explosion_fragment_power = config["explosion_fragment_power"].as<float>();
            projectile_potency = config["projectile_potency"].as<float>();
            // Weapons
            // Bazooka
            bazooka_damage = config["bazooka_damage"].as<int>();
            bazooka_radius = config["bazooka_radius"].as<int>();
            bazooka_misile_restitution = config["bazooka_misile_restitution"].as<float>();
            bazooka_misile_density = config["bazooka_misile_density"].as<float>();
            // Mortar
            mortar_damage = config["mortar_damage"].as<int>();
            mortar_radius = config["mortar_radius"].as<int>();
            mortar_fragments = config["mortar_fragments"].as<int>();
            mortar_misile_restitution = config["mortar_misile_restitution"].as<float>();
            mortar_misile_density = config["mortar_misile_density"].as<float>();
            mortar_max_ammo = config["mortar_max_ammo"].as<int>();
            // Green Grenade
            green_grenade_damage = config["green_grenade_damage"].as<int>();
            green_grenade_radius = config["green_grenade_radius"].as<int>();
            green_grenade_restitution = config["green_grenade_restitution"].as<float>();
            green_grenade_density = config["green_grenade_density"].as<float>();
            // Red Grenade
            red_grenade_damage = config["red_grenade_damage"].as<int>();
            red_grenade_radius = config["red_grenade_radius"].as<int>();
            red_grenade_fragments = config["red_grenade_fragments"].as<int>();
            red_grenade_max_ammo = config["red_grenade_max_ammo"].as<int>();
            red_grenade_restitution = config["red_grenade_restitution"].as<float>();
            red_grenade_density = config["red_grenade_density"].as<float>();
            // Banana
            banana_damage = config["banana_damage"].as<int>();
            banana_radius = config["banana_radius"].as<int>();
            banana_restitution = config["banana_restitution"].as<float>();
            banana_density = config["banana_density"].as<float>();
            banana_max_ammo = config["banana_max_ammo"].as<int>();
            // Holy Grenade
            holy_grenade_damage = config["holy_grenade_damage"].as<int>();
            holy_grenade_radius = config["holy_grenade_radius"].as<int>();
            holy_grenade_restitution = config["holy_grenade_restitution"].as<float>();
            holy_grenade_density = config["holy_grenade_density"].as<float>();
            holy_grenade_max_ammo = config["holy_grenade_max_ammo"].as<int>();
            // Dynamite
            dynamite_damage = config["dynamite_damage"].as<int>();
            dynamite_radius = config["dynamite_radius"].as<int>();
            dynamite_max_ammo = config["dynamite_max_ammo"].as<int>();
            dynamite_restitution = config["dynamite_restitution"].as<float>();
            dynamite_density = config["dynamite_density"].as<float>();
            // Baseball bat
            baseball_bat_damage = config["baseball_bat_damage"].as<int>();
            // Airstrike
            airstrike_damage = config["airstrike_damage"].as<int>();
            airstrike_radius = config["airstrike_radius"].as<int>();
            airstrike_max_ammo = config["airstrike_max_ammo"].as<int>();
            // Fragments
            fragment_damage = config["fragment_damage"].as<int>();
            fragment_radius = config["fragment_radius"].as<int>();
            std::cout << "Config file read successfully" << std::endl;
        } catch (const YAML::Exception& e) {
            // Handle YAML parsing errors (e.g. the file could not be found)
            // Maybe throw an exception and catch it in the main?
            std::cerr << "Error reading YAML file: " << e.what() << std::endl;
            std::cerr << "In column " << e.mark.column << " and line " << e.mark.line << std::endl;
            // Print additional information about the error, if available
        } catch(...) {
            std::cerr << "Something went wrong and an unknown exception was caught in the ConfigSingleton"
                      << std::endl;
        }
    }
// Game
    int max_players;
    int plat_small;
    int plat_big;
    float plat_height;
    float plat_friction;
    float worm_width;
    float worm_height;
    float worm_friction;
    int start_life;
    int extra_health;
    int null_state;
    int initial_worms_turn;
    int turn_time;
    float worm_speed;
    float worm_jump_speed;
    float worm_jump_hor_speed;
    float worm_backflip_speed;
    float worm_backflip_hor_speed;

// Explosions

    float explosion_power;
    float explosion_fragment_power;
    float projectile_potency;

// Weapons
// Bazooka
    int bazooka_damage;
    int bazooka_radius;
    float bazooka_misile_restitution;
    float bazooka_misile_density;

// Mortar
    int mortar_damage;
    int mortar_radius;
    int mortar_fragments;
    float mortar_misile_restitution;
    float mortar_misile_density;
    int mortar_max_ammo;

// Green Grenade
    int green_grenade_damage;
    int green_grenade_radius;
    float green_grenade_restitution;
    float green_grenade_density;

// Red Grenade
    int red_grenade_damage;
    int red_grenade_radius;
    int red_grenade_fragments;
    int red_grenade_max_ammo;
    float red_grenade_restitution;
    float red_grenade_density;

// Banana
    int banana_damage;
    int banana_radius = 0;
    float banana_restitution = 0;
    float banana_density = 0;
    int banana_max_ammo = 0;

// Holy Grenade
    int holy_grenade_damage;
    int holy_grenade_radius;
    float holy_grenade_restitution;
    float holy_grenade_density;
    int holy_grenade_max_ammo;

// Dynamite
    int dynamite_damage;
    int dynamite_radius;
    int dynamite_max_ammo;
    int dynamite_restitution;
    int dynamite_density;

// Baseball bat
    int baseball_bat_damage;

// Airstrike
    int airstrike_damage;
    int airstrike_radius;
    int airstrike_max_ammo;

// Fragments
    int fragment_damage;
    int fragment_radius;

    // Reference them in the code as for example ConfigSingleton::getInstance().plat_small

};

#endif  // CONFIG_SINGLETON_H
