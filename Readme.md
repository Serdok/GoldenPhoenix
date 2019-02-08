# L'oeuf du phénix

Projet en LIFAP4

## Getting started

Pour le moment, l'application ne fonctionne que sous Linux.

### Prerequisites

Les librairies externes sont fournies avec le projet! Le projet requiert *cmake 3.10* ou plus.
Si [cmake](http://cmake.org/) n'est pas installé, un script est founi pour le faire. 
[cmake](http://cmake.org/) sera installé à la racine de l'ordinateur (/usr/local/bin)
```
cd /path/to/game
sh cmake_installer.sh
```
Si l'installation échoue à cause de manque de droits, essayer avec
```
sudo sh cmake_installer.sh
```

### Installing

Après avoir téléchargé le git, lancer
```
cd /path/to/game
make help
```
La commande *make help* vous guidera selon le cas souhaité.


## Built with

[SDL2](http://libsdl.org) - The graphics engine
* [SDL2_image](http://libsdl.org/SDL_image)
* [SDL2_ttf](http://libsdl.org/SDL_ttf)
* [SDL2_mixer](http://libsdl.org/SDL_mixer)

## Authors

* **Anass LAHNIN** - *p1709385*
* **Geoffroy HEURTEL** - *p1707053*
* **Julia FRANCOIS** - *p1501626*
