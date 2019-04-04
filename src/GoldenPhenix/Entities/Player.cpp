//
// Created by serdok on 05/03/19.
//

#include "Player.h"

Player::Player( Room* currentRoom ) : Entity( 100, Vector2i( 3, ROOM_HEIGHT - 1 ), VEC2_DOWN ), _currentRoom( currentRoom )
{

}

Player::~Player()
{
    _currentRoom = nullptr;
    _items.clear();
}

void Player::AddItem( const Object& object )
{
    for (auto& obj : _items)
    {
        if (obj.GetObject().GetID() == object.GetID())
        {
            obj.Add( 1 );
            return;
        }
        if (obj.GetObject().GetID() == ObjectID::Nothing)
        {
            obj = ItemStack( object, 1 );
            return;
        }
    }

    _items.push_back( ItemStack( object, 1 ) );
}

void Player::RemoveItem( const Object& object )
{
    for (auto& obj : _items)
        if (obj.GetObject().GetID() == object.GetID())
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
#ifdef DEBUG

    std::cout << "Player is in Room id " << _currentRoom->GetRoomID() << std::endl;

    std::cout << std::endl;

    std::cout << "    0   1   2   3   4   5   6" << std::endl;
    std::cout << "    |   |   |   |   |   |   |" << std::endl;
    for (int y=0 ; y<ROOM_HEIGHT ; ++y)
    {
        std::cout << y << " - ";
        for (int x=0 ; x<ROOM_WIDTH ; ++x)
        {
            if (Vector2i( x, y ) != _position)
                std::cout << _currentRoom->GetSquare( Vector2i( x, y ) ) << "   ";
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
    if (action == "down") // Origin is at the top-left
    {
        // Look left
        if (GetDirection() == VEC2_UP)
        {
            _crouched = false;
            // If next case is out of bounds, do not move 
            if (_position.y + VEC2_UP.y > ROOM_HEIGHT - 1)
            {
                _position.y = ROOM_HEIGHT - 1;
                return;
            }

            // If next case is a wall, do not move
            if (_currentRoom->GetSquare( _position + VEC2_UP ) == -2)
                return;

            // Move left
            Translate( VEC2_UP );
        }
        else
        {
            SetDirection( VEC2_UP );
        }
    }

    if (action == "right")
    {
        // Look up
        if (GetDirection() == VEC2_RIGHT)
        {
            _crouched = false;
            // If next case is out of bounds, do not move
            if (_position.x + VEC2_RIGHT.x > ROOM_WIDTH - 1)
            {
                _position.x = ROOM_WIDTH - 1;
                return;
            }

            // If next case is a wall, return
            if (_currentRoom->GetSquare( _position + VEC2_RIGHT ) == -2)
                return;

            // Move up
            Translate( VEC2_RIGHT );
        }
        else
        {
            SetDirection( VEC2_RIGHT );
        }
    }

    if (action == "up") // Origin is at the top-left
    {
        // Look right
        if (GetDirection() == VEC2_DOWN)
        {
            _crouched = false;
            // If next case is out of bounds, do not move
            if (_position.y + VEC2_DOWN.y < 0)
            {
                _position.y = 0;
                return;
            }

            // If next case is a wall, return
            if (_currentRoom->GetSquare( _position + VEC2_DOWN ) == -2)
                return;

            // Move right
            Translate( VEC2_DOWN );
        }
        else
        {
            SetDirection( VEC2_DOWN );
        }
    }

    if (action == "left")
    {
        // Look down
        if (GetDirection() == VEC2_LEFT)
        {
            _crouched = false;
            // If next case is out of bounds, do not move
            if (_position.x + VEC2_LEFT.x < 0)
            {
                _position.x = 0;
                return;
            }

            // If next case is a wall, return
            if (_currentRoom->GetSquare( _position + VEC2_LEFT ) == -2)
                return;

            // Move down
            Translate( VEC2_LEFT );
        }
        else
        {
            SetDirection( VEC2_LEFT );
        }
    }


    if (action == "duck") _crouched = !_crouched;
    if (action == "jump") _grounded = !_grounded;
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

void Player::EmptyInventory()
{
    _items.clear();
    _heldItem = 0;
}

const std::vector< ItemStack >& Player::GetItems() const
{
    return _items;
}

void Player::Kill()
{
    if (_life <= 0)
    {
        std::cout << "Player died!" << std::endl;
        ++_deaths;
        EmptyInventory();
        _life = 100;
        _money = 400;
    }
}

unsigned int Player::GetDeaths() const
{
    return _deaths;
}