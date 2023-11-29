#include "projectile_fragment.h"

#define FRAGMENT_DAMAGE ConfigSingleton::getInstance().get_fragment_damage()
#define FRAGMENT_RADIUS ConfigSingleton::getInstance().get_fragment_radius()

ProjectileFragment::ProjectileFragment(b2Body* body, float angle): Projectile(body , FRAGMENT_DAMAGE, FRAGMENT_RADIUS, FRAGMENT_PROJECTILE, EXPLOSIVE, 0, 0 , angle ) {}



// b2Body* ProjectileFragment::createFragmentBody(b2Body* father_body , float angle){
//     b2Vec2 pos = father_body->GetPosition();

//     float xOffset = cos(angle) * father_body->GetFixtureList()->GetShape()->m_radius +0.1f;
//     float yOffset = sin(angle) * father_body->GetFixtureList()->GetShape()->m_radius +0.1f;

//     b2BodyDef fragment_def;
//     fragment_def.type = b2_dynamicBody;
//     fragment_def.bullet = true;
//     fragment_def.position.Set(pos.x + xOffset, pos.y + yOffset);
//     fragment_def.angle = angle;
//     b2Body* fragment = father_body->GetWorld()->CreateBody(&fragment_def);

//     b2CircleShape fragment_shape;
//     fragment_shape.m_radius = 0.1;
//     b2FixtureDef fragment_fixture;
//     fragment_fixture.shape = &fragment_shape;
//     fragment_fixture.density = 1;
//     fragment_fixture.friction = 0;
//     fragment->CreateFixture(&fragment_fixture);

//     return fragment;
// }




ProjectileFragment::~ProjectileFragment() {}