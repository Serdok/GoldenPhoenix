//
// Created by serdok on 05/03/19.
//

#include "Castle.h"

Castle::Castle( const std::string& filename )
{
    std::ifstream file( filename.c_str() );
    if (!file.good())
        throw Exception( "Failed to open " + filename + '!', __FILE__, __LINE__ );

    std::string contents;
    std::ostringstream oss;
    oss << file.rdbuf();
    contents = oss.str();

    file.seekg( 0, std::ios_base::beg );
    std::string line;
    std::getline( file, line );
    std::cout << line << std::endl;
}

Castle::~Castle()
{

}