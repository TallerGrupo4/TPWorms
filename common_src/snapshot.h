#include <string>
#include <vector>


#ifndef SNAPSHOT_H
#define SNAPSHOT_H


class WormSnapshot {
public:
    char id;
    float pos_x;
    float pos_y;
    float angle;
    int life;
    int direction;
    int weapon;
    int state;

    WormSnapshot(char id, float pos_x, float pos_y, float angle, int life, int direction, int weapon,
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

class PlatformSnapshot {
public:
    char type;
    float pos_x;
    float pos_y;
    float angle;

    PlatformSnapshot(char type, float pos_x, float pos_y, float angle):
            type(type), pos_x(pos_x), pos_y(pos_y), angle(angle) {};
    ~PlatformSnapshot(){};
};
 

class Snapshot {
public:
    std::vector<WormSnapshot> worms;
    std::vector<PlatformSnapshot> platforms;

    Snapshot(){};
    Snapshot(std::vector<WormSnapshot> worms, std::vector<PlatformSnapshot> platforms):
            worms(worms), platforms(platforms){};
    
    ~Snapshot(){};
};

// Snapshot game_state(){
    //return Snapshot(worms , {});
// }

// Snapshot map_state(){
    //return Snapshot({}, platforms);



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


// TODO: IMPLEMENT POLYMORPHISM

// class GameSnapshot: public Snapshot {
//     std::vector<WormSnapshot> worms;
//     // std::vector<ProjectileSnapshot> projectiles;

// public:
//     GameSnapshot(std::vector<WormSnapshot> worms): worms(worms){};
//     ~GameSnapshot(){};

//     std::vector<WormSnapshot> get_worms() { return worms; }

//     // std::vector<ProjectileSnapshot> get_projectiles(){
//     //     return projectiles;
//     // }
// };



// class MapSnapshot: public Snapshot {
//     std::vector<PlatformSnapshot> platforms;

// public:
//     MapSnapshot(std::vector<PlatformSnapshot> platforms): platforms(platforms){};
//     ~MapSnapshot(){};

//     std::vector<PlatformSnapshot> get_platforms() { return platforms; }
// };


#endif  // SNAPSHOT_H
