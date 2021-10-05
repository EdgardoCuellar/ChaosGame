#include <functional>
#include "Screen.hpp"

using namespace std;

Screen::Screen() noexcept = default;

Screen::~Screen() noexcept = default;

void Screen::init(const char *title, int xpos, int ypos, int wigth, int height, bool fullscreen) {
    int flags = 0;
    if (fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0){
        cout << "All is init" << endl;

        window = SDL_CreateWindow(title, xpos, ypos, wigth, height, flags);
        if (window){
            cout << "Window created" << endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer){
            SDL_SetRenderDrawColor(renderer, 33, 33, 33, 255);
            cout << "Renderer create" << endl;
        }

        isRunning = true;
    } else{
        isRunning = false;
    }
}

void Screen::handleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            switch (event.button.button) {
                case SDL_BUTTON_LEFT:
                    if (points.size() < 3)
                        points.emplace_back(event.motion.x, event.motion.y, SIZE, points.size()+1);
                    else if (points.size() < 4)
                        points.emplace_back(event.motion.x, event.motion.y, SIZE, 0);
                    break;
            }
            break;

    }
}

void Screen::update(){
    if (points.size()>=4 && points.size() < MAX){
        addPoint();
    }
}

void Screen::render(){
    // Background
    SDL_SetRenderDrawColor(renderer, COLORS[0][0], COLORS[0][1], COLORS[0][2], 255);
    SDL_RenderClear(renderer);
    displayBase();
    // Display all point
    SDL_RenderPresent(renderer);
}

void Screen::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "All clean up" << endl;
}

void Screen::getPoints(Point &pt) noexcept {
    SDL_SetRenderDrawColor(renderer, COLORS[pt.getColor()][0], COLORS[pt.getColor()][1], COLORS[pt.getColor()][2], 255);
    vector<array<int, 2>> tmp = pt.getPoint();
    for (int i = 0; i < tmp.size()/2; ++i) {
        SDL_RenderDrawLine(renderer, tmp[i*2][0], tmp[i*2][1], tmp[(i*2)+1][0], tmp[(i*2)+1][1]);
    }
    SDL_RenderDrawLine(renderer, static_cast<int>(pt.getPosX())-pt.getPosR(), static_cast<int>(pt.getPosY()),
                       static_cast<int>(pt.getPosX())+pt.getPosR(), static_cast<int>(pt.getPosY()));
}

void Screen::displayBase() noexcept {
    for (auto & point : points) {
        getPoints(point);
    }
}

void Screen::addPoint() noexcept {
    srand(points[points.size()-1].getPosX()*points[points.size()-1].getPosY());
    int rnb = rand() % 3;
    float newPosX, newPosY;
    if (points[rnb].getPosX() > points[points.size()-1].getPosX())
        newPosX = points[points.size()-1].getPosX() + (points[rnb].getPosX() - points[points.size()-1].getPosX()) / 2;
    else
        newPosX = points[rnb].getPosX() + (points[points.size()-1].getPosX() - points[rnb].getPosX()) / 2;

    if (points[rnb].getPosY() > points[points.size()-1].getPosY())
        newPosY = points[points.size()-1].getPosY() + (points[rnb].getPosY() - points[points.size()-1].getPosY()) / 2;
    else
        newPosY = points[rnb].getPosY() + (points[points.size()-1].getPosY() - points[rnb].getPosY()) / 2;

    points.emplace_back(newPosX, newPosY, SIZE, rnb+1);
}
