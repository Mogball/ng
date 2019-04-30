#pragma once

#include <Box2D/Box2D.h>

namespace ng {

    class Entity {
        b2Body *m_body;

    public:
        Entity(b2Body *body) :
            m_body(body)
        { }

        b2Body &body() { return *m_body; }
        const b2Body &body() const { return *m_body; }
    };

}
