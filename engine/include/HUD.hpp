#pragma once
#include <SDL3/SDL.h>
#include "Actor.hpp"
inline void drawHUD(SDL_Renderer*r,const HeroActor&h,int stage,int tokens){
 SDL_SetRenderDrawBlendMode(r,SDL_BLENDMODE_BLEND);SDL_SetRenderDrawColor(r,0,0,0,185);SDL_FRect bg{12,12,500,58};SDL_RenderFillRect(r,&bg);
 SDL_SetRenderDrawColor(r,220,55,55,255);SDL_FRect hp{28,30,(float)(h.hp*34),18};SDL_RenderFillRect(r,&hp);
 SDL_SetRenderDrawColor(r,70,175,245,255);SDL_FRect progress{245,30,(float)((stage+1)*14),18};SDL_RenderFillRect(r,&progress);
 SDL_SetRenderDrawColor(r,245,205,40,255);SDL_FRect coin{465,29,(float)(tokens>0?26:10),20};SDL_RenderFillRect(r,&coin);
}
