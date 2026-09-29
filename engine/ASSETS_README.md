# Art and audio pipeline

The engine now has an asset manager and animation component. Final sprite sheets can be dropped into an assets directory and mapped to animation clips without rewriting character physics or AI.

The repository intentionally does not bundle ripped Nintendo ROM graphics, sprite sheets, music or sound effects. The current renderer uses engine-generated placeholder shapes while gameplay is built. Original or user-supplied art can replace those assets later.

Recommended sprite-sheet organization:
assets/heroes/
assets/enemies/mushroom/
assets/enemies/kong/
assets/bosses/
assets/tilesets/
assets/ui/
assets/music/
assets/sfx/
