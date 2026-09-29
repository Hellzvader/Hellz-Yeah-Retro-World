#pragma once
#include <string>
#include <unordered_map>
struct AnimationClip{std::string name;int firstFrame{},frameCount{1};float fps{8};bool loop{true};};
struct Animator{
 std::unordered_map<std::string,AnimationClip> clips;std::string current="idle";float clock{};
 void play(const std::string&n){if(current!=n){current=n;clock=0;}}
 void update(float dt){clock+=dt;}
 int frame()const{auto it=clips.find(current);if(it==clips.end())return 0;auto&c=it->second;int f=(int)(clock*c.fps);if(c.loop)f%=c.frameCount;else if(f>=c.frameCount)f=c.frameCount-1;return c.firstFrame+f;}
};
