cmake_minimum_required( VERSION 3.10 )
project( Golden_Phoenix VERSION 0.1 DESCRIPTION "Jeu L'Aigle d'Or" )
set( CMAKE_CXX_STANDARD 14 )


# Root path relative to bin
set( ROOT "${PROJECT_BINARY_DIR}/../.." )
IF (IS_DIRECTORY ${ROOT}/bin AND IS_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
	set( ROOT ${PROJECT_SOURCE_DIR} ) # Make path easier to read
ENDIF (IS_DIRECTORY ${ROOT}/bin AND IS_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# List of directories in src
set( SRC_DIRS ${ROOT}/src ${ROOT}/src/Core ${ROOT}/src/Helpers ${ROOT}/src/Rendering ${ROOT}/src/GoldenPhenix )

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

# Add documentation
find_package( Doxygen REQUIRED )
IF (DOXYGEN_FOUND STREQUAL NO)
	message( FATAL "Doxygen executable not found, documentation cannot be built. To install, type 'sudo apt install doxygen' in a terminal" )
ENDIF (DOXYGEN_FOUND STREQUAL NO)
IF (DOXYGEN_DOT_FOUND STREQUAL NO)
	message( FATAL "Dot executable not found, class diagram cannot be built. To install, type 'sudo apt install graphviz' in a terminal" )
ENDIF (DOXYGEN_DOT_FOUND STREQUAL NO)
set( DOXYGEN_QUIET YES )
set( DOXYGEN_EXTRACT_ALL YES )
set( DOXYGEN_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/doc/doxygen )
set( DOXYGEN_IMAGE_PATH ${PROJECT_SOURCE_DIR}/data/images )
set( DOXYGEN_PROJECT_LOGO ${PROJECT_SOURCE_DIR}/doc/doxygen/DoxygenProjectLogo.png )
set( DOXYGEN_USE_MDFILE_AS_MAINPAGE ${PROJECT_SOURCE_DIR}/Readme.md )
set( DOXYGEN_WARN_LOGFILE ${PROJECT_SOURCE_DIR}/doc/doxygen/warnings.log )
doxygen_add_docs(
		${PROJECT_NAME}_Documentation
		${SRC_DIRS} ${PROJECT_SOURCE_DIR}/Readme.md
		ALL
		COMMENT "Generating documentation for ${PROJECT_NAME} ..."
)

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
# message( "Adding SDL2_mixer files." )
# include_directories( ${ROOT}/extern/include/SDL2_mixer )
# set( SDL2_mixer ${ROOT}/extern/lib/SDL2_mixer )

message( "Adding FMod files." )
include_directories( ${ROOT}/extern/include/FMod )
set( FMod ${ROOT}/extern/lib/FMod )


# !!! Provide each .cpp file manually !!!
# Build the executable
message( "Adding sources." )
add_executable( ${PROJECT_NAME}
                src/Core/Game.cpp src/Helpers/Exceptions.cpp
                src/Rendering/Texture.cpp src/Core/main.cpp src/Core/AudioManager.cpp src/Core/Timer.cpp
                src/GoldenPhenix/Room.cpp src/GoldenPhenix/Door.cpp src/GoldenPhenix/Castle.cpp src/GoldenPhenix/StartScreen.cpp )

# List of header files for the compiler (-I option for g++)
target_include_directories( ${PROJECT_NAME} PUBLIC ${ROOT}/src/Core ${ROOT}/src/Helpers ${ROOT}/src/Rendering ${ROOT}/src/GoldenPhenix )

# List of library links for the compiler (-l option for g++)
message( "Adding libraries." )
target_link_libraries( ${PROJECT_NAME}
	${SDL2}/libSDL2-2.0.so.0 ${SDL2_image}/libSDL2_image-2.0.so.0
	${SDL2_ttf}/libSDL2_ttf-2.0.so.0 # ${SDL2_mixer}/libSDL2_mixer-2.0.so.0
	${FMod}/libfmod.so.10.11 ${FMod}/libfmodL.so.10.11
)

# Build documentation when building the game
add_dependencies( ${PROJECT_NAME} ${PROJECT_NAME}_Documentation )

# readlink allows to trace symbolic links
# ldd allows to show path to library used in a binary