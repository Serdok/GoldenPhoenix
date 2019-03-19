#include "Entity.h"

Entity::Entity()
: _life( 1 ), _position( VEC2_ZERO ), _direction( VEC2_RIGHT )
{

}

Entity::Entity( int life, const Vector2f& position, const Vector2f& direction )
: _life( life ), _position( position ), _direction( direction )
{

}

Entity::~Entity() = default;

int Entity::GetLife() const
{
    return _life;
}

const Vector2f& Entity::GetPosition() const
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
}

void Entity::SetPosition( const Vector2f& position )
{
    _position = position;
}

void Entity::SetDirection( const Vector2f& direction )
{
    _direction = direction;
}

void Entity::Translate( const Vector2f& direction )
{
    _position += direction;
}

void Entity::Update()
{
    // Overridden in derived classes
}