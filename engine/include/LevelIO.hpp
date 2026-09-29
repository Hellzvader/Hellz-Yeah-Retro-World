#pragma once
#include "World.hpp"
#include <fstream>
#include <sstream>
#include <string>
inline bool loadWorld(World&w,const std::string&path){
 std::ifstream f(path);if(!f)return false;std::string sig;int version{};
 f>>sig>>version;if(sig!="HYRWORLD")return false;f>>w.width>>w.height;w.objects.clear();
 int type;float x,y,ww,hh;std::string name;
 while(f>>type>>x>>y>>ww>>hh>>name)w.objects.push_back({static_cast<ObjectType>(type),{x,y,ww,hh},name});
 return true;
}
