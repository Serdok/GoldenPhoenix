//
// Created by serdok on 05/03/19.
//

#ifndef GOLDEN_PHOENIX_ROOM_H
#define GOLDEN_PHOENIX_ROOM_H

// Custom headers
#include "Door.h"


// SDL2 headers


// FMod headers


// C++ headers



// Enums
//! List of the possible ground items
enum GROUND : char
{
    wall = 'M',
    nothing = '_',
    oblivion = 'O',
    oblivion_room = 'Q',
    iron_key = 'I',
    golden_key = 'G',
    use_grappling_hook = 'H',
    life_potion = 'L',
    bat = 'B',
    money = 'W',
    hint_1 = 'X',
    hint_2 = 'Y',
    hint_3 = 'Z'
};


// Constants
const int ROOM_WIDTH = 7;
const int ROOM_HEIGHT = 6;


//! Class holding all information about a room in the castle
class Room
{
public:
    //! List of the possible room dispositions
    enum ROOMS
    {
        room = 0, ///< Classic room
        corridor ///< Corridor room
    };

private:
    int _id;
    ROOMS _type;
    GROUND _items[ ROOM_WIDTH ][ ROOM_HEIGHT ];
    bool _lit;
    // Player* _player;
    // Bat* _bat;
    Door* _leftDoor;
    Door* _upperDoor;
    Door* _rightDoor;


public:
    Room( const std::vector< char >& info );
    ~Room();

    // void AttachPlayer( Player* player );

    void LoadRoom();
    void SaveRoom();

    void Update();
    void Render();

private:

};


#endif //GOLDEN_PHOENIX_ROOM_H
