#pragma once

#include <Box2D/Box2D.h>
#include <vector>

namespace ng {

    struct Properties {
        float density = 1;
        float friction = 0.4;
        float restitution = 0.1;
    };

    class Entity {
        b2BodyDef m_body_def;
        b2FixtureDef m_fixture_def;
        b2PolygonShape m_shape;

        b2Body *m_body;
        b2Fixture *m_fixture;

    public:
        inline b2BodyDef      &body_def()    { return m_body_def; }
        inline b2FixtureDef   &fixture_def() { return m_fixture_def; }
        inline b2PolygonShape &shape()       { return m_shape; }
        inline b2Body        *&body()        { return m_body; }
        inline b2Fixture     *&fixture()     { return m_fixture; }

        inline const b2BodyDef      &body_def()    const { return m_body_def; }
        inline const b2FixtureDef   &fixture_def() const { return m_fixture_def; }
        inline const b2PolygonShape &shape()       const { return m_shape; }
        inline b2Body       * const &body()        const { return m_body; }
        inline b2Fixture    * const &fixture()     const { return m_fixture; }

    public:
        static void create_rect(
                b2World &world, Entity &ent, int type,
                float w, float h,
                float x = 0, float y = 0, float angle = 0,
                Properties props = {});

    };

}
