//
// Created by serdok on 26/01/19.
//

#ifndef GOLDEN_PHOENIX_GETRESOURCEPATH_H
#define GOLDEN_PHOENIX_GETRESOURCEPATH_H

// Custom headers
#include "Exceptions.h"

// C++ headers
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;


//! Return the absolute path from the filename. Format will be /ProjectSourceDir/data/
inline std::string GetResourcePath( const std::string& filename )
{
    static std::string path;
    if (path.empty())
    {
        path = fs::current_path();
        size_t pos = path.rfind( "bin" );
        path = path.substr( 0, pos ) + "data/";
    }

    return filename.empty() ? path : path + filename;
}

#endif //GOLDEN_PHOENIX_GETRESOURCEPATH_H
