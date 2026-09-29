#pragma once
#include "Multiplayer.hpp"
#include <string>
enum class LobbyMode{Offline,Host,Client};
struct LobbyState{
 LobbyMode mode{LobbyMode::Offline};bool active{};bool inGame{};std::string hostAddress{"127.0.0.1"};uint16_t port{28777};
 void host(){mode=LobbyMode::Host;active=true;}
 void join(const std::string&address){mode=LobbyMode::Client;hostAddress=address;active=true;}
 void close(){mode=LobbyMode::Offline;active=false;inGame=false;}
};
