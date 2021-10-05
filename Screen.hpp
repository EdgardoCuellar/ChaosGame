#ifndef SDL2_TEST_SCREEN_HPP
#define SDL2_TEST_SCREEN_HPP

#include <SDL2/SDL.h>
#include "Point.h"
#include <vector>
#include <iostream>
#include <random>

// OPTION
int const WITDH = 1000;
int const HEIGHT = 1000;
int const COLORS[5][3] = {{30,30,30}, {48,79,254}, {0, 200, 83}, {213, 0, 0}};
int const SIZE = 1;
int const MAX = 25000;

class Screen{
    bool isRunning{};
    SDL_Window *window{};
    SDL_Renderer *renderer{};
    std::vector<Point> points;

public:
    Screen () noexcept;
    ~Screen() noexcept;

    void init(const char* title, int xpos, int ypos, int wigth, int height, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void clean();

    void displayBase() noexcept;
    void addPoint() noexcept;
    inline void getPoints(Point& pt) noexcept;

    bool running() const {return isRunning; };
};

#endif //SDL2_TEST_SCREEN_HPP
