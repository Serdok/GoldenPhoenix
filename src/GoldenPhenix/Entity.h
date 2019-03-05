#ifndef GOLDEN_PHOENIX_ENTITY_H
#define GOLDEN_PHOENIX_ENTITY_H

#include "Vector2.h"

//Create a class Entity
class Entity{
	protected:
		int life;//The entity has life points
		Vector2<int> position;//The entity has a position defined by a 2-dimentional vector 
		Vector2<int> direction;//The entity can head to a direction defined by a 2-dimentional vector

	public:
		Entity();//Set the life points at 1, and the position and direction vectors at (0,0)
		Entity(int l, Vector2i p,Vector2i d);//Set the life points at the given parameter l, and the position and direction at the given parameters p and d
		int getLife()const; //Return the life points of the entity
		void setLife(int a); //Set the life points at "a"
		void AddLife(int a); //Add "a" life points to the current life points
		int getPosition()const; //Return the position vector of the entity
		void setPosition(Vector2<int> vect);//Set the position of the entity at vector vect
		int getDirection()const;//Return the direction vector of the entity
		void setDirection(Vector2<int> vect);//Set the direction of the entity at vector vect
}


#endif