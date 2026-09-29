#pragma once
struct NetplayRules{
 int maxPlayers{4};
 int inputDelay{3};
 bool friendlyFire{false};
 bool sharedLives{false};
 bool pauseRequiresHost{true};
 bool allowMidLevelJoin{false};
 float maxPlayerSeparation{1250.f};
};
