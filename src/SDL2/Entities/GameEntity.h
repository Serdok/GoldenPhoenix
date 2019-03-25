//
// Created by serdok on 09/03/19.
//

#ifndef GOLDEN_PHOENIX_GAMEENTITY_H
#define GOLDEN_PHOENIX_GAMEENTITY_H

// Custom headers
#include "Vector2.h"

// SDL2 headers
#include "SDL.h"


//! Class representing a game entity that will not be drawn
class GameEntity
{
private:
    Vector2f _position = VEC2_ZERO;
    float _rotation = 0.0f;
    Vector2f _scale = VEC2_ONE;

    bool _active = true;


public:
    /**
     * Create an entity
     * @param position [in] Initial position of the entity (default : ( 0, 0 ))
     */
    explicit GameEntity( const Vector2f& position = VEC2_ZERO );

    /**
     * Create an entity
     * @param x [in] Initial x coordinate of the entity
     * @param y [in] Initial y coordinate of the entity
     */
    GameEntity( float x, float y );

    virtual ~GameEntity();

    //! Set the entity to a new position
    void SetPosition( const Vector2f& position );

    //! Get the position of the entity
    const Vector2f& GetPosition() const;

    /**
     * Translate the entity
     * @param direction [in] The direction of the translation
     */
    void Translate( const Vector2f& direction );

    //! Set the rotation of the entity
    void SetRotation( float rotation = 0.0f );

    //! Get the rotation of the entity
    float GetRotation() const;

    //! Rotate the entity
    void Rotate( float amount );

    //! Set the active state of the entity
    void SetActive( bool active );

    //! Get the active state of the entity
    bool GetActive() const;

    //! Set the scale of the entity
    void SetScale( const Vector2f& scale );

    //! Get the scale of the entity
    const Vector2f& GetScale() const;

    //! Update the entity. This function should be overridden in derived classes since no update happens here.
    virtual void Update();
};


#endif //GOLDEN_PHOENIX_GAMEENTITY_H
