#pragma once
#include <SDL3/SDL.h>
#include "GameData.hpp"
inline void drawCharacterSelect(SDL_Renderer*r,int selected){
 SDL_SetRenderDrawColor(r,18,24,42,255);SDL_RenderClear(r);
 for(int i=0;i<(int)HEROES.size();i++){SDL_FRect card{185.f+i*310,220.f,260.f,300.f};if(i==selected)SDL_SetRenderDrawColor(r,240,190,45,255);else SDL_SetRenderDrawColor(r,55,75,105,255);SDL_RenderFillRect(r,&card);}
}
