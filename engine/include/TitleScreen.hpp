#pragma once
#include <SDL3/SDL.h>
inline void drawTitleScreen(SDL_Renderer*r,int selection){
 SDL_SetRenderDrawColor(r,10,18,38,255);SDL_RenderClear(r);
 SDL_FRect logo{240,100,800,150};SDL_SetRenderDrawColor(r,35,145,230,255);SDL_RenderFillRect(r,&logo);
 for(int i=0;i<3;i++){SDL_FRect b{430.f,330.f+i*75,420.f,54.f};if(i==selection)SDL_SetRenderDrawColor(r,245,190,35,255);else SDL_SetRenderDrawColor(r,55,70,100,255);SDL_RenderFillRect(r,&b);}
}
