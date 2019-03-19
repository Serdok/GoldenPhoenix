//
// Created by ggeof
//

#ifndef GOLDEN_PHOENIX_TRADER_H
#define GOLDEN_PHOENIX_TRADER_H

#include "Object.h"
#include "Player.h"
 
#include <iostream>
#include <utility>

class Trader
{
	private :
		const int price_Crowbar = 200;
		const int price_GrapplingHook = 300;
		const int price_Torch = 150;
		const int price_LifePotion = 100;

		Player* player;

	public :
		Trader(Player * playerb);
		~Trader();

		// Function for purchase objet in the trade
		// Return true if purchasing is possible 
		// False else
		bool Purchase(const int id_object);
		int getPrice(const int id_Object);

};


#endif
