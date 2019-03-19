//
// Created by serdok on 05/03/19.
//

#ifndef GOLDEN_PHOENIX_CASTLE_H
#define GOLDEN_PHOENIX_CASTLE_H

// Custom headers
#include "Room.h"
#include "Player.h"
#include "Bat.h"


// C++ headers
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>


//! Game manager.
class Castle
{
private:
    std::vector< Room* > _rooms;
    bool _thereIsABat;
    Bat* _bat;
    Player* _player;
    unsigned int _deaths;
    int _score;
    bool _ringIsInInventory=false;
   
public:
    //! Create a castle from a file containing rooms data. Rooms data files must be located in data/rooms/
    Castle( const std::string& filename );

    ~Castle();

    //! Update the game
    void Update();

    void ProcessActions( const std::string& action );

    void PickUp();

    int getScore();

    void setScore( int s );


    const Player* const GetPlayer() const;
    Player* const GetPlayer();
    const Bat* const GetBat() const;
    Bat* const GetBat();

private:

};


#endif //GOLDEN_PHOENIX_CASTLE_H
