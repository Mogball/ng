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

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, -20);
    b2Body *groundBody = world.CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(50, 10);
    groundBody->CreateFixture(&groundBox, 0);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0, 10);
    bodyDef.angle = 0.9;
    b2Body *body = world.CreateBody(&bodyDef);
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1, 1);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1;
    fixtureDef.friction = 0.3;
    fixtureDef.restitution = 0.5;
    body->CreateFixture(&fixtureDef);

    float timeStep = 1.0 / 60;

    Graphics graphics{ window };

    Geometry groundGeo = {
        { -50, -10, 50, -10, 50, 10, -50, 10 },
        { 0, 1, 2, 2, 3, 0 },
    };

    Geometry dynamicGeo = {
        { -1, -1, 1, -1, 1, 1, -1, 1 },
        { 0, 1, 2, 2, 3, 0 },
    };

    handler.set_delegate(GLFW_KEY_W, [body](GLFWwindow *, int action, int) {
        if (action != GLFW_PRESS) { return; };
        b2Vec2 force{ 0, 50 };
        body->ApplyLinearImpulseToCenter(force, false);
        body->ApplyAngularImpulse(10, false);
        std::cout << "MEOW" << std::endl;
    });

    std::vector<Entity> ents;
    ents.emplace_back(fvec2{ 0.2, 0.2 }, 0.1, 0.5);
    ents.emplace_back(fvec2{-0.5, 0   }, 0.2, 0.3);

    glViewport(0, 0, window.width(), window.height());
    while (window.poll()) {
        world.Step(timeStep, 6, 2);

        b2Vec2 position = body->GetPosition();
        float32 angle = body->GetAngle();

        glClear(GL_COLOR_BUFFER_BIT);

        Entity dynamicEnt{ fvec2{ -position.x, position.y }, angle, 1 };

        position = groundBody->GetPosition();
        angle = groundBody->GetAngle();

        Entity groundEnt{ fvec2{ -position.x, position.y }, 0, 1 };

        graphics.draw(groundGeo, { groundEnt });
        graphics.draw(dynamicGeo, { dynamicEnt });
    }

    return EXIT_SUCCESS;
}
