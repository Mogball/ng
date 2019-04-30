#include "entity.h"

namespace ng {

    void Entity::create_rect(
            b2World &world, Entity &ent, int type,
            float w, float h,
            float x, float y, float angle,
            Properties props) {
        auto &body_def = ent.body_def();
        body_def.type = static_cast<b2BodyType>(type);
        body_def.position.Set(x, y);
        body_def.angle = angle;
        ent.body() = world.CreateBody(&body_def);
        ent.shape().SetAsBox(w, h);
        auto &fixture_def = ent.fixture_def();
        fixture_def.shape = &ent.shape();
        fixture_def.density = props.density;
        fixture_def.friction = props.friction;
        fixture_def.restitution = props.restitution;
        ent.fixture() = ent.body()->CreateFixture(&fixture_def);
    }

}
