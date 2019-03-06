//
// Created by serdok on 05/03/19.
//

#include "Castle.h"

Castle::Castle( const std::string& filename )
{
    std::ifstream file( filename.c_str() );
    if (!file.good())
        throw Exception( "Failed to open " + filename + '!', __FILE__, __LINE__ );

    for (int room = 0 ; room < NUM_ROOMS ; ++room)
    {
        int line = 1;
        std::vector< std::string > content;
        std::string data;
        while (line < 11 && std::getline( file, data ))
        {
            if (data.empty()) // Skip empty lines
                continue;

            content.emplace_back( data );
            ++line;
        }
        _rooms[ room ] = new Room( content );
        content.clear();
    }

    file.close();
}

Castle::~Castle()
{
    for (auto& room : _rooms)
        delete room;
}