#include "projectile_manager.h"

ProjectileManager::ProjectileManager(): projectiles(), projectile_id(0) {}

ProjectileManager::~ProjectileManager() {}

void ProjectileManager::correct_angle_projectile(std::shared_ptr<Projectile> projectile){
    b2Vec2 velocity = projectile->get_body()->GetLinearVelocity();
    float angle = atan2(velocity.y, velocity.x);
    projectile->set_angle(angle);
}

void ProjectileManager::update_during_game(int& it, int& width, int& height){
        for (auto& projectile : projectiles){
        if (projectile->get_state() == ALIVE){
            correct_angle_projectile(projectile);
            projectile->decresease_timer(it);
        }
        check_out_of_map_projectile(*projectile, width , height);
        if ( (projectile->get_timer() <= 0 && projectile->get_explosion_type() == EXPLOSIVE_TIMER) || projectile->get_state() == EXPLODED){
            projectile->explode(projectiles);
        }
    }
}

void ProjectileManager::check_out_of_map_projectile(Projectile& p, int width, int height){
    float p_x = p.get_body()->GetPosition().x;
    float p_y = p.get_body()->GetPosition().y;
 
    if (p_x < -width/2 || p_x > width/2 || p_y < -height/2 || p_y > height/2){
        p.set_state(EXPLODED);
    }
 }

bool ProjectileManager::has_projectiles(){
    return !projectiles.empty();
}

void ProjectileManager::update_post_game(b2World& world){
    std::vector <std::shared_ptr<Projectile>> dead_projectiles;
    for (auto& projectile : projectiles){
        if (projectile->get_state() == EXPLODED){
            dead_projectiles.push_back(projectile);
        }
    }
    for (auto& projectile : dead_projectiles){
        world.DestroyBody(projectile->get_body());
        projectiles.erase(projectile);
    }
}



void ProjectileManager::add_projectile(std::shared_ptr<Projectile> projectile){
    projectiles.insert(projectile);
}

std::vector<ProjectileSnapshot> ProjectileManager::get_projectiles_snapshot(){
    std::vector<ProjectileSnapshot> projectiles_snapshot;
    for (auto& projectile : projectiles){
        if (projectile->get_id() == INVALID){
            projectile->set_id(projectile_id);
            projectile_id++;
        }
        ProjectileSnapshot projectile_snapshot = projectile->get_snapshot();
        projectiles_snapshot.push_back(projectile_snapshot);
    }
    return projectiles_snapshot;
}

void ProjectileManager::reset_id(){
    projectile_id = 0;
}
    

std::unordered_set<std::shared_ptr<Projectile>>& ProjectileManager::get_projectiles(){
    return projectiles;
}
