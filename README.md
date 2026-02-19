# prog

> Application Qt/CMake simple (projet d'exemple)

## Description

Projet Qt C++ utilisant CMake. Contient les sources et les fichiers UI pour une
petite application de démonstration.

## Prérequis

- Qt 6 installé (ex. via Qt Online Installer)
- CMake (>= 3.20)
- Ninja (recommandé) ou un générateur de votre choix
- MinGW (si vous utilisez la chaîne MinGW) ou MSVC selon votre installation

## Ouvrir avec Qt Creator

1. Ouvrez `CMakeLists.txt` dans Qt Creator.
2. Configurez la chaîne et le kit (Qt, compilateur).
3. Appuyez sur Build / Run.

## Build depuis la ligne de commande (Windows)

Adaptez `CMAKE_PREFIX_PATH` vers votre installation Qt.

```powershell
cmake -S . -B build -G "Ninja" -DCMAKE_PREFIX_PATH="C:/Qt/6.x.x/mingw_64/lib/cmake"
cmake --build build --config Debug
```

Exécutable généré (exemple) : `build/Debug/prog.exe` ou dans le répertoire
spécifique au kit (ex. `build/Desktop_Qt_6_10_2_MinGW_64_bit-Debug/`).

## Contribuer

- Faites un fork et ouvrez une merge request pour proposer des changements.

## Licence

Aucune licence fournie — ajoutez un fichier `LICENSE` si vous souhaitez en
ajouter une.# prog