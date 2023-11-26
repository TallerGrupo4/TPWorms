#include <list>
#include <memory>
#include <iostream>
#include "worm.h"

#ifndef TEAM_H
#define TEAM_H

class Team {
private:
    std::list<std::shared_ptr<Worm>> worms;
    char first_worm_id = -1;
public:
    Team() {}
    ~Team() {}
    void push_back(std::shared_ptr<Worm> worm) {
        if (worms.empty()) {
            first_worm_id = worm->get_id();
        }
        worms.push_back(worm);
    }
    char get_next_player_id() {
        std::shared_ptr<Worm> worm = worms.front();
        worms.pop_front();
        worms.push_back(worm);

        return worm->get_id();
    }
    bool is_empty() {
        return worms.empty();
    }
    int size() {
        return worms.size();
    }
    void remove_player(char player_id) {
        for (auto it = worms.begin(); it != worms.end(); ++it) {
            if ((*it)->get_id() == player_id) {
                worms.erase(it);
                return;
            }
        }
    }
    bool has_player(char player_id) {
        for (auto& worm: worms) {
            if (worm->get_id() == player_id) return true;
        }
        return false;
    }
    std::shared_ptr<Worm> get_worm(char worm_id) {
        for (auto& worm: worms) {
            if (worm->get_id() == worm_id) return worm;
        }
        throw WormNotFound();
    }
    std::list<std::shared_ptr<Worm>>& get_worms() {
        return worms;
    }
};

#endif // TEAM_H
