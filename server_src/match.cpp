#include "./match.h"

#include <memory>

#include <box2d/box2d.h>
#include <yaml-cpp/yaml.h>

#include "../common_src/constants.h"
#include "../common_src/queue.h"
#include "../common_src/thread.h"

#include "gameCommand.h"


Match::Match(std::string map_route):
        name(),
        world(b2Vec2(0, -10)),
        builder(world),
        keep_running(true),
        match_started(false),
        players(),
        queue(QUEUE_MAX_SIZE),
        turn(0),
        id_counter(0) {
    builder.create_big_platform(0, 0);
}

int Match::add_player() {                        // TODO: Make army (group of worms instead of one)
    b2Body* player = builder.create_worm(0, 1);  // TODO: randomize position
    players.push_back(player);
    return id_counter++;
}

void Match::run() {
    while (keep_running) {
        GameCommand* c;
        if (queue.try_pop(c)) {
            c->execute();
        }
        world.Step(1.0f / 60.0f, 8, 3);
        // broadcaster.broadcast(WorldState(world));
    }
}

void Match::move_player(int direction, int id) {
    b2Body* player = players[id];
    player->SetLinearVelocity(b2Vec2(0, 0));
    float impulse = player->GetMass() * direction * WORM_SPEED;
    player->ApplyLinearImpulseToCenter(b2Vec2(impulse, 0), true);
}

Match::~Match() {}
