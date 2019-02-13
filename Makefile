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
	cmake . -Bbuild/debug -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles"

cache_release:
	@ mkdir -p build/release
	cmake . -Bbuild/release -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles"

caches: cache_release cache_debug

clean:
	@ rm -rf doc/doxygen/html build/* bin/*
	@ echo "Cleaning all generated files ..."

doc:
	@ doxygen build/debug/Doxyfile
	@ echo "Generating doxumentation ..."

.PHONY: doc clean
