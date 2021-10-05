#include <iostream>
#include "Screen.hpp"

int main(int argc, char* argv[]) {
    Screen *screen = new Screen();
    screen->init("Chaos game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WITDH, HEIGHT, false);

    while (screen->running()){
        screen->handleEvents();
        screen->update();
        screen->render();
    }

    screen->clean();

    return 0;
}
