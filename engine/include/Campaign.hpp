#pragma once
#include <string>
#include <vector>
struct StageDef { std::string id,title,theme,boss; };
struct Campaign {
 std::string title="Hellz Yeah Retro World";
 std::string premise="The Kong family has taken Peach. Mario and Bowser form an uneasy alliance and cross both kingdoms to bring her home.";
 std::vector<StageDef> stages={
  {"1-1","Broken Mushroom Road","mushroom-jungle",""},
  {"1-2","Barrel Border","jungle",""},
  {"1-3","Kremling Crossing","river-jungle","Kong Guardian"},
  {"2-1","Vineway Heights","treetops",""},
  {"2-2","Mine Cart Mayhem","mine",""},
  {"2-3","Deep Kong Mine","mine","Kong Guardian"},
  {"3-1","Ghost Ship Approach","ship",""},
  {"3-2","Kremling Armada","ship",""},
  {"3-3","Storm Deck","storm-ship","Kong Guardian"},
  {"4-1","Factory Invasion","factory",""},
  {"4-2","Hot Machine","factory-lava",""},
  {"4-3","Power Core","factory","Kong Guardian"},
  {"5-1","Kong Stronghold","fortress",""},
  {"5-2","Peach's Prison","fortress",""},
  {"5-3","The Rescue","throne-room","Final Kong Battle"}
 };
};
