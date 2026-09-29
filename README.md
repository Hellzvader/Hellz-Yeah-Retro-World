# Hellz Yeah Retro World

Hellz Yeah Retro World is a from-scratch native Windows retro platformer engine and game project.

## Engine
- C++20
- SDL3
- Native Windows executable
- Built-in level/editor framework
- Mario, Luigi and Bowser hero framework
- Mushroom Kingdom and Kong enemy systems
- Campaign progression and boss framework
- TikFinity chaos-event integration
- Keyboard and SDL gamepad support
- 1-4 player multiplayer architecture
- Deterministic 60 Hz simulation foundation for netplay
- Windows builds through GitHub Actions

## Build
The active project is in `engine/`.

On Windows, run:
`engine/build-windows.bat`

Or use the **Windows Engine Build** workflow in GitHub Actions and download the generated artifact after a successful build.

## Project rule
This repository is native C++/SDL3 only. The old Lua/LÖVE prototype has been removed.

The repository does not bundle Nintendo ROMs, ripped sprites, music, or other proprietary game assets.
