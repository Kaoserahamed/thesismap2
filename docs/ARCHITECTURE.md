# Architecture

## Modules
- `core`: Game loop, window, GameStateMachine, EventBus, WorldState, Input, DebugOverlay.
- `world`: (placeholder) world entities and stations.
- `player`: (placeholder) player controller.
- `systems`: (placeholder) game systems.
- `ui`: (placeholder) UI.
- `util`: Log, Assets, Json helpers.

## Ownership
- `Game` owns Window, GameStateMachine, Input.
- `GameStateMachine` owns state stack (unique_ptr).
- `Assets` caches resources (static maps).
- `WorldState` shared by value/reference where needed.

## Data folders
- `assets/data`: JSON game content.
- `assets/models`, textures, audio, shaders, fonts: media.

## Update/Draw split
- `Update(dt)` changes state only; no draw calls.
- `draw()` issues render calls only.
