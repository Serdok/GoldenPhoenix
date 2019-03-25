//
// Created by serdok on 26/01/19.
//

#ifndef GOLDEN_PHOENIX_GETRESOURCEPATH_H
#define GOLDEN_PHOENIX_GETRESOURCEPATH_H

// Custom headers
#include "Exceptions.h"

// C++ headers
#include <cstring>
#include <libgen.h>
#include <string>
#include <unistd.h>


//! Return the absolute path from the filename. Format will be /ProjectSourceDir/data/
inline std::string GetResourcePath( const std::string& filename )
{
    const char SEP = '/';

    static std::string path;
    if (path.empty())
    {
#ifdef _WIN32 // Windows

#else // Unix, Mac
        char result[ 2048 ];
        ssize_t count = readlink( "/proc/self/exe", result, 2048 );
        if (count < 0)
            throw Exception( "Failed to get resource path : " + std::string( strerror( errno ) ), __FILE__, __LINE__ );

        path = std::string( dirname( result ) );
#endif // OS

        size_t pos = path.rfind( "bin" );
        path = path.substr( 0, pos ) + "data" + SEP;
    }

    return filename.empty() ? path : path + filename;
}

#endif //GOLDEN_PHOENIX_GETRESOURCEPATH_H
