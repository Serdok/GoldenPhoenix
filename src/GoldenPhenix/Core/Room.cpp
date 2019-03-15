//
// Created by serdok on 05/03/19.
//

#include "Room.h"

Room::Room( std::queue< std::string >& data )
: _id( 0 ), _isCorridor( false )
{
    // Each room has 10 lines describing them
    if (data.size() != 10)
        throw Exception( "A room failed to load!", __FILE__, __LINE__ );

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

    // std::cout << "Room id " << _id << " loading ..." << std::endl;

    // Load information about joining rooms and doors
    for (int line = 0 ; line < 3 ; ++line)
    {
        std::string doorInfo;
        doorInfo = data.front();
        data.pop();


        std::string id;
        id.push_back( doorInfo[ 8 ] );
        ( '0' <= doorInfo[ 9 ] && doorInfo[ 9 ] <= '9' ) ? id.push_back( doorInfo[ 9 ] ) : (void) id;

        switch (doorInfo[ 4 ])
        {
            case 'O':_joiningDoors[ line ] = new Door( Door::opening, Door::open, (doorInfo.length() == 11 || doorInfo.length() == 12), ( doorInfo[ doorInfo.length() - 1 ] == 'T' ) );
                break;

            case 'C':
                _joiningDoors[ line ] = new Door( Door::chest, (Door::OPEN_TYPES) doorInfo[ 6 ], (doorInfo.length() == 11 || doorInfo.length() == 12),
                                                  ( doorInfo[ doorInfo.length() - 1 ] == 'T' ) );
                break;

            case 'D':
                _joiningDoors[ line ] = new Door( Door::door, (Door::OPEN_TYPES) doorInfo[ 6 ], (doorInfo.length() == 11 || doorInfo.length() == 12),
                                                  ( doorInfo[ doorInfo.length() - 1 ] == 'T' ) );
                break;

            case 'G':
                _joiningDoors[ line ] = new Door( Door::grid, (Door::OPEN_TYPES) doorInfo[ 6 ], (doorInfo.length() == 11 || doorInfo.length() == 12),
                                                  ( doorInfo[ doorInfo.length() - 1 ] == 'T' ) );
                break;

            case 'F':_joiningDoors[ line ] = new Door( Door::chimney, Door::open, false, false );
                break;

            case 'M':
            default:_joiningDoors[ line ] = new Door( Door::wall, Door::open_impossible, false, false );
        }

        _joiningRooms[ line ] = (int) std::stoul( id );

    }

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
                    _ground[ row ][ col ] = (int) Object::EGG.ToObjectID();
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

    // std::cout << "Room id : " << _id << " loading done!" << std::endl;
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

int Room::GetSquare( const Vector2i& position ) const
{
    return _ground[ position.x ][ position.y ];
}

int& Room::GetSquare( const Vector2i& position )
{
    return _ground[ position.x ][ position.y ];
}