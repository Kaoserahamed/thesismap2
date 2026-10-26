# Last Train: 03:17 — agent rules

## Game in one paragraph
A first-person 3D mystery game. The player is a night-shift train operator whose
shift begins at 03:17 AM. The railway is a time loop. The player explores a train
and three stations, talks to 5-7 passengers, solves 8-12 puzzles, operates train
controls, and reaches one of three endings. No combat, no gore. Atmosphere comes
from lighting, sound, and environmental storytelling. Target: a 30-45 minute
first playthrough.

## Signature mechanic (protect it)
"The train remembers." At every loop reset, volatile world state is restored but
selected persistent changes and all journal knowledge remain. Passengers, props,
and dialogue vary by loop number. Every system must be written so that it can ask
the LoopSystem what state an entity is in right now.

## Tech stack
- C++17, CMake >= 3.20, raylib 5.5 (FetchContent), nlohmann/json 3.11 (FetchContent)
- No other third-party libraries unless I approve them in chat.
- Targets: Windows 10/11 (MSVC 2022 or MinGW-w64) and Linux (GCC/Clang). Keep code portable.
- Verify every raylib call against the headers in the fetched raylib source
  (build/_deps/raylib-src/src/raylib.h, raymath.h, rlgl.h). Never guess an API.

## Architecture rules
- Source in src/, grouped by module: core, world, player, systems, ui, util.
- One class or struct per .h/.cpp pair. Headers use #pragma once.
- Modules talk through an EventBus and a shared WorldState, not through global variables.
- Game content (dialogue, items, clues, puzzles, missions, endings, loop rules,
  station layouts, passenger data) lives in JSON under assets/data/. Code must not
  hard-code story text.
- Prefer composition over deep inheritance. Prefer value types and std::unique_ptr.
  No raw new/delete. No naked owning pointers.
- Every system exposes a small public interface in its header, has a one-line
  comment explaining its job, and logs problems through util/Log.h (never silently fail).
- Rendering and update are separate: Update(dt) must not issue draw calls.

## Code style
- Types PascalCase, functions camelCase, members m_camelCase, constants kPascalCase.
- Max ~300 lines per file; split when larger. No commented-out code.
- Use const, enum class, and std::optional where appropriate. Avoid macros.

## Build commands
  cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
  cmake --build build --config Debug -j
  Run: build/LastTrain (Windows MSVC: build/Debug/LastTrain.exe)

## Working agreement
1. Before coding any task, reply with a short plan: files to add/change, new
   data formats, risks. Wait for me to say "go".
2. Implement only the task I gave you. Do not add features from later steps.
3. After implementing, build. If the build fails, fix it before reporting.
4. Finish with: what changed (files), how to test it in-game, known gaps.
5. Keep docs/ARCHITECTURE.md updated with module responsibilities and data formats.
6. Prefer a small working feature over a large half-working one.

## Definition of done for any task
- Compiles with zero warnings at /W4 or -Wall -Wextra.
- Runs without crashing for 5 minutes of play.
- No hard-coded story text outside assets/data/.
- Acceptance checklist of the task passes.

## Debug conventions
- F1 toggles debug overlay (FPS, position, loop number, active flags).
- Keys F5-F9 are reserved for debug actions defined per task.
- Debug code is wrapped in `#ifndef NDEBUG`.
