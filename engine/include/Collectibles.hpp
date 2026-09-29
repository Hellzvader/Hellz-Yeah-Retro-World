#pragma once
#include "World.hpp"
#include "Actor.hpp"
struct CollectibleState{int coins{},bananas{},letters{};};
inline void collectAt(World&w,const HeroActor&h,CollectibleState&s){
 for(auto&o:w.objects)if(o.type==ObjectType::Coin&&o.bounds.w>0&&h.x<o.bounds.x+o.bounds.w&&o.bounds.x<h.x+34&&h.y<o.bounds.y+o.bounds.h&&o.bounds.y<h.y+48){s.coins++;o.bounds.w=o.bounds.h=0;}
}
