#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include <sys/types.h>

#include "constants.h"

#ifndef COMMAND_H
#define COMMAND_H

class Command {
private:
    const char code;
    const uint match_id;
    const std::string map_name;

    const std::map<uint, std::string> matches_availables;
    const uint8_t number_of_players;
    const std::vector<std::string> map_names = {};

public:
    explicit Command(const char n_code):
            code(n_code),
            match_id(DEFAULT),
            map_name(""),
            matches_availables({}),
            number_of_players(DEFAULT) {}

    Command(const char n_code, const uint id_match):
            code(n_code),
            match_id(id_match),
            map_name(""),
            matches_availables({}),
            number_of_players(DEFAULT) {}

    Command(const char n_code, const uint id_match, const std::string& map_n):
            code(n_code),
            match_id(id_match),
            map_name(map_n),
            matches_availables({}),
            number_of_players(DEFAULT) {}

    Command(const char n_code, const std::map<uint, std::string>& matches_availables):
            code(n_code),
            match_id(DEFAULT),
            map_name(""),
            matches_availables(matches_availables),
            number_of_players(DEFAULT) {}

    Command(const char n_code, const uint id_match,
            const std::map<uint, std::string>& matches_availables):
            code(n_code),
            match_id(id_match),
            map_name(""),
            matches_availables(matches_availables),
            number_of_players(DEFAULT) {}

    Command(const char n_code, const uint id_match, const std::vector<std::string>& map_n,
            const uint8_t number_players):
            code(n_code),
            match_id(id_match),
            map_name(""),
            matches_availables({}),
            number_of_players(number_players),
            map_names(map_n) {}

    char get_code() const { return code; }

    uint get_match_id() const { return match_id; }

    std::string get_map_name() const { return map_name; }

    std::map<uint, std::string> get_available_matches() const { return matches_availables; }

    std::vector<std::string> get_map_names() const { return map_names; }

    uint8_t get_number_of_players() const { return number_of_players; }

    ~Command() {}
};

#endif  // COMMAND_H
