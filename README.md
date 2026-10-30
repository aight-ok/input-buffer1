# Input Buffer — iOS / Geometry Dash 2.208

Version 0.2.0 is a safer, expanded source scaffold for the traditional input-buffer mod.

## Target reported by user

- iPhone / iOS 18
- Geometry Dash iOS 2.208
- Geode 5.11.2
- Geode Enterprise installation via KSign

The metadata now targets Geode 5.11.2 and the iOS 2.208 game version. This is not proof that the source compiles or that every runtime hook is supported by the Enterprise/JIT-less setup.

## Planned all-input behavior

- Buffer discrete jump/orb-style press and release events.
- Support player 1 and player 2 independently.
- Preserve press/release order.
- Expire stale queued inputs after a configurable window.
- Add policies for continuous movement and trigger interactions only after their game semantics are verified.
- Clear queued input on pause, restart, death, level exit, and mod disable.

## Important limitation

This is still a **source prototype**, not a finished playable `.geode` file. `src/main.cpp` only confirms that the mod loads. It does not intercept, delay, or replay gameplay inputs yet.

A correct all-input implementation cannot safely treat every event the same way. A buffered jump/orb tap is a discrete action; ship/UFO/wave/swing movement and held inputs are continuous and must preserve press duration and release timing. Pads and other triggers are generally activated by in-game collision rather than by a player button, so they cannot simply be replayed as button presses.

Before adding gameplay hooks, verify the exact Geode 5.11.2 iOS 2.208 bindings and determine whether the Enterprise build supports the required hook types. Do not guess offsets or call unverified private methods: that risks crashes and stuck inputs.

## Build

Build on a computer with the matching Geode SDK/CLI and iOS toolchain configured:

```sh
geode build
```

The project has not been compiled against the user's exact iOS binary. A successful build on another platform would not prove iOS runtime compatibility.

## Next engineering milestone

1. Verify the exact button event hook used by the 5.11.2 / 2.208 iOS bindings.
2. Verify player identity and input-state APIs.
3. Implement and test a discrete tap queue first.
4. Add safe cleanup on pause/restart/death/exit.
5. Add separate handling for held movement inputs, then evaluate trigger interactions individually.
