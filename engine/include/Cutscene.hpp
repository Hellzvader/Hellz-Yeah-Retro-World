#pragma once
#include "Story.hpp"
#include <string>
struct CutscenePlayer{
 int stage{-1},index{};bool active{};
 void begin(int s){stage=s;index=0;active=false;for(const auto&b:STORY)if(b.stage==s){active=true;break;}}
 const StoryBeat* current()const{int n=0;for(const auto&b:STORY)if(b.stage==stage){if(n==index)return &b;n++;}return nullptr;}
 void next(){index++;if(!current())active=false;}
};
