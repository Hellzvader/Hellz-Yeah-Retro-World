#pragma once
#include "Actor.hpp"
#include "Gamepad.hpp"
#include <array>
#include <string>

struct PlayerSlot{
 bool joined{};
 bool local{};
 bool connected{};
 int controller{-1};
 std::string name{"Player"};
 HeroActor hero{};
 uint32_t lastInputFrame{};
};

struct MultiplayerState{
 static constexpr int MAX_PLAYERS=4;
 std::array<PlayerSlot,MAX_PLAYERS> players{};
 int count()const{int n=0;for(const auto&p:players)if(p.joined)n++;return n;}
 int joinLocal(int controller,int heroIndex){
  for(int i=0;i<MAX_PLAYERS;i++)if(!players[i].joined){
   auto&p=players[i];p.joined=p.local=p.connected=true;p.controller=controller;
   p.name="Player "+std::to_string(i+1);p.hero.heroIndex=heroIndex%HEROES.size();p.hero.hp=p.hero.def().hp;return i;
  }return -1;
 }
 void leave(int i){if(i>=0&&i<MAX_PLAYERS)players[i]=PlayerSlot{};}
};
