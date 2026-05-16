# Advanced Calculator (C++20 + Qt6)

Ce README contient **exactement le tutoriel d'installation et de lancement** avec les commandes pour exécuter l'application (le `main` est dans `src/main.cpp`).

## Tutoriel Linux (Ubuntu/Debian)

### 1) Installer les dépendances
```bash
sudo apt update
sudo apt install -y build-essential cmake ninja-build qt6-base-dev qt6-base-dev-tools qt6-tools-dev qt6-tools-dev-tools libqt6charts6-dev
```

### 2) Cloner le projet et entrer dans le dossier
```bash
git clone <URL_DU_REPO>
cd advanced-calculator-c-
```

### 3) Configurer le projet (CMake)
```bash
cmake -S . -B build -G Ninja
```

### 4) Compiler
```bash
cmake --build build -j
```

### 5) Lancer l'application (point d'entrée: `main`)
```bash
./build/advanced_calculator
```

---

## Tutoriel Windows (MSVC + Qt6)

### 1) Prérequis
- Installer **Visual Studio 2022** (Desktop development with C++).
- Installer **Qt 6.5+** avec le kit MSVC (via Qt Maintenance Tool).
- Installer **CMake** et **Ninja** (ou utiliser ceux de Visual Studio).

### 2) Ouvrir le bon terminal
Ouvrir **x64 Native Tools Command Prompt for VS 2022**.

### 3) Cloner le projet et entrer dans le dossier
```bat
git clone <URL_DU_REPO>
cd advanced-calculator-c-
```

### 4) Configurer le projet
```bat
cmake -S . -B build -G Ninja
```

### 5) Compiler
```bat
cmake --build build
```

### 6) Lancer l'application (point d'entrée: `main`)
```bat
build\advanced_calculator.exe
```

---

## Dépannage rapide

### Erreur `Qt6Config.cmake not found`
Qt6 n'est pas détecté par CMake. Définir `CMAKE_PREFIX_PATH` vers le dossier Qt.

Exemple Linux:
```bash
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=/opt/Qt/6.6.2/gcc_64
```

Exemple Windows:
```bat
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=C:\Qt\6.6.2\msvc2019_64
```
=======
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
