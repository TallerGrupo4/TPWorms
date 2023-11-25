#include <list>

#ifndef TEAM_H
#define TEAM_H

class Team {
private:
    std::list<char> players;
    char first_player_id = -1;
    bool finished = false;
public:
    Team() {}
    ~Team() {}
    void push_back(char player_id) {
        if (players.empty()) {
            first_player_id = player_id;
        }
        players.push_back(player_id);
    }
    char get_next_player() {
        char player_id = players.front();
        players.pop_front();
        players.push_back(player_id);
        if (players.front() == first_player_id) {
            finished = true;
        }
        return player_id;
    }
    bool is_empty() {
        return players.empty();
    }
    int size() {
        return players.size();
    }
    void remove_player(char player_id) {
        players.remove(player_id);
    }
    bool has_player(char player_id) {
        for (auto& player: players) {
            if (player == player_id) return true;
        }
        return false;
    }
    std::list<char>& get_players() {
        return players;
    }
    bool finished_turn() {
        return finished;
    }
    void reset() {
        finished = false;
    }
};

#endif // TEAM_H
