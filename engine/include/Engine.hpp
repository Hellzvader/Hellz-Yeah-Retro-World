#pragma once
#include <SDL3/SDL.h>
#include "World.hpp"

class Engine {
public:
    bool init();
    int run();
    void shutdown();
private:
    SDL_Window* window{};
    SDL_Renderer* renderer{};
    bool running{true};
    bool playMode{false};
    World world;
    float playerX{100}, playerY{400}, vx{}, vy{};
    bool grounded{};
    float cameraX{};
    ObjectType brush{ObjectType::Ground};

    void event(const SDL_Event& e);
    void update(float dt);
    void draw();
    void drawEditor();
    void drawGame();
    void placeObject(float x,float y);
};
