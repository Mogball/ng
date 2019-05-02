#pragma once

#include "entity.h"
#include "graphics.h"
#include "key_handler.h"
#include "mouse_handler.h"
#include "properties.h"
#include "window.h"
#include <Box2D/Box2D.h>
#include <list>

namespace ng {

    class Game {
        Window m_window;
        Graphics m_graphics;
        KeyHandler m_key_handler;
        MouseHandler m_mouse_handler;
        b2World m_world;
        std::list<Entity> m_entities;

    public:
        Game(std::string name, int w, int h, float scale, float gravity);

        inline KeyHandler &key_handler() { return m_key_handler; }
        inline MouseHandler &mouse_handler() { return m_mouse_handler; }

        b2Vec2 window_to_game_coords(float x, float y);

        void run();

        Entity &create_rect(
                const Location &loc = {},
                const Properties &props = {},
                b2BodyType type = b2_dynamicBody);

        Entity &create_circle(
                const Location &loc = {},
                const Properties &props = {},
                b2BodyType type = b2_dynamicBody);

        Entity &create_shape(
                const b2Shape &shape,
                const Location &loc,
                const Properties &props,
                b2BodyType type);
    };

}
