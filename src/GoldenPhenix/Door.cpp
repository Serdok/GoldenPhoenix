//
// Created by serdok on 05/03/19.
//

#include "Door.h"

Door::Door( const std::vector< char >& info )
{
    _door = (DOORS) info[ 0 ];
    _openType = (OPEN_TYPES) info[ 1 ];
    _linksTo = info[ 2 ];
    if (info.size() == 4)
    {
        _hasTorch = true;
        _lit = (info[ 3 ] == 'T');
    }
    else
        _hasTorch = false;
}

Door::~Door()
{

}

int Door::getLink() const
{
    return _linksTo;
}