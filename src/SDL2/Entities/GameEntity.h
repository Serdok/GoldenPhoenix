//
// Created by serdok on 09/03/19.
//

#ifndef GOLDEN_PHOENIX_GAMEENTITY_H
#define GOLDEN_PHOENIX_GAMEENTITY_H

// Custom headers
#include "Vector2.h"


//! Class representing a game entity. Has physics, but will not be drawn
class GameEntity
{
public:
    //! Space of the object
    enum SPACE
    {
        local = 0, ///< Relative to its parent
        world ///< Relative to the world
    };

private:
    Vector2f _position;
    float _rotation;

    bool _active;
    GameEntity* _parent;

    Vector2f _scale;


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

    //! Set a new position to the entity
    void SetPosition( const Vector2f& position );

    //! Get the position of the entity depending of the space
    Vector2f GetPosition( SPACE space = local ) const;

    //! Move the entity
    void Translate( const Vector2f& direction );

    //! Set a new rotation to the entity
    void SetRotation( float rotation = 0.0f );

    //! Get the rotation of the entity depending of the space
    float GetRotation( SPACE space = local ) const;

    //! Rotate the entity
    void Rotate( float amount );

    //! Set the active state of the entity
    void SetActive( bool active );

    //! Get the active state of the entity
    bool GetActive() const;

    //! Set a new parent to the entity
    void SetParent( GameEntity* parent = nullptr );

    //! Get the parent of the entity
    GameEntity* GetParent() const;

    //! Set the scale of the entity
    void SetScale( const Vector2f& scale );

    //! Get the scale of the entity
    Vector2f GetScale( SPACE space = local ) const;

    //! Update the entity. This function should be overridden in derived classes since no update happens here.
    virtual void Update();

    //! Render the entity. This function should be overridden in derived classes since no render happens here.
    virtual void Render();
};


#endif //GOLDEN_PHOENIX_GAMEENTITY_H
