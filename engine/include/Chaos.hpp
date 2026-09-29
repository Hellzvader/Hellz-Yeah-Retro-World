#pragma once
#include "Actor.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

struct ChaosEvent { std::string viewer,gift; int value{}; };

inline std::vector<ChaosEvent> readChaosQueue(const std::string& path){
 std::ifstream f(path); std::vector<ChaosEvent> out; std::string line;
 while(std::getline(f,line)){std::stringstream s(line);std::string u,g,v;if(std::getline(s,u,'|')&&std::getline(s,g,'|')&&std::getline(s,v))try{out.push_back({u,g,std::stoi(v)});}catch(...){}}
 if(!out.empty()){f.close();std::ofstream clear(path,std::ios::trunc);}
 return out;
}
inline void applyChaos(const ChaosEvent&e,std::vector<EnemyActor>& enemies,float px,float py){
 int count=e.value>=1000?10:e.value>=100?5:1;
 for(int i=0;i<count;i++){EnemyActor a;a.defIndex=8+(i%8);a.x=px+260+i*55;a.y=py-80-(i%3)*30;a.hp=a.def().hp;a.vx=-a.def().speed;a.viewer=e.viewer;enemies.push_back(a);}
}
