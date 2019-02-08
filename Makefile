MAKEFLAGS += --no-print-directory

default_target: refresh_debug debug

all: refresh debug release

debug: 
	cmake --build bin/debug --target all -- -j 2

release: 
	cmake --build bin/release --target all -- -j 2

refresh_debug:
	@ touch CMakeLists.txt
	cmake -Bbin/debug -S. -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles"

refresh_release:
	@ touch CMakeLists.txt
	cmake -Bbin/release -S. -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles"

refresh: refresh_debug refresh_release


init:
	@ touch CMakeLists.txt
	@ rm -rf bin/debug/* bin/release/*
	cmake -Bbin/debug -S. -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles"
	cmake -Bbin/release -S. -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles"

.PHONY:
clean_debug:
	cmake --build bin/debug --target clean

.PHONY:
clean_release:
	cmake --build bin/release --target clean

.PHONY:
clean: clean_debug clean_release

help:
	@ echo "Dans le cas d'une installation fraîche, lancer make init"
	@ echo "Dans le cas d'une modification du fichier CMakeLists.txt, lancer make refresh"
	@ echo "Dans le cas d'un rebuild précis, lancer make debug || make release"
	@ echo "Dans le cas d'un nettoyage des fichiers, lancer make clean"
