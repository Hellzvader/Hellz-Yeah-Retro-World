#pragma once
#include "Multiplayer.hpp"
#include <algorithm>
struct MultiplayerCamera{
 float x{},zoom{1};
 void update(const MultiplayerState&m,int worldWidth){
  bool any=false;float lo=0,hi=0;
  for(const auto&p:m.players)if(p.joined&&p.connected){if(!any){lo=hi=p.hero.x;any=true;}else{lo=std::min(lo,p.hero.x);hi=std::max(hi,p.hero.x);}}
  if(!any)return;float center=(lo+hi)*.5f;x=std::clamp(center-640.f,0.f,std::max(0.f,(float)worldWidth-1280));float spread=hi-lo;zoom=spread>900?.78f:spread>650?.88f:1.f;
 }
};
