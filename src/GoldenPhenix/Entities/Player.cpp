//
// Created by serdok on 05/03/19.
//

#include "Player.h"

Player::Player( Room* currentRoom )
: Entity( 100, Vector2i( 4, 3 ), VEC2_RIGHT ), _currentRoom( currentRoom )
{
    for (int i = 0 ; i < 99 ; ++i)
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
    if (_items.size() > _heldItem)
        return _items.at( _heldItem );
    else
        return _items.at( 0 );
}

void Player::Update()
{
#ifdef DEBUG

    std::cout << "Player is in Room id " << _currentRoom->GetRoomID() << std::endl;

    std::cout << std::endl;
    std::cout << "    0   1   2   3   4   5   6" << std::endl;
    std::cout << "    |   |   |   |   |   |   |" << std::endl;
    for (int row = 0 ; row < ROOM_HEIGHT ; ++row)
    {
        std::cout << row << " - ";
        for (int col = 0 ; col < ROOM_WIDTH ; ++col)
        {
            if (Vector2i( row, col ) != _position)
                std::cout << _currentRoom->ToString( Vector2i( row, col ) ) << "   ";
            else
                std::cout << "P" << "   ";
        }
        std::cout << std::endl;
    }


    std::cout << std::endl;

    std::cout << "Player is at " << _position << std::endl;
    std::cout << "Player has " << _life << " life remaining" << std::endl;
    std::cout << "Player has " << _money << " money remaining" << std::endl;
    std::cout << "Player is " << ( _crouched ? "" : "not" ) << " crouched" << std::endl;
    std::cout << "Player is " << ( _grounded ? "not" : "" ) << " jumping" << std::endl;

    std::cout << std::endl << std::endl;

#endif // DEBUG
}

bool Player::Crouched() const
{
    return _crouched;
}

bool Player::Grounded() const
{
    return _grounded;
}

Room* const Player::GetCurrentRoom()
{
    return _currentRoom;
}

const Room* const Player::GetCurrentRoom() const
{
    return _currentRoom;
}

void Player::SetCurrentRoom( Room* room )
{
    _currentRoom = room;
}

void Player::ProcessActions( const std::string& action )
{
    if (action == "up")
    {
        // Look left
        SetDirection( VEC2_LEFT );

        // If next case is out of bounds, do not move
        if (_position.x + VEC2_LEFT.x < 0)
        {
            _position.x = 0;
            return;
        }

        // If next case is a wall, do not move
        if (_currentRoom->GetSquare( _position + VEC2_LEFT ) == -2)
            return;

        // Move left
        Translate( VEC2_LEFT );
    }

    if (action == "right")
    {
        // Look up
        SetDirection( VEC2_UP );

        // If next case is out of bounds, do not move
        if (_position.y + VEC2_UP.y > ROOM_WIDTH - 1)
        {
            _position.y = ROOM_WIDTH - 1;
            return;
        }

        // If next case is a wall, return
        if (_currentRoom->GetSquare( _position + VEC2_UP ) == -2)
            return;

        // Move up
        Translate( VEC2_UP );
    }

    if (action == "down")
    {
        // Look right
        SetDirection( VEC2_RIGHT );

        // If next case is out of bounds, do not move
        if (_position.x + VEC2_RIGHT.x > ROOM_HEIGHT - 1)
        {
            _position.x = ROOM_HEIGHT - 1;
            return;
        }

        // If next case is a wall, return
        if (_currentRoom->GetSquare( _position + VEC2_RIGHT ) == -2)
            return;

        // Move right
        Translate( VEC2_RIGHT );
    }

    if (action == "left")
    {
        // Look down
        SetDirection( VEC2_DOWN );

        // If next case is out of bounds, do not move
        if (_position.y + VEC2_DOWN.y < 0)
        {
            _position.y = 0;
            return;
        }

        // If next case is a wall, return
        if (_currentRoom->GetSquare( _position + VEC2_DOWN ) == -2)
            return;

        // Move down
        Translate( VEC2_DOWN );
    }

    if (action == "duck") _crouched = !_crouched;
    if (action == "jump") _grounded = !_grounded;


    if (action == "inv 0") _heldItem = 0;
    if (action == "inv 1") _heldItem = 1;
    if (action == "inv 2") _heldItem = 2;
    if (action == "inv 3") _heldItem = 3;
    if (action == "inv 4") _heldItem = 4;
    if (action == "inv 5") _heldItem = 5;
    if (action == "inv 6") _heldItem = 6;
    if (action == "inv 7") _heldItem = 7;
    if (action == "inv 8") _heldItem = 8;
    if (action == "inv 9") _heldItem = 9;
}

int Player::GetMoney()
{
    return _money;
}

void Player::AddMoney( int m )
{
    _money += m;
}

void Player::SetMoney( int m )
{
    _money = m;
}

void Player::clearItems()
{
    _items.clear();
    _items.emplace_back( ItemStack( Object::NOTHING, 1 ) );
    _heldItem = 0;
}