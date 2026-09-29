#pragma once
#include "World.hpp"
#include "Actor.hpp"
struct EnvironmentState{bool underwater{},onVine{},onIce{},onConveyor{};float wind{};};
inline void scanEnvironment(const World&w,const HeroActor&h,EnvironmentState&s){
 s.underwater=s.onVine=false;
 for(const auto&o:w.objects){bool hit=h.x<o.bounds.x+o.bounds.w&&o.bounds.x<h.x+34&&h.y<o.bounds.y+o.bounds.h&&o.bounds.y<h.y+48;if(!hit)continue;if(o.type==ObjectType::Water)s.underwater=true;if(o.type==ObjectType::Vine)s.onVine=true;}
}
