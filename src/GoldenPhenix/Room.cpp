//
// Created by serdok on 05/03/19.
//

#include "Room.h"

Room::Room( const std::vector< std::string >& data )
{
    if (data.size() != 10)
        throw Exception( "A room failed to load!", __FILE__, __LINE__ );

    _id = (int) std::stoul( data[ 0 ] );
}

Room::~Room()
{
    for (auto& room : _joiningRooms)
        delete room;
}

void Room::AddRoom( Room::JoiningDirections direction, Room* room )
{
    _joiningRooms[ direction ] = room;
}

Room* Room::GetRoom( Room::JoiningDirections direction ) const
{
    return _joiningRooms[ direction ];
}