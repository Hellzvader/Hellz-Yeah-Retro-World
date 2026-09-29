#pragma once
#include <string>
#include <fstream>

struct SaveData {
 int unlockedStage{0};
 int selectedHero{0};
 int totalTokens{0};
 bool peachRescued{false};

 bool save(const std::string& path) const {
  std::ofstream f(path); if(!f)return false;
  f<<"HYRSAVE 1\n"<<unlockedStage<<" "<<selectedHero<<" "<<totalTokens<<" "<<peachRescued<<"\n"; return true;
 }
 bool load(const std::string& path) {
  std::ifstream f(path); if(!f)return false; std::string sig;int ver{};
  f>>sig>>ver;if(sig!="HYRSAVE")return false;f>>unlockedStage>>selectedHero>>totalTokens>>peachRescued;return true;
 }
};
