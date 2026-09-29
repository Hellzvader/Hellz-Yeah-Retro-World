#pragma once
#include <SDL3/SDL.h>
#include <algorithm>
#include <cctype>
#include <string>
#include <unordered_map>

struct SpriteClip{int frameW{},frameH{},frames{1};float fps{8.f};};

class SpriteLibrary{
public:
 explicit SpriteLibrary(SDL_Renderer* r=nullptr):renderer(r){}
 void setRenderer(SDL_Renderer*r){renderer=r;}
 SDL_Texture* load(const std::string&id,const std::string&path){
  auto it=textures.find(id);if(it!=textures.end())return it->second;
  if(!renderer)return nullptr;
  std::string resolved=path;
  if(!SDL_GetPathInfo(resolved.c_str(),nullptr)){if(const char*base=SDL_GetBasePath()){resolved=std::string(base)+path;}}
  SDL_Surface*s=nullptr;
  auto dot=resolved.find_last_of('.');
  std::string ext=dot==std::string::npos?"":resolved.substr(dot);
  std::transform(ext.begin(),ext.end(),ext.begin(),[](unsigned char ch){return (char)std::tolower(ch);});
  // SDL core build uses BMP strips; PNG source sheets are preprocessed into BMP strips by the asset tool.\n  if(ext==".bmp")s=SDL_LoadBMP(resolved.c_str());
  if(!s)return nullptr;
  // BMP strips can use magenta as a transparency key; PNG keeps native alpha.
  if(ext!=".png")SDL_SetSurfaceColorKey(s,true,SDL_MapSurfaceRGB(s,255,0,255));
  SDL_Texture*t=SDL_CreateTextureFromSurface(renderer,s);SDL_DestroySurface(s);
  if(t){SDL_SetTextureScaleMode(t,SDL_SCALEMODE_NEAREST);textures[id]=t;}return t;
 }
 bool draw(const std::string&id,const std::string&path,const SpriteClip&clip,float time,float x,float y,float w,float h,bool flip=false){
  SDL_Texture*t=load(id,path);if(!t)return false;
  int count=std::max(1,clip.frames);int frame=(int)(time*clip.fps)%count;
  SDL_FRect src{(float)(frame*clip.frameW),0.f,(float)clip.frameW,(float)clip.frameH};
  SDL_FRect dst{x,y,w,h};
  SDL_RenderTextureRotated(renderer,t,&src,&dst,0,nullptr,flip?SDL_FLIP_HORIZONTAL:SDL_FLIP_NONE);
  return true;
 }
 void clear(){for(auto&p:textures)if(p.second)SDL_DestroyTexture(p.second);textures.clear();}
 ~SpriteLibrary(){clear();}
private:
 SDL_Renderer*renderer{};std::unordered_map<std::string,SDL_Texture*>textures;
};
