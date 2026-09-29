#pragma once
#include "Actor.hpp"
#include "World.hpp"
struct RescueState{bool foundPeach{},rescued{},finalBossDefeated{};};
inline void updateRescue(const HeroActor&h,const World&w,RescueState&r,bool finalBossAlive){
 r.finalBossDefeated=!finalBossAlive;
 for(const auto&o:w.objects)if(o.type==ObjectType::Peach&&h.x<o.bounds.x+o.bounds.w&&o.bounds.x<h.x+34&&h.y<o.bounds.y+o.bounds.h&&o.bounds.y<h.y+48){r.foundPeach=true;if(r.finalBossDefeated)r.rescued=true;}
}
