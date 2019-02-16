MAKEFLAGS += --no-print-directory

debug:
	@ mkdir -p bin/debug
	cmake --build build/debug --target all -- -j 2

release:
	@ mkdir -p bin/release
	cmake --build build/release --target all -- -j 2

executables: release debug doc

cache_debug:
	@ mkdir -p build/debug
	cmake . -Bbuild/debug -DCMAKE_BUILD_TYPE=Debug -G "CodeBlocks - Unix Makefiles"

cache_release:
	@ mkdir -p build/release
	cmake . -Bbuild/release -DCMAKE_BUILD_TYPE=Release -G "CodeBlocks - Unix Makefiles"

caches: cache_release cache_debug

clean:
	@ echo "Cleaning all generated files ..."
	@ rm -rf doc/doxygen/html build bin doc/Diagrams/*.png

doc:
	@ echo "Generating doxumentation ..."
	@ doxygen build/debug/Doxyfile

uml:
	@ echo "Refreshing diagrams ..."
	@ java -jar script/plantuml.jar doc/Diagrams/*.puml

.PHONY: doc clean
