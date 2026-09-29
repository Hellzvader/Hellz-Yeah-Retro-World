#pragma once
#include <cstdint>
#include <array>

struct NetInput{
 uint32_t frame{};
 uint8_t player{};
 uint16_t buttons{};
 int8_t axisX{},axisY{};
};

struct NetplayState{
 static constexpr int MAX_PLAYERS=4;
 bool enabled{};
 bool host{};
 uint32_t simulationFrame{};
 uint32_t inputDelay{3};
 std::array<NetInput,MAX_PLAYERS> frameInputs{};
 void beginFrame(){simulationFrame++;}
 bool ready()const{
  if(!enabled)return true;
  for(int p=0;p<MAX_PLAYERS;p++)if(frameInputs[p].frame+inputDelay<simulationFrame)return false;
  return true;
 }
};

// Netplay rule: gameplay simulation advances on fixed ticks using only serialized
// NetInput. Rendering, audio and particles never affect authoritative game state.
