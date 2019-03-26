#include "Bat.h"

Bat::Bat( const Vector2i& position )
: Entity( 1, position, VEC2_UP )
{

}

Bat::~Bat() = default;

void Bat::Attack( Entity* entity )
{
    entity->AddLife( -15 );
}


void Bat::Activate()
{
    _active = true;
}

void Bat::Deactivate()
{
    _active = false;
}

bool Bat::GetActiveState() const
{
    return _active;
}