//
// Created by ggeof
//

#include "Trader.h"

Trader::Trader(Player * playerb)
{
	player = playerb;
}

Trader::~Trader()
{
	delete player;
}

bool Trader::Purchase(const int id_Object)
{
	Object object = Object::ToObject((ObjectID) id_Object );
	int price;
	switch (id_Object){
		case 2 :
			price = price_Crowbar;
			break;
		case 5 :
			price = price_GrapplingHook;
			break;
		case 6 :
			price = price_Torch;
			break;
		case 7 :
			price = price_LifePotion;
			break;
	}
	if((player->getMoney()-price) >= 0)
	{
		player->AddItem(object);
		player->AddMoney(-price);
		return true;
	}	
	else
		return false;	
}

int Trader::getPrice(const int id_Object){
	switch (id_Object){
		case 2 :
			return price_Crowbar;
		case 5 :
			return price_GrapplingHook;
		case 6 :
			return price_Torch;
		case 7 :
			return price_LifePotion;
		default:
			return 0;
	}

}