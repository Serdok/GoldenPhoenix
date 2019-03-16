//
// Created by serdok on 05/03/19.
//

#include "Player.h"

Player::Player( Room* currentRoom )
: Entity(), _currentRoom( currentRoom ), _grounded( true ), _crouched( false )
{
    for (int i=0 ; i<4 ; ++i)
        _items.emplace_back( Object::NOTHING, 0 );
}

Player::~Player()
{
    _currentRoom = nullptr;
}

void Player::AddItem( const Object& object )
{
    for (auto& obj : _items)
        if (obj.GetObject().id == object.id)
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

void Player::RemoveItem( const Object& object )
{
    for (auto& obj : _items)
        if (obj.GetObject().id == object.id)
        {
            obj.Remove( 1 );
            return;
        }
}

const ItemStack& Player::GetHeldItem() const
{
    return _items.at( _heldItem );
}

ItemStack& Player::GetHeldItem()
{
    return _items.at( _heldItem );
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

void Player::ProcessInputs( const char key )
{
    switch (key)
    {
        case 'z':
            SetDirection( VEC2_UP );
            Translate( VEC2_UP );
            break;
        case 'd':
            SetDirection( VEC2_RIGHT );
            Translate( VEC2_RIGHT );
            break;
        case 's':
            SetDirection( VEC2_DOWN );
            Translate( VEC2_DOWN );
            break;
        case 'q':
            SetDirection( VEC2_LEFT );
            Translate( VEC2_LEFT );
            break;
        case '1':
            _heldItem = 0;
            break;
        case '2':
            _heldItem = 1;
            break;
        case '3':
            _heldItem = 2;
            break;
        case '4':
            _heldItem = 3;
            break;
        default:
            break;
    }
}