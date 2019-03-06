//
// Created by serdok on 05/03/19.
//

#ifndef GOLDEN_PHOENIX_ROOM_H
#define GOLDEN_PHOENIX_ROOM_H

// Custom headers
#include "Door.h"
#include "Exceptions.h"


// SDL2 headers


// FMod headers


// C++ headers
#include <array>
#include <iostream>


// Constants
const int ROOM_WIDTH = 7;
const int ROOM_HEIGHT = 6;


//! Class holding all information about a room in the castle
class Room
{
public:
    enum JoiningDirections
    {
        North = 0, East, South, West,

        TOTAL
    };

private:
    Room* _currentRoom;
    std::array< Room*, Room::TOTAL > _joiningRooms;

    unsigned int _id;


public:
    Room( const std::vector< std::string >& data );
    ~Room();

    void AddRoom( JoiningDirections direction, Room* room );

    Room* GetRoom( JoiningDirections direction ) const;

private:

};


#endif //GOLDEN_PHOENIX_ROOM_H
