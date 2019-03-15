//
// Created by serdok on 09/03/19.
//

#include "GameEntity.h"

GameEntity::GameEntity( const Vector2f& position ) : _position( position ), _active( true ), _parent( nullptr ),
                                                     _rotation( 0.0f ), _scale( VEC2_ONE )
{

}

GameEntity::GameEntity( float x, float y ) : GameEntity( Vector2f( x, y ))
{

}

GameEntity::~GameEntity() = default;

void GameEntity::SetPosition( const Vector2f& position )
{
    _position = position;
}

Vector2f GameEntity::GetPosition( GameEntity::SPACE space ) const
{
    if (space == local || !_parent)
        return _position;

    Vector2f parentScale = _parent->GetScale();
    Vector2f rotation = RotateVector( _position*parentScale, _parent->GetRotation( local ));

    return _parent->GetPosition() + rotation;
}

void GameEntity::Translate( const Vector2f& direction )
{
    _position += direction;
}

void GameEntity::SetRotation( float rotation )
{
    _rotation = rotation;

    if (_rotation >= 360.0f)
        _rotation -= 360.0f;

    if (_rotation < 0.0f)
        _rotation += 360.0f;
}

float GameEntity::GetRotation( GameEntity::SPACE space ) const
{
    if (space == local || !_parent)
        return _rotation;

    return _parent->GetRotation() + _rotation;
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

void GameEntity::SetParent( GameEntity* parent )
{
    if (!parent)
    {
        _position = GetPosition();
        _rotation = GetRotation();
        _scale = GetScale();
    }
    else
    {
        if (_parent)
            SetParent();

        Vector2f parentScale = parent->GetScale();

        _position = RotateVector( GetPosition() - parent->GetPosition(), -parent->GetRotation());
        _position /= parentScale;

        _rotation -= parent->GetRotation();

        _scale /= parentScale;
    }

    _parent = parent;
}

GameEntity* GameEntity::GetParent() const
{
    return _parent;
}

void GameEntity::SetScale( const Vector2f& scale )
{
    _scale = scale;
}

Vector2f GameEntity::GetScale( GameEntity::SPACE space ) const
{
    if (space == local || !_parent)
        return _scale;

    return _parent->GetScale()*_scale;
}

void GameEntity::Update()
{
    // Overridden in derived classes
}

void GameEntity::Render()
{
    // Overridden in derived classes
}