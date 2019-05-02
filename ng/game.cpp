#include "game.h"

namespace ng {

    Game::Game(std::string name, int w, int h, float scale, float gravity) :
        m_window{ std::move(name), w, h },
        m_graphics{ m_window, scale },
        m_key_handler{ m_window.get() },
        m_mouse_handler{ m_window.get() },
        m_world{ b2Vec2{ 0, -gravity } }
    { }

    b2Vec2 Game::window_to_game_coords(float x, float y) {
        float w = m_window.width();
        float h = m_window.height();
        // Convert x: [0, W] -> [-1, 1], y: [0, H] -> [-1, 1]
        x = (2 * x - w) / w;
        y = (2 * y - h) / h;
        // Convert orthogonal scale
        // If W > H, then y: [-1, 1] but x: [-W/H, W/H]
        float ortho = std::max(w, h);
        x *= ortho / h;
        y *= ortho / w;
        float scale = m_graphics.scale();
        x /= scale;
        y /= scale;
        return { -x, -y };
    }

    void Game::run() {
        constexpr auto time_step = 1.0 / 60;
        constexpr auto velocity_iterations = 6;
        constexpr auto position_iterations = 2;

        while (m_window.poll()) {
            glClear(GL_COLOR_BUFFER_BIT);

            m_world.Step(time_step, velocity_iterations, position_iterations);

            for (auto &ent : m_entities) {
                m_graphics.draw(ent);
            }
        }
    }

    Entity &Game::create_rect(
            const Location &loc,
            const Properties &props,
            b2BodyType type) {
        b2PolygonShape shape;
        shape.SetAsBox(loc.w, loc.h);
        return create_shape(shape, loc, props, type);
    }

    Entity &Game::create_circle(
            const Location &loc,
            const Properties &props,
            b2BodyType type) {
        b2CircleShape shape;
        shape.m_radius = loc.r;
        return create_shape(shape, loc, props, type);
    }

    Entity &Game::create_shape(
            const b2Shape &shape,
            const Location &loc,
            const Properties &props,
            b2BodyType type) {
        b2BodyDef body_def;
        body_def.type = type;
        body_def.position.Set(loc.x, loc.y);
        body_def.angle = loc.angle;
        body_def.linearVelocity.Set(loc.vx, loc.vy);
        body_def.angularVelocity = loc.omega;

        b2Body *body = m_world.CreateBody(&body_def);

        b2FixtureDef fixture_def;
        fixture_def.shape = &shape;
        fixture_def.density = props.density;
        fixture_def.friction = props.friction;
        fixture_def.restitution = props.restitution;

        body->CreateFixture(&fixture_def);

        m_entities.emplace_back(body);
        return m_entities.back();
    }

}
