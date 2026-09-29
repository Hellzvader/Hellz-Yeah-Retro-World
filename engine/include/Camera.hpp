#pragma once
#include <algorithm>
struct Camera{
 float x{},y{};int viewW{1280},viewH{720};
 void follow(float tx,float ty,int worldW,int worldH){
  x=std::clamp(tx-viewW*.38f,0.f,std::max(0.f,(float)worldW-viewW));
  y=std::clamp(ty-viewH*.55f,0.f,std::max(0.f,(float)worldH-viewH));
 }
};
