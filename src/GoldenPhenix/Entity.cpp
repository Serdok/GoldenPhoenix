#include "Entity.h"

Entity::Entity() : _life( 1 ), _position( Vector2i()), _direction( Vector2i())
{

}

Entity::Entity( int life, const Vector2i& position, const Vector2i& direction ) : _life( life ), _position( position ),
                                                                                  _direction( direction )
{

}

int Entity::getLife() const
{
    return _life;
}

Vector2i Entity::getPosition() const
{
    return _position;
}

Vector2i Entity::getDirection() const
{
    return _direction;
}

void Entity::setLife( int a )
{
    _life = a;
}

void Entity::AddLife( int a )
{
    _life += a;
}

void Entity::setPosition( const Vector2i& position )
{
    _position = position;
}

void Entity::setDirection( const Vector2i& direction )
{
    _direction = direction;
}