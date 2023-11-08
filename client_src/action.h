

#ifndef ACTION_H
#define ACTION_H

class Action {
public:
    char code = -1;
    std::string msg = "";
    uint8_t number_of_players = 0;
    uint match_id = 0;


    int id_worm = -1;
    int movement_x = 0;

    Action() = default;
    ~Action() = default;
};

#endif // ACTION_H
