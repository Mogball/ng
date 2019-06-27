#include "game.h"
#include <iostream>

using namespace ng;

int main() {
    ng::Game game{ "Memes", 1920, 1080, 0.1, 25 };

    //auto &key_handler = game.key_handler();
    //key_handler.set_delegate(GLFW_KEY_ESCAPE, [](GLFWwindow *win, int, int) {
    //    glfwSetWindowShouldClose(win, GLFW_TRUE);
    //});
    //auto &mouse_handler = game.mouse_handler();
    //mouse_handler.set_delegate(GLFW_MOUSE_BUTTON_LEFT, [&game](GLFWwindow *win, int action, int) {
    //    if (action != GLFW_PRESS) { return; }
    //    double x, y;
    //    glfwGetCursorPos(win, &x, &y);
    //    auto v = game.window_to_game_coords(x, y);
    //    game.create_rect({ .w = 0.5, .h = 0.5, .x = v.x, .y = v.y });
    //});

    //mouse_handler.set_delegate(GLFW_MOUSE_BUTTON_RIGHT, [&game](GLFWwindow *win, int action, int) {
    //    if (action != GLFW_PRESS) { return; }
    //    double x, y;
    //    glfwGetCursorPos(win, &x, &y);
    //    auto v = game.window_to_game_coords(x, y);
    //    game.create_circle({ .r = 0.5, .x = v.x, .y = v.y, .vx = 25 }, { .density = 3 });
    //});

    game.create_rect({ .w = 20, .h = 20, .x = 0, .y = 0 }, {}, b2_staticBody);
    game.run();

    return EXIT_SUCCESS;
}
