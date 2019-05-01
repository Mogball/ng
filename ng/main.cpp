#include "game.h"
#include <iostream>

using namespace ng;

int main() {
    ng::Game game{ "Memes", 1920, 1080, 0.02 };

    auto &key_handler = game.key_handler();
    key_handler.set_delegate(GLFW_KEY_ESCAPE, [](GLFWwindow *win, int, int) {
        glfwSetWindowShouldClose(win, GLFW_TRUE);
    });
    auto &mouse_handler = game.mouse_handler();
    mouse_handler.set_delegate(GLFW_MOUSE_BUTTON_LEFT, [&game](GLFWwindow *win, int action, int) {
        if (action != GLFW_PRESS) { return; }
        double x, y;
        glfwGetCursorPos(win, &x, &y);
        auto v = game.window_to_game_coords(x, y);
        game.create_rect({ 1, 1, v.x, v.y, 0 });
    });

    mouse_handler.set_delegate(GLFW_MOUSE_BUTTON_RIGHT, [&game](GLFWwindow *win, int action, int) {
        if (action != GLFW_PRESS) { return; }
        double x, y;
        glfwGetCursorPos(win, &x, &y);
        auto v = game.window_to_game_coords(x, y);
        game.create_rect({ 5, 5, v.x, v.y, 0, 100 }, { .density = 10 });
    });

    game.create_rect({ 50, 10, 0, -20, 0 }, {}, b2_staticBody);
    game.create_rect({ 1, 1, 0, 20, 0.2 });
    game.run();

    return EXIT_SUCCESS;
}
