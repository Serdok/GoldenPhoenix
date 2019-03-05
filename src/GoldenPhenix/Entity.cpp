#include "Entity.h"

Entity::Entity(){
	life = 1;
	position= Vector2i();
	direction=Vector2i();
}

Entity::Entity(int l, Vector2i p, Vector2i d){
	life = l;
	position = p;
	direction = d;
}

int Entity::getLife()const{
	return life;
}

int Entity::getPosition()const{
	return position;
}

int Entity::getDirection()const{
	return direction;
}

void Entity::setLife(int a){
	life=a;
}

void Entity::AddLife(int a){
	life=life+a;
}

void Entity::setPosition(Vector2i vect){
	position=vect;
}

void Entity::setDirection(Vector2i vect){
	direction=vect;
}