#pragma once
#include "Lobby.hpp"
#include "NetProtocol.hpp"
#include "Sync.hpp"
#include <array>
#include <cstdint>

struct PeerState{
 bool present{},timedOut{};
 uint32_t lastSequence{},lastFrame{};
 uint64_t lastSeenMs{};
};

struct NetSession{
 LobbyState lobby{};
 std::array<PeerState,MultiplayerState::MAX_PLAYERS> peers{};
 SyncState sync{};
 uint32_t sequence{};
 static constexpr uint64_t TIMEOUT_MS=5000;
 static constexpr uint64_t RECONNECT_GRACE_MS=15000;

 void seen(int p,uint32_t seq,uint32_t frame,uint64_t now){
  if(p<0||p>=MultiplayerState::MAX_PLAYERS)return;
  auto&x=peers[p];x.present=true;x.timedOut=false;x.lastSequence=seq;x.lastFrame=frame;x.lastSeenMs=now;
 }
 void tick(uint64_t now){
  for(auto&p:peers)if(p.present&&now-p.lastSeenMs>TIMEOUT_MS)p.timedOut=true;
 }
 bool canReconnect(int p,uint64_t now)const{
  return p>=0&&p<MultiplayerState::MAX_PLAYERS&&peers[p].present&&now-peers[p].lastSeenMs<=RECONNECT_GRACE_MS;
 }
};
