
cmake_minimum_required( VERSION 3.10 )
project( Golden_Phoenix VERSION 3.0 DESCRIPTION "Jeu L'Aigle d'Or" )
set( CMAKE_CXX_STANDARD 14 )


# Root path relative to bin
set( ROOT "${PROJECT_BINARY_DIR}/../.." )
IF (IS_DIRECTORY ${ROOT}/bin AND IS_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
	set( ROOT ${PROJECT_SOURCE_DIR} ) # Make path easier to read
ENDIF (IS_DIRECTORY ${ROOT}/bin AND IS_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# List of directories in src
set( SRC_DIRS
     ${ROOT}/src
     ${ROOT}/src/SDL2 ${ROOT}/src/SDL2/Core ${ROOT}/src/SDL2/Helpers ${ROOT}/src/SDL2/Entities
     ${ROOT}/src/GoldenPhenix ${ROOT}/src/GoldenPhenix/Core ${ROOT}/src/GoldenPhenix/Helpers ${ROOT}/src/GoldenPhenix/Entities
     )

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
message( "Locating SDL2 files." )
include_directories( ${ROOT}/extern/include/SDL2 )
set( SDL2 ${ROOT}/extern/lib/SDL2 )

# SDL2_image library
message( "Locating SDL2_image files." )
include_directories( ${ROOT}/extern/include/SDL2_image )
set( SDL2_image ${ROOT}/extern/lib/SDL2_image )

# SDL2_ttf library
message( "Locating SDL2_ttf files." )
include_directories( ${ROOT}/extern/include/SDL2_ttf )
set( SDL2_ttf ${ROOT}/extern/lib/SDL2_ttf )

message( "Locating FMod files." )
include_directories( ${ROOT}/extern/include/FMod )
set( FMod ${ROOT}/extern/lib/FMod )


# !!! Provide each .cpp file manually !!!
# Build the executable
message( "Locating sources for no graphics mode." )
add_executable( ${PROJECT_NAME}
                src/GoldenPhenix/Core/Castle.cpp src/GoldenPhenix/Core/Door.cpp src/GoldenPhenix/Core/Room.cpp
                src/GoldenPhenix/Entities/Bat.cpp src/GoldenPhenix/Entities/Entity.cpp src/GoldenPhenix/Entities/ItemStack.cpp src/GoldenPhenix/Entities/Object.cpp src/GoldenPhenix/Entities/Player.cpp
                src/GoldenPhenix/Helpers/Exceptions.cpp

                src/GoldenPhenix/main.cpp
                )

message( "Locating sources for SDL2 mode." )
add_executable( ${PROJECT_NAME}_SDL2
                src/GoldenPhenix/Core/Castle.cpp src/GoldenPhenix/Core/Door.cpp src/GoldenPhenix/Core/Room.cpp
                src/GoldenPhenix/Entities/Bat.cpp src/GoldenPhenix/Entities/Entity.cpp src/GoldenPhenix/Entities/ItemStack.cpp src/GoldenPhenix/Entities/Object.cpp src/GoldenPhenix/Entities/Player.cpp
                src/GoldenPhenix/Helpers/Exceptions.cpp

                src/SDL2/Core/AudioManager.cpp src/SDL2/Core/GameManager.cpp src/SDL2/Core/Graphics.cpp src/SDL2/Core/Timer.cpp
                src/SDL2/Entities/GameEntity.cpp src/SDL2/Entities/Texture.cpp src/SDL2/Entities/AnimatedTexture.cpp src/SDL2/Entities/StartScreen.cpp
                src/SDL2/main.cpp
                )

# List of header files for the compiler (-I option for g++)
target_include_directories( ${PROJECT_NAME} PUBLIC
                            ${ROOT}/src/GoldenPhenix ${ROOT}/src/GoldenPhenix/Core ${ROOT}/src/GoldenPhenix/Entities ${ROOT}/src/GoldenPhenix/Helpers
                            )

target_include_directories( ${PROJECT_NAME}_SDL2 PUBLIC
                            ${ROOT}/src/GoldenPhenix ${ROOT}/src/GoldenPhenix/Core ${ROOT}/src/GoldenPhenix/Entities ${ROOT}/src/GoldenPhenix/Helpers
                            ${ROOT}/src/SDL2 ${ROOT}/src/SDL2/Core ${ROOT}/src/SDL2/Entities ${ROOT}/src/SDL2/Helpers
                            )

# List of library links for the compiler (-l option for g++)
message( "Locating libraries for SDL2 mode." )
target_link_libraries( ${PROJECT_NAME}_SDL2
                       ${SDL2}/libSDL2-2.0.so.0 ${SDL2_image}/libSDL2_image-2.0.so.0
                       ${SDL2_ttf}/libSDL2_ttf-2.0.so.0
                       ${FMod}/libfmod.so.10.11 ${FMod}/libfmodL.so.10.11
                       )

# Build documentation when building the game
add_dependencies( ${PROJECT_NAME} ${PROJECT_NAME}_Documentation )
add_dependencies( ${PROJECT_NAME}_SDL2 ${PROJECT_NAME} )


# readlink allows to trace symbolic links
# ldd allows to show path to libraries used in a binary