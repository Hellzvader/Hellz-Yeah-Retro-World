#pragma once
#include "Gamepad.hpp"
#include "NetProtocol.hpp"
enum InputBits:uint16_t{IB_LEFT=1,IB_RIGHT=2,IB_UP=4,IB_DOWN=8,IB_JUMP=16,IB_ATTACK=32,IB_SPECIAL=64,IB_INTERACT=128,IB_START=256};
inline uint16_t packButtons(const PadInput&i){return(i.left?IB_LEFT:0)|(i.right?IB_RIGHT:0)|(i.up?IB_UP:0)|(i.down?IB_DOWN:0)|(i.jump?IB_JUMP:0)|(i.attack?IB_ATTACK:0)|(i.special?IB_SPECIAL:0)|(i.interact?IB_INTERACT:0)|(i.start?IB_START:0);}
inline int8_t packAxis(float v){if(v>1)v=1;if(v<-1)v=-1;return(int8_t)(v*127);}
inline InputPacket makeInputPacket(uint8_t player,uint32_t seq,uint32_t frame,const PadInput&i){InputPacket p;p.h.type=PacketType::Input;p.h.player=player;p.h.sequence=seq;p.frame=frame;p.buttons=packButtons(i);p.axisX=packAxis(i.axisX);p.axisY=packAxis(i.axisY);return p;}
