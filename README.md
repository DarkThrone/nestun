# nestun

A NES emulator built from scratch in C++23.

## Prerequisites

A C++ compiler with C++23 support (clang++ recommended), Make, and curl (for downloading doctest).

### Linux (Ubuntu/Debian)

```bash
sudo apt install clang make curl \
    libx11-dev libxrandr-dev libxinerama-dev \
    libxcursor-dev libxi-dev libgl-dev
```

### Linux (Arch)

```bash
sudo pacman -S clang make curl \
    libx11 libxrandr libxinerama libxcursor libxi mesa
```

### macOS

Xcode command line tools cover everything — no extra packages needed.

```bash
xcode-select --install
```

## Getting started

Clone the repo with submodules (raylib is vendored as a submodule):

```bash
git clone --recursive https://github.com/DarkThrone/nestun.git
cd nestun
```

If you already cloned without `--recursive`:

```bash
git submodule update --init --recursive
```

Download doctest and build:

```bash
make setup   # downloads doctest.h into external/
make         # builds raylib (first time only) + nestun
```

## Build targets

| Target | Description |
|---|---|
| `make` | Build the emulator (`build/nestun`) |
| `make test` | Build and run the test suite |
| `make raylib` | Force-rebuild raylib from source |
| `make bear` | Regenerate `compile_commands.json` for clangd |
| `make setup` | Download doctest header |
| `make clean` | Remove build artifacts (keeps raylib) |
| `make clean-all` | Remove build artifacts and clean raylib |
| `make help` | List all targets |

## Project structure

```
nestun/
├── src/                  # Emulator source
│   ├── main.cpp          # Entry point + render loop
│   ├── cpu.cpp           # 6502 core
│   ├── bus.cpp           # Memory bus + address decoding
│   └── ...
├── include/              # Headers
│   ├── cpu.h
│   ├── bus.h
│   └── ...
├── tests/                # doctest unit tests
├── external/             # Third-party dependencies
│   ├── raylib/           # git submodule
│   └── doctest.h         # downloaded via make setup
├── Makefile
└── README.md
```

## LSP setup

The project uses clangd for IDE support. Generate `compile_commands.json` with:

```bash
make bear
```

This requires [Bear](https://github.com/rizsotto/Bear) to be installed (`apt install bear` / `brew install bear` / `pacman -S bear`).

## Dependencies

| Dependency | Version | How |
|---|---|---|
| [raylib](https://github.com/raysan5/raylib) | latest | git submodule, compiled from source |
| [doctest](https://github.com/doctest/doctest) | 2.4.11 | single header, downloaded via `make setup` |
