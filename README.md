# Terminal Pong

![C](https://img.shields.io/badge/C-000000?style=for-the-badge&logo=c&logoColor=white)
![Assembly](https://img.shields.io/badge/NASM-007ACC?style=for-the-badge&logo=linux&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-x86_64-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![ncurses](https://img.shields.io/badge/ncurses-terminal_UI-2E8B57?style=for-the-badge)
![Makefile](https://img.shields.io/badge/build-make-6DB33F?style=for-the-badge)
![License](https://img.shields.io/badge/License-Apache_2.0-blue?style=for-the-badge)

A terminal-based Pong game for Linux x86-64 built with **C**, **NASM assembly**, and **ncurses**.

The project splits responsibilities cleanly:

* **C** handles the application structure, input, UI, and game state management.
* **Assembly** handles the game mechanics and ball physics.
* **ncurses** handles terminal rendering.
* **Makefile** ties everything together into a simple build process.

---

## Features

* Splash screen with custom author text
* Main menu with game mode selection
* Two-player mode
* Single-player AI mode
* Terminal UI rendered with ncurses
* C + Assembly split for gameplay logic
* Linux x86-64 build target
* Lightweight build process using `make`

---

## What I built

This project was created as a small retro-style terminal game and as a systems-programming exercise.

### Core architecture

The codebase is organized into clear layers:

* `src/main.c` controls the main loop and screen flow.
* `src/ui.c` draws the splash screen, menu, and game screen.
* `src/input.c` handles keyboard input and mode switching.
* `src/game.c` initializes the game state.
* `asm/update_game.asm` updates the ball movement, wall collisions, paddle collisions, and scoring.
* `asm/helpers.asm` resets the ball after points.

### Design choices

* The game state is stored in a C struct with fixed offsets so the assembly code can access it safely.
* The assembly follows the Linux x86-64 System V ABI.
* The build is intentionally lightweight so it can be compiled quickly on Fedora.
* The UI is state-based, using splash / menu / playing modes.
* AI mode was added so the game can be played solo.

---

## Project structure

```text
pong-asm/
├── Makefile
├── README.md
├── include/
│   ├── game.h
│   ├── input.h
│   ├── ui.h
│   └── config.h
├── src/
│   ├── main.c
│   ├── game.c
│   ├── input.c
│   └── ui.c
└── asm/
    ├── update_game.asm
    └── helpers.asm
````

---

## Requirements

You need:

* Linux x86-64
* `gcc`
* `nasm`
* `ncurses-devel`
* `make`

On Fedora, install them with:

```bash
sudo dnf install gcc nasm ncurses-devel --setopt=install_weak_deps=False
```

---

## Build

From the project root:

```bash
make
```

To remove build artifacts:

```bash
make clean
```

---

## Run

```bash
./pong
```

---

## Controls

### In the menu

* `Enter` or `Space` → continue from splash
* `1` → two-player mode
* `2` → single-player AI mode
* `Q` → quit

### In the game

* `↑` / `↓` → move the controllable paddle
* `W` / `S` → alternate paddle controls in two-player mode
* `Q` → quit

---

## How it works

### Game flow

1. The program starts in the splash screen.
2. The player moves to the main menu.
3. The player selects either two-player mode or AI mode.
4. The game loop updates input, physics, and rendering every frame.

### Assembly responsibilities

The assembly layer handles:

* ball movement
* wall collision
* paddle collision
* score updates
* ball reset after scoring

This keeps the hot gameplay logic close to the metal.

### C responsibilities

The C layer handles:

* initialization
* terminal setup
* input handling
* UI drawing
* mode switching
* AI paddle movement

---

## Notes

* The assembly code is written for **Linux x86-64**.
* The project uses a fixed struct layout so C and assembly agree on memory offsets.
* The terminal UI is intentionally simple and lightweight.
* This is a small project, but it demonstrates low-level integration between C and assembly.

---

## Future improvements

Possible next upgrades:

* highlighted menu selection
* animated splash screen
* smoother paddle motion
* smarter AI prediction
* pause menu
* sound effects
* fullscreen-style terminal intro

---

## Author

**BIOWESS**

---

## License

* This project is licensed under the Apache License 2.0.
* License text: see the [LICENSE](LICENSE) file
