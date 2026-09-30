# Local Visual Asset Pack

Hellz Yeah Retro World is an unofficial, non-commercial fan project. Nintendo-related characters, names, artwork and game assets remain the property of their respective rights holders. The engine code and original project code are separate from those assets.

## Reference / credits
Sprite-sheet reference pages selected for this project:
- The Spriters Resource — Super Mario All-Stars / Super Mario Bros.
- The Spriters Resource — Super Mario All-Stars / Super Mario Bros. 3
- The Spriters Resource — Super Mario World
- The Spriters Resource — Donkey Kong Country
- The Spriters Resource — Donkey Kong Country 2
- The Spriters Resource — Donkey Kong Country 3

Credit the individual sheet submitter/ripper listed on each source page when preparing a local asset pack.

## Local-only assets
This directory is ignored by Git except for this README. Proprietary/ripped graphics are not committed to the public repository. Put prepared BMP animation strips here and the Windows build will load them relative to the executable.

### Heroes
- heroes/mario_idle.bmp
- heroes/mario_run.bmp
- heroes/mario_jump.bmp
- heroes/luigi_idle.bmp
- heroes/luigi_run.bmp
- heroes/luigi_jump.bmp
- heroes/bowser_idle.bmp
- heroes/bowser_run.bmp
- heroes/bowser_jump.bmp

### Mushroom enemies
- enemies/mushroom/goomba.bmp
- enemies/mushroom/koopa.bmp
- enemies/mushroom/paratroopa.bmp
- enemies/mushroom/bobomb.bmp
- enemies/mushroom/beetle.bmp
- enemies/mushroom/shyguy.bmp
- enemies/mushroom/hammerbro.bmp
- enemies/mushroom/lakitu.bmp

### Kong enemies / boss
- enemies/kong/kritter.bmp
- enemies/kong/klump.bmp
- enemies/kong/necky.bmp
- enemies/kong/zinger.bmp
- enemies/kong/gnawty.bmp
- enemies/kong/klaptrap.bmp
- enemies/kong/army.bmp
- enemies/kong/mini_necky.bmp
- bosses/dk_guardian.bmp

### Powerups and world art
- items/mushroom.bmp
- items/fireflower.bmp
- items/star.bmp
- items/heart.bmp
- items/banana.bmp
- items/coin.bmp
- tiles/ground.bmp
- tiles/platform.bmp
- props/barrel.bmp
- props/vine.bmp
- props/exit.bmp

Sheets should be converted/prepared as equal-sized horizontal BMP frame strips. Magenta RGB(255,0,255) is treated as transparent. Nearest-neighbor scaling is used for crisp pixel art.


## Active gameplay animation states

The runtime manifest now supports the cleaned gameplay-only source-sheet states being prepared for local visual builds:

- Mario: idle / run / jump
- Luigi: idle / run / jump
- Bowser: idle / run / jump / fire / smash
- King Zing: flight / attack / hurt
- Kudgel: walk / jump / club smash

Special/gag poses (including the Mario mop/cleaning frames) are intentionally excluded from normal gameplay animation sets.
