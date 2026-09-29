#pragma once
#include "Actor.hpp"
#include "World.hpp"
#include <vector>
inline bool inside(const HeroActor&h,const Rect&r){return h.x<r.x+r.w&&r.x<h.x+34&&h.y<r.y+r.h&&r.y<h.y+48;}
struct TraversalState{bool climbing{},swimming{};float checkpointX{120},checkpointY{500};};
inline void updateTraversal(HeroActor&h,TraversalState&s,const World&w,float dt,bool up,bool down){
 s.climbing=false;s.swimming=false;
 for(const auto&o:w.objects){
  if(o.type==ObjectType::Vine&&inside(h,o.bounds)){s.climbing=true;h.vy=(down?1.f:0.f)-(up?1.f:0.f);h.vy*=145.f;}
  if(o.type==ObjectType::Water&&inside(h,o.bounds)){s.swimming=true;h.vy*=.90f;if(up)h.vy-=520*dt;}
  if(o.type==ObjectType::Checkpoint&&inside(h,o.bounds)){s.checkpointX=o.bounds.x;s.checkpointY=o.bounds.y-48;}
 }
}
inline void respawnAtCheckpoint(HeroActor&h,const TraversalState&s){h.x=s.checkpointX;h.y=s.checkpointY;h.vx=h.vy=0;h.hp=h.def().hp;}
