//
// Created by serdok on 05/03/19.
//

#include "Door.h"

Door::Door( DOORS door, OPEN_TYPES type, bool hasTorch, bool torchLit )
: _door( door ), _requires( type ), _hasTorch( hasTorch ), _torchLit( torchLit )
{

}

Door::~Door() = default;

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