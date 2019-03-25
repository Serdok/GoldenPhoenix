//
// Created by serdok on 05/03/19.
//

#include "Room.h"

Room::Room( std::queue< std::string >& data )
: _id( 0 ), _isCorridor( false )
{
    // Each room must have 10 lines describing them
    if (data.size() != 10)
        throw Exception( "A room failed to load!", __FILE__, __LINE__ );

    LoadID( data );
    LoadJoiningData( data );
    LoadGround( data );
}

Room::~Room()
{
    for (auto joiningDoor : _joiningDoors)
        delete joiningDoor;
}

unsigned int Room::GetRoomID( Room::JoiningDirections direction ) const
{
    return _joiningRooms[ direction ];
}

unsigned int Room::GetRoomID() const
{
    return _id;
}

int Room::GetSquare( const Vector2i& position ) const
{
    return _ground[ position.x ][ position.y ];
}

int& Room::GetSquare( const Vector2i& position )
{
    return _ground[ position.x ][ position.y ];
}

Door* Room::GetDoor( Room::JoiningDirections direction )
{
    return _joiningDoors[ direction ];
}

const Door* const Room::GetDoor( Room::JoiningDirections direction ) const
{
    return _joiningDoors[ direction ];
}

bool Room::IsCorridor() const
{
    return _isCorridor;
}

void Room::LoadID( std::queue< std::string >& data )
{
    // Load the room number and type
    std::string first = data.front();
    data.pop();

    auto space = first.find( ' ' );
    if (space != std::string::npos)
    {
        _id = (int) std::stoul( first.substr( 0, space ));
        _isCorridor = ( first.substr( space )[ 0 ] == 'C' );
    }
    else
        _id = (int) std::stoul( first );

#ifdef DEBUG
    std::cout << "Room id " << _id << " loading ..." << std::endl;
#endif // DEBUG
}

void Room::LoadJoiningData( std::queue< std::string >& data )
{
    // Load information about joining rooms and doors
    for (int line = 0 ; line < 3 ; ++line)
    {
        std::string doorInfo;
        doorInfo = data.front();
        data.pop();

        std::string id = std::string();
        id.push_back( doorInfo[ 8 ] );
        ( '0' <= doorInfo[ 9 ] && doorInfo[ 9 ] <= '9' ) ? id.push_back( doorInfo[ 9 ] ) : (void) id;

        switch (doorInfo[ 4 ])
        {
            case 'O':
                _joiningDoors[ line ] = new Door( Door::opening, Door::open, (doorInfo.length() == 11 || doorInfo.length() == 12), ( doorInfo[ doorInfo.length() - 1 ] == 'T' ) );
                break;

            case 'C':
                _joiningDoors[ line ] = new Door( Door::chest, (Door::OPEN_TYPES) doorInfo[ 6 ], (doorInfo.length() == 11 || doorInfo.length() == 12),
                                                  ( doorInfo[ doorInfo.length() - 1 ] == 'T' ) );
                id = "0";
                switch (doorInfo[ 8 ])
                {
                    case 'L':
                        _joiningDoors[ line ]->AddObject( (uint8_t) ObjectID::LifePotion );
                        break;
                    case 'W':
                        _joiningDoors[ line ]->AddObject( -1 );
                        break;
                    case 'I':
                        _joiningDoors[ line ]->AddObject( (uint8_t) ObjectID::IronKey );
                        break;
                    default:
                        break;
                }
                break;

            case 'P':
                _joiningDoors[ line ] = new Door( Door::door, (Door::OPEN_TYPES) doorInfo[ 6 ], (doorInfo.length() == 11 || doorInfo.length() == 12),
                                                  ( doorInfo[ doorInfo.length() - 1 ] == 'T' ) );
                break;

            case 'G':
                _joiningDoors[ line ] = new Door( Door::grid, (Door::OPEN_TYPES) doorInfo[ 6 ], (doorInfo.length() == 11 || doorInfo.length() == 12),
                                                  ( doorInfo[ doorInfo.length() - 1 ] == 'T' ) );
                break;

            case 'D':
                _joiningDoors[ line ] = new Door( Door::chimney, Door::open, false, false );
                break;

            case 'M':
            default:
                _joiningDoors[ line ] = new Door( Door::wall, Door::open_impossible, false, false );
                id = "0";
                break;
        }

        _joiningRooms[ line ] = (int) std::stoul( id );

    }
}

void Room::LoadGround( std::queue< std::string >& data )
{
    // Store ground data
    for (int row=0 ; row<ROOM_HEIGHT ; ++row)
    {
        std::string groundInfo = data.front();
        data.pop();

        for (int col=0 ; col<ROOM_WIDTH ; ++col)
        {
            // offset of 4, get only odd numbers
            switch (groundInfo[ 3 + (2*col + 1) ])
            {
                case 'E':
                    _ground[ row ][ col ] = (uint8_t) ObjectID::Egg;
                    break;
                case 'R':
                    _ground[ row ][ col ] = (uint8_t) ObjectID::CursedRing;
                    break;
                case 'Z':
                    _ground[ row ][ col ] = (uint8_t) ObjectID::Hint3;
                    break;
                case 'Y':
                    _ground[ row ][ col ] = (uint8_t) ObjectID::Hint2;
                    break;
                case 'X':
                    _ground[ row ][ col ] = (uint8_t) ObjectID::Hint1;
                    break;
                case 'L':
                    _ground[ row ][ col ] = (uint8_t) ObjectID::LifePotion;
                    break;
                case 'G':
                    _ground[ row ][ col ] = (uint8_t) ObjectID::GoldenKey;
                    break;
                case 'I':
                    _ground[ row ][ col ] = (uint8_t) ObjectID::IronKey;
                    break;
                case 'W':
                    _ground[ row ][ col ] = -1;
                    break;
                case 'M':
                    _ground[ row ][ col ] = -2;
                    break;
                case 'O':
                    _ground[ row ][ col ] = -3;
                    break;
                case 'Q':
                    _ground[ row ][ col ] = -4;
                    break;
                case 'B':
                    _ground[ row ][ col ] = -5;
                    break;
                case 'H':
                    _ground[ row ][ col ] = -6;
                    break;
                case '_':
                default:
                    _ground[ row ][ col ] = (int) ObjectID::Nothing;
                    break;
            }
        }
    }
}

std::string Room::ToString( const Vector2i& position ) const
{
    switch (GetSquare( position ))
    {
        case -6: return "H";
        case -5: return "B";
        case -4: return "Q";
        case -3: return "O";
        case -2: return "M";
        case -1: return "W";
        default: return Object::ToObject( (ObjectID) GetSquare( position ) ).ToString();
    }
}