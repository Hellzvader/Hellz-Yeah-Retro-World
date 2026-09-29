#pragma once
#include <SDL3/SDL.h>
#include <string>
#include <unordered_map>
class Assets{
public:
 SDL_Texture* texture(SDL_Renderer*r,const std::string&id,const std::string&bmp){
  auto it=textures.find(id);if(it!=textures.end())return it->second;
  SDL_Surface*s=SDL_LoadBMP(bmp.c_str());if(!s)return nullptr;SDL_Texture*t=SDL_CreateTextureFromSurface(r,s);SDL_DestroySurface(s);textures[id]=t;return t;
 }
 void clear(){for(auto&p:textures)if(p.second)SDL_DestroyTexture(p.second);textures.clear();}
private:std::unordered_map<std::string,SDL_Texture*>textures;
};
