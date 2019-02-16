//
// Created by serdok on 26/01/19.
//

#ifndef GOLDEN_PHOENIX_GETRESOURCEPATH_H
#define GOLDEN_PHOENIX_GETRESOURCEPATH_H

// SDL2 headers
#include "SDL.h"

// C++ headers
#include <string>
#include <iostream>
using std::cerr;


//! Return the absolute path from the filename
std::string GetResourcePath( const std::string& filename );

#endif //GOLDEN_PHOENIX_GETRESOURCEPATH_H
