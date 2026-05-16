# Advanced Calculator (C++20 + Qt6)

Professional-grade desktop calculator with modular architecture, modern dark UI, extensible services, and cross-platform design.

## Implemented Modes
- Basic + Scientific calculator (parentheses, constants, functions, preview, keyboard Enter)
- Programmer mode architecture page (base conversion/bitwise ready)
- Unit conversion architecture page (all requested categories scaffolded)
- Math Notes workspace with local persistence
- Full JSON-backed history with timestamps and persistent storage

## Advanced Features
- Expression parser engine (modular `core/`)
- Settings + theme service
- Startup fade animation
- Mini graph visualizer demo (sin curve)
- Session-backed autosave style services
- Plugin-ready folder (`src/plugins`)

## Build
### Linux
```bash
sudo apt install qt6-base-dev qt6-charts-dev cmake g++
cmake -S . -B build
cmake --build build -j
./build/advanced_calculator
```

### Windows (MSVC)
1. Install Qt 6.5+ with MSVC kit.
2. Open x64 Native Tools prompt.
3. Build:
```bat
cmake -S . -B build -G "Ninja"
cmake --build build
build\advanced_calculator.exe
```

## Architecture
- `src/app`: application bootstrapping
- `src/core`: parser/engine layer
- `src/services`: persistence, settings, history, formula manager
- `src/ui`: views/widgets and navigation
- `themes/`: QSS themes with support for custom themes
- `data/`: runtime local storage

## Notes
Currency conversion is API-ready in architecture but intentionally offline by default.
