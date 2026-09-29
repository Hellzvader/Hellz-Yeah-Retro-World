#pragma once
#include <SDL3/SDL.h>
inline void drawEnding(SDL_Renderer*r,float t){
 SDL_SetRenderDrawColor(r,12,20,45,255);SDL_RenderClear(r);
 SDL_FRect peach{590,180,70,110};SDL_SetRenderDrawColor(r,245,120,180,255);SDL_RenderFillRect(r,&peach);
 SDL_FRect mario{430,390,55,80};SDL_SetRenderDrawColor(r,225,45,45,255);SDL_RenderFillRect(r,&mario);
 SDL_FRect bowser{770,365,90,105};SDL_SetRenderDrawColor(r,205,110,25,255);SDL_RenderFillRect(r,&bowser);
 float w=300.f+(float)((int)(t*40)%300);SDL_SetRenderDrawColor(r,245,205,50,255);SDL_FRect banner{(1280-w)/2,540,w,18};SDL_RenderFillRect(r,&banner);
}
