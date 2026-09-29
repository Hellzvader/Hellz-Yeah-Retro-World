#pragma once
#include <vector>
struct Particle{float x{},y{},vx{},vy{},life{1};};
inline void updateParticles(std::vector<Particle>&p,float dt){for(auto&a:p){a.x+=a.vx*dt;a.y+=a.vy*dt;a.vy+=500*dt;a.life-=dt;}}
inline void burst(std::vector<Particle>&p,float x,float y){for(int i=0;i<8;i++)p.push_back({x,y,(i-4)*45.f,-160.f-(i%3)*35.f,.7f});}
