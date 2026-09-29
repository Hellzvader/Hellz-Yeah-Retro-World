#pragma once
#include "World.hpp"
#include "Campaign.hpp"
#include "Actor.hpp"
#include <vector>\n#include <string>\n#include <stdexcept>\n\ninline int enemyIndexById(const std::string&id){\n for(int i=0;i<(int)ENEMIES.size();++i)if(ENEMIES[i].id==id)return i;\n throw std::runtime_error("Unknown enemy id: "+id);\n}

struct LevelBuild { World world; std::vector<EnemyActor> enemies; float spawnX=120,spawnY=500; };

inline LevelBuild buildStage(int stage){
 LevelBuild b;b.world.width=3600+(stage%3)*500;b.world.height=720;
 b.world.objects.push_back({ObjectType::Ground,{0,610,(float)b.world.width,110},"Ground"});
 for(int i=0;i<11;i++){
  float x=360+i*285+(i%2)*35;float y=500-(i%3)*70;
  b.world.objects.push_back({ObjectType::Platform,{x,y,150,24},"Platform"});
  if(i%2==0)b.world.objects.push_back({ObjectType::Coin,{x+60,y-38,20,20},"Token"});
  if(i%3==0)b.world.objects.push_back({ObjectType::Barrel,{x+115,y-50,42,50},"Barrel"});
  if((stage==3||stage==4)&&i%3==1)b.world.objects.push_back({ObjectType::Vine,{x+75,y-165,20,165},"Vine"});
  if((stage==1||stage==6||stage==7)&&i==5)b.world.objects.push_back({ObjectType::Water,{x-120,565,420,45},"Water"});
  if((stage==9||stage==10||stage==11)&&i%4==2)b.world.objects.push_back({ObjectType::Hazard,{x+35,590,85,20},"Hazard"});
  if(i==4||i==8)b.world.objects.push_back({ObjectType::Checkpoint,{x,y-70,28,70},"Checkpoint"});
  if((stage==4||stage==9)&&i%4==0)b.world.objects.push_back({ObjectType::MovingPlatform,{x,y-110,130,22},"Moving Platform"});
  if((stage>=12)&&i%3==2)b.world.objects.push_back({ObjectType::BreakableBlock,{x+35,y-52,48,48},"Breakable"});
 }
 b.world.objects.push_back({ObjectType::Exit,{(float)b.world.width-150,500,64,110},"Exit"});
 if(stage==14)b.world.objects.push_back({ObjectType::Peach,{(float)b.world.width-250,515,40,70},"Peach"});
 static const std::vector<std::string> kongRegular={
  "kritter","klump","necky","zinger","gnawty","klaptrap","army","mini_necky",
  "kaboing","klampon","kruncha","kutlass","kannon","klobber","neek","click_clack",
  "flitter","spiny_dkc2","screech"
 };
 for(int i=0;i<12+stage;i++){
  EnemyActor e;e.defIndex=enemyIndexById(kongRegular[(i+stage)%kongRegular.size()]);
  e.x=650+i*210;e.y=540;e.hp=e.def().hp;e.vx=-e.def().speed;b.enemies.push_back(e);
 }
 if(stage%3==2){
  static const char* bosses[]={"dk_guardian","king_zing","kudgel"};
  EnemyActor boss;boss.defIndex=enemyIndexById(bosses[(stage/3)%3]);
  boss.x=b.world.width-600;boss.y=500;boss.hp=boss.def().hp;boss.vx=-boss.def().speed;b.enemies.push_back(boss);
 }
 return b;
}
