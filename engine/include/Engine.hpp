#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include "World.hpp"
#include "Actor.hpp"
#include "Campaign.hpp"
#include "LevelFactory.hpp"
#include "SpriteLibrary.hpp"
#include "Gamepad.hpp"
#include "StreamerBotBridge.hpp"

struct Projectile { float x{},y{},vx{},life{}; bool alive{true}; };

class Engine {
public:
 bool init(); int run(); void shutdown();
private:
 SDL_Window* window{}; SDL_Renderer* renderer{};
 SpriteLibrary sprites;
 GamepadManager gamepads;
 PadInput pad{},previousPad{};
 StreamerBotBridge streamerBot;
 bool running{true},playMode{true};
 World world; HeroActor hero; std::vector<EnemyActor> enemies; std::vector<Projectile> shots;
 Campaign campaign; int stageIndex{0}; float cameraX{},hurtTimer{},attackTimer{},visualTime{};
 ObjectType brush{ObjectType::Ground};

 void loadStage(int index); void event(const SDL_Event& e); void update(float dt);
 void updateHero(float dt); void updateEnemies(float dt); void updateCombat(float dt);
 void draw(); void drawEditor(); void drawGame(); void placeObject(float x,float y);
 void drawHero(); void drawEnemy(const EnemyActor& e); bool drawWorldObject(const WorldObject& o);
 void fire(); void smash(); void applyStreamCommand(const StreamCommand& command);
};
