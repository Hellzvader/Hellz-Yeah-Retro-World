#pragma once
#include "Actor.hpp"
#include <vector>
#include <cmath>

struct BarrelActor { float x{},y{},vx{},vy{}; bool carried{},active{true}; };
struct MovingPlatform { Rect bounds{}; float originX{},originY{},range{160},speed{1}; bool vertical{}; };
struct Checkpoint { float x{},y{}; bool active{}; };
struct Hazard { Rect bounds{}; int damage{1}; };
struct VineActor { Rect bounds{}; };

inline void updateMovingPlatforms(std::vector<MovingPlatform>& p,float time){
 for(auto& m:p){
  float d=std::sin(time*m.speed)*m.range;
  if(m.vertical)m.bounds.y=m.originY+d; else m.bounds.x=m.originX+d;
 }
}
