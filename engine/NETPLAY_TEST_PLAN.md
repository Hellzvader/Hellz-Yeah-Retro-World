# Netplay test plan
1. Verify two local controllers independently control two player slots.
2. Verify four local controllers join/leave without reassigning existing slots.
3. Run the same recorded input stream twice and compare state hashes every 60 frames.
4. Host/client handshake must reject mismatched protocol versions.
5. Simulate 100-250 ms latency with three-frame input delay.
6. Disconnect a client for less than 15 seconds and reclaim its player slot.
7. Verify a disconnected player cannot freeze the host indefinitely.
8. Verify stage transition occurs on the same simulation frame for every peer.
9. Verify boss HP, collectibles, checkpoints and Peach rescue state are included in authoritative synchronization before public netplay testing.
10. Test Xbox-compatible, PlayStation-compatible and generic SDL-mapped controllers.

Current code provides the multiplayer model, packet definitions, input serialization, heartbeat/reconnect state and transport boundary. A concrete UDP backend and runtime integration still need to be completed and compiled/tested.
