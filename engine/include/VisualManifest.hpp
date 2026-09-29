#pragma once
#include "SpriteLibrary.hpp"
#include <string>
#include <unordered_map>

struct VisualDef{std::string path;SpriteClip clip;float drawW{},drawH{};};

inline const std::unordered_map<std::string,VisualDef>& visualManifest(){
 static const std::unordered_map<std::string,VisualDef> v={
  {"mario_idle",{"heroes/mario_idle.bmp",{32,48,1,1},34,48}},
  {"mario_run",{"heroes/mario_run.bmp",{32,48,4,10},34,48}},
  {"mario_jump",{"heroes/mario_jump.bmp",{32,48,1,1},34,48}},
  {"luigi_idle",{"heroes/luigi_idle.bmp",{32,48,1,1},34,48}},
  {"luigi_run",{"heroes/luigi_run.bmp",{32,48,4,10},34,48}},
  {"luigi_jump",{"heroes/luigi_jump.bmp",{32,48,1,1},34,48}},
  {"bowser_idle",{"heroes/bowser_idle.bmp",{48,48,1,1},56,56}},
  {"bowser_run",{"heroes/bowser_run.bmp",{48,48,4,8},56,56}},
  {"bowser_jump",{"heroes/bowser_jump.bmp",{48,48,1,1},56,56}},
  {"goomba",{"enemies/mushroom/goomba.bmp",{32,32,2,6},38,38}},
  {"koopa",{"enemies/mushroom/koopa.bmp",{32,48,2,7},40,50}},
  {"paratroopa",{"enemies/mushroom/paratroopa.bmp",{48,48,2,8},48,48}},
  {"bobomb",{"enemies/mushroom/bobomb.bmp",{32,32,2,8},38,38}},
  {"beetle",{"enemies/mushroom/beetle.bmp",{32,32,2,7},38,38}},
  {"shyguy",{"enemies/mushroom/shyguy.bmp",{32,32,2,7},38,38}},
  {"hammerbro",{"enemies/mushroom/hammerbro.bmp",{48,48,4,8},48,48}},
  {"lakitu",{"enemies/mushroom/lakitu.bmp",{48,48,2,6},48,48}},
  {"kritter",{"enemies/kong/kritter.bmp",{48,48,4,9},52,52}},
  {"klump",{"enemies/kong/klump.bmp",{64,64,4,7},64,64}},
  {"necky",{"enemies/kong/necky.bmp",{48,48,4,9},52,52}},
  {"zinger",{"enemies/kong/zinger.bmp",{48,48,4,12},48,48}},
  {"gnawty",{"enemies/kong/gnawty.bmp",{48,48,4,8},48,48}},
  {"klaptrap",{"enemies/kong/klaptrap.bmp",{48,48,4,10},52,52}},
  {"army",{"enemies/kong/army.bmp",{48,48,4,8},52,52}},
  {"mini_necky",{"enemies/kong/mini_necky.bmp",{48,48,4,10},48,48}},
  {"dk_guardian",{"bosses/dk_guardian.bmp",{96,96,4,8},112,112}}
 };
 return v;
}
inline const VisualDef* visualFor(const std::string&id){auto&v=visualManifest();auto it=v.find(id);return it==v.end()?nullptr:&it->second;}
