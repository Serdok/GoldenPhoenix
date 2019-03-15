# L'oeuf du phénix

Projet en LIFAP4

## Getting started

Pour le moment, l'application ne fonctionne que sous Linux.

### Prerequisites

Les librairies externes sont fournies avec le projet!

#### CMake
Le projet requiert *cmake 3.10* ou plus.
Si [cmake](http://cmake.org/) n'est pas installé, un script est founi pour le faire. 
[cmake](http://cmake.org/) sera installé à la racine de l'ordinateur (/usr/local/bin)
```bash
cd /path/to/dir
sh cmake_installer.sh
```
Si l'installation échoue à cause de manque de droits, essayer avec
```bash
sudo sh cmake_installer.sh
```

#### Plantuml
Les diagrammes sont crées à l'aide de [plantuml](http://plantuml.com/). Il requiert [dot](https://graphviz.gitlab.io/) d'installé. Pour l'installer,

```bash
sudo apt install graphviz
```
Avec ce package installé, le diagramme sera aussi disponible dans la documentation.

### Installing

Le projet utilise le package [FindDoxygen.cmake](cmake/FindDoxygen.cmake) pour générer automatiquement la documentation. Ce package provoquera une erreur lors de la génération si le chemin absolu vers le projet contient des espaces ou des accents.

#### Contributing
Télécharger et extraire l'archive. Puis lancer la cible
```bash
make help
```
qui vous guidera selon le cas souhaité.

Si vous utilisez [Code::Blocks](http://www.codeblocks.org/), le fichier .cbp est disponible dans le dossier [build](./build).

Le projet construit 2 exécutables avec en suffixe le moteur graphique utilisé. Par exemple, l'exécutable Golden_Phoenix_SDL2 utilise la SDL2 pour les graphismes.

#### Playing
Télécharger et extraire l'archive. Puis suivre ces étapes :
```bash
cd /path/to/dir
make cache_release      # Construit le cache cmake dans le dossier build/release
make release            # Construit l'exécutable dans le dossier bin/release
bin/release/Golden_Phoenix_SDL2
```

## Built with

[SDL2](http://libsdl.org) - The graphics engine
* [SDL2_image](http://libsdl.org/SDL_image)
* [SDL2_ttf](http://libsdl.org/SDL_ttf)

[FMod](https://www.fmod.com/) - The audio engine

## Authors

* **Anass LAHNIN** - *p1709385*
* **Geoffroy HEURTEL** - *p1707053*
* **Julia FRANCOIS** - *p1501626*
