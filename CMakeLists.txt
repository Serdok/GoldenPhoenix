cmake_minimum_required( VERSION 3.10 )
project( Game )
set( CMAKE_CXX_STANDARD 14 )


# Root path relative to bin
set( ROOT "${PROJECT_BINARY_DIR}/../.." )
message( ${ROOT} )

# Search path for FindXXX.cmake files
set( CMAKE_MODULE_PATH ${ROOT}/cmake ${CMAKE_MODULE_PATH} )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_<Debug> ${ROOT}/bin/debug )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_<Release> ${ROOT}/bin/release )


# Define preprocessor flags (#ifdef DEBUG)
IF (CMAKE_BUILD_TYPE STREQUAL Debug)
	add_definitions( -DDEBUG )
	set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ROOT}/bin/debug )
ELSEIF (CMAKE_BUILD_TYPE STREQUAL Release)
	set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ROOT}/bin/release )
ENDIF (CMAKE_BUILD_TYPE STREQUAL Debug)

# Add doxymentation if building in debug mode
IF (CMAKE_BUILD_TYPE STREQUAL Debug)
	find_package( Doxygen REQUIRED )
	set( DOXYFILE_IN /cmake ${CMAKE_MODULE_PATH} )
	set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_<Debug> ${ROOT}/bin/debug )
	set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_<Release> ${ROOT}/bin/release )
ENDIF (CMAKE_BUILD_TYPE STREQUAL Debug)


# Define preprocessor flags (#ifdef DEBUG)
IF (CMAKE_BUILD_TYPE STREQUAL Debug)
	add_definitions( -DDEBUG )
	set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ROOT}/bin/debug )
ELSEIF (CMAKE_BUILD_TYPE STREQUAL Release)
	set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ROOT}/bin/release )
ENDIF (CMAKE_BUILD_TYPE STREQUAL Debug)

# Add doxymentation if building in debug mode
IF (CMAKE_BUILD_TYPE STREQUAL Debug)
	find_package( Doxygen REQUIRED )
	set( DOXYFILE_IN "${ROOT}/doc/doxygen/Doxyfile.in" )
	set( DOXYFILE ${PROJECT_BINARY_DIR}/Doxyfile )
	configure_file( ${DOXYFILE_IN} ${DOXYFILE} @ONLY )
	execute_process(
			COMMAND ${DOXYGEN_EXECUTABLE} "${DOXYFILE}"
			WORKING_DIRECTORY "${ROOT}/doc/doxygen"
	)
ENDIF (CMAKE_BUILD_TYPE STREQUAL Debug)


# SDL2 package
include_directories( ${ROOT}/extern/SDL2/include )
find_library( SDL2_LIBRARY NAMES libSDL2.so PATHS ${ROOT}/extern/SDL2/lib )

# SDL2_image package
include_directories( ${ROOT}/extern/SDL2_image/include )
find_library( SDL2_IMAGE_LIBRARY NAMES libSDL2_image.so PATHS ${ROOT}/extern/SDL2_image/lib )

# SDL2_ttf package
include_directories( ${ROOT}/extern/SDL2_ttf/include )
find_library( SDL2_TTF_LIBRARY NAMES libSDL2_ttf.so PATHS ${ROOT}/extern/SDL2_ttf/lib )

# SDL2_mixer package
include_directories( ${ROOT}/extern/SDL2_mixer/include )
find_library( SDL2_MIXER_LIBRARY NAMES libSDL2_mixer.so PATHS ${ROOT}/extern/SDL2_mixer/lib )


# Header path for auto-completion and relative path
include_directories( ${ROOT}/src/Core )
include_directories( ${ROOT}/src/Helpers )
include_directories( ${ROOT}/src/Rendering )

# !!! Provide each .cpp file manually !!!
# Build the executable
add_executable( ${PROJECT_NAME}
                src/Core/Game.cpp src/Helpers/Exceptions.cpp
                src/Rendering/Texture.cpp src/Helpers/GetResourcePath.cpp src/Core/main.cpp )

# List of header files for the compiler
target_include_directories( ${PROJECT_NAME} PUBLIC ${ROOT}/src/Core ${ROOT}/src/Helpers ${ROOT}/src/Rendering )

# List of library links for the compiler
target_link_libraries( ${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY} ${SDL2_MIXER_LIBRARY} )
