//
// Created by serdok on 05/03/19.
//

#include "Door.h"

Door::Door( DOORS door, OPEN_TYPES type, bool hasTorch, bool torchLit )
: _door( door ), _requires( type ), _hasTorch( hasTorch ), _torchLit( torchLit )
{

}

Door::DOORS Door::GetDoorType() const
{
    return _door;
}

Door::OPEN_TYPES Door::GetOpenType() const
{
    return _requires;
}

bool Door::GetTorchState() const
{
    return _hasTorch && _torchLit;
}

bool Door::HasTorch() const
{
    return _hasTorch;
}

void Door::AddObject( int objectID )
{
    _objectID = objectID;
}

int Door::GetObject() const
{
    return _objectID;
}

void Door::SetDoorType( Door::DOORS door )
{
    _door = door;
}

void Door::SetOpenType( Door::OPEN_TYPES requirement )
{
    _requires = requirement;
}

void Door::RemoveObject()
{
    _objectID = 0;
}

void Door::SetTorchState()
{
	_torchLit = true;
}

std::string Door::Save() const
{
    std::string data;
    data.append( "    " );

    switch (GetDoorType())
    {
        case DOORS::wall:
            data.append( "M" );
            break;
        case DOORS::opening:
            data.append( "O" );
            break;
        case DOORS::door:
            data.append( "P" );
            break;
        case DOORS::grid:
            data.append( "G" );
            break;
        case DOORS::chest:
            data.append( "C" );
            break;
        case DOORS::chimney:
            data.append( "D" );
            break;
        default:
            break;
    }

    if (GetDoorType() == DOORS::wall)
        return data;

    switch (GetOpenType())
    {
        case OPEN_TYPES::open:
            data.append( " O" );
            break;
        case OPEN_TYPES::open_impossible:
            data.append( " N" );
            break;
        case OPEN_TYPES::crowbar:
            data.append( " B" );
            break;
        case OPEN_TYPES::iron_key:
            data.append( " I" );
            break;
        case OPEN_TYPES::gold_key:
            data.append( " G" );
            break;
    }

    if (GetDoorType() == DOORS::chest)
        switch (GetObject())
        {
            case ObjectID::LifePotion:
                data.append( " L" );
                break;
            case ObjectID::Hint2:
                data.append( " Y" );
                break;
            case -1:
                data.append( " W" );
                break;
        }

    if (GetTorchState())
        data.append( " T" );
    else if (HasTorch())
        data.append( " F" );

    return data;
}