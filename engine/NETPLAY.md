# Controller + Netplay architecture

## Controllers
The engine supports up to four SDL3 gamepads. Standard mapping:
- Left stick / D-pad: movement
- South button: jump
- West button: attack
- East button: special
- North button: interact / barrel
- Start: pause

Keyboard remains available for Player 1.

## Netplay
Gameplay is being structured around a deterministic 60 Hz fixed simulation tick. Network play exchanges compact per-player input frames rather than transmitting the whole rendered world every frame.

Planned transport layer:
- host/join lobby
- 2-4 players
- input delay configuration
- frame-numbered input packets
- desync checks
- reconnect handling
- optional rollback once deterministic simulation is verified

Rendering, particles, camera shake and audio are kept outside authoritative simulation so they cannot create gameplay desyncs.

The networking transport itself is not finished yet. Gamepad input and the deterministic/fixed-step foundation are now represented in engine code.
