# Activate the character sprites in an existing Windows build

The engine loads external BMP strips from `assets/imported/` relative to the
folder containing `HellzYeahRetroEngine.exe`. If the files are absent, it
renders the built-in pixel-art fallback characters.

For the personal Windows test build, extract the separately provided
`HellzYeah_Activate_Character_Sprites.zip` **into the same folder as the EXE**.
Expected paths include:

- `assets/imported/heroes/mario_idle.bmp`
- `assets/imported/heroes/mario_run.bmp`
- `assets/imported/heroes/mario_jump.bmp`
- `assets/imported/heroes/luigi_idle.bmp`
- `assets/imported/heroes/luigi_run.bmp`
- `assets/imported/heroes/luigi_jump.bmp`
- `assets/imported/heroes/bowser_idle.bmp`
- `assets/imported/heroes/bowser_run.bmp`
- `assets/imported/heroes/bowser_jump.bmp`
- `assets/imported/heroes/bowser_fire.bmp`
- `assets/imported/heroes/bowser_smash.bmp`
- `assets/imported/characters/peach_idle.bmp`

Do not place the BMP files beside the EXE without their subfolders. The
current character strips are provisional; they need animation-frame review.
This does not install enemy sprites or terrain artwork. The GitHub Actions
build does not currently contain these character BMPs; it only copies artwork
that is present in the repository at build time.

If characters still appear as fallback graphics, check the folder paths and
launch the EXE from a terminal to see missing sprite path messages.
