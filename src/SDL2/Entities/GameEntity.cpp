//
// Created by serdok on 09/03/19.
//

#include "GameEntity.h"

GameEntity::GameEntity( const Vector2f& position )
: _position( position ), _active( true ), _rotation( 0.0f ), _scale( VEC2_ONE )
{

}

GameEntity::GameEntity( float x, float y )
: GameEntity( Vector2f( x, y ) )
{

}

GameEntity::~GameEntity() = default;

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

void GameEntity::Render()
{
    // Overridden in derived classes
}