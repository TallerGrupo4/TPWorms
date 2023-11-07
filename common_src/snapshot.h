#include <string>
#include <vector>


#ifndef SNAPSHOT_H
#define SNAPSHOT_H

class Snapshot {
public:
    Snapshot(){};
    ~Snapshot(){};
};


// // server
// WormSnapshot worm();
// parser.parse_snapshot(Snapshot worm)
// protocol.send_worm(Snapshot worm)

// // client
// received;
// if (created) protocol.recv_map(received)
// else protocol.recv_worm(received)
// parser.parse(received) // Snapshot received
// sdl.render(receieved)

class WormSnapshot: public Snapshot {
public:
    int id;
    float pos_x;
    float pos_y;
    float angle;
    int life;
    int direction;
    int weapon;
    int state;

    WormSnapshot(int id, float pos_x, float pos_y, float angle, int life, int direction, int weapon,
                 int state):
            id(id),
            pos_x(pos_x),
            pos_y(pos_y),
            angle(angle),
            life(life),
            direction(direction),
            weapon(weapon),
            state(state){};
    ~WormSnapshot(){};
};

class GameSnapshot: public Snapshot {
    std::vector<WormSnapshot> worms;
    // std::vector<ProjectileSnapshot> projectiles;

public:
    GameSnapshot(std::vector<WormSnapshot> worms): worms(worms){};
    ~GameSnapshot(){};

    std::vector<WormSnapshot> get_worms() { return worms; }

    // std::vector<ProjectileSnapshot> get_projectiles(){
    //     return projectiles;
    // }
};

class PlatformSnapshot: public Snapshot {
public:
    float pos_x;
    float pos_y;
    float angle;
    char type;

    PlatformSnapshot(float pos_x, float pos_y, float angle, char type):
            pos_x(pos_x), pos_y(pos_y), angle(angle), type(type){};
    ~PlatformSnapshot(){};
};

class MapSnapshot: public Snapshot {
    std::vector<PlatformSnapshot> platforms;

public:
    MapSnapshot(std::vector<PlatformSnapshot> platforms): platforms(platforms){};
    ~MapSnapshot(){};

    std::vector<PlatformSnapshot> get_platforms() { return platforms; }
};


#endif  // SNAPSHOT_H