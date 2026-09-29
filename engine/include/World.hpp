#pragma once
#include <string>
#include <vector>

struct Rect { float x{}, y{}, w{}, h{}; };

enum class ObjectType { Ground, Platform, PlayerSpawn, Enemy, Coin, Barrel, Vine, Exit };

struct WorldObject {
    ObjectType type{ObjectType::Ground};
    Rect bounds{};
    std::string name;
};

class World {
public:
    int width = 3200;
    int height = 720;
    std::vector<WorldObject> objects;
    void makeDemo();
    bool save(const std::string& path) const;
};
