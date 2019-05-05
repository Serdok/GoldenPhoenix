//
// Created by serdok on 05/03/19.
//

#include "Player.h"

Player::~Player()
{
    _currentRoom = nullptr;
    _items.clear();
}

void Player::AddItem( const Object& object )
{
    if (_items.empty())
        _items.emplace_back( ItemStack( Object::ToObject( ObjectID::Nothing ), 0 ) );

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

            if (_items.back() != ItemStack( Object::ToObject( ObjectID::Nothing ), 0 ))
                _items.emplace_back( ItemStack( Object::ToObject( ObjectID::Nothing ), 0 ) );

            return;
        }
    }
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

    // std::cout << "Player is in Room id " << _currentRoom->GetRoomID() << std::endl;
    //
    // std::cout << std::endl;
    //
    // std::cout << "    0   1   2   3   4   5   6" << std::endl;
    // std::cout << "    |   |   |   |   |   |   |" << std::endl;
    // for (int y=0 ; y<ROOM_HEIGHT ; ++y)
    // {
    //     std::cout << y << " - ";
    //     for (int x=0 ; x<ROOM_WIDTH ; ++x)
    //     {
    //         if (Vector2i( x, y ) != _position)
    //             std::cout << _currentRoom->GetSquare( Vector2i( x, y ) ) << "   ";
    //         else
    //             std::cout << "P" << "   ";
    //     }
    //     std::cout << std::endl;
    // }
    //
    //
    // std::cout << std::endl;
    //
    // std::cout << "Player is at " << _position << std::endl;
    // std::cout << "Player has " << _life << " life remaining" << std::endl;
    // std::cout << "Player has " << _money << " money remaining" << std::endl;
    // std::cout << "Player is " << ( _crouched ? "" : "not" ) << " crouched" << std::endl;
    // std::cout << "Player is " << ( _grounded ? "not" : "" ) << " jumping" << std::endl;
    //
    // std::cout << std::endl << std::endl;

#endif // DEBUG

    ActivateTorch();
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
        // Look up
        if (GetDirection() == VEC2_UP)
        {
            _crouched = false;
            // If next case is out of bounds, do not move 
            if (_position.y + VEC2_UP.y > ROOM_HEIGHT - 1)
            {
                // _position.y = ROOM_HEIGHT - 1;
                return;
            }

            // If next case is a wall, do not move
            if (_currentRoom->GetSquare( _position + VEC2_UP ) >= -2 && _currentRoom->GetSquare(  _position + VEC2_UP ) != 0)
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
        // Look right
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
            if (_currentRoom->GetSquare( _position + VEC2_RIGHT ) >= -2 && _currentRoom->GetSquare(  _position + VEC2_RIGHT ) != 0)
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
        // Look down
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
            if (_currentRoom->GetSquare( _position + VEC2_DOWN ) >= -2 && _currentRoom->GetSquare(  _position + VEC2_DOWN ) != 0)
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
        // Look left
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
            if (_currentRoom->GetSquare( _position + VEC2_LEFT ) >= -2 && _currentRoom->GetSquare(  _position + VEC2_LEFT ) != 0 )
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
    if (action == "jump") _grounded = false;

    if (action == "long jump")
    {
        _crouched = false;
        _grounded = false;

        //Est ce que le joueur est au bord de la salle
        if (_position.x + _direction.x < 0)
            return;

        if (_position.x + _direction.x > ROOM_WIDTH - 1)
            return;

        if (_position.y + _direction.y < 0)
            return;

        if (_position.y + _direction.y > ROOM_HEIGHT - 1)
            return;

        //Est ce que le joueur est devant un objet
        if(!(_currentRoom->GetSquare( _position + _direction + _direction ) >= -2 && _currentRoom->GetSquare( _position + _direction + _direction ) != 0 ))
        {   
            //Le joueur va pas percuter le mur
            if (_position.x + 2*_direction.x < 0)
            {
                _position.x = 0;
                return;
            }
            if (_position.y + 2*_direction.y < 0)
            {
                _position.y = 0;
                return;
            }
            if (_position.x + 2*_direction.x > ROOM_WIDTH - 1)
            {
                _position.x = ROOM_WIDTH - 1;
                return;
            }
            if (_position.y + 2*_direction.y > ROOM_HEIGHT - 1 )
            {
                _position.y = ROOM_HEIGHT - 1;
                return;
            }

            Translate( 2.0f*_direction );    
        }
        else
        {
            //Si il va percuter le mur
            if (_position.x + _direction.x < 0)
            {
                _position.x = 0;
                return;
            }
            if (_position.y + _direction.y < 0)
            {
                _position.y = 0;
                return;
            }
            if (_position.x + _direction.x > ROOM_WIDTH - 1)
            {
                _position.x = ROOM_WIDTH - 1;
                return;
            }
            if (_position.y + _direction.y > ROOM_HEIGHT - 1 )
            {
                _position.y = ROOM_HEIGHT - 1;
                return;
            }

            //Si il percute un objet
            if (!(_currentRoom->GetSquare( _position + _direction ) >= -2 && _currentRoom->GetSquare( _position + _direction ) != 0 ) )
            {
                Translate( _direction );
                return;
            }
        }
    }
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
    _items.emplace_back( ItemStack( Object::ToObject( ObjectID::Nothing ), 0 ));
    _heldItem = 0;
    _isTorchLit = false;
}

const std::vector< ItemStack >& Player::GetItems() const
{
    return _items;
}

void Player::Kill()
{
    std::cout << "Player died!" << std::endl;
    ++_deaths;
    EmptyInventory();
    _life = 100;
    _money = 400;
    _crouched = false;
    _grounded = true;
}

unsigned int Player::GetDeaths() const
{
    return _deaths;
}

void Player::SetHeldItem( int index )
{
    _heldItem = index;
}


void Player::DeselectItem()
{
    // Last item is always NOTHING
    _heldItem = _items.size() - 1;
}

bool Player::HasObject( const Object& o ) const
{
    for (auto item : _items)
        if (item.GetObject().GetID() == o.GetID())
            return true;

    return false;
}

int Player::GetObjectPositionFromInventory( const Object& o ) const
{
    int i = 0;
    for (auto it = _items.begin() ; it != _items.end() ; ++it, ++i)
        if (it->GetObject().GetID() == o.GetID())
            return i;

    // Deselect item
    return _items.size() - 1;
}

bool Player::TorchLit() const
{
    return _isTorchLit;
}

void Player::ActivateTorch()
{
    const Room* const room = GetCurrentRoom();
    const Vector2i& position = GetPosition();
    const ItemStack& held = GetHeldItem();

    if (held.GetObject().GetID() != ObjectID::Torch)
    {
        _isTorchLit = false;
        return;
    }

    if (!_isTorchLit && !_grounded)
    {
        if (position == Vector2i( 0, ROOM_HEIGHT - 2 )) // Left door
        {
            const Door* const door = room->GetDoor( Room::Left );
            if (door->GetTorchState())
                _isTorchLit = true;
        }
        if (position == Vector2i( ROOM_WIDTH - 1, ROOM_HEIGHT - 2 )) // Right door
        {
            const Door* const door = room->GetDoor( Room::Right );
            if (door->GetTorchState())
                _isTorchLit = true;
        }
        if (position == Vector2i( 3, 0 )) // Up door
        {
            const Door* const door = room->GetDoor( Room::Up );
            if (door->GetTorchState())
                _isTorchLit = true;
        }
    }
    else if (_isTorchLit && !_grounded)
    {
        if (GetPosition() == Vector2i( 0, ROOM_HEIGHT - 2 ) && GetCurrentRoom()->GetDoor( Room::Left )->HasTorch() &&
            !GetCurrentRoom()->GetDoor( Room::Left )->GetTorchState()) // Left door
        {
            GetCurrentRoom()->GetDoor( Room::Left )->SetTorchState();
            GetHeldItem().Use( 1 );
        }
        if (GetPosition() == Vector2i( ROOM_WIDTH - 1, ROOM_HEIGHT - 2 ) &&
            GetCurrentRoom()->GetDoor( Room::Right )->HasTorch() &&
            !GetCurrentRoom()->GetDoor( Room::Right )->GetTorchState()) // Right door
        {
            GetCurrentRoom()->GetDoor( Room::Right )->SetTorchState();
            GetHeldItem().Use( 1 );
        }
        if (GetPosition() == Vector2i( 3, 0 ) && GetCurrentRoom()->GetDoor( Room::Up )->HasTorch() &&
            !GetCurrentRoom()->GetDoor( Room::Up )->GetTorchState()) // Upper door
        {
            GetCurrentRoom()->GetDoor( Room::Up )->SetTorchState();
            GetHeldItem().Use( 1 );
        }
    }
}

void Player::SetGrounded(bool grounded)
{
    
    _grounded=grounded;
}

void Player::Save( const std::string& filename ) const
{
    std::ofstream save( filename.c_str() );
    if (!save.good())
        throw Exception( "Failed to save player data!", __FILE__, __LINE__ );

    save << "P " << std::to_string( _currentRoom->GetRoomID() ) << ' ' << _position << ' ' << _direction << '\n';

    save << _life << ' ' << _money << ' ' << _deaths << '\n';

    for (const auto& item : _items)
        save << item.GetObject().GetID() << ' ' << item.GetAmount() << ' ' << item.GetDurability() << '\n';

    save.close();
    std::cout << "Player saved!" << std::endl;
}

int Player::Load( const std::string& filename )
{
    std::ifstream save( filename.c_str() );
    if (!save.good())
        throw Exception( "Failed to load player data from " + filename, __FILE__, __LINE__ );

    // Get last values, ignore it
    save.seekg( -10, std::ios::end );
    const auto last = save.tellg();
    save.clear();
    save.seekg( 0, std::ios::beg );


    char P;
    save >> P;
    if (P != 'P')
        throw Exception( "Failed to load player data from " + filename, __FILE__, __LINE__ );

    int id;
    save >> id >> _position >> _direction;

    save >> _life >> _money >> _deaths;

    int itemID, amount, durability;
    while (save.tellg() != last)
    {
        save >> itemID >> amount >> durability;
        _items.emplace_back( ItemStack( Object::ToObject((ObjectID) itemID ), amount, durability ));
    }
    DeselectItem();

    save.close();
    return id;
}