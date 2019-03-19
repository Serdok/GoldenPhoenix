//
// Created by serdok on 09/03/19.
//

#ifndef GOLDEN_PHOENIX_GAMEENTITY_H
#define GOLDEN_PHOENIX_GAMEENTITY_H

// Custom headers
#include "Entity.h"


//! Class representing a game entity that will not be drawn
class GameEntity : public Entity
{
public:

private:
    Vector2f _position;
    float _rotation;
    Vector2f _scale;

    bool _active;


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

    ~GameEntity() override;

    void SetRotation( float rotation = 0.0f );

    //! Get the rotation of the entity depending of the space
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
    void Update() override;
};


#endif //GOLDEN_PHOENIX_GAMEENTITY_H
