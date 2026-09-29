#pragma once
#include "Actor.hpp"
#include <algorithm>
enum class PowerupType { Mushroom, FireFlower, Star, Heart, BananaBunch };
struct Powerup { PowerupType type; float x{},y{}; bool active{true}; };
inline void applyPowerup(HeroActor& h,PowerupType p){
 if(p==PowerupType::Mushroom||p==PowerupType::Heart)h.hp=std::min(h.def().hp,h.hp+1);
 if(p==PowerupType::BananaBunch)h.hp=std::min(h.def().hp,h.hp+2);
}
