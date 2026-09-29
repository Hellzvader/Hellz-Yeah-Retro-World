#pragma once
#include "GameState.hpp"
struct MenuState{
 int selection{};
 int count{3};
 void up(){selection=(selection+count-1)%count;}
 void down(){selection=(selection+1)%count;}
};
