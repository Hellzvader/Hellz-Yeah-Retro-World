#pragma once
#include "Actor.hpp"
#include <cmath>
struct BossState{int phase{1};float timer{};bool enraged{};};
inline void updateBoss(EnemyActor&e,BossState&s,float px,float dt){
 if(!e.alive)return;s.timer+=dt;
 int maxHp=e.def().hp;s.phase=e.hp<=maxHp/3?3:e.hp<=maxHp*2/3?2:1;s.enraged=s.phase==3;
 float mult=s.phase==1?1.f:s.phase==2?1.35f:1.75f;
 e.vx=(px>e.x?1.f:-1.f)*e.def().speed*mult;
 if(std::fmod(s.timer,s.phase==3?1.1f:1.8f)<dt*2)e.vy=-390-(s.phase*35);
}
