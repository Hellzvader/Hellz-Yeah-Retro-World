# Hellz Yeah Retro Engine — Native Engine

This folder is the new from-scratch Windows game engine/editor. The older LÖVE files at repository root are only the discarded prototype and will not be the final engine.

## Milestone 1
- Native C++20 application
- SDL3 window, renderer, keyboard/gamepad foundation
- Built-in level/world representation
- Level editor placement brushes
- Ground/platform collision
- Built-in Play/Test mode
- Camera
- Native level save format (.hyrworld)

## Editor controls
- 1 Ground
- 2 Platform
- 3 Enemy
- 4 Token
- 5 Barrel
- 6 Vine
- 7 Exit
- Left click places selected object
- A/D or arrows pan editor
- F2 saves level1.hyrworld
- F5 enters/exits Play Test
- ESC exits Play Test / closes editor

## Play controls
A/D or arrows move. Space/Z jumps. F5 returns to editor.

## Windows build
Install Visual Studio 2022 with Desktop development with C++ and CMake support.

From a Developer Command Prompt:
```
cd engine
cmake -S . -B build -A x64
cmake --build build --config Release
```

The executable is generated under `engine/build/Release/`.

SDL3 is fetched by CMake during the build. Future milestones will add the visual docked editor, sprite/animation importer, character/enemy makers, events, world graph, audio, TikFinity integration, packaging and game export.
