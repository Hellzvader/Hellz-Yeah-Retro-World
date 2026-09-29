#pragma once
#include <SDL3/SDL.h>
#include <string>
struct ThemeColors{SDL_Color sky,far,ground,accent;};
inline ThemeColors themeFor(const std::string&t){
 if(t.find("jungle")!=std::string::npos||t.find("treetop")!=std::string::npos)return {{35,90,120,255},{25,110,65,255},{55,125,45,255},{235,195,45,255}};
 if(t.find("mine")!=std::string::npos)return {{22,18,28,255},{50,40,55,255},{90,70,55,255},{220,150,50,255}};
 if(t.find("ship")!=std::string::npos)return {{25,55,90,255},{35,75,105,255},{95,65,40,255},{220,220,210,255}};
 if(t.find("factory")!=std::string::npos)return {{28,30,35,255},{55,60,65,255},{80,75,70,255},{235,85,35,255}};
 if(t.find("fortress")!=std::string::npos||t.find("throne")!=std::string::npos)return {{28,18,32,255},{65,35,65,255},{75,65,75,255},{210,60,60,255}};
 return {{80,155,220,255},{95,180,100,255},{60,145,65,255},{245,205,45,255}};
}
