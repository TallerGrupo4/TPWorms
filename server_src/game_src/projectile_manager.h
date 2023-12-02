#include "projectile.h"
#include <box2d/box2d.h>

#ifndef PROJECTILE_MANAGER_H
#define PROJECTILE_MANAGER_H

class ProjectileManager {
private:
    std::unordered_set<std::shared_ptr<Projectile>> projectiles;
    int projectile_id;

    void correct_angle_projectile(std::shared_ptr<Projectile> projectile);
    
    public:

    ProjectileManager();

    ~ProjectileManager();

    bool has_projectiles();

    void update_during_game(int& it, int& width, int& height);

    void check_out_of_map_projectile(Projectile& p, int width, int height);

    void update_post_game(b2World& world);

    void add_projectile(std::shared_ptr<Projectile> projectile);

    std::vector<ProjectileSnapshot> get_projectiles_snapshot();
    
    std::unordered_set<std::shared_ptr<Projectile>>& get_projectiles();

    void reset_id();


};

#endif //PROJECTILE_MANAGER_H