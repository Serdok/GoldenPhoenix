//
// Created by ggeof
//

#ifndef GOLDEN_PHOENIX_TRADER_H
#define GOLDEN_PHOENIX_TRADER_H

// Custom headers
#include "Object.h"
#include "Player.h"


//! Class managing the shop system in the game
class Trader
{
private:
    const int price_Crowbar = 200;
    const int price_GrapplingHook = 250;
    const int price_Torch = 150;
    const int price_LifePotion = 100;

    Player* _player;


public:
    //! Load the trader with a player from the castle
    explicit Trader( Player* player );

    //! Free resources without deleting the Player
    ~Trader();

    /**
     * Purchase an item from its ID
     * @param [in] id_Object The ID of the object
     * @return true if the purchase went through successfully, false otherwise
     */
    bool Purchase( const ObjectID id_Object );

    //! Return the price of an object
    int GetPrice( const ObjectID id_Object );

};


#endif
