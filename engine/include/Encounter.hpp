#pragma once
#include "Actor.hpp"
#include <vector>
struct Encounter{float left{},right{};bool active{},cleared{};int remaining{};};
inline void updateEncounter(Encounter&e,const HeroActor&h,const std::vector<EnemyActor>&enemies){
 if(!e.active&&h.x>=e.left&&h.x<=e.right)e.active=true;if(!e.active)return;e.remaining=0;
 for(const auto&a:enemies)if(a.alive&&a.x>=e.left&&a.x<=e.right)e.remaining++;if(e.remaining==0)e.cleared=true;
}
