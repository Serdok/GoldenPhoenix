//
// Created by serdok on 05/03/19.
//

#include "Player.h"

Player::Player( Room* currentRoom )
: Entity(), _currentRoom( currentRoom )
{
    for (int i=0 ; i<4 ; ++i)
        _items.emplace_back( Object::NOTHING, 0 );
}

void Player::AddItem( const Object& object )
{
    Object::ID id = object.id;
    for (auto& obj : _items)
        if (obj.GetObject().id == id)
        {
            obj.Add( 1 );
            return;
        }
        else if (obj.GetObject().id == Object::ID::Nothing)
        {
            obj = { object, 1 };
            return;
        }
}

ItemStack& Player::GetHeldItems()
{
    return _items.at( (unsigned long) _heldItem );
}

void Player::Update()
{
    if (_position.x < 0)
        _position.x = 0;
    if (_position.y < 0)
        _position.y = 0;
    if (_position.x > 6)
        _position.x = 6;
    if (_position.y > 5)
        _position.y = 5;

}

void Player::Jump()
{
    if (_grounded)
    {
        _grounded = false;
        _position += VEC2_UP;
    }
    else
    {
        _grounded = true;
        _position += VEC2_DOWN;
    }
}

void Player::LongJump()
{
    _position += 2*_direction;
}

bool Player::Crouched() const
{
    return _crouched;
}

bool Player::Grounded() const
{
    return _grounded;
}

Room* Player::GetCurrentRoom() const
{
    return _currentRoom;
}