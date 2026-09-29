#pragma once
#include "World.hpp"
struct EditorState{ObjectType brush{ObjectType::Ground};float zoom{1};bool grid{true};int gridSize{16};bool showCollision{true};};
inline Rect snappedRect(float x,float y,float w,float h,const EditorState&e){
 int g=e.grid?e.gridSize:1;return {(float)((int)x/g*g),(float)((int)y/g*g),w,h};
}
