//
// Created by serdok on 26/01/19.
//

#ifndef GOLDEN_PHOENIX_GETRESOURCEPATH_H
#define GOLDEN_PHOENIX_GETRESOURCEPATH_H

// Custom headers
#include "Exceptions.h"

// C++ headers
#include <unistd.h>
#include <string>


//! Return the absolute path from the filename. Format will be /ProjectSourceDir/data/
inline std::string GetResourcePath( const std::string& filename )
{
    const char SEP = '/';

    static std::string path;
    if (path.empty())
    {
        char tmp[ 1024 ];
        if (getcwd( tmp, 1024 ) == nullptr)
            throw Exception( "Failed to get current working directory", __FILE__, __LINE__ );

        path = std::string( tmp );


        size_t pos = path.rfind( "bin" );
        path = path.substr( 0, pos ) + "data" + SEP;
    }

    return filename.empty() ? path : path + filename;
}

#endif //GOLDEN_PHOENIX_GETRESOURCEPATH_H
