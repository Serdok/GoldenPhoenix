//
// Created by serdok on 05/03/19.
//

#ifndef GOLDEN_PHOENIX_DOOR_H
#define GOLDEN_PHOENIX_DOOR_H

// Custom headers
// #include "Inventory.h"


// SDL2 headers


// FMod headers


// C++ headers
#include <vector>



//! Class holding all information about a door.
class Door
{
public:
    //! List of the possible doors
    enum DOORS : char
    {
        wall = 'M',
        opening = 'O',
        door = 'D',
        grid = 'G',
        chest = 'C',
        fireplace = 'F'
    };

    //! List of the possible actions on a door
    enum OPEN_TYPES : char
    {
        open = 'O',
        open_impossible = 'N',
        crowbar = 'B',
        iron_key = 'I',
        gold_key = 'G'
    };

private:
    DOORS _door;
    OPEN_TYPES _openType;
    bool _hasTorch;
    bool _lit;
    int _linksTo;

public:
    Door( const std::vector< char >& info );
    ~Door();

    int getLink() const;

private:

};


#endif //GOLDEN_PHOENIX_DOOR_H
