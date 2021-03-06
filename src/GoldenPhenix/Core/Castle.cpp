//
// Created by serdok on 05/03/19.
//

#include "Castle.h"

Castle::Castle( bool useCustomTimer )
        : _usingCustomTimer( useCustomTimer )
{
    // Load game data
    LoadCastle();
}

Castle::~Castle() noexcept( false )
{
    // Save game data
    _player->Save( GetResourcePath( "rooms/save.player" ));
    SaveRooms( GetResourcePath( "rooms/save.rooms" ));

    std::ofstream player( GetResourcePath( "rooms/save.player" ), std::ios_base::app );
    if (!player.good())
        throw Exception( "Failed to write to " + GetResourcePath( "rooms/save.player" ) + '!', __FILE__, __LINE__ );

    player << _exitCastle;

    if (_lastRoomID < 10) player << " 00" << _lastRoomID;
    else if (_lastRoomID < 100) player << " 0" << _lastRoomID;
    else player << _lastRoomID;

    if (_score < 10) player << " 00" << _score;
    else if (_score < 100) player << " 0" << _score;
    else player << ' ' << _score;

    player.close();

    // Free resources
    for (auto& room : _rooms)
        delete room;
    _rooms.clear();

    delete _player;
    delete _bat;
    delete _rat;
}

void Castle::Update()
{
    // Move bat if there is one in the room
    MoveBat();

    // Move rat if there is one in the room
    MoveRat();

    // Move the player if he fell in an oblivion passage
    if (_player->GetCurrentRoom()->GetSquare( _player->GetPosition()) == -4)
    {
        if (Room::GetOblivionLink( _player->GetCurrentRoom()->GetRoomID()))
            _player->SetCurrentRoom( _rooms.at( Room::GetOblivionLink( _player->GetCurrentRoom()->GetRoomID()) - 1 ));
        _player->SetPosition( Vector2i(3,3));
        SpawnRat();
        SpawnBat();
    }

    // Move the player if he fell in an oblivion trap
    if (_player->GetCurrentRoom()->GetSquare( _player->GetPosition()) == -3)
    {
        _lastRoomID = _player->GetCurrentRoom()->GetRoomID();
        _player->SetCurrentRoom( _rooms.at( FindRoomID( 666 )));
        _player->SetPosition( Vector2i(3,3));
        SpawnRat();
        SpawnBat();
    }

    // Use the torch if it is lit
    if (_player->GetHeldItem().GetObject().GetID() == ObjectID::Torch && _player->TorchLit())
        if (_iteration%60 == 0)
        {
            _player->GetHeldItem().Use( 1 );
            std::cout << _player->GetHeldItem().GetDurability() << std::endl;
        }

    // Remove one life every 500th pass
    RemoveALife();

    // Update the player
    _player->Update();
}

void Castle::ProcessActions( const std::string& action )
{
    if (action == "left" && !_player->Crouched())
    {   
        MoveToLeftRoom();
        _attacked = false;
    }

    if (action == "right" && !_player->Crouched())
    {
        MoveToRightRoom();
        _attacked = false;
    }

    if (action == "up")
    {
        MoveToUpperRoom();
        _attacked = false;
    }

    if (action == "pick")
    {
        PickUp();
        _attacked = false;
    }

    if (action == "kill")
        KillPlayer();

    if (action == "use")
        Use();

    if (!_movedToNextRoom)
        _player->ProcessActions( action );

    _movedToNextRoom = false;
}

void Castle::PickUp()
{
    // Condition to pick up an object : Crouched and nothing must be held
    if (_player->Crouched() && _player->GetHeldItem().GetObject().GetID() == ObjectID::Nothing)
    {
        for (int obj = ObjectID::IronKey ; obj < ObjectID::TOTAL ; ++obj)
        {
            if (_player->GetCurrentRoom()->GetSquare( _player->GetPosition() + _player->GetDirection()) == obj)
            {
                _player->AddItem( Object::ToObject((ObjectID) obj ));
                switch (obj)
                {
                    case ObjectID::IronKey:AddScore( 100 );
                        break;
                    case ObjectID::GoldKey:AddScore( 200 );
                        break;
                    case ObjectID::Hint1:
                    case ObjectID::Hint2:
                    case ObjectID::Hint3:AddScore( 50 );
                        _player->DeselectItem();
                        break;
                    case ObjectID::LifePotion:AddScore( 50 );
                        break;
                    case ObjectID::CursedRing:AddScore( 200 );
                        _ringIsInInventory = true;
                        _player->DeselectItem();
                        break;
                    default:break;
                }

                // Remove the object from the ground
                _player->GetCurrentRoom()->GetSquare( _player->GetPosition() + _player->GetDirection()) = ObjectID::Nothing;
            }
        }

        if (_player->GetCurrentRoom()->GetSquare( _player->GetPosition() + _player->GetDirection()) == -1) // Money
        {
            MoneyRoom();
            AddScore( 100 );

            // Remove the object from the ground
            _player->GetCurrentRoom()->GetSquare( _player->GetPosition() + _player->GetDirection()) = ObjectID::Nothing;
        }
    }
        // Special case for the egg : must be standing
    else if (!_player->Crouched() && _player->GetHeldItem().GetObject().GetID() == ObjectID::Nothing)
    {
        if (_player->GetCurrentRoom()->GetSquare( _player->GetPosition() + _player->GetDirection()) == ObjectID::Egg && !GetRingIsInInventory())
        {
            _player->AddItem( Object::ToObject( ObjectID::Egg ));
            AddScore( 500 );
            _player->GetCurrentRoom()->GetSquare( Vector2i(5, 3) ) = ObjectID::Column;
            _player->DeselectItem();
        }
        if (_player->GetCurrentRoom()->GetSquare( _player->GetPosition() + _player->GetDirection()) == ObjectID::Helmet)
        {
            _player->AddItem( Object::ToObject( ObjectID::Helmet ));
            AddScore( 200 );
            _player->AddMoney( 50 );
            _player->GetCurrentRoom()->GetSquare( Vector2i(5, 3)) = ObjectID::Column;
            _player->GetCurrentRoom()->GetSquare( Vector2i(4, 3)) = -3;
            _player->DeselectItem();
        }
    }
}

int Castle::GetScore()
{
    return _score;
}

void Castle::AddScore( int s )
{
    _score += s;
}

void Castle::SetScore( int s )
{
    _score = s;
}

const Player* const Castle::GetPlayer() const
{
    return _player;
}

Player* const Castle::GetPlayer()
{
    return _player;
}

const Bat* const Castle::GetBat() const
{
    return _bat;
}

Bat* const Castle::GetBat()
{
    return _bat;
}

const Rat* const Castle::GetRat() const
{
    return _rat;
}

Rat* const Castle::GetRat()
{
    return _rat;
}

const std::vector< Room* >& Castle::GetRooms() const
{
    return _rooms;
}

bool Castle::OpenDoor( Door* door, Room::JoiningDirections direction )
{
    bool success = false;
    switch (door->GetOpenType())
    {
        // If door is open, pass through
        case Door::OPEN_TYPES::open:
            if (_player->GetCurrentRoom()->GetRoomID( direction ) == 0)
                _exitCastle = true;
            else
            {
                _exitCastle = false;
                const Room* const currentRoom = _player->GetCurrentRoom();

                // Move player to next room
                _player->SetCurrentRoom( GetRooms().at( _player->GetCurrentRoom()->GetRoomID( direction ) - 1 ));
                PlacePlayer( currentRoom );

                // Create bat if necessary
                SpawnBat();

                // Create rat if necessary
                SpawnRat();
                success = true;
            }
            break;
        case Door::OPEN_TYPES::iron_key:
            // Don't bother trying to open the door if the inventory is empty ...
            if (_player->GetItems().empty())
                return false;

            if (_player->GetHeldItem().GetObject().GetID() == ObjectID::IronKey)
            {
                // Use the key and move
                const Room* const currentRoom = _player->GetCurrentRoom();
                _player->SetCurrentRoom( GetRooms().at( _player->GetCurrentRoom()->GetRoomID( direction ) - 1 ));
                PlacePlayer( currentRoom );

                // Create bat if necessary
                SpawnBat();

                // Create rat if necessary
                SpawnRat();

                // Change door type to OPEN
                door->SetOpenType( Door::OPEN_TYPES::open );
                success = true;
            }
            break;
        case Door::OPEN_TYPES::gold_key:
            // Don't bother trying to open the door if the inventory is empty ...
            if (_player->GetItems().empty())
                return false;

            if (_player->GetHeldItem().GetObject().GetID() == ObjectID::GoldKey)
            {
                // Use the key and move
                const Room* const currentRoom = _player->GetCurrentRoom();
                _player->SetCurrentRoom( GetRooms().at( _player->GetCurrentRoom()->GetRoomID( direction ) - 1 ));
                PlacePlayer( currentRoom );

                // Create bat if necessary
                SpawnBat();

                // Create rat if necessary
                SpawnRat();

                // Change door type to OPEN
                door->SetOpenType( Door::OPEN_TYPES::open );
                success = true;
            }
            break;
        case Door::OPEN_TYPES::crowbar:
            // Don't bother trying to open the door if the inventory is empty ...
            if (_player->GetItems().empty())
                return false;

            if (_player->GetHeldItem().GetObject().GetID() == ObjectID::Crowbar &&
                _player->GetHeldItem().GetAmount() >= 1 && _player->GetHeldItem().GetDurability() > 0)
            {
                // 60% chance to open the door
                if (Random( 0, 100 ) >= 40)
                {
                    // Move player to the next room
                    const Room* const currentRoom = _player->GetCurrentRoom();
                    _player->SetCurrentRoom( GetRooms().at( _player->GetCurrentRoom()->GetRoomID( direction ) - 1 ));
                    PlacePlayer( currentRoom );

                    // Create bat if necessary
                    SpawnBat();

                    // Create rat if necessary
                    SpawnRat();

                    // Change door type to OPEN
                    door->SetOpenType( Door::OPEN_TYPES::open );
                    success = true;
                }

                // Use [1, 3] durability from the crowbar each time, even on fail
                if (_player->GetHeldItem().GetDurability() <= 0)
                    _player->GetHeldItem().Remove( 1 );
                else
                    _player->GetHeldItem().Use((int) Random( 0, 3 ));
            }
            break;
        case Door::OPEN_TYPES::open_impossible:
            // Can't open the door
        default:success = false;
            break;

    }

    return success;
}

void Castle::MoveToLeftRoom()
{
    _failedToOpenDoor = false;
    if (_player->GetPosition() == Vector2i( 0, ROOM_HEIGHT - 2 ) && _player->GetDirection() == VEC2_LEFT) // Left door
    {
#ifdef DEBUG
        std::cout << "Trying to move to the left room of ID " << _player->GetCurrentRoom()->GetRoomID( Room::Left )
                  << std::endl;
#endif // DEBUG

        Door* door = _player->GetCurrentRoom()->GetDoor( Room::Left );

        switch (door->GetDoorType())
        {
            case Door::DOORS::opening:
            case Door::DOORS::door:
            case Door::DOORS::grid:if (!OpenDoor( door, Room::Left )) _failedToOpenDoor = true;
                break;
            case Door::DOORS::wall:
            default:break;
        }
    }

    if (_player->GetPosition() == Vector2i( 1, ROOM_HEIGHT - 2 ) && _player->GetDirection() == VEC2_LEFT) // Left chest
    {
        if (_player->GetCurrentRoom()->GetDoor( Room::Left )->GetDoorType() == Door::DOORS::chest)
            if (!OpenChest( Room::Left )) _failedToOpenDoor = true;
    }
}

void Castle::MoveToRightRoom()
{
    _failedToOpenDoor = false;
    if (_player->GetPosition() == Vector2i( ROOM_WIDTH - 1, ROOM_HEIGHT - 2 )
        && _player->GetDirection() == VEC2_RIGHT) // Right door
    {
#ifdef DEBUG
        std::cout << "Trying to move to the right room of ID " << _player->GetCurrentRoom()->GetRoomID( Room::Right )
                  << std::endl;
#endif // DEBUG

        Door* door = _player->GetCurrentRoom()->GetDoor( Room::Right );

        switch (door->GetDoorType())
        {
            case Door::DOORS::opening:
            case Door::DOORS::door:
            case Door::DOORS::grid: if (!OpenDoor( door, Room::Right )) _failedToOpenDoor = true;
                break;
            case Door::DOORS::wall:
            default:break;
        }
    }

    if (_player->GetPosition() == Vector2i( ROOM_WIDTH - 2, ROOM_HEIGHT - 2 )
        && _player->GetDirection() == VEC2_RIGHT) // Right chest
    {
        if (_player->GetCurrentRoom()->GetDoor( Room::Right )->GetDoorType() == Door::DOORS::chest)
            if (!OpenChest( Room::Right )) _failedToOpenDoor = true;
    }
}

void Castle::MoveToUpperRoom()
{
    _failedToOpenDoor = false;
    if (_player->GetPosition() == Vector2i( 3, 0 ) && _player->GetDirection() == VEC2_DOWN && !_player->Crouched()) // Upper door
    {
#ifdef DEBUG
        std::cout << "Trying to move to the upper room of ID " << _player->GetCurrentRoom()->GetRoomID( Room::Up )
                  << std::endl;
#endif // DEBUG

        Door* door = _player->GetCurrentRoom()->GetDoor( Room::Up );

        switch (door->GetDoorType())
        {
            case Door::DOORS::opening:
            case Door::DOORS::door:
            case Door::DOORS::grid:if (!OpenDoor( door, Room::Up )) _failedToOpenDoor = true;
                break;
            case Door::DOORS::wall:
            default:break;
        }
    }

    if (_player->GetPosition() == Vector2i( 3, 1 )
        && _player->GetDirection() == VEC2_DOWN
        && _player->Crouched()) // Chimney
    {
        if (_player->GetCurrentRoom()->GetDoor( Room::Up )->GetDoorType() == Door::DOORS::chimney)
            if (!OpenDoor( _player->GetCurrentRoom()->GetDoor( Room::Up ), Room::Up )) _failedToOpenDoor = true;
    }
}

bool Castle::ExitCastle() const
{
    return _exitCastle;
}

void Castle::EnterCastle()
{
    _exitCastle = false;
    _player->SetPosition( Vector2i( 3, 0 ));
    _player->SetDirection( VEC2_UP );
    _player->SetCurrentRoom( _rooms.at( 6 - 1 ));
    SpawnBat();
    SpawnRat();
}

void Castle::Use()
{
    // Don't bother trying to use an object if the inventory is empty ...
    if (_player->GetItems().empty())
        return;

    if (_player->GetHeldItem().GetObject().GetID() == ObjectID::LifePotion)
    {
        _player->AddLife( 80 );
        _player->RemoveItem( Object::ToObject( ObjectID::LifePotion ));
    }

    if (_player->GetHeldItem().GetObject().GetID() == ObjectID::GrapplingHook)
    {
        bool hookPossible = false;
        for (int i = 0 ; i < ROOM_WIDTH ; ++i)
            for (int j = 0 ; j < ROOM_HEIGHT ; ++j)
                if (_player->GetCurrentRoom()->GetSquare( Vector2i( i, j )) == -6)
                    hookPossible = true;

        if (hookPossible)
        {
            if (_player->GetCurrentRoom()->GetRoomID() != 666)
            {
                _player->SetCurrentRoom( _rooms.at( Room::GetOblivionOrigin( _player->GetCurrentRoom()->GetRoomID())
                                                    - 1 ));
            }
            else
            {
                _player->SetCurrentRoom( _rooms.at( FindRoomID( _lastRoomID )));
                _lastRoomID = 0;
            }
            for (int i = 0 ; i < ROOM_WIDTH ; ++i)
                for (int j = 0 ; j < ROOM_HEIGHT ; ++j)
                    if (_player->GetCurrentRoom()->GetSquare( Vector2i( i, j )) == -6 || _player->GetCurrentRoom()->GetSquare( Vector2i( i, j )) == -3)
                    {
                        if (_player->GetCurrentRoom()->GetSquare( Vector2i( i-1, j )) == 0 
                            || _player->GetCurrentRoom()->GetSquare( Vector2i( i-1, j )) < -2)
                        {
                            _player->SetDirection(VEC2_LEFT);
                            _player->SetPosition( Vector2i(i-1, j));
                        }
                        else if (_player->GetCurrentRoom()->GetSquare( Vector2i( i+1, j )) == 0 
                            || _player->GetCurrentRoom()->GetSquare( Vector2i( i+1, j )) < -2)
                        {
                            _player->SetDirection(VEC2_RIGHT);
                            _player->SetPosition( Vector2i(i+1, j));
                        }
                        else if (_player->GetCurrentRoom()->GetSquare( Vector2i(i, j-1)) == 0 
                            || _player->GetCurrentRoom()->GetSquare( Vector2i(i, j-1)) < -2)
                        {
                            _player->SetDirection(VEC2_DOWN);
                            _player->SetPosition( Vector2i(i, j-1));
                        }
                        else
                        {
                            _player->SetDirection(VEC2_UP);
                            _player->SetPosition( Vector2i(i, j+1));
                        }
                    }
            _player->GetHeldItem().Remove( 1 );
        }
    }
}

void Castle::SpawnBat()
{
    Vector2i spawn;

    if (BatInRoom( &spawn ))
    {
        _bat->Activate();
        _bat->SetPosition( spawn );
    }
    else
        _bat->Deactivate();

}

void Castle::SpawnRat()
{
    Vector2i spawn;

    if (RatInRoom( &spawn ))
    {
        _rat->Activate();
        _rat->SetPosition( spawn );
    }
    else
        _rat->Deactivate();

}

void Castle::MoveBat()
{
    if (_bat->GetActiveState())
    {
        if (_iteration%40 == 0)
        {
            if(_bat->GetPosition().y == _player->GetPosition().y)
            {
                if (_bat->GetPosition().x == 0) // Hit the left wall
                    _bat->SetDirection( VEC2_RIGHT ); // Move right
                else if (_bat->GetPosition().x == ROOM_WIDTH - 1) // Hit the right wall
                    _bat->SetDirection( VEC2_LEFT ); // Move left
                _bat->Translate( _bat->GetDirection());
            }
            else
            {
                if(_bat->GetPosition().y < _player->GetPosition().y)
                    _bat->Translate( VEC2_UP); // Move up
                else if(_bat->GetPosition().y > _player->GetPosition().y)
                    _bat->Translate( VEC2_DOWN ); // Move down
            }

            // Bat moved, it can attack again
            _attacked = false;
        }


        if (_bat->GetPosition() == _player->GetPosition() && !_player->Crouched())
        {
            if (!_attacked)
            {
                _bat->Attack( _player );
                _attacked = true;
            }
        }
    }
}

void Castle::MoveRat()
{
    int move = _iteration%700;
    if (_rat->GetActiveState())
    {
        if (move%12 == 0)
        {
            if (_rat->GetPosition().x == 0)
            {
                _rat->SetVisible( true );
                _rat->SetDirection( VEC2_RIGHT ); // Move right
            }
            else if (_rat->GetPosition().x == ROOM_WIDTH - 1)
            {
                _rat->SetVisible( false );
                _rat->SetDirection( VEC2_LEFT ); // Move right
            }
            _rat->Translate( _rat->GetDirection());

            // Rat moved, it can attack again
            _attacked = false;
        }


        if (_rat->GetPosition() == _player->GetPosition() && _player->Grounded() && _rat->GetVisible())
        {
            if (!_attacked)
            {
                _rat->Attack( _player );
                _attacked = true;
            }
        }
    }
}

void Castle::RemoveALife()
{
    if (_iteration%700 == 0)
    {
        _player->AddLife( -1 );
        if (_ringIsInInventory)
            _player->AddLife( -10 );
    }
}

void Castle::KillPlayer()
{
    _shouldReset = true;
    _exitCastle = true;
    _player->Kill();
    SetScore( 0 );
}

bool Castle::BatInRoom( Vector2i* spawn )
{
    Vector2i location;
    for (int i = 0 ; i < ROOM_HEIGHT ; ++i)
    {
        for (int j = 0 ; j < ROOM_WIDTH ; ++j)
        {
            if (_player->GetCurrentRoom()->GetSquare( Vector2i( i, j )) == -5)
            {
                location = Vector2i( i, j );
                if (spawn)
                    *spawn = location;
                return true;
            }
        }
    }

    if (spawn)
        *spawn = Vector2i( -1, 0 );
    return false;
}

bool Castle::RatInRoom( Vector2i* spawn )
{
    Vector2i location;
    for (int i = 0 ; i < ROOM_HEIGHT ; ++i)
    {
        for (int j = 0 ; j < ROOM_WIDTH ; ++j)
        {
            if (_player->GetCurrentRoom()->GetSquare( Vector2i( i, j )) == -7)
            {
                location = Vector2i( i, j );
                if (spawn)
                    *spawn = location;
                return true;
            }
        }
    }

    if (spawn)
        *spawn = Vector2i( -4, 0 );
    return false;
}

bool Castle::OpenChest( Room::JoiningDirections direction )
{
    Door* chest = _player->GetCurrentRoom()->GetDoor( direction );
    int id = chest->GetObject();
    bool open = false;

    std::cout << id << std::endl;

    // The chest has no object
    if (id == 0) return true;

    switch (chest->GetOpenType())
    {
        // If door is open, pass through
        case Door::OPEN_TYPES::open:
            open = true;
            break;
        case Door::OPEN_TYPES::iron_key:
            // Don't bother trying to open the door if the inventory is empty ...
            if (_player->GetItems().empty())
                return false;

            if (_player->GetHeldItem().GetObject().GetID() == ObjectID::IronKey)
            {
                open = true;
            }
            break;
        case Door::OPEN_TYPES::gold_key:
            // Don't bother trying to open the door if the inventory is empty ...
            if (_player->GetItems().empty())
                return false;

            if (_player->GetHeldItem().GetObject().GetID() == ObjectID::GoldKey)
            {  
                open = true;
            }
            break;
        case Door::OPEN_TYPES::crowbar:
            // Don't bother trying to open the door if the inventory is empty ...
            if (_player->GetItems().empty())
                return false;

            if (_player->GetHeldItem().GetObject().GetID() == ObjectID::Crowbar &&
                _player->GetHeldItem().GetAmount() >= 1 && _player->GetHeldItem().GetDurability() > 0)
            {
                // 60% chance to open the door
                if (Random( 0, 100 ) >= 40)
                {
                    open = true;
                }

                // Use [1, 3] durability from the crowbar each time, even on fail
                if (_player->GetHeldItem().GetDurability() <= 0)
                    _player->GetHeldItem().Remove( 1 );
                else
                    _player->GetHeldItem().Use((int) Random( 0, 3 ));
            }
            break;
        case Door::OPEN_TYPES::open_impossible:
            // Can't open the door
        default: return false;
            break;

    }


    if(open)
    {    // Chest contains an object
        if (id > 0)
            _player->AddItem( Object::ToObject((ObjectID) id ));
        else // Chest contains an unlisted object (money, ...)
        {
            if (id == -1) // Money
               MoneyRoom();
        }
        // Remove the object from the chest
        chest->RemoveObject();
    }
    return open;
}

void Castle::PlacePlayer( const Room* const previousRoom )
{
    const Room* const currentRoom = _player->GetCurrentRoom();

    Room::JoiningDirections directionToPreviousRoom = Room::JoiningDirections::TOTAL;

    // Get the direction to go back from the room we were before
    for (int direction = 0 ; direction < Room::JoiningDirections::TOTAL ; ++direction)
    {
        if (currentRoom->GetRoomID((Room::JoiningDirections) direction ) == previousRoom->GetRoomID())
            directionToPreviousRoom = (Room::JoiningDirections) direction;
    }

    // Place player accordingly to the last room direction
    switch (directionToPreviousRoom)
    {
        case Room::Left:_player->SetDirection( VEC2_RIGHT );
            _player->SetPosition( Vector2i( 0, ROOM_HEIGHT - 2 ));
            break;
        case Room::Up:_player->SetDirection( VEC2_UP );
            if (currentRoom->GetDoor( directionToPreviousRoom )->GetDoorType() == Door::DOORS::chimney)
                _player->SetPosition( Vector2i( 3, 1 ));
            else
                _player->SetPosition( Vector2i( 3, 0 ));
            break;
        case Room::Right:_player->SetDirection( VEC2_LEFT );
            _player->SetPosition( Vector2i( ROOM_WIDTH - 1, ROOM_HEIGHT - 2 ));
            break;
        default:_player->SetDirection( VEC2_UP );
            _player->SetPosition( Vector2i( 4, 3 ));
            break;
    }

    _player->SetGrounded();
    _movedToNextRoom = true;
    _failedToOpenDoor = false;
}

float Castle::Random( float low, float high )
{
    // C++ 11 random number generator
    std::random_device rd;
    std::mt19937 mt( rd());
    std::uniform_real_distribution< float > random( low, std::nextafter( high, MAXFLOAT ));
    return random( mt );
}

void Castle::AddIteration( unsigned int it )
{
    if (_usingCustomTimer)
        _iteration += it;
    else
        ++_iteration;
}

void Castle::LoadCastle()
{
    if (fs::exists( GetResourcePath( "rooms/save.rooms" )))
    {
        std::cout << "Loaded saved room data!" << std::endl;
        LoadRooms( GetResourcePath( "rooms/save.rooms" ));
    }
    else
    {
        std::cout << "Loaded default room data!" << std::endl;
        LoadRooms( GetResourcePath( "rooms/default.rooms" ));
    }

    delete _player;
    _player = new Player();
    if (fs::exists( GetResourcePath( "rooms/save.player" )))
    {
        std::cout << "Loaded saved player data!" << std::endl;

        std::ifstream player( GetResourcePath( "rooms/save.player" ), std::ios::binary );
        if (!player.good()) throw Exception( "Failed to read from " + GetResourcePath( "rooms/save.player" ) + '!', __FILE__, __LINE__ );
        player.seekg( -9, std::ios::end );
        player >> _exitCastle >> _lastRoomID >> _score;
        player.close();

        _player->SetCurrentRoom( _rooms.at( FindRoomID( _player->Load( GetResourcePath( "rooms/save.player" )))));
    }
    else
    {
        std::cout << "Loaded default player data!" << std::endl;
        _player->SetCurrentRoom( _rooms.at( FindRoomID( _player->Load( GetResourcePath( "rooms/default.player" )))));
    }

    // Create monsters
    delete _bat;
    _bat = new Bat( VEC2_ZERO );
    _bat->Deactivate();

    delete _rat;
    _rat = new Rat( VEC2_ZERO );
    _rat->Deactivate();

    SpawnBat();
    SpawnRat();
}

void Castle::LoadRooms( const std::string& filename )
{
    for (auto& room : _rooms)
        delete room;
    _rooms.clear();

    std::ifstream file( filename.c_str() );
    if (!file.good())
        throw Exception( "Failed to read from " + filename + '!', __FILE__, __LINE__ );

    std::queue< std::string > contentQUEUE; // Put everything in a queue (better data processing)
    while (!file.eof())
    {
        int lineNB = 1;
        std::vector <std::string> contentVECTOR;
        std::string line;
        while (lineNB < 11 && std::getline( file, line ))
        {
            if (line.empty()) // Skip empty lines
                continue;

            contentVECTOR.emplace_back( line );
            ++lineNB;
        }

        for (const auto& i : contentVECTOR)
            contentQUEUE.push( i );

        _rooms.emplace_back( new Room( contentQUEUE ));
        while (!contentQUEUE.empty()) contentQUEUE.pop();
        contentVECTOR.clear();
    }

    file.close();
    std::cout << _rooms.size() << " rooms loaded!" << std::endl;

    _lastRoomID = 0;
    _ringIsInInventory = false;
    _shouldReset = false;
}

bool Castle::ShouldReset() const
{
    return _shouldReset;
}

void Castle::SaveRooms( const std::string& filename )
{
    std::ofstream rooms( filename.c_str(), std::ios::binary );
    if (!rooms.good())
        throw Exception( "Failed to write to " + filename + '!', __FILE__, __LINE__ );

    for (const auto& room : _rooms)
    {
        std::queue <std::string> data = room->Save();

        if (room != _rooms.back())
        {
            while (!data.empty())
            {
                rooms << data.front();
                data.pop();
            }
            rooms << '\n';
        }
        else
        {
            while (!data.empty())
            {
                if (data.size() == 1)
                {
                    std::string last = data.front();
                    data.pop();

                    // Remove last line break, exit the while() loop
                    rooms << last.substr( 0, last.find( '\n' ));
                    continue;
                }

                rooms << data.front();
                data.pop();
            }
        }
    }
    rooms.close();

    std::cout << "Rooms data saved!" << std::endl;
}

unsigned int Castle::FindRoomID( unsigned int id ) const
{
    for (auto i = 0 ; i < _rooms.size() ; ++i)
        if (_rooms[ i ]->GetRoomID() == id)
            return i;
    return 0;
}

bool Castle::FailedToOpenDoor() const
{
    return _failedToOpenDoor;
}

bool Castle::GetRingIsInInventory() const
{
    return _ringIsInInventory;
}

void Castle::MoneyRoom()
{
    int id = _player->GetCurrentRoom()->GetRoomID();
    int money = (id/10) * 25 + id%10;
    _player->AddMoney(money);
    AddScore(money);
}