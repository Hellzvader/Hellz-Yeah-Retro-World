#pragma once
#include <string>
#include <vector>

enum class HeroId { Mario, Luigi, Bowser };
enum class EnemyFamily { Mushroom, Kong };

struct HeroDef {
 HeroId id; std::string name; float speed,jump; int hp; bool fire,smash;
};
struct EnemyDef {
 std::string id,name; EnemyFamily family; int hp; float speed; bool flying,boss;
};

inline const std::vector<HeroDef> HEROES={
 {HeroId::Mario,"Mario",235,535,3,true,false},
 {HeroId::Luigi,"Luigi",220,585,3,true,false},
 {HeroId::Bowser,"Bowser",185,465,6,true,true}
};

inline const std::vector<EnemyDef> ENEMIES={
 {"goomba","Goomba",EnemyFamily::Mushroom,1,70,false,false},
 {"koopa","Koopa Troopa",EnemyFamily::Mushroom,2,65,false,false},
 {"paratroopa","Koopa Paratroopa",EnemyFamily::Mushroom,2,70,true,false},
 {"bobomb","Bob-omb",EnemyFamily::Mushroom,1,85,false,false},
 {"beetle","Buzzy Beetle",EnemyFamily::Mushroom,2,75,false,false},
 {"shyguy","Shy Guy",EnemyFamily::Mushroom,1,80,false,false},
 {"hammerbro","Hammer Bro",EnemyFamily::Mushroom,3,70,false,false},
 {"lakitu","Lakitu",EnemyFamily::Mushroom,3,80,true,false},
 {"kritter","Kritter",EnemyFamily::Kong,2,90,false,false},
 {"klump","Klump",EnemyFamily::Kong,4,55,false,false},
 {"necky","Necky",EnemyFamily::Kong,2,85,true,false},
 {"zinger","Zinger",EnemyFamily::Kong,2,100,true,false},
 {"gnawty","Gnawty",EnemyFamily::Kong,1,75,false,false},
 {"klaptrap","Klaptrap",EnemyFamily::Kong,2,105,false,false},
 {"army","Army",EnemyFamily::Kong,3,65,false,false},
 {"mini_necky","Mini-Necky",EnemyFamily::Kong,1,110,true,false},
 {"dk_guardian","Kong Guardian",EnemyFamily::Kong,12,75,false,true}
};
