#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <sys/types.h>
#include "constants.h"

#ifndef COMMAND_H
#define COMMAND_H

// Create constructors for the Command based on the code
// Make every attribute of the struct constant after initialization
class Command {
private:
    const char code;
    const uint match_id;
    const std::string map_name;

    const std::map<uint, std::string> matches_availables;
    const uint8_t number_of_players;
    uint8_t worm_id;
    const std::vector<std::string> map_names = {};

public:

    Command(const char code): code(code), match_id(DEFAULT), map_name(""), matches_availables({}), number_of_players(DEFAULT), worm_id(DEFAULT) {};

    Command(const char code, const uint match_id): code(code), match_id(match_id), map_name(""), matches_availables({}), number_of_players(DEFAULT), worm_id(DEFAULT) {};

    Command(const char code, const uint match_id, const uint8_t worm_id): code(code), match_id(match_id), map_name(""), matches_availables({}), number_of_players(DEFAULT), worm_id(worm_id) {};

    Command(const char code, const uint match_id, const std::string map_name): code(code), match_id(match_id), map_name(map_name), matches_availables({}), number_of_players(DEFAULT), worm_id(DEFAULT) {};

    Command(const char code, const uint match_id, const std::string map_name, const uint8_t worm_id): code(code), match_id(match_id), map_name(map_name), matches_availables({}), number_of_players(DEFAULT), worm_id(DEFAULT) {};

    Command(const char code, const std::map<uint, std::string> matches_availables): code(code), match_id(DEFAULT), map_name(""), matches_availables(matches_availables), number_of_players(DEFAULT), worm_id(DEFAULT) {};

    Command(const char code, const uint match_id, const std::map<uint, std::string> matches_availables, const uint8_t worm_id): code(code), match_id(match_id), map_name(""), matches_availables(matches_availables), number_of_players(DEFAULT), worm_id(worm_id) {};

    Command(const char code, const uint match_id, const std::vector<std::string> map_names, const uint8_t number_of_players, const uint8_t worm_id): code(code), match_id(match_id), map_name(""), matches_availables({}), number_of_players(number_of_players), worm_id(worm_id), map_names(map_names) {};

    char get_code() const { return code; }

    uint8_t get_worm_id() const { return worm_id; }

    uint get_match_id() const { return match_id; }

    std::string get_map_name() const { return map_name; }

    std::map<uint, std::string> get_available_matches() const { return matches_availables; }

    std::vector<std::string> get_map_names() const { return map_names; }

    uint8_t get_number_of_players() const { return number_of_players; }

    ~Command() {};
};

#endif // COMMAND_H
