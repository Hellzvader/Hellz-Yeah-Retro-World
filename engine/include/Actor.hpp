#pragma once
#include "GameData.hpp"
#include "World.hpp"
#include <string>

struct HeroActor {
 int heroIndex=0; float x=120,y=500,vx=0,vy=0; int hp=3; bool grounded=false; float facing=1;
 const HeroDef& def() const { return HEROES.at(heroIndex); }
 void switchNext(){ heroIndex=(heroIndex+1)%HEROES.size(); hp=def().hp; }
 void switchPrev(){ heroIndex=(heroIndex+(int)HEROES.size()-1)%HEROES.size(); hp=def().hp; }
};

struct EnemyActor {
 int defIndex=0; float x=0,y=0,vx=-70,vy=0; int hp=1; bool alive=true; std::string viewer;
 const EnemyDef& def() const { return ENEMIES.at(defIndex); }
};
