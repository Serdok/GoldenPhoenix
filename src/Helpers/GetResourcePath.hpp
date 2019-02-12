//
// Created by serdok on 26/01/19.
//

#ifndef GAME_GETRESOURCEPATH_HPP
#define GAME_GETRESOURCEPATH_HPP

// SDL2 headers
#include "SDL.h"

// C++ headers
#include <string>
#include <iostream>
using std::cerr;


//! Return the absolute path from the filename
std::string GetResourcePath( const std::string& filename );

#endif //GAME_GETRESOURCEPATH_HPP
