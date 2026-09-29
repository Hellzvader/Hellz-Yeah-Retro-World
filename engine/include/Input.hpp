#pragma once
#include <SDL3/SDL.h>
struct InputState{
 bool left{},right{},up{},down{},jump{},attack{},special{},interact{},pause{};
 bool chaosRandom{},chaosFive{},chaosMega{};
};
inline InputState readInput(){
 const bool*k=SDL_GetKeyboardState(nullptr);InputState i;
 i.left=k[SDL_SCANCODE_A]||k[SDL_SCANCODE_LEFT];i.right=k[SDL_SCANCODE_D]||k[SDL_SCANCODE_RIGHT];
 i.up=k[SDL_SCANCODE_W]||k[SDL_SCANCODE_UP];i.down=k[SDL_SCANCODE_S]||k[SDL_SCANCODE_DOWN];
 i.jump=k[SDL_SCANCODE_SPACE]||k[SDL_SCANCODE_Z];i.attack=k[SDL_SCANCODE_X];
 i.special=k[SDL_SCANCODE_C];i.interact=k[SDL_SCANCODE_V];i.pause=k[SDL_SCANCODE_ESCAPE];
 i.chaosRandom=k[SDL_SCANCODE_J];i.chaosFive=k[SDL_SCANCODE_K];i.chaosMega=k[SDL_SCANCODE_L];
 return i;
}
