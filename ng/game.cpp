#include "game.h"

static constexpr auto GRAVITY = -10;

namespace ng {

    void Game::set_key_delegates() {
        m_key_handler.set_delegate(GLFW_KEY_ESCAPE, [](GLFWwindow *win, int, int) {
            glfwSetWindowShouldClose(win, GLFW_TRUE);
        });
    }

    Game::Game() :
        m_window{},
        m_graphics{ m_window },
        m_key_handler{ m_window.get() },
        m_world{ b2Vec2{ 0, GRAVITY } }
    {
        set_key_delegates();
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
            float w, float h,
            float x, float y, float angle,
            b2BodyType type, Properties props) {
        b2BodyDef body_def;
        body_def.type = type;
        body_def.position.Set(x, y);
        body_def.angle = angle;

        b2Body *body = m_world.CreateBody(&body_def);

        b2PolygonShape shape;
        shape.SetAsBox(w, h);

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
