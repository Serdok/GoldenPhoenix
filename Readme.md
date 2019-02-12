# L'oeuf du phénix

Projet en LIFAP4

## Getting started

Pour le moment, l'application ne fonctionne que sous Linux.

### Prerequisites

Les librairies externes sont fournies avec le projet! Le projet requiert *cmake 3.10* ou plus.
Si [cmake](http://cmake.org/) n'est pas installé, un script est founi pour le faire. 
[cmake](http://cmake.org/) sera installé à la racine de l'ordinateur (/usr/local/bin)
```bash
cd /path/to/game
sh cmake_installer.sh
```
Si l'installation échoue à cause de manque de droits, essayer avec
```bash
sudo sh cmake_installer.sh
```

### Installing

#### Contributing
Télécharger et extraire l'archive. Puis suivre ces étapes :
> cd /path/to/dir
```bash
make caches         # Construit le cache cmake dans le dossier build/
make executables    # Construit les executables dans le dossier bin/
```

Il existe d'autres cibles : 
```bash
make cache_debug    # Construit seulement le cache cmake pour le mode debug
make cache_release  # Construit seulement le cache cmake pour le mode release
make debug          # Construit seulement l'exécutable en mode debug
make release        # Construit seulement l'exécutable en mode release
make clean          # Nettoie tous les fichiers générés dans les dossiers doc/doxygen, build et bin
``` 

> make caches<br/>
Cette commande construit (ou rafraichît) les fichiers caches de cmake. Elle ne doit être appelée qu'une seule fois,  

> make executables<br/>
Cette commande construit (ou rafraîchit) les exécutables selon les modifications des fichiers source.

#### Playing
Télécharger et extraire l'archive. Puis suivre ces étapes :
> cd /path/to/dir
```bash
make cache_release      # Construit le cache cmake dans le dossier build/release
make release            # Construit l'exécutable dans le dossier bin/release
bin/release/Game
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
