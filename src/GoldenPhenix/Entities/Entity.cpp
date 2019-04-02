#include "Entity.h"

Entity::Entity() = default;

Entity::Entity( int life, const Vector2i& position, const Vector2f& direction )
: _life( life ), _position( position ), _direction( direction )
{

}

Entity::~Entity() = default;

int Entity::GetLife() const
{
    return _life;
}

const Vector2i& Entity::GetPosition() const
{
    return _position;
}

const Vector2f& Entity::GetDirection() const
{
    return _direction;
}

void Entity::SetLife( int a )
{
    _life = a;
}

void Entity::AddLife( int a )
{
    _life += a;
    if(_life >= 100)
    	_life = 100;
}

void Entity::SetPosition( const Vector2i& position )
{
    _position = position;
}

void Entity::SetDirection( const Vector2f& direction )
{
    _direction = direction;
}

void Entity::Translate( const Vector2i& v )
{
    _position += v;
}

void Entity::Update()
{
    // Overridden in derived classes
}