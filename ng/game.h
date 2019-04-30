#pragma once

#include "entity.h"
#include "graphics.h"
#include "key_handler.h"
#include "properties.h"
#include "window.h"
#include <Box2D/Box2D.h>
#include <list>

namespace ng {

    class Game {
        Window m_window;
        Graphics m_graphics;
        KeyHandler m_key_handler;
        b2World m_world;
        std::list<Entity> m_entities;

    private:
        void set_key_delegates();

    public:
        Game();

        void run();

        Entity &create_rect(
                float w, float h,
                float x, float y, float angle = 0,
                b2BodyType type = b2_dynamicBody,
                Properties props = {});
    };

}
