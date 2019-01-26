MAKEFLAGS += --no-print-directory

all: debug release

debug: 
	cmake --build bin/debug --target all -- -j 2

release: 
	cmake --build bin/release --target all -- -j 2

rebuild:
	@ rm -rf bin/debug
	@ rm -rf bin/release
	@ touch CMakeLists.txt
	cmake -B bin/debug -S . -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles"
	cmake -B bin/release -S . -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles"

init: rebuild debug release
