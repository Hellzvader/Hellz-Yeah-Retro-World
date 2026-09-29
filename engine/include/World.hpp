#pragma once
#include <string>
#include <vector>

struct Rect { float x{}, y{}, w{}, h{}; };
enum class ObjectType {
 Ground, Platform, PlayerSpawn, Enemy, Coin, Barrel, Vine, Exit,
 MovingPlatform, Checkpoint, Hazard, Water, BreakableBlock, Peach
};
struct WorldObject { ObjectType type{ObjectType::Ground}; Rect bounds{}; std::string name; };

class World {
public:
 int width=3200,height=720; std::vector<WorldObject> objects;
 void makeDemo(); bool save(const std::string& path) const;
};
