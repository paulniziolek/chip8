# CHIP-8 Emulator (C++ / SDL2)

Minimal CHIP-8 emulator written in C++17 using SDL2 (graphics/input/audio) and spdlog (logging).

---

## Dependencies

- CMake (>= 3.15)
- SDL2
- spdlog
- C++17 compiler

### Install examples

**macOS (Homebrew)**
```sh
brew install cmake sdl2 spdlog
```

**Ubuntu / Debian**

```sh
sudo apt update
sudo apt install cmake libsdl2-dev libspdlog-dev
```

---

## Build

```sh
sh build.sh
```

Binary output:

```sh
build/chip8
```

---

## Run

```sh
build/chip8 path/to/rom
```

Enable debug logs:

```sh
build/chip8 path/to/rom log
```

---

## Controls

CHIP-8 keypad mapping:

```
1 2 3 C    ->    1 2 3 4
4 5 6 D    ->    Q W E R
7 8 9 E    ->    A S D F
A 0 B F    ->    Z X C V
```

Other:

* Space: pause / resume
* F9: toggle debug logging
* F10: restart
* F12: quit

---

