#include "Engine.hpp"
#include <algorithm>
#include <cmath>

static bool overlap(float x,float y,float w,float h,const Rect& b){
 return x<b.x+b.w && b.x<x+w && y<b.y+b.h && b.y<y+h;
}
static void rect(SDL_Renderer* r,float x,float y,float w,float h){
 SDL_FRect q{x,y,w,h}; SDL_RenderFillRect(r,&q);
}
bool Engine::init(){
 if(!SDL_Init(SDL_INIT_VIDEO|SDL_INIT_GAMEPAD)) return false;
 window=SDL_CreateWindow("Hellz Yeah Retro Engine",1280,720,SDL_WINDOW_RESIZABLE);
 if(!window) return false;
 renderer=SDL_CreateRenderer(window,nullptr);
 if(!renderer) return false;
 SDL_SetRenderVSync(renderer,1);
 world.makeDemo();
 return true;
}
void Engine::shutdown(){ if(renderer)SDL_DestroyRenderer(renderer); if(window)SDL_DestroyWindow(window); SDL_Quit(); }
void Engine::event(const SDL_Event& e){
 if(e.type==SDL_EVENT_QUIT) running=false;
 if(e.type==SDL_EVENT_KEY_DOWN){
  switch(e.key.key){
   case SDLK_ESCAPE: if(playMode) playMode=false; else running=false; break;
   case SDLK_F5: playMode=!playMode; if(playMode){playerX=120;playerY=520;vx=vy=0;} break;
   case SDLK_1: brush=ObjectType::Ground;break; case SDLK_2:brush=ObjectType::Platform;break;
   case SDLK_3:brush=ObjectType::Enemy;break; case SDLK_4:brush=ObjectType::Coin;break;
   case SDLK_5:brush=ObjectType::Barrel;break; case SDLK_6:brush=ObjectType::Vine;break;
   case SDLK_7:brush=ObjectType::Exit;break;
   case SDLK_F2: world.save("level1.hyrworld");break;
  }
 }
 if(!playMode && e.type==SDL_EVENT_MOUSE_BUTTON_DOWN && e.button.button==SDL_BUTTON_LEFT){
  float x=e.button.x+cameraX,y=e.button.y; placeObject(x,y);
 }
}
void Engine::placeObject(float x,float y){
 WorldObject o; o.type=brush; o.bounds={std::floor(x/16)*16,std::floor(y/16)*16,48,48}; o.name="Object";
 if(brush==ObjectType::Ground||brush==ObjectType::Platform)o.bounds={std::floor(x/16)*16,std::floor(y/16)*16,96,24};
 if(brush==ObjectType::Vine)o.bounds={std::floor(x/16)*16,std::floor(y/16)*16,20,160};
 if(brush==ObjectType::Exit)o.bounds={std::floor(x/16)*16,std::floor(y/16)*16,64,110};
 world.objects.push_back(o);
}
void Engine::update(float dt){
 const bool left=SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_A]||SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_LEFT];
 const bool right=SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_D]||SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_RIGHT];
 if(playMode){
  vx=(right-left)*230.0f; vy+=1450*dt;
  if((SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_SPACE]||SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_Z])&&grounded){vy=-530;grounded=false;}
  playerX+=vx*dt; playerY+=vy*dt; grounded=false;
  for(const auto&o:world.objects) if(o.type==ObjectType::Ground||o.type==ObjectType::Platform){
   if(overlap(playerX,playerY,34,48,o.bounds)&&vy>=0&&playerY+48-vy*dt<=o.bounds.y+4){playerY=o.bounds.y-48;vy=0;grounded=true;}
  }
  if(playerY>800){playerX=120;playerY=500;vy=0;}
  cameraX=std::clamp(playerX-450.0f,0.0f,(float)world.width-1280);
 } else {
  if(left)cameraX=std::max(0.0f,cameraX-500*dt);
  if(right)cameraX=std::min((float)world.width-1280,cameraX+500*dt);
 }
}
void Engine::drawGame(){
 SDL_SetRenderDrawColor(renderer,16,28,48,255); SDL_RenderClear(renderer);
 for(const auto&o:world.objects){
  switch(o.type){
   case ObjectType::Ground:case ObjectType::Platform:SDL_SetRenderDrawColor(renderer,45,145,65,255);break;
   case ObjectType::Enemy:SDL_SetRenderDrawColor(renderer,190,70,45,255);break;
   case ObjectType::Coin:SDL_SetRenderDrawColor(renderer,250,210,40,255);break;
   case ObjectType::Barrel:SDL_SetRenderDrawColor(renderer,135,75,35,255);break;
   case ObjectType::Vine:SDL_SetRenderDrawColor(renderer,30,180,65,255);break;
   case ObjectType::Exit:SDL_SetRenderDrawColor(renderer,70,180,235,255);break;
   default:SDL_SetRenderDrawColor(renderer,220,220,220,255);break;
  } rect(renderer,o.bounds.x-cameraX,o.bounds.y,o.bounds.w,o.bounds.h);
 }
 SDL_SetRenderDrawColor(renderer,235,55,45,255);rect(renderer,playerX-cameraX,playerY,34,48);
}
void Engine::drawEditor(){
 drawGame();
 SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND);
 SDL_SetRenderDrawColor(renderer,10,10,14,220);rect(renderer,0,0,1280,76);
 SDL_SetRenderDrawColor(renderer,60,170,240,255);rect(renderer,16,16,210,44);
 // Toolbar is keyboard-driven in milestone 1; full dockable GUI comes next.
}
void Engine::draw(){ if(playMode)drawGame(); else drawEditor(); SDL_RenderPresent(renderer); }
int Engine::run(){
 Uint64 last=SDL_GetTicks();
 while(running){SDL_Event e;while(SDL_PollEvent(&e))event(e);Uint64 now=SDL_GetTicks();float dt=std::min((now-last)/1000.0f,0.033f);last=now;update(dt);draw();}
 return 0;
}
