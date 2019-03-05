#include "Player.h"

Player::Player(){
	score=0;
	money=0;
	hand=0;
	life=1;
	position=Vector2i();
	direction=Vector2i();
	AssociateKeyActions();
	inventory = new Inventory( this );
}

Player::Player(int s, int m, OBJECTS h, int l, Vector2i p, Vector2i d){
	score=s;
	money=m;
	hand=h;
	life=l;
	position=p;
	direction=d;
	AssociateKeyActions();
	inventory = new Inventory( this );
}

Player::~Player(){
	delete inventory;
}

void AssociateKeyActions(){
	keyActions[1]=HeadLeft;
	keyActions[2]=HeadRight;
	keyActions[3]=HeadUp;
	keyActions[4]=HeadDown;
	keyActions[5]=MoveLeft;
	keyActions[6]=MoveRight;
	keyActions[7]=MoveUp;
	keyActions[8]=MoveDown;
	keyActions[9]=Jump;
	keyActions[10]=LongJump;
	keyActions[11]=PickUp;
	keyActions[12]=Use;
	keyActions[13]=PutInHand;
	keyActions[14]=Open;
}

OBJECTS Player::getHand()const{
	return hand;
}

int Player::getMoney()const{
	return money;
}

int Player::getScore()const{
	return score;
}

void Player::setHand(OBJECTS o){
	hand=o;
}

void Player::setMoney(int m){
	money=m;
}

void Player::setScore(int s){
	score=s;
}

void Player::AddMoney(int m){
	money=money+m;
}

void Player::HeadLeft(){
	direction = VEC2_LEFT;
}

void Player::MoveLeft(){
	position += VEC2_LEFT;
}

void Player::HeadRight(){
	direction = VEC2_RIGHT
}

void Player::MoveRight(){
	position += VEC2_RIGHT;
}

void Player::HeadUp(){
	direction = VEC2_UP;
}

void Player::MoveUp(){
	position += VEC2_UP;
}

void Player::HeadDown(){
	direction = VEC2_DOWN;
}

void Player::MoveDown(){
	position += VEC2_DOWN;
}

void Player::Jump(){

}

void Player::LongJump(){
	position += 2 * direction;
}

void Player::PickUp(){

}

void Player::Use(){

}

void Player::PutInHand(){

}

void Player::Open(){

}

Action Player::getAction(int a)const{

}