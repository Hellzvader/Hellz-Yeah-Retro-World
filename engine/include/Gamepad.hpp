#pragma once
#include <SDL3/SDL.h>
#include <array>

struct PadInput{
 bool left{},right{},up{},down{},jump{},attack{},special{},interact{},start{};
 float axisX{},axisY{};
};

class GamepadManager{
public:
 static constexpr int MAX_PLAYERS=4;
 std::array<SDL_Gamepad*,MAX_PLAYERS> pads{};
 ~GamepadManager(){shutdown();}
 void scan(){
  int count=0;SDL_JoystickID* ids=SDL_GetGamepads(&count);
  if(!ids)return;
  for(int i=0;i<count&&i<MAX_PLAYERS;i++)if(!pads[i])pads[i]=SDL_OpenGamepad(ids[i]);
  SDL_free(ids);
 }
 void shutdown(){for(auto&p:pads){if(p){SDL_CloseGamepad(p);p=nullptr;}}}
 PadInput read(int player)const{
  PadInput i{};if(player<0||player>=MAX_PLAYERS||!pads[player])return i;auto*p=pads[player];
  auto b=[&](SDL_GamepadButton x){return SDL_GetGamepadButton(p,x);};
  i.left=b(SDL_GAMEPAD_BUTTON_DPAD_LEFT);i.right=b(SDL_GAMEPAD_BUTTON_DPAD_RIGHT);
  i.up=b(SDL_GAMEPAD_BUTTON_DPAD_UP);i.down=b(SDL_GAMEPAD_BUTTON_DPAD_DOWN);
  i.jump=b(SDL_GAMEPAD_BUTTON_SOUTH);i.attack=b(SDL_GAMEPAD_BUTTON_WEST);
  i.special=b(SDL_GAMEPAD_BUTTON_EAST);i.interact=b(SDL_GAMEPAD_BUTTON_NORTH);
  i.start=b(SDL_GAMEPAD_BUTTON_START);
  i.axisX=SDL_GetGamepadAxis(p,SDL_GAMEPAD_AXIS_LEFTX)/32767.f;
  i.axisY=SDL_GetGamepadAxis(p,SDL_GAMEPAD_AXIS_LEFTY)/32767.f;
  if(i.axisX<-.25f)i.left=true;if(i.axisX>.25f)i.right=true;
  if(i.axisY<-.25f)i.up=true;if(i.axisY>.25f)i.down=true;
  return i;
 }
};
