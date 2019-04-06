#include "Rat.h"

Rat::Rat( const Vector2i& position )
: Entity( 1, position, VEC2_RIGHT)
{

}

Rat::~Rat() = default;

void Rat::Attack( Entity* entity )
{
    entity->AddLife( -10 );
}


void Rat::Activate()
{
    _active = true;
}

void Rat::Deactivate()
{
    _active = false;
}

bool Rat::GetActiveState() const
{
    return _active;
}

void Rat::SetVisible(bool visible)
{
    _visible = visible;
}

bool Rat::GetVisible() const
{
    return _visible;
}