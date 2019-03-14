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


const int NUM_ROOMS = 2;


//! Game manager.
class Castle
{
private:
    std::array< Room*, NUM_ROOMS > _rooms;
    bool _thereIsABat;
    Bat bat;
    Player player;

public:
    Castle( const std::string& filename );
    ~Castle();
    void Update();
    void movePLeft();
    void movePRight();
    void movePUp();
    void movePDown();
    void PickUp();


private:

};


#endif //GOLDEN_PHOENIX_CASTLE_H
