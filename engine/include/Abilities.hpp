#pragma once
#include "Actor.hpp"
struct AbilityState{float fireCooldown{},smashCooldown{},invincible{},glideFuel{1};bool powered{};};
inline void tickAbilities(AbilityState&a,float dt){if(a.fireCooldown>0)a.fireCooldown-=dt;if(a.smashCooldown>0)a.smashCooldown-=dt;if(a.invincible>0)a.invincible-=dt;}
inline float heroRunMultiplier(const HeroActor&h){return h.heroIndex==0?1.28f:h.heroIndex==1?1.24f:1.12f;}
