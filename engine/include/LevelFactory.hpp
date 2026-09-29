#pragma once
#include "World.hpp"
#include "Campaign.hpp"
#include "Actor.hpp"
#include <vector>

struct LevelBuild { World world; std::vector<EnemyActor> enemies; float spawnX=120,spawnY=500; };

inline LevelBuild buildStage(int stage){
 LevelBuild b; b.world.width=3600+(stage%3)*500; b.world.height=720;
 b.world.objects.push_back({ObjectType::Ground,{0,610,(float)b.world.width,110},"Ground"});
 for(int i=0;i<11;i++){
  float x=360+i*285+(i%2)*35; float y=500-(i%3)*70;
  b.world.objects.push_back({ObjectType::Platform,{x,y,150,24},"Platform"});
  if(i%2==0)b.world.objects.push_back({ObjectType::Coin,{x+60,y-38,20,20},"Token"});
  if(i%3==0)b.world.objects.push_back({ObjectType::Barrel,{x+115,y-50,42,50},"Barrel"});
 }
 b.world.objects.push_back({ObjectType::Exit,{(float)b.world.width-150,500,64,110},"Exit"});
 for(int i=0;i<12+stage;i++){
  EnemyActor e; e.defIndex=(8+(i+stage)%8)%ENEMIES.size(); e.x=650+i*210; e.y=540; e.hp=e.def().hp; e.vx=-e.def().speed; b.enemies.push_back(e);
 }
 if(stage%3==2){EnemyActor boss;boss.defIndex=16;boss.x=b.world.width-600;boss.y=520;boss.hp=boss.def().hp;b.enemies.push_back(boss);}
 return b;
}
