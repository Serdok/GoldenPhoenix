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
    _ringIsInInventory = false;

    _score = 0;
    _deaths = 0;

    _iteration = 0;

    _bat = new Bat();
    _thereIsABat = false;
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
    ++_iteration;


    // Move bat if there is one in the room
    if (_thereIsABat)
    {
        if (_bat->GetPosition().x == 0)
            _bat->SetDirection( VEC2_RIGHT );
        else if (_bat->GetPosition().x == ROOM_WIDTH - 1)
            _bat->SetDirection( VEC2_LEFT );
        else
            _bat->Translate( _bat->GetDirection() );
        if (_bat->GetPosition() == _player->GetPosition())
            _bat->Attack( _player );
    }

    // Remove one life every 500th pass
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

    // Kill the player
    if (_player->GetLife() == 0)
    {
        ++_deaths;
        _player->clearItems();
        _player->SetCurrentRoom( _rooms[ 5 ] );
        _player->SetLife( 100 );
        SetScore( 0 );
        _player->SetMoney( 400 );
        _player->SetPosition( Vector2i( 4, 3 ) );
    }


    _player->Update();
}

void Castle::ProcessActions( const std::string& action )
{
    if (action == "left")
        MoveToLeftRoom();

    if (action == "right")
        MoveToRightRoom();

    if (action == "up")
        MoveToUpperRoom();

    _player->ProcessActions( action );

    if (action == "pick")
        PickUp();
}

void Castle::PickUp()
{
    if (_player->Crouched())
    {
        for (int i = 3 ; i < 11 ; ++i)
        {
            if (_player->GetCurrentRoom()->GetSquare( _player->GetPosition() + _player->GetDirection() ) == i)
                _player->AddItem( Object::ToObject( (ObjectID) i ) );
        }
        if (_player->GetCurrentRoom()->GetSquare( _player->GetPosition() + _player->GetDirection() ) == 11)
        {
            _player->AddItem( Object::CURSED_RING );
            _ringIsInInventory = true;
        }

#ifdef DEBUG
        std::cout << "Picked " << Object::ToObject( (ObjectID) _player->GetCurrentRoom()->GetSquare( _player->GetPosition() + _player->GetDirection() ) ).ToString() << std::endl;
#endif // DEBUG

        _player->GetCurrentRoom()->GetSquare( _player->GetPosition() + _player->GetDirection() ) = 0;
    }
    else
    {
        if (_player->GetCurrentRoom()->GetSquare( _player->GetPosition() + _player->GetDirection()) == 1)
            _player->AddItem( Object::EGG );
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
                _player->SetCurrentRoom( GetRooms().at( _player->GetCurrentRoom()->GetRoomID( direction ) - 1 ));
            }
            break;
        case Door::OPEN_TYPES::iron_key:
            if (_player->GetHeldItem().GetObject().ToObjectID() == ObjectID::IronKey && _player->GetHeldItem().GetAmount() >= 1)
            {
                // Use the key and move
                _player->SetCurrentRoom( GetRooms().at( _player->GetCurrentRoom()->GetRoomID( direction ) - 1 ));

                _player->GetHeldItem().Remove( 1 );

                // Change door type to OPEN
                door->SetOpenType( Door::OPEN_TYPES::open );
            }
            break;
        case Door::OPEN_TYPES::gold_key:
            if (_player->GetHeldItem().GetObject().ToObjectID() == ObjectID::GoldenKey && _player->GetHeldItem().GetAmount() >= 1)
            {
                // Use the key and move
                _player->SetCurrentRoom( GetRooms().at( _player->GetCurrentRoom()->GetRoomID( direction ) - 1 ));

                _player->GetHeldItem().Remove( 1 );

                // Change door type to OPEN
                door->SetOpenType( Door::OPEN_TYPES::open );
            }
            break;
        case Door::OPEN_TYPES::crowbar:
            if (_player->GetHeldItem().GetObject().ToObjectID() == ObjectID::Crowbar && _player->GetHeldItem().GetAmount() >= 1 && _player->GetHeldItem().GetDurability() > 0)
            {
                // Use one durability from the crowbar and move
                _player->SetCurrentRoom( GetRooms().at( _player->GetCurrentRoom()->GetRoomID( direction ) - 1 ));


                if (_player->GetHeldItem().GetDurability() <= 0)
                    _player->GetHeldItem().Remove( 1 );
                else
                    _player->GetHeldItem().Use( 1 );

                // Change door type to OPEN
                door->SetOpenType( Door::OPEN_TYPES::open );
            }
            break;
        case Door::OPEN_TYPES::open_impossible:
        default:
            break;

    }
}

void Castle::MoveToLeftRoom()
{
    if (_player->GetPosition() == Vector2i( 4, 0 ) && _player->GetDirection() == VEC2_DOWN) // Left door
    {
#ifdef DEBUG
        std::cout << "Trying to move to the left room of ID " << _player->GetCurrentRoom()->GetRoomID( Room::West ) << std::endl;
#endif // DEBUG

        Door* door = _player->GetCurrentRoom()->GetDoor( Room::West );

        switch (door->GetDoorType())
        {
            case Door::DOORS::opening:
            case Door::DOORS::door:
            case Door::DOORS::grid:
                OpenDoor( door, Room::West );
                break;
            case Door::DOORS::chest:
                if (door->GetObject() > 0) // Listed object
                    _player->AddItem( Object::ToObject( (ObjectID) door->GetObject() ) );
                else if (door->GetObject() < 0)// Money or unlisted objects
                    _player->AddMoney( 100 );
                else
                    door->RemoveObject( door->GetObject() );
                break;
            case Door::DOORS::wall:
            default:
                break;
        }
    }
}

void Castle::MoveToRightRoom()
{
    if (_player->GetPosition() == Vector2i( 4, ROOM_WIDTH - 1 ) && _player->GetDirection() == VEC2_UP) // Right door
    {
#ifdef DEBUG
        std::cout << "Trying to move to the right room of ID " << _player->GetCurrentRoom()->GetRoomID( Room::East ) << std::endl;
#endif // DEBUG

        Door* door = _player->GetCurrentRoom()->GetDoor( Room::East );

        switch (door->GetDoorType())
        {
            case Door::DOORS::opening:
            case Door::DOORS::door:
            case Door::DOORS::grid:
                OpenDoor( door, Room::East );
                break;
            case Door::DOORS::wall:
            default:
                break;
        }
    }
}

void Castle::MoveToUpperRoom()
{
    if (_player->GetPosition() == Vector2i( 0, 3 ) && _player->GetDirection() == VEC2_LEFT) // Upper door
    {
#ifdef DEBUG
        std::cout << "Trying to move to the upper room of ID " << _player->GetCurrentRoom()->GetRoomID( Room::North ) << std::endl;
#endif // DEBUG

        Door* door = _player->GetCurrentRoom()->GetDoor( Room::North );

        switch (door->GetDoorType())
        {
            case Door::DOORS::opening:
            case Door::DOORS::door:
            case Door::DOORS::grid:
            case Door::DOORS::chimney:
                OpenDoor( door, Room::North );
                break;
            case Door::DOORS::wall:
            default:
                break;
        }
    }
}

bool Castle::ExitCastle() const
{
    return _exitCastle;
}

void Castle::EnterCastle()
{
    _exitCastle = false;
    _player->SetPosition( Vector2i( 0, 3 ) );
    _player->SetDirection( VEC2_RIGHT );
}

void Castle::ReplacePlayer( unsigned int previousRoomID, Room::JoiningDirections direction )
{
    // Get the new room
    Room* newRoom = _rooms.at( _player->GetCurrentRoom()->GetRoomID( direction ) - 1 );

    // Get direction to go back to the previous room relative to the new one
    Room::JoiningDirections returnDirection = Room::JoiningDirections::TOTAL;
    for (int i=0 ; i<(int) Room::JoiningDirections::TOTAL ; ++i)
    {
        if (newRoom->GetRoomID( (Room::JoiningDirections) i ) == previousRoomID)
            returnDirection = (Room::JoiningDirections) i;
    }

    switch (returnDirection)
    {
        case Room::West:
            _player->SetPosition( Vector2i( 5, 1 ) );
            _player->SetDirection( VEC2_DOWN );
            break;
        case Room::North:
            _player->SetPosition( Vector2i( 0, 4 ) );
            _player->SetDirection( VEC2_LEFT );
            break;
        case Room::East:
            _player->SetPosition( Vector2i( 5, ROOM_WIDTH - 1 ) );
            _player->SetDirection( VEC2_UP );
            break;
        case Room::TOTAL:
            _player->SetPosition( Vector2i( 4, 3 ) );
            _player->SetDirection( VEC2_RIGHT );
        default: break;
    }
}