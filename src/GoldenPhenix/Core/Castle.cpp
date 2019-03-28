//
// Created by serdok on 05/03/19.
//

#include "Castle.h"

Castle::Castle( const std::string& filename )
{
    std::ifstream file( filename.c_str(), std::ios::binary );
    if (!file.good())
        throw Exception( "Failed to open " + filename + '!', __FILE__, __LINE__ );

    while (!file.eof())
    {
        int lineNB = 1;
        std::vector< std::string > contentVECTOR;
        std::string line;
        while (lineNB < 11 && std::getline( file, line ))
        {
            if (line.empty()) // Skip empty lines
                continue;

            contentVECTOR.emplace_back( line );
            ++lineNB;
        }
        std::queue< std::string > contentQUEUE; // Put everything in a queue (better data processing)
        for (const auto& i : contentVECTOR)
            contentQUEUE.push( i );

        _rooms.emplace_back( new Room( contentQUEUE ));
        contentVECTOR.clear();
    }
    file.close();
    std::cout << _rooms.size() << " rooms loaded!" << std::endl;

    // Player starts in room id #6
    _player = new Player( _rooms[ 5 ] );
#ifdef DEBUG
    _bat = new Bat( VEC2_ZERO );
    _bat->Deactivate();
#endif // DEBUG
}

Castle::~Castle()
{
    for (auto room : _rooms)
        delete room;

    delete _player;
    delete _bat;
}

void Castle::Update()
{
    // Move bat if there is one in the room
    MoveBat();

    // Remove one life every 500th pass
    RemoveALife();

    // Kill the player
    KillPlayer();


    _player->Update();
}

void Castle::ProcessActions( const std::string& action )
{
    if (action == "left")
    {
        MoveToLeftRoom();
        _attacked = false;
    }

    if (action == "right")
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

    if (!_movedToNextRoom)
        _player->ProcessActions( action );

    _movedToNextRoom = false;
}

void Castle::PickUp()
{
    if (_player->Crouched())
    {
        for (int i = 3 ; i < 11 ; ++i)
        {
            if (_player->GetCurrentRoom()->GetSquare( _player->GetPosition() + _player->GetDirection()) == i)
                _player->AddItem( Object::ToObject((ObjectID) i ));
        }
        if (_player->GetCurrentRoom()->GetSquare( _player->GetPosition() + _player->GetDirection()) ==
            (int) ObjectID::CursedRing)
        {
            _player->AddItem( Object::CURSED_RING() );
            _ringIsInInventory = true;
        }

#ifdef DEBUG
        std::cout << "Picked " << Object::ToObject((ObjectID) _player->GetCurrentRoom()->GetSquare(
                _player->GetPosition() + _player->GetDirection())).ToString() << std::endl;
#endif // DEBUG

        _player->GetCurrentRoom()->GetSquare( _player->GetPosition() + _player->GetDirection()) = 0;
    }
    else
    {
        if (_player->GetCurrentRoom()->GetSquare( _player->GetPosition() + _player->GetDirection()) == 1)
            _player->AddItem( Object::EGG() );
    }
}

int Castle::GetScore()
{
    return _score;
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

const std::vector< Room* >& Castle::GetRooms() const
{
    return _rooms;
}

void Castle::OpenDoor( Door* door, Room::JoiningDirections direction )
{
    switch (door->GetOpenType())
    {
        case Door::OPEN_TYPES::open:
            if (_player->GetCurrentRoom()->GetRoomID( direction ) == 0)
                _exitCastle = true;
            else
            {
                _exitCastle = false;
                const Room* const currentRoom = _player->GetCurrentRoom();
                _player->SetCurrentRoom( GetRooms().at( _player->GetCurrentRoom()->GetRoomID( direction ) - 1 ));
                PlacePlayer( currentRoom );

                // Create bat if necessary
                SpawnBat();
            }
            break;
        case Door::OPEN_TYPES::iron_key:
            if (_player->GetHeldItem().GetObject().ToObjectID() == ObjectID::IronKey &&
                _player->GetHeldItem().GetAmount() >= 1)
            {
                // Use the key and move
                const Room* const currentRoom = _player->GetCurrentRoom();
                _player->SetCurrentRoom( GetRooms().at( _player->GetCurrentRoom()->GetRoomID( direction ) - 1 ));
                PlacePlayer( currentRoom );

                // Create bat if necessary
                SpawnBat();

                // Change door type to OPEN
                door->SetOpenType( Door::OPEN_TYPES::open );

                _player->GetHeldItem().Remove( 1 );
            }
            break;
        case Door::OPEN_TYPES::gold_key:
            if (_player->GetHeldItem().GetObject().ToObjectID() == ObjectID::GoldKey &&
                _player->GetHeldItem().GetAmount() >= 1)
            {
                // Use the key and move
                const Room* const currentRoom = _player->GetCurrentRoom();
                _player->SetCurrentRoom( GetRooms().at( _player->GetCurrentRoom()->GetRoomID( direction ) - 1 ));
                PlacePlayer( currentRoom );

                // Create bat if necessary
                SpawnBat();

                // Change door type to OPEN
                door->SetOpenType( Door::OPEN_TYPES::open );

                _player->GetHeldItem().Remove( 1 );
            }
            break;
        case Door::OPEN_TYPES::crowbar:
            if (_player->GetHeldItem().GetObject().ToObjectID() == ObjectID::Crowbar &&
                _player->GetHeldItem().GetAmount() >= 1 && _player->GetHeldItem().GetDurability() > 0)
            {
                // Use one durability from the crowbar and move
                const Room* const currentRoom = _player->GetCurrentRoom();
                _player->SetCurrentRoom( GetRooms().at( _player->GetCurrentRoom()->GetRoomID( direction ) - 1 ));
                PlacePlayer( currentRoom );

                // Create bat if necessary
                SpawnBat();

                // Change door type to OPEN
                door->SetOpenType( Door::OPEN_TYPES::open );

                if (_player->GetHeldItem().GetDurability() <= 0)
                    _player->GetHeldItem().Remove( 1 );
                else
                    _player->GetHeldItem().Use( 1 );
            }
            break;
        case Door::OPEN_TYPES::open_impossible:
        default:break;

    }
}

void Castle::MoveToLeftRoom()
{
    if (_player->GetPosition() == Vector2i( 4, 0 ) && _player->GetDirection() == VEC2_DOWN) // Left door
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
            case Door::DOORS::grid:OpenDoor( door, Room::Left );
                break;
            case Door::DOORS::wall:
            default:break;
        }
    }

    if (_player->GetPosition() == Vector2i( 4, 1 ) && _player->GetDirection() == VEC2_DOWN) // Left chest
    {
        if (_player->GetCurrentRoom()->GetDoor( Room::Left )->GetDoorType() == Door::DOORS::chest)
            OpenChest( Room::Left );
    }
}

void Castle::MoveToRightRoom()
{
    if (_player->GetPosition() == Vector2i( 4, ROOM_WIDTH - 1 ) && _player->GetDirection() == VEC2_UP) // Right door
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
            case Door::DOORS::grid:OpenDoor( door, Room::Right );
                break;
            case Door::DOORS::wall:
            default:break;
        }
    }

    if (_player->GetPosition() == Vector2i( 4, ROOM_WIDTH - 2 ) && _player->GetDirection() == VEC2_UP) // Right chest
    {
        if (_player->GetCurrentRoom()->GetDoor( Room::Right )->GetDoorType() == Door::DOORS::chest)
            OpenChest( Room::Right );
    }
}

void Castle::MoveToUpperRoom()
{
    if (_player->GetPosition() == Vector2i( 0, 3 ) && _player->GetDirection() == VEC2_LEFT) // Upper door
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
            case Door::DOORS::grid:
            case Door::DOORS::chimney:OpenDoor( door, Room::Up );
                break;
            case Door::DOORS::wall:
            default:break;
        }
    }
}

bool Castle::ExitCastle() const
{
    return _exitCastle;
}

void Castle::EnterCastle()
{
    if (_player->GetCurrentRoom()->GetRoomID() == 6)
    {
        _exitCastle = false;
        _player->SetPosition( Vector2i( 0, 3 ));
        _player->SetDirection( VEC2_RIGHT );
    }
}

void Castle::Use()
{
    if (_player->GetHeldItem().GetObject().ToObjectID() == ObjectID::LifePotion)
    {
        _player->AddLife( 80 );
        _player->RemoveItem( Object::LIFE_POTION() );
    }

    /*if(_player->GetHeldItem().GetObject().ToObjectID() == ObjectID::GrapplingHook)
    {
        
        _player->RemoveItem(Object::GRAPPLING_HOOK);
    }*/

    if (!_player->Grounded())
    {
        if (_player->GetHeldItem().GetObject().ToObjectID() == ObjectID::Torch)
        {
            if (_player->GetPosition() == Vector2i( 4, 0 ))
            {
                _player->GetCurrentRoom()->GetDoor( Room::Left )->SetTorchState();
                _player->GetHeldItem().Use( 1 );
            }
            if (_player->GetPosition() == Vector2i( 4, ROOM_WIDTH - 1 ))
            {
                _player->GetCurrentRoom()->GetDoor( Room::Right )->SetTorchState();
                _player->GetHeldItem().Use( 1 );
            }
            if (_player->GetPosition() == Vector2i( 0, 3 ))
            {
                _player->GetCurrentRoom()->GetDoor( Room::Up )->SetTorchState();
                _player->GetHeldItem().Use( 1 );
            }
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

void Castle::MoveBat()
{
    if (_bat->GetActiveState())
    {
        if (_iteration%25 == 0)
        {
            if (_bat->GetPosition().y == 0)
                _bat->SetDirection( VEC2_UP ); // Move right
            else if (_bat->GetPosition().y == ROOM_WIDTH - 1)
                _bat->SetDirection( VEC2_DOWN ); // Move left

            _bat->Translate( _bat->GetDirection() );
            _attacked = false;
        }


        if (_bat->GetPosition() == _player->GetPosition())
        {
            if (!_attacked)
            {
                _bat->Attack( _player );
                _attacked = true;
            }
        }
    }
}

void Castle::RemoveALife()
{
    ++_iteration;
    if (_iteration >= 500)
    {
        _player->AddLife( -1 );
        if (_ringIsInInventory)
            _player->AddLife( -10 );
        _iteration = 0;

        --_score;
        if (_score < 0)
            _score = 0;
    }
}

void Castle::KillPlayer()
{
    if (_player->GetLife() <= 0)
    {
        ++_deaths;
        _player->clearItems();
        _player->SetCurrentRoom( _rooms.at( 6 - 1 ));
        _player->SetLife( 100 );
        SetScore( 0 );
        _player->SetMoney( 400 );
        _player->SetPosition( Vector2i( 4, 3 ));
        SpawnBat();
    }
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

void Castle::OpenChest( Room::JoiningDirections direction )
{
    Door* chest = _player->GetCurrentRoom()->GetDoor( direction );
    int id = chest->GetObject();

    // The chest has no object
    if (id == 0)    return;

    // Chest contains an object
    if (id > 0)
    {
        Object item = Object::ToObject( (ObjectID) id );
        _player->AddItem( item );
    }
    else // Chest contains an unlisted object (money, ...)
    {
        if (id == -1) // Money
            _player->AddMoney( 100 );
    }

    chest->RemoveObject();
}

void Castle::PlacePlayer( const Room* const previousRoom )
{
    const Room* const currentRoom = _player->GetCurrentRoom();

    Room::JoiningDirections directionToPreviousRoom = Room::JoiningDirections::TOTAL;

    for (int direction=0 ; direction<Room::JoiningDirections::TOTAL ; ++direction)
    {
        if (currentRoom->GetRoomID( (Room::JoiningDirections) direction ) == previousRoom->GetRoomID())
            directionToPreviousRoom = (Room::JoiningDirections) direction;
    }

    switch (directionToPreviousRoom)
    {
        case Room::Left:
            _player->SetPosition( Vector2i( 4, 0 ) );
            _player->SetDirection( VEC2_UP );
            break;
        case Room::Up:
            _player->SetPosition( Vector2i( 0, 3 ) );
            _player->SetDirection( VEC2_RIGHT );
            break;
        case Room::Right:
            _player->SetPosition( Vector2i( 4, ROOM_WIDTH - 1 ) );
            _player->SetDirection( VEC2_DOWN );
            break;
        default:
            _player->SetPosition( Vector2i( 4, 3 ) );
            _player->SetDirection( VEC2_LEFT );
            break;
    }

    _movedToNextRoom = true;
}