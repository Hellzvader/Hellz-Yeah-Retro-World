#pragma once
#include "Gameplay.hpp"
#include "Actor.hpp"
#include <cmath>
inline void updateBarrels(std::vector<BarrelActor>& bs,HeroActor& h,float dt){
 for(auto&b:bs)if(b.active){
  if(b.carried){b.x=h.x+h.facing*34;b.y=h.y+5;continue;}
  b.vy+=1300*dt;b.x+=b.vx*dt;b.y+=b.vy*dt;
  if(b.y>565){b.y=565;b.vy=0;b.vx*=.985f;}
 }
}
inline int nearestBarrel(std::vector<BarrelActor>&bs,const HeroActor&h){
 for(int i=0;i<(int)bs.size();++i)if(bs[i].active&&!bs[i].carried&&std::abs(bs[i].x-h.x)<70&&std::abs(bs[i].y-h.y)<70)return i;return -1;
}
inline void throwBarrel(BarrelActor&b,const HeroActor&h){b.carried=false;b.vx=h.facing*520;b.vy=-170;}
