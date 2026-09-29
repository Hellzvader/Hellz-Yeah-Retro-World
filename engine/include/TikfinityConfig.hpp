#pragma once
#include <string>
struct TikfinityConfig{
 bool enabled{true};
 std::string queuePath{"tikfinity_queue.txt"};
 int maxEnemies{28};
 int lowGiftSpawn{1};
 int mediumGiftSpawn{5};
 int highGiftSpawn{10};
};
