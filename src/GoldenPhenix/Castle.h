//
// Created by serdok on 05/03/19.
//

#ifndef GOLDEN_PHOENIX_CASTLE_H
#define GOLDEN_PHOENIX_CASTLE_H

// Custom headers
#include "Exceptions.h"
#include "Room.h"


// C++ headers
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


//! Game manager.
class Castle
{
private:
    Room* _rooms;

public:
    Castle( const std::string& filename );
    ~Castle();


private:

};


#endif //GOLDEN_PHOENIX_CASTLE_H
