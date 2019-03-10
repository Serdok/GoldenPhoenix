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


//! Return the absolute path from the filename. Format will be /ProjectSourceDir/data/
inline std::string GetResourcePath( const std::string& filename )
{
    const char SEP = '/';

    static std::string path;
    if (path.empty())
    {
        char* base = SDL_GetBasePath();
        if (base)
        {
            path = base;
            SDL_free( base );
        }
        else
        {
            std::cerr << "Error getting " + filename + " path : " << SDL_GetError() << '\n';
            return std::string();
        }

        size_t pos = path.rfind( "bin" );
        path = path.substr( 0, pos ) + "data" + SEP;
    }

    return filename.empty() ? path : path + filename;
}

#endif //GOLDEN_PHOENIX_GETRESOURCEPATH_H
