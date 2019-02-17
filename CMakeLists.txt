cmake_minimum_required( VERSION 3.10 )
project( Golden_Phoenix )
set( CMAKE_CXX_STANDARD 14 )


# Root path relative to bin
set( ROOT "${PROJECT_BINARY_DIR}/../.." )
IF (IS_DIRECTORY ${ROOT}/bin AND IS_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
	set( ROOT ${PROJECT_SOURCE_DIR} )
ENDIF (IS_DIRECTORY ${ROOT}/bin AND IS_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# List of directories in src
set( SRC_DIRS ${ROOT}/src/Core ${ROOT}/src/Helpers ${ROOT}/src/Rendering )

# Search path for FindXXX.cmake files
set( CMAKE_MODULE_PATH ${ROOT}/cmake ${CMAKE_MODULE_PATH} )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_<Debug> ${ROOT}/bin/debug )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_<Release> ${ROOT}/bin/release )


# Define preprocessor flags (#ifdef DEBUG)
IF (CMAKE_BUILD_TYPE STREQUAL Debug)
	message( "Set executable output directory for debug mode to ${ROOT}/bin/debug." )
	add_definitions( -DDEBUG )
	#set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ROOT}/bin/debug )
ELSEIF (CMAKE_BUILD_TYPE STREQUAL Release)
	message( "Set executable output directory for release mode to ${ROOT}/bin/release." )
	#set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ROOT}/bin/release )
ENDIF (CMAKE_BUILD_TYPE STREQUAL Debug)

# Add documentation if building in debug mode
IF (CMAKE_BUILD_TYPE STREQUAL Debug)
	message( "Building documentation ..." )
	find_package( Doxygen REQUIRED )
	set( DOXYFILE_IN "${ROOT}/doc/doxygen/Doxyfile.in" )
	set( DOXYFILE ${PROJECT_BINARY_DIR}/Doxyfile )
	IF (DOXYGEN_DOT_FOUND STREQUAL NO)
		message( "Dot executable not found, class diagram cannot be integrated within documentation." )
	ENDIF (DOXYGEN_DOT_FOUND STREQUAL NO)
	configure_file( ${DOXYFILE_IN} ${DOXYFILE} @ONLY )
	execute_process(
			COMMAND ${DOXYGEN_EXECUTABLE} "${DOXYFILE}"
			WORKING_DIRECTORY "${ROOT}/doc/doxygen"
	)
	message( "Done!" )
ENDIF (CMAKE_BUILD_TYPE STREQUAL Debug)

# Update diagrams if building in debug mode
IF (CMAKE_BUILD_TYPE STREQUAL Debug)
	message( "Refreshing diagrams ..." )
	execute_process(
			COMMAND java -jar script/plantuml.jar doc/Diagrams/Class.puml doc/Diagrams/Gantt.puml -o doc/Diagrams/
	        WORKING_DIRECTORY ${ROOT}
	)
	message( "Done!" )
ENDIF (CMAKE_BUILD_TYPE STREQUAL Debug)


# SDL2 package
message( "Included SDL2 files." )
include_directories( ${ROOT}/extern/SDL2/include )
add_library( libSDL SHARED IMPORTED )
set_target_properties( libSDL PROPERTIES IMPORTED_LOCATION ${ROOT}/extern/SDL2/lib/libSDL2-2.0.so.0 )

# SDL2_image package
message( "Included SDL2_image files." )
include_directories( ${ROOT}/extern/SDL2_image/include )
add_library( libSDL_image SHARED IMPORTED )
set_target_properties( libSDL_image PROPERTIES IMPORTED_LOCATION ${ROOT}/extern/SDL2_image/lib/libSDL2_image-2.0.so.0 )

# SDL2_ttf package
message( "Included SDL2_ttf files." )
include_directories( ${ROOT}/extern/SDL2_ttf/include )
add_library( libSDL_ttf SHARED IMPORTED )
set_target_properties( libSDL_ttf PROPERTIES IMPORTED_LOCATION ${ROOT}/extern/SDL2_ttf/lib/libSDL2_ttf-2.0.so.0 )

# SDL2_mixer package
message( "Included SDL2_mixer files." )
include_directories( ${ROOT}/extern/SDL2_mixer/include )
add_library( libSDL_mixer SHARED IMPORTED )
set_target_properties( libSDL_mixer PROPERTIES IMPORTED_LOCATION ${ROOT}/extern/SDL2_mixer/lib/libSDL2_mixer-2.0.so.0 )


# Header path for auto-completion and relative path
include_directories( ${SRC_DIRS} )


# !!! Provide each .cpp file manually !!!
# Build the executable
message( "Scanning sources ..." )
add_executable( ${PROJECT_NAME}
                src/Core/Game.cpp src/Helpers/Exceptions.cpp
                src/Rendering/Texture.cpp src/Helpers/GetResourcePath.cpp src/Core/main.cpp )
message( "Done!" )

# List of header files for the compiler (-I option for g++)
target_include_directories( ${PROJECT_NAME} PUBLIC ${ROOT}/src/Core ${ROOT}/src/Helpers ${ROOT}/src/Rendering )

# List of library links for the compiler (-l option for g++)
message( "Scanning libraries ..." )
target_link_libraries( ${PROJECT_NAME} libSDL libSDL_image libSDL_ttf libSDL_mixer )
message( "Done!" )
