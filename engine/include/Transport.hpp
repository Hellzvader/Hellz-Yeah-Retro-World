#pragma once
#include "NetProtocol.hpp"
#include <SDL3/SDL.h>
#include <array>
#include <cstdint>
#include <cstring>
#include <deque>
#include <vector>

// Platform-neutral transport boundary. The Windows UDP backend implements this interface.
// Keeping sockets outside simulation lets offline/local/netplay share identical gameplay code.
struct NetworkMessage{std::vector<uint8_t> bytes;};
class Transport{
public:
 virtual ~Transport()=default;
 virtual bool open(uint16_t port)=0;
 virtual bool connectTo(const char*host,uint16_t port)=0;
 virtual bool send(const void*data,size_t size)=0;
 virtual bool receive(NetworkMessage&out)=0;
 virtual void close()=0;
};
