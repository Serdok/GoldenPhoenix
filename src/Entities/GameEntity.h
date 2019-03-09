//
// Created by serdok on 09/03/19.
//

#ifndef GOLDEN_PHOENIX_GAMEENTITY_H
#define GOLDEN_PHOENIX_GAMEENTITY_H

// Custom headers
#include "Vector2.h"


class GameEntity
{
public:
    enum SPACE
    {
        local = 0, world
    };

private:
    Vector2f _position;
    float _rotation;

    bool _active;
    GameEntity* _parent;

    Vector2f _scale;


public:
    explicit GameEntity( const Vector2f& position = VEC2_ZERO );

    GameEntity( float x, float y );

    ~GameEntity();

    void SetPosition( const Vector2f& position );

    Vector2f GetPosition( SPACE space = local ) const;

    void Translate( const Vector2f& direction );


    void SetRotation( float rotation = 0.0f );

    float GetRotation( SPACE space = local ) const;

    void Rotate( float amount );

    void SetActive( bool active );

    bool GetActive() const;

    void SetParent( GameEntity* parent = nullptr );

    GameEntity* GetParent() const;

    void SetScale( const Vector2f& scale );

    Vector2f GetScale( SPACE space = local ) const;

    virtual void Update();

    virtual void Render();
};


#endif //GOLDEN_PHOENIX_GAMEENTITY_H
