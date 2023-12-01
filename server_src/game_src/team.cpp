#include "team.h"
#include "../../common_src/custom_errors.h"

Team::Team() {}


void Team::push_back(std::shared_ptr<Worm> worm) {
    if (worms.empty()) {
        first_worm_id = worm->get_id();
    }
    worms.push_back(worm);
}
char Team::get_next_player_id() {
    if (worms.empty()) {
        throw NoWormsLeft();
    }
    std::shared_ptr<Worm> worm = worms.front();
    worms.pop_front();
    worms.push_back(worm);

    return worm->get_id();
}
bool Team::is_empty() {
    return worms.empty();
}

int Team::size() {
    return worms.size();
}

void Team::remove_player(char player_id) {
    for (auto it = worms.begin(); it != worms.end(); ++it) {
        if ((*it)->get_id() == player_id) {
            worms.erase(it);
            return;
        }
    }
}

void Team::add_health_to_worms(int health) {
    for (auto& worm: worms) {
        worm->add_health(health);
    }
}

bool Team::has_player(char player_id) {
    for (auto& worm: worms) {
        if (worm->get_id() == player_id) return true;
    }
    return false;
}

std::shared_ptr<Worm> Team::get_worm(char worm_id) {
    for (auto& worm: worms) {
        if (worm->get_id() == worm_id) return worm;
    }
    throw WormNotFound();
}

std::list<std::shared_ptr<Worm>>& Team::get_worms() {
    return worms;
}

Team::~Team() {}


