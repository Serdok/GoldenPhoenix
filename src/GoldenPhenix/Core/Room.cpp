//
// Created by serdok on 05/03/19.
//

#include "Room.h"

std::map< int, int > Room::_oblivionLinks;

Room::Room( std::queue< std::string >& data )
: _ground(), _joiningRooms(), _joiningDoors()
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
    //return _ground[ position.y*ROOM_HEIGHT + position.x ];
    return test[ position.y ][ position.x ];
}

int& Room::GetSquare( const Vector2i& position )
{
    // return _ground[ position.y*ROOM_HEIGHT + position.x ];
    return test[ position.y ][ position.x ];
}

Door* const Room::GetDoor( Room::JoiningDirections direction )
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
        _isCorridor = ( first.substr( space )[ 1 ] == 'C' );
    }
    else
        _id = (int) std::stoul( first );
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

        bool hasTorch, torchLit;
        hasTorch = (doorInfo.length() == 11 || doorInfo.length() == 12 || (doorInfo[ doorInfo.length() - 1 ] == 'T' || doorInfo[ doorInfo.length() - 1 ] == 'F'));
        torchLit = hasTorch && (doorInfo[ doorInfo.length() - 1 ] == 'T');


        switch (doorInfo[ 4 ])
        {
            case 'O':
                _joiningDoors[ line ] = new Door( Door::opening, Door::open,
                                                  hasTorch,
                                                  torchLit);
                break;

            case 'C':
                _joiningDoors[ line ] = new Door( Door::chest, (Door::OPEN_TYPES) doorInfo[ 6 ],
                                                  hasTorch,
                                                  torchLit);
                id = "0";
                switch (doorInfo[ 8 ])
                {
                    case 'L':_joiningDoors[ line ]->AddObject((uint8_t) ObjectID::LifePotion );
                        break;
                    case 'W':_joiningDoors[ line ]->AddObject( -1 );
                        break;
                    case 'I':_joiningDoors[ line ]->AddObject((uint8_t) ObjectID::IronKey );
                        break;
                    case 'Y':_joiningDoors[ line ]->AddObject((uint8_t) ObjectID::Hint2 );
                    default:break;
                }
                break;

            case 'P':
                _joiningDoors[ line ] = new Door( Door::door, (Door::OPEN_TYPES) doorInfo[ 6 ],
                                                  hasTorch,
                                                  torchLit);
                break;

            case 'G':
                _joiningDoors[ line ] = new Door( Door::grid, (Door::OPEN_TYPES) doorInfo[ 6 ],
                                                  hasTorch,
                                                  torchLit);
                break;

            case 'D':_joiningDoors[ line ] = new Door( Door::chimney, (Door::OPEN_TYPES) doorInfo[ 6 ], false, false );
                break;

            case 'M':
            default:_joiningDoors[ line ] = new Door( Door::wall, Door::open_impossible, false, false );
                id = "0";
                break;
        }

        if (doorInfo.length() > 8 && id.empty() && (doorInfo[ 8 ] != 'T' && doorInfo[ 8 ] != 'F'))
        {
            id.push_back( doorInfo[ 8 ] );
            if (doorInfo.length() > 9)
                ( '0' <= doorInfo[ 9 ] && doorInfo[ 9 ] <= '9' ) ? id.push_back( doorInfo[ 9 ] ) : (void) id;
        }

        if ((doorInfo.length() == 7) || (id.empty() || id == "0"))
            _joiningRooms[ line ] = 0;
        else
            _joiningRooms[ line ] = (int) std::stoul( id );

    }
}

void Room::LoadGround( std::queue< std::string >& data )
{
    int temp[ ROOM_HEIGHT ][ ROOM_WIDTH ];
    // Store ground data
    for (int x=0 ; x<ROOM_HEIGHT ; ++x)
    {
        std::string groundInfo = data.front();
        data.pop();

        for (int y=0 ; y<ROOM_WIDTH ; ++y)
        {
            // Get oblivion room link (is there is any)
            std::string link = std::string();
            if (groundInfo.length() > 18)
            {
                link.push_back(groundInfo[18]);
                if (groundInfo.length() > 19)
                    link.push_back(groundInfo[19]);
            }

            // offset of 4, get only odd numbers
            switch (groundInfo[ 3 + ( 2*y + 1 ) ])
            {
                case 'E':temp[ x ][ y ] = (uint8_t) ObjectID::Egg;
                    break;
                case 'R':temp[ x ][ y ] = (uint8_t) ObjectID::CursedRing;
                    break;
                case 'Z':temp[ x ][ y ] = (uint8_t) ObjectID::Hint3;
                    break;
                case 'Y':temp[ x ][ y ] = (uint8_t) ObjectID::Hint2;
                    break;
                case 'X':temp[ x ][ y ] = (uint8_t) ObjectID::Hint1;
                    break;
                case 'L':temp[ x ][ y ] = (uint8_t) ObjectID::LifePotion;
                    break;
                case 'G':temp[ x ][ y ] = (uint8_t) ObjectID::GoldKey;
                    break;
                case 'I':temp[ x ][ y ] = (uint8_t) ObjectID::IronKey;
                    break;
                case 'W':temp[ x ][ y ] = -1;
                    break;
                case 'M':temp[ x ][ y ] = -2;
                    break;
                case 'O':temp[ x ][ y ] = -3;
                    break;
                case 'Q':temp[ x ][ y ] = -4;
                    _oblivionLinks[ _id ] = (int) std::stoul(link);
                    break;
                case 'B':temp[ x ][ y ] = -5;
                    break;
                case 'H':temp[ x ][ y ] = -6;
                    break;
                case 'S':temp[ x ][ y ] = -7;
                    break;
                case '_':
                default:temp[ x ][ y ] = (int) ObjectID::Nothing;
                    break;
            }
        }
    }
    
    // Copy loaded data
    for (int x=0 ; x<ROOM_HEIGHT ; ++x)
        for (int y=0 ; y<ROOM_WIDTH ; ++y)
        {
            _ground[ y*ROOM_HEIGHT + x ] = temp[ x ][ y ];
            test[ x ][ y ] = temp[ x ][ y ];
            test2[ y ][ x ] = temp[ x ][ y ];
        }
}

std::string Room::ToString( const Vector2i& position ) const
{
    switch (GetSquare( position ))
    {
        case -7: return "S";
        case -6: return "H";
        case -5: return "B";
        case -4: return "Q";
        case -3: return "O";
        case -2: return "M";
        case -1: return "W";
        default: return Object::ToObject( (ObjectID) GetSquare( position ) ).name;
    }
}

int Room::GetOblivionLink( int id )
{
    auto it = _oblivionLinks.find( id );
    if (it == _oblivionLinks.end())
        return 0;

    return it->second;
}

int Room::GetOblivionOrigin( int id )
{
    for (const auto& link : _oblivionLinks)
        if (link.second == id)
            return link.first;

    return 0;
}

std::queue< std::string > Room::Save() const
{
    std::queue< std::string > data;
    std::string line;

    line.append( std::to_string( _id ) );
    if (_isCorridor)
        line.append( " C" );
    line.append( "\n" );
    data.push( line );

    for (int i=0 ; i<JoiningDirections::TOTAL ; ++i)
    {
        line = GetDoor( (JoiningDirections) i )->Save();
        int link = GetRoomID( (JoiningDirections) i );
        if (link != 0)
            line.insert( 7, " " + std::to_string( link ) );

        line.append( "\n" );
        data.push( line );
    }

    for (int i=0 ; i<ROOM_HEIGHT ; ++i)
    {
        line = "    ";
        bool oblivion = false;
        bool origin = true;
        for (int j = 0 ; j < ROOM_WIDTH ; ++j)
        {
            switch (GetSquare( Vector2i( j, i ) ))
            {
                case -7: line.append( "S" ); break;
                case -6: line.append( "H" ); oblivion = true; origin = false; break;
                case -5: line.append( "B" ); break;
                case -4: line.append( "Q" ); oblivion = true; origin = true; break;
                case -3: line.append( "O" ); break;
                case -2: line.append( "M" ); break;
                case -1: line.append( "W" ); break;
                case ObjectID::Nothing: line.append( "_" ); break;
                case ObjectID::Egg: line.append( "E" ); break;
                case ObjectID::IronKey: line.append( "I" ); break;
                case ObjectID::GoldKey: line.append( "G" ); break;
                case ObjectID::GrapplingHook: line.append( "H" ); break;
                case ObjectID::LifePotion: line.append( "L" ); break;
                case ObjectID::Hint1: line.append( "X" ); break;
                case ObjectID::Hint3: line.append( "Z" ); break;
                case ObjectID::CursedRing: line.append( "R" ); break;
                default: std::cerr << "Missing : " << GetSquare( Vector2i( j, i ) ) << std::endl;
            }
            line.append( " " );
        }
        line.pop_back(); // Remove last space from the line

        if (oblivion)
        {
            if (origin)
                line.append( " " + std::to_string( GetOblivionLink( _id ) ) );
            else if (_id != 666) // Room id 666 is a trap
                line.append( " " + std::to_string( GetOblivionOrigin( _id ) ));
        }

        line.append( "\n" );
        data.push( line );
    }

    return data;
}