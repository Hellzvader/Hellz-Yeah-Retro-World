#pragma once
#include <string>
class Audio{
public:void playSfx(const std::string&id){lastSfx=id;}void playMusic(const std::string&id){if(currentMusic!=id)currentMusic=id;}const std::string&music()const{return currentMusic;}
private:std::string currentMusic,lastSfx;
};
