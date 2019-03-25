//
// Created by serdok on 09/03/19.
//

#include "GameEntity.h"

GameEntity::GameEntity( const Vector2f& position )
: _position( position )
{

}

GameEntity::GameEntity( float x, float y )
: GameEntity( Vector2f( x, y ) )
{

}

GameEntity::~GameEntity() = default;

void GameEntity::SetPosition( const Vector2f& position )
{
    _position = position;
}

const Vector2f& GameEntity::GetPosition() const
{
    return _position;
}

void GameEntity::Translate( const Vector2f& v )
{
    _position += v;
}

void GameEntity::SetRotation( float rotation )
{
    _rotation = rotation;

    if (_rotation >= 360.0f)
        _rotation -= 360.0f;

    if (_rotation < 0.0f)
        _rotation += 360.0f;
}

float GameEntity::GetRotation() const
{
    return _rotation;
}

void GameEntity::Rotate( float amount )
{
    _rotation += amount;
}

void GameEntity::SetActive( bool active )
{
    _active = active;
}

bool GameEntity::GetActive() const
{
    return _active;
}

void GameEntity::SetScale( const Vector2f& scale )
{
    _scale = scale;
}

const Vector2f& GameEntity::GetScale() const
{
    return _scale;
}

void GameEntity::Update()
{
    // Overridden in derived classes
}