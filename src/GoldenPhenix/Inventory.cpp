#include "Inventory.h"


Inventory::Inventory(Player * p){
	player=p;	

	objects[1]=0;
	effects[1]=Crowbar;

	objects[4]=0;
	effects[4]=GrapplingHook;

	objects[5]=0;
	effects[5]=Torch;

	objects[6]=0;
	effects[6]=LifePotion;
}

Inventory::~Inventory(){
	player=NULL;
}

void Inventory::LifePotion(){
	p->AddLife(90);
	Consume(6);
}

void Inventory::GrapplingHook(){

	Consume(4);
}

void Inventory::Torch(){

	Consume(5);
}

void Inventory::Crowbar(){

	Consume(1);
}

void Inventory::Consume(OBJECTS o){
	objects[o] -= 1;
}

int Inventory::ItemsLeft(OBJECTS o){
	return objects[o];
}

Effect Inventory::getEffect(OBJECTS o)const{

}