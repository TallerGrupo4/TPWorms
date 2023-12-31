#include "worm.h"


Worm::Worm(b2Body* body, char id, char team_id):
        Entity(body, WORM),
        id(id),
        life(START_LIFE),
        state(STILL),
        curr_tool(NO_TOOL),
        act_dir(DER),
        last_still_angle(0),
        last_y(0),
        number_contacts(0),
        team_id(team_id),
        aiming_angle(0),
        has_used_tool(false) {
    body->GetUserData().pointer = (uintptr_t)this;
    tools.push_back(std::make_shared<Bazooka>());
    tools.push_back(std::make_shared<Mortar>());
    tools.push_back(std::make_shared<GreenGrenade>());
    tools.push_back(std::make_shared<RedGrenade>());
    tools.push_back(std::make_shared<Banana>());
    tools.push_back(std::make_shared<HolyGrenade>());
    tools.push_back(std::make_shared<Dynamite>());
    tools.push_back(std::make_shared<Bat>());
    tools.push_back(std::make_shared<Airstrike>());
    tools.push_back(std::make_shared<Teleporter>());
    tools.push_back(nullptr);
}

int Worm::get_id() { return id; }

int Worm::get_angle() {
    float angle = body->GetAngle();
    float normalized_angle = fmod(angle, PI);
    int degree = round(normalized_angle * RADTODEG);
    return degree;
}

void Worm::move(int dir) {
    if (!in_contact()) {
        return;
    }
    if (state != STILL && state != MOVING && state != CLIMBING) {
        return;
    }
    act_dir = dir;
    body->SetLinearVelocity(b2Vec2(0, 0));
    float m = body->GetMass();
    float impulse_x = dir * WORM_SPEED * cos(body->GetAngle()) * m;
    float impulse_y = dir * WORM_SPEED * sin(body->GetAngle()) * m;
    body->ApplyLinearImpulseToCenter(b2Vec2(impulse_x, impulse_y), true);
    if (get_angle() != 0) {
        state = CLIMBING;
    } else {
        state = MOVING;
    }
}

void Worm::jump(int dir) {
    if (!in_contact() || state != STILL) {
        return;
    }
    body->SetLinearVelocity(b2Vec2(0, 0));
    float m = body->GetMass();
    if (dir == FORWARD) {
        body->ApplyLinearImpulseToCenter(
                b2Vec2(m * WORM_JUMP_HOR_SPEED * act_dir, m * WORM_JUMP_SPEED), true);
        state = JUMPING;

    } else if (dir == BACKWARD) {
        body->ApplyLinearImpulseToCenter(
                b2Vec2(m * -WORM_BACKFLIP_HOR_SPEED * act_dir, m * WORM_BACKFLIP_SPEED), true);
        state = BACKFLIPPING;
    }
}

bool Worm::use_tool(int power, float x, float y, int time, ProjectileManager& projectiles) {
    if (tools[curr_tool] == nullptr || has_used_tool) {
        return false;
    }
    if (!tools[curr_tool]->has_ammo()) {
        return false;
    }
    if (!tools[curr_tool]->use(body, act_dir, aiming_angle * DEGTORAD, time, power, x, y,
                               projectiles)) {
        return false;
    }
    has_used_tool = true;
    aiming_angle = 0;
    state = SHOOTED;
    curr_tool = NO_TOOL;
    return true;
}

void Worm::aim(int angle_inc, int direction) {
    if ((state != STILL && state != AIMING) || tools[curr_tool] == nullptr ||
        !tools[curr_tool]->can_aim() || !tools[curr_tool]->has_ammo() || has_used_tool) {
        return;
    }
    if (angle_inc == -1) {
        aiming_angle -= 5.625f;
        if (aiming_angle <= MIN_AIMING_ANGLE) {
            aiming_angle = MIN_AIMING_ANGLE;
        }
    } else if (angle_inc == 1) {
        aiming_angle += 6.0f;
        if (aiming_angle >= MAX_AIMING_ANGLE) {
            aiming_angle = MAX_AIMING_ANGLE;
        }
    }
    state = AIMING;
    act_dir = direction;
}

void Worm::change_tool(int scroll_direction) {
    curr_tool += scroll_direction;
    if (curr_tool < 0) {
        curr_tool = tools.size() - 1;
    } else if (curr_tool >= (int)tools.size()) {
        curr_tool = 0;
    }
}

void Worm::store_tool() { curr_tool = NO_TOOL; }

bool Worm::in_contact() { return number_contacts > 0; }

void Worm::add_contact() { number_contacts++; }

void Worm::remove_contact() { number_contacts--; }

void Worm::set_used_tool(bool value) { has_used_tool = value; }

WormSnapshot Worm::get_snapshot() {
    float pos_x;
    float pos_y;
    int angle;
    if (body == nullptr) {  // SHOULD DECIDE WHAT TO DO WITH WORM BODY OR SOMETHING
        pos_x = 0;
        pos_y = 0;
        angle = 0;
    } else {
        pos_x = body->GetPosition().x;
        pos_y = body->GetPosition().y;
        angle = get_angle();
    }
    int current_ammo = 0;
    if (curr_tool != NO_TOOL) {
        current_ammo = tools[curr_tool]->get_ammo();
    }
    WormSnapshot snapshot(id, pos_x, pos_y, angle, START_LIFE, life, act_dir, curr_tool, state,
                          team_id, aiming_angle, current_ammo);

    return snapshot;
}

int Worm::get_state() { return state; }

void Worm::set_state(int new_state) { state = new_state; }

void Worm::set_last_still_angle(float angle) { last_still_angle = angle; }

float Worm::last_angle() { return last_still_angle; }

void Worm::reset_aiming_angle() { aiming_angle = 0; }

float Worm::get_last_y() { return last_y; }

void Worm::set_last_y(float y) { last_y = y; }

void Worm::set_curr_tool(int new_tool) { curr_tool = new_tool; }

void Worm::apply_damage(int damage) {
    set_curr_tool(tools.size() - 1);
    life -= damage;
    state = DAMAGED;
    if (life <= 0) {
        life = 0;
        state = DEAD;
    }
}

void Worm::add_ammo(int ammo, TOOLS tool) { tools[tool]->add_ammo(ammo); }

void Worm::add_health(int health) { life += health; }

int Worm::get_number_contacts() { return number_contacts; }

void Worm::cheat_ammo() {
    for (auto& tool: tools) {
        if (tool != nullptr) {
            tool->add_ammo(1);
        }
    }
}

void Worm::cheat_has_shooted() { has_used_tool = false; }
