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
