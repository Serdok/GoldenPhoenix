#ifndef GOLDEN_PHOENIX_PLAYER_H
#define GOLDEN_PHOENIX_PLAYER_H

#include "Entity.h"
#include "Inventory.h"
#include <map>

using Action = void (*)();//Name all void function without parameters as Action

//Create a class Player heir of class Entity
class Player : public Entity{
	private:	
		int life;//The player has life points
		Vector2<int> position;//The player has a position in game defined by a 2-dimentional vector
		Vector2<int> direction;//The player can head to a direction defined by a 2-dimentional vector
		int score;//The player has score points
		int money;//The player has money
		Inventory * inventory;//The player has an inventory 
		OBJECTS hand;//The player can hold an object
		std::map<int, Action> keyActions;//Associate an integer to an action 

		void HeadLeft();//1 : The player is facing left
		void HeadRight();//2 : The player is facing right
		void HeadUp();//3 : The player is facing up
		void HeadDown();//4 : The player is facing down
		void MoveLeft();//5 : Allow the player to move to the left
		void MoveRight();//6 : Allow the player to move to the right
		void MoveUp();//7 : Allow the player to move up
		void MoveDown();//8 : Allow the player to move down
		void Jump();//9 : Allow the player to jump
		void LongJump();//10 : Allow the player to make long jumps
		void PickUp();//11 : Allow the player to pick up objects
		void Use();//12 : Allow the player to use objects
		void PutInHand();//13 : Allow the player to put an object in his/her hand
		void Open();//14 : Allow the player to open doors, chests and fireplaces
		void AssociateKeyActions();//Associate an action with a key

	public:
		Player();//Set the score and money at 0,, the life at 1, the direction and position vectors at (0,0), and the object in hand at 0
		Player(int s, int m, OBJECTS h, int l, Vector2i p, Vector2i d);//Set the score, money and life at given parameters s, m and l, the object in hand at given parameters an object defined by h, and the position and direction at given parameters p and d
		~Player();//Destroy the inventory
		OBJECTS getHand()const;//Return an integer associated to an object that is in the hand
		void setHand(OBJECTS o);//Set an object in the player's hand
		int getMoney()const;//Return the money owned by the player
		void setMoney(int m);//Set the money at "m"
		int getScore()const;//Return the player's score points
		void setScore(int s);//Set the score at "s"
		Action getAction(int a)const;//Return the action to do regarding "a"
		void AddMoney(int m);//Add "m" money to the current amount

}

#endif