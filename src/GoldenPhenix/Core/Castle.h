//
// Created by serdok on 05/03/19.
//

#ifndef GOLDEN_PHOENIX_CASTLE_H
#define GOLDEN_PHOENIX_CASTLE_H

// Custom headers
#include "Exceptions.h"
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
    unsigned int _score;
    unsigned int _money;

public:
    //! Create a castle from a file containing rooms data. Rooms data files must be located in data/rooms/
    Castle( const std::string& filename );

    ~Castle();

    //! Update the game
    void Update();

    void movePLeft();

    void movePRight();

    void movePUp();

    void movePDown();

    void PickUp();

    int getScore();

    void setScore( int s );

    int getMoney();

    void setMoney( int m );

private:

};


#endif //GOLDEN_PHOENIX_CASTLE_H
