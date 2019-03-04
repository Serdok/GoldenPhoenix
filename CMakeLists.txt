cmake_minimum_required( VERSION 3.10 )
project( Golden_Phoenix )
set( CMAKE_CXX_STANDARD 14 )


# Root path relative to bin
set( ROOT "${PROJECT_BINARY_DIR}/../.." )
IF (IS_DIRECTORY ${ROOT}/bin AND IS_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
	set( ROOT ${PROJECT_SOURCE_DIR} ) # Make path easier to read
ENDIF (IS_DIRECTORY ${ROOT}/bin AND IS_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# List of directories in src
set( SRC_DIRS ${ROOT}/src/Core ${ROOT}/src/Helpers ${ROOT}/src/Rendering )

# Search path for FindXXX.cmake files
set( CMAKE_MODULE_PATH ${ROOT}/cmake ${CMAKE_MODULE_PATH} )


# Define preprocessor flags (#ifdef DEBUG) and binaries output
IF (CMAKE_BUILD_TYPE STREQUAL Debug)
	message( "Set executable output directory to ${ROOT}/bin/debug." )
	set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ROOT}/bin/debug )
	add_definitions( -DDEBUG )
ELSEIF (CMAKE_BUILD_TYPE STREQUAL Release)
	message( "Set executable output directory to ${ROOT}/bin/release." )
	set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ROOT}/bin/release )
ENDIF (CMAKE_BUILD_TYPE STREQUAL Debug)

# Add documentation if building in debug mode
IF (CMAKE_BUILD_TYPE STREQUAL Debug)
	message( "Building documentation." )
	find_package( Doxygen REQUIRED )
	set( DOXYFILE_IN "${ROOT}/doc/doxygen/Doxyfile.in" )
	set( DOXYFILE ${PROJECT_BINARY_DIR}/Doxyfile )
	IF (DOXYGEN_DOT_FOUND STREQUAL NO)
		message( WARNING "Dot executable not found, class diagram cannot be integrated within documentation. It can still be found under doc/diagram directory." )
	ENDIF (DOXYGEN_DOT_FOUND STREQUAL NO)
	configure_file( ${DOXYFILE_IN} ${DOXYFILE} @ONLY )
	execute_process(
			COMMAND ${DOXYGEN_EXECUTABLE} "${DOXYFILE}"
			WORKING_DIRECTORY "${ROOT}/doc/doxygen"
	)
ENDIF (CMAKE_BUILD_TYPE STREQUAL Debug)

# Update diagrams if building in debug mode
IF (CMAKE_BUILD_TYPE STREQUAL Debug)
	message( "Refreshing diagrams." )
	execute_process(
			COMMAND java -jar script/plantuml.jar doc/diagrams/Class.puml doc/diagrams/Gantt.puml -o ${ROOT}/doc/diagrams/
	        WORKING_DIRECTORY ${ROOT}
	)
ENDIF (CMAKE_BUILD_TYPE STREQUAL Debug)


# SDL2 library
message( "Adding SDL2 files." )
include_directories( ${ROOT}/extern/include/SDL2 )
set( SDL2 ${ROOT}/extern/lib/SDL2 )

# SDL2_image library
message( "Adding SDL2_image files." )
include_directories( ${ROOT}/extern/include/SDL2_image )
set( SDL2_image ${ROOT}/extern/lib/SDL2_image )

# SDL2_ttf library
message( "Adding SDL2_ttf files." )
include_directories( ${ROOT}/extern/include/SDL2_ttf )
set( SDL2_ttf ${ROOT}/extern/lib/SDL2_ttf )

# SDL2_mixer library
message( "Adding SDL2_mixer files." )
include_directories( ${ROOT}/extern/include/SDL2_mixer )
set( SDL2_mixer ${ROOT}/extern/lib/SDL2_mixer )

message( "Adding FMod files." )
include_directories( ${ROOT}/extern/include/FMod )
set( FMod ${ROOT}/extern/lib/FMod )


# !!! Provide each .cpp file manually !!!
# Build the executable
message( "Adding sources." )
add_executable( ${PROJECT_NAME}
                src/Core/Game.cpp src/Helpers/Exceptions.cpp
                src/Rendering/Texture.cpp src/Core/main.cpp src/Rendering/Sound.cpp src/Rendering/Sound.h )

# List of header files for the compiler (-I option for g++)
target_include_directories( ${PROJECT_NAME} PUBLIC ${ROOT}/src/Core ${ROOT}/src/Helpers ${ROOT}/src/Rendering )

# List of library links for the compiler (-l option for g++)
message( "Adding libraries." )
target_link_libraries( ${PROJECT_NAME}
	${SDL2}/libSDL2-2.0.so.0 ${SDL2_image}/libSDL2_image-2.0.so.0
	${SDL2_ttf}/libSDL2_ttf-2.0.so.0 ${SDL2_mixer}/libSDL2_mixer-2.0.so.0
	${FMod}/libfmod.so.10.11
)

# readlink allows to trace symbolic links
# ldd allows to show path to library used in a binary