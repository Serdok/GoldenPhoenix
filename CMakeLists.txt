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
		message( WARNING "Dot executable not found, class diagram cannot be integrated within documentation." )
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
			COMMAND java -jar script/plantuml.jar doc/diagrams/Class.puml doc/diagrams/Gantt.puml -o doc/diagrams/
	        WORKING_DIRECTORY ${ROOT}
	)
ENDIF (CMAKE_BUILD_TYPE STREQUAL Debug)


# SDL2 library
message( "Adding SDL2 files." )
include_directories( ${ROOT}/extern/SDL2/include )
#add_library( libSDL SHARED IMPORTED )
#set_target_properties( libSDL PROPERTIES IMPORTED_LOCATION ${ROOT}/extern/SDL2/lib/libSDL2-2.0.so.0.9.0 )
find_library( libSDL NAMES libSDL2-2.0.so.0.9.0 HINTS ${ROOT}/extern/SDL2/lib )

# SDL2_image library
message( "Adding SDL2_image files." )
include_directories( ${ROOT}/extern/SDL2_image/include )
#add_library( libSDL_image SHARED IMPORTED )
#set_target_properties( libSDL_image PROPERTIES IMPORTED_LOCATION ${ROOT}/extern/SDL2_image/lib/libSDL2_image-2.0.so.0.2.2 )
find_library( libSDL_image NAMES libSDL2_image-2.0.so.0.2.2 HINTS ${ROOT}/extern/SDL2_image/lib )

# SDL2_ttf library
message( "Adding SDL2_ttf files." )
include_directories( ${ROOT}/extern/SDL2_ttf/include )
#add_library( libSDL_ttf SHARED IMPORTED )
#set_target_properties( libSDL_ttf PROPERTIES IMPORTED_LOCATION ${ROOT}/extern/SDL2_ttf/lib/libSDL2_ttf-2.0.so.0.14.1 )
find_library( libSDL_ttf NAMES libSDL2_ttf-2.0.so.0.14.1 HINTS ${ROOT}/extern/SDL2_ttf/lib )

# SDL2_mixer library
message( "Adding SDL2_mixer files." )
include_directories( ${ROOT}/extern/SDL2_mixer/include )
#add_library( libSDL_mixer SHARED IMPORTED )
#set_target_properties( libSDL_mixer PROPERTIES IMPORTED_LOCATION ${ROOT}/extern/SDL2_mixer/lib/libSDL2_mixer-2.0.so.0.2.2 )
find_library( libSDL_mixer NAMES libSDL2_mixer-2.0.so.0.2.2 HINTS ${ROOT}/extern/SDL2_mixer/lib )


# Header path for auto-completion and relative path (IDE)
include_directories( ${SRC_DIRS} )


# !!! Provide each .cpp file manually !!!
# Build the executable
message( "Adding sources." )
add_executable( ${PROJECT_NAME}
                src/Core/Game.cpp src/Helpers/Exceptions.cpp
                src/Rendering/Texture.cpp src/Helpers/GetResourcePath.cpp src/Core/main.cpp )

# List of header files for the compiler (-I option for g++)
target_include_directories( ${PROJECT_NAME} PUBLIC ${ROOT}/src/Core ${ROOT}/src/Helpers ${ROOT}/src/Rendering )

# List of library links for the compiler (-l option for g++)
message( "Adding libraries." )
target_link_libraries( ${PROJECT_NAME} ${libSDL} ${libSDL_image} ${libSDL_ttf} ${libSDL_mixer} )
