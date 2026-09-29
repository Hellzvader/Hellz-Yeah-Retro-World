#pragma once
#include "Actor.hpp"
#include <cmath>

inline void enemyBrain(EnemyActor& e,float px,float py,float dt,float time){
 if(!e.alive)return;
 const auto& d=e.def();
 float dx=px-e.x;
 if(d.boss){
  e.vx=(dx>0?1.f:-1.f)*d.speed;
  if(std::abs(dx)<300 && std::fmod(time,2.0f)<dt*2)e.vy=-430;
 } else if(d.flying){
  e.vx=(dx>0?1.f:-1.f)*d.speed*.75f;
  e.y+=std::sin(time*3+e.x*.01f)*32*dt;
 } else if(d.id=="klaptrap"){
  e.vx=(dx>0?1.f:-1.f)*d.speed*1.35f;
 } else if(d.id=="klump"||d.id=="army"){
  e.vx=(dx>0?1.f:-1.f)*d.speed*.55f;
 } else {
  if(std::abs(dx)<420)e.vx=(dx>0?1.f:-1.f)*d.speed;
 }
}
