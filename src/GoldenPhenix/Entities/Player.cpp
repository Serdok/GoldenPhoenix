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

void Player::setCurrentRoom(Room * room){
    _currentRoom=room;
}

void Player::ProcessActions( const std::string& action )
{
    if (action == "up")
    {
        SetDirection( VEC2_UP );
        Translate( VEC2_UP );
    }

    if (action == "right")
    {
        SetDirection( VEC2_RIGHT );
        Translate( VEC2_RIGHT );
    }

    if (action == "down")
    {
        SetDirection( VEC2_DOWN );
        Translate( VEC2_DOWN );
    }

    if (action == "left")
    {
        SetDirection( VEC2_LEFT );
        Translate( VEC2_LEFT );
    }

    if (action == "duck")   _crouched = !_crouched;

    if (action == "inv 1")  _heldItem = 0;
    if (action == "inv 2")  _heldItem = 1;
    if (action == "inv 3")  _heldItem = 2;
    if (action == "inv 4")  _heldItem = 3;
}

int Player::getMoney()
{
    return _money;
}

void AddMoney(int m){
    _money += m;
}

void Player::setMoney( int m )
{
    _money = m;
}

void Player::clearItems(){
    _items.clear();
}