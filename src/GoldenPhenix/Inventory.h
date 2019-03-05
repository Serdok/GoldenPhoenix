#include <map>
#include "Player.h"

using Effect = void (*)();//Name all void function without parameters as Effect

//Defined the objects
enum OBJECTS{
	NOTHING = 0;
	CROWBAR = 1;
	IRON_KEY = 2;
	GOLDEN_KEY = 3;
	GRAPPLING_HOOK = 4;
	TORCH = 5;
	LIFE_POTION = 6;
	HINT_1 = 7;
	HINT_2 = 8;
	HINT_3 = 9;
	CURSED_RING = 10;
	EGG = 11;
}

//Create a class Inventory
class Inventory{
	private:
		std::map<OBJECTS, int> objects;//Associate an object to an integer that represents the amount of a certain object that the player has
		std::map<OBJECTS, Effect> effects;//Associate an object to an effect
		Player * player;//Create a pointer on the player

		void LifePotion();//Add life points, consume a life potion
		void GrapplingHook();//Allow to go up a level(from the underground to the ground floor, and from the ground floor the the first floor), consume a grappling hook
		void Torch();//Allow to have light, durability is dropping
		void Crowbar();//Allow to open some doors and chests, durability is dropping

	public:
		Inventory(Player * p);//Set the amount of some objects(torch, life potion, crowbar, grappling hook) to 0, and their effects  
		~Inventory();
		void Consume(OBJECTS o);//Consume an object
		int ItemsLeft(OBJECTS o);//Return the amount of objects the player has
		Effect getEffect(OBJECTS o)const;//Return the effect regarding the object "o"

}