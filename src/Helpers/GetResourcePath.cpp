//
// Created by serdok on 26/01/19.
//

#include "GetResourcePath.hpp"


std::string GetResourcePath( const std::string& filename )
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