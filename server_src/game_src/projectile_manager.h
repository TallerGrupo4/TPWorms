#include <memory>
#include <unordered_set>
#include <vector>

#include <box2d/box2d.h>

#include "projectile.h"

#ifndef PROJECTILE_MANAGER_H
#define PROJECTILE_MANAGER_H

class ProjectileManager {
private:
    std::unordered_set<std::shared_ptr<Projectile>> projectiles;
    float wind_force;
    int projectile_id;

    void correct_angle_projectile(std::shared_ptr<Projectile> projectile);

public:
    ProjectileManager();

    ~ProjectileManager();

    bool has_projectiles();

    void randomize_wind();

    void apply_wind(Projectile& projectile);

    float get_wind_force();

    void update_during_game(const int& it, const int& width, const int& height);

    void check_out_of_map_projectile(Projectile& p, int width, int height);

    void update_post_game(b2World& world);

    void add_projectile(std::shared_ptr<Projectile> projectile);

    std::vector<ProjectileSnapshot> get_projectiles_snapshot();

    std::unordered_set<std::shared_ptr<Projectile>>& get_projectiles();

    void reset_id();
};

#endif  // PROJECTILE_MANAGER_H
