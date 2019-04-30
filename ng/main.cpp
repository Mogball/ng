#include "entity.h"
#include "key_handler.h"
#include "graphics.h"
#include "window.h"
#include <linmath.h>
#include <Box2D/Box2D.h>
#include <iostream>

using namespace ng;

int main() {
    Window window;
    KeyHandler handler{ window.get() };
    handler.set_delegate(GLFW_KEY_E, [](GLFWwindow *, int action, int) {
        if (action >= 2) { return; }
        std::cout << (action ? "Pressed" : "Released") << std::endl;
    });
    handler.set_delegate(GLFW_KEY_ESCAPE, [](GLFWwindow *win, int action, int) {
        glfwSetWindowShouldClose(win, GLFW_TRUE);
    });

    b2Vec2 gravity{ 0, -10 };
    b2World world{ gravity };

    Entity ground;
    Entity::create_rect(world, ground, b2_staticBody, 50, 10, 0, -20);

    Entity ent;
    Entity::create_rect(world, ent, b2_dynamicBody, 1, 1, 0, 10, 0.9,
            { 1, 0.3, 0.5 });

    float timeStep = 1.0 / 60;

    Graphics graphics{ window };

    handler.set_delegate(GLFW_KEY_W, [&ent](GLFWwindow *, int action, int) {
        if (action != GLFW_PRESS) { return; };
        b2Vec2 force{ 0, 50 };
        ent.body()->ApplyLinearImpulseToCenter(force, false);
        ent.body()->ApplyAngularImpulse(10, false);
    });

    glViewport(0, 0, window.width(), window.height());
    while (window.poll()) {
        world.Step(timeStep, 6, 2);

        glClear(GL_COLOR_BUFFER_BIT);

        graphics.draw(ground);
        graphics.draw(ent);
    }

    return EXIT_SUCCESS;
}
