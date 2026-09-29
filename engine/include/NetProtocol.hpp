#pragma once
#include <cstdint>
#include <array>

static constexpr uint32_t HYR_NET_MAGIC=0x4859524E;
static constexpr uint16_t HYR_NET_VERSION=1;

enum class PacketType:uint8_t{Hello,Welcome,Input,Ping,Pong,StateHash,Disconnect,Reconnect};

#pragma pack(push,1)
struct PacketHeader{uint32_t magic{HYR_NET_MAGIC};uint16_t version{HYR_NET_VERSION};PacketType type{};uint8_t player{};uint32_t sequence{};};
struct HelloPacket{PacketHeader h;char playerName[24]{};};
struct InputPacket{PacketHeader h;uint32_t frame{};uint16_t buttons{};int8_t axisX{},axisY{};};
struct HashPacket{PacketHeader h;uint32_t frame{};uint64_t hash{};};
#pragma pack(pop)
