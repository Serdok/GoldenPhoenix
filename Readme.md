# L'oeuf du phénix

Projet en LIFAP4

## Getting started

Pour le moment, l'application ne fonctionne que sous Linux.

### Prerequisites

Les librairies externes sont fournies avec le projet! Le projet requiert *cmake 3.10* ou plus.
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

### Installing

Le projet utilise le package [FindDoxygen.cmake](cmake/FindDoxygen.cmake). Ce package n'aime pas les chemins absolus avec des accents, cela provoquera une erreur lors de la génération.

#### Contributing
Télécharger et extraire l'archive. Puis suivre ces étapes :
```bash
cd /path/to/dir
make caches         # Construit le cache cmake dans le dossier build/
make executables    # Construit les executables dans le dossier bin/
```

Il existe d'autres cibles : 
```bash
make cache_debug    # Construit seulement le cache cmake pour le mode debug
make cache_release  # Construit seulement le cache cmake pour le mode release
make debug          # Construit seulement l'exécutable en mode debug
make release        # Construit seulement l'exécutable en mode release
make clean          # Nettoie tous les fichiers générés dans les dossiers doc/doxygen, doc/diagrams, build et bin
make doc            # Rafraîchit la documentation du projet. La documentation est initialement générée lors de la génération des caches
make uml            # Rafraîchit les images des diagrammes du projet. Les images sont initialement générées lors de la génération des caches

``` 

*make caches*<br/>
Cette commande construit les fichiers caches de cmake. Cette cible doit être appelée qu'une fois après avoir téléchargé l'archive.

*make executables*<br/>
Cette commande construit (ou rafraîchit) les exécutables. Cette cible doit être appelée en cas de modification dans les [fichiers sources](src) ou du fichier [CMakeLists.txt](CMakeLists.txt).<br/>
Elle équivaut à la cible *make all* pour un Makefile classique.

Si vous utilisez [Code::Blocks](http://www.codeblocks.org/), le projet est disponible dans le dossier build.

#### Playing
Télécharger et extraire l'archive. Puis suivre ces étapes :
```bash
cd /path/to/dir
make cache_release      # Construit le cache cmake dans le dossier build/release
make release            # Construit l'exécutable dans le dossier bin/release
bin/release/Golden_Phoenix
```

## Built with

[SDL2](http://libsdl.org) - The graphics engine
* [SDL2_image](http://libsdl.org/SDL_image)
* [SDL2_ttf](http://libsdl.org/SDL_ttf)
* [SDL2_mixer](http://libsdl.org/SDL_mixer)

## Authors

* **Anass LAHNIN** - *p1709385*
* **Geoffroy HEURTEL** - *p1707053*
* **Julia FRANCOIS** - *p1501626*
