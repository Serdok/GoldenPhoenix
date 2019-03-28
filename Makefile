MAKEFLAGS += --no-print-directory

default_target: help

debug:
	@ mkdir -p bin/debug
	cmake --build build/debug --target all -- -j 2

release:
	@ mkdir -p bin/release
	cmake --build build/release --target all -- -j 2

executables: release debug

cache_debug:
	@ mkdir -p build/debug
	cmake . -Bbuild/debug -DCMAKE_BUILD_TYPE=Debug -G "CodeBlocks - Unix Makefiles"

cache_release:
	@ mkdir -p build/release
	cmake . -Bbuild/release -DCMAKE_BUILD_TYPE=Release -G "CodeBlocks - Unix Makefiles"

caches: cache_release cache_debug

clean:
	cmake --build build/release --target clean -- -j 2
	cmake --build build/debug --target clean -- -j 2

mrproper:
	@ echo "Cleaning all generated files ..."
	@ rm -rf doc/doxygen/html build bin doc/Diagrams/*.png

doc:
	@ echo "Generating documentation ..."
	cmake --build build/debug --target Golden_Phoenix_Documentation -- -j 2

uml:
	@ echo "Refreshing diagrams ..."
	@ java -jar script/plantuml.jar doc/diagrams/*.puml

help:
	@ echo "All targets available : "
	@ echo "	- debug 	-> Build the executables in debug mode"
	@ echo "	- release 	-> Build the executables in release mode"
	@ echo "	- executables 	-> Build the executables in both modes"
	@ echo ""
	@ echo "	- cache_debug 	-> Create the CMake cache for debug mode"
	@ echo "	- cache_release -> Create the CMake cache for release mode"
	@ echo "	- caches 	-> Create the CMake caches for both modes"
	@ echo ""
	@ echo "	- mrproper 	-> Delete all generated files and folders"
	@ echo "	- clean		-> Delete documentation, .o and executable (CMake target)"
	@ echo "	- doc 		-> Build the documentation"
	@ echo "	- uml 		-> Build the diagrams"

.PHONY: doc clean help mrproper
