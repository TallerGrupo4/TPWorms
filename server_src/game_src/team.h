#include <list>
#include <memory>
#include "worm.h"

#ifndef TEAM_H
#define TEAM_H

class Team {
private:
    std::list<std::shared_ptr<Worm>> worms;
    char first_worm_id = -1;
public:
    Team();

    void push_back(std::shared_ptr<Worm> worm);
    
    char get_next_player_id();

    bool is_empty();

    int size();

    void remove_player(char player_id);

    bool has_player(char player_id);

    std::shared_ptr<Worm> get_worm(char worm_id);
    
    std::list<std::shared_ptr<Worm>>& get_worms();

    void add_health_to_worms(int health);

    ~Team();
};

#endif  // TEAM_H