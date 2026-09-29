#pragma once
#include "Multiplayer.hpp"
#include <cstdint>
inline uint64_t hashMix(uint64_t h,uint64_t v){h^=v+0x9e3779b97f4a7c15ULL+(h<<6)+(h>>2);return h;}
inline uint64_t simulationHash(const MultiplayerState&m,int stage){
 uint64_t h=1469598103934665603ULL;h=hashMix(h,(uint64_t)stage);
 for(const auto&p:m.players)if(p.joined){h=hashMix(h,(uint64_t)(p.hero.x*100));h=hashMix(h,(uint64_t)(p.hero.y*100));h=hashMix(h,(uint64_t)p.hero.hp);h=hashMix(h,(uint64_t)p.hero.heroIndex);}
 return h;
}
struct SyncState{uint32_t lastVerifiedFrame{};uint64_t localHash{},remoteHash{};int desyncCount{};void compare(uint32_t f,uint64_t local,uint64_t remote){localHash=local;remoteHash=remote;if(local!=remote)desyncCount++;else lastVerifiedFrame=f;}};
