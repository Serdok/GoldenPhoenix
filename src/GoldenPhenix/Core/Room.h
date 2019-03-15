//
// Created by serdok on 05/03/19.
//

#ifndef GOLDEN_PHOENIX_ROOM_H
#define GOLDEN_PHOENIX_ROOM_H

// Custom headers
#include "Door.h"
#include "Exceptions.h"
#include "Object.h"
#include "Vector2.h"


// SDL2 headers


// C++ headers
#include <array>
#include <iostream>
#include <queue>


// Constants
const int ROOM_WIDTH = 7;
const int ROOM_HEIGHT = 6;


//! Class holding all information about a room in the castle
class Room
{
public:
    enum JoiningDirections
    {
        West = 0, North, East,

        TOTAL
    };

private:
    unsigned int _id;
    bool _isCorridor;

    int _ground[ ROOM_HEIGHT ][ ROOM_WIDTH ];

    std::array< unsigned int, Room::TOTAL > _joiningRooms;
    std::array< Door*, Room::TOTAL > _joiningDoors;


public:
    Room( std::queue< std::string >& data );
    ~Room();

    unsigned int GetRoomID( JoiningDirections direction ) const;

    int GetSquare( const Vector2i& position ) const;
    int& GetSquare( const Vector2i& position );

private:

};


#endif //GOLDEN_PHOENIX_ROOM_H
