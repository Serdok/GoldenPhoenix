# L'aigle d'or

Projet en LIFAP4

## Getting started

Pour le moment, l'application ne fonctionne que sous Linux.

### Prerequisites

Les librairies sont fournies avec le projet! Le projet utilise cmake 3.13.3 </br>
Si [cmake](http://cmake.org/) n'est pas installé, un script est founi pour le faire. 
[cmake](http://cmake.org/) sera installé à la racine de l'ordinateur (/usr/local/bin)
```
cd /path/to/game
./cmake_installer.sh
```
Si l'installation échoue à cause de manque de droits, essayer avec
```
sudo ./cmake_installer.sh
```

### Installing

Normalement, les éxecutables sont déjà présents dans leurs dossiers (bin/debug et bin/release). Si ce n'est pas le cas:
```
cd /path/to/game
make init
```
La commande *make init* rafraîchit le cache cmake en cas de modifications locales.

## Built with

[SDL2](http://libsdl.org) - The graphics engine
* [SDL2_image](http://libsdl.org/SDL_image)
* [SDL2_ttf](http://libsdl.org/SDL_ttf)
* [SDL2_mixer](http://libsdl.org/SDL_mixer)

## Authors

* **Anass LAHNIN** - *p1709385*
* **Geoffroy HEURTEL** - *num etu*
* **Julia ...** - *num etu*
