#include "World.hpp"
#include <fstream>

void World::makeDemo() {
    objects.clear();
    objects.push_back({ObjectType::Ground,{0,610,3200,110},"Ground"});
    objects.push_back({ObjectType::Platform,{420,490,220,24},"Platform"});
    objects.push_back({ObjectType::Platform,{780,410,200,24},"Platform"});
    objects.push_back({ObjectType::PlayerSpawn,{120,550,32,48},"Player"});
    objects.push_back({ObjectType::Enemy,{720,560,36,36},"Enemy"});
    objects.push_back({ObjectType::Coin,{520,450,20,20},"Token"});
    objects.push_back({ObjectType::Barrel,{1050,560,42,50},"Barrel"});
    objects.push_back({ObjectType::Vine,{1450,320,20,290},"Vine"});
    objects.push_back({ObjectType::Exit,{2900,500,64,110},"Exit"});
}
bool World::save(const std::string& path) const {
    std::ofstream f(path);
    if(!f) return false;
    f << "HYRWORLD 1\n" << width << " " << height << "\n";
    for(const auto& o: objects)
        f << static_cast<int>(o.type)<<" "<<o.bounds.x<<" "<<o.bounds.y<<" "<<o.bounds.w<<" "<<o.bounds.h<<" "<<o.name<<"\n";
    return true;
}
