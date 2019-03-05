//
// Created by serdok on 05/03/19.
//

#include "Room.h"

Room::Room( const std::vector< char >& info )
{

}

Room::~Room()
{
    delete _leftDoor;
    delete _upperDoor;
    delete _rightDoor;
}

void Room::LoadRoom()
{

}

void Room::SaveRoom()
{

}

void Room::Update()
{

}

void Room::Render()
{

}

// void Room::AttachPlayer( Player* player )
// {
//     _player = player;
// }
