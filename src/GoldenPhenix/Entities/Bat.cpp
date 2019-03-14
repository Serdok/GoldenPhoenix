#include "Bat.h"

Bat::Bat():Entity()
{

}

void Bat::Attack(Entity & entity)
{
	entity.AddLife(-15);
}
