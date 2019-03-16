#include "Bat.h"

Bat::Bat() = default;
Bat::~Bat() = default;

void Bat::Attack( Entity* entity )
{
    entity->AddLife( -15 );
}
