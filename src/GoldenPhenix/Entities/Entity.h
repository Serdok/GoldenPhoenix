#ifndef GOLDEN_PHOENIX_ENTITY_H
#define GOLDEN_PHOENIX_ENTITY_H

// Custom headers
#include "Vector2.h"


//! Class representing a living entity.
class Entity
{
protected:
    int _life; ///< Life of the entity
    Vector2f _position; ///< Position of the entity
    Vector2f _direction; ///< Direction of the eyes of the entity

public:
    //! Default constructor : set life to 1, position to the origin and direction to the right
    Entity();

    //! Set life, position and direction to specific values.
    Entity( int life, const Vector2f& position, const Vector2f& direction );

    virtual ~Entity();

    //! Getter for the life
    int GetLife() const;

    //! Setter for the life
    void SetLife( int a );

    //! Adds the current life by a given amount
    void AddLife( int a );

    //! Getter for the position
    const Vector2f& GetPosition() const;

    //! Setter for the position
    void SetPosition( const Vector2f& position = VEC2_ZERO );

    //! Translate by a certain amount
    void Translate( const Vector2f& direction );

    // Getter for the direction
    const Vector2f& GetDirection() const;

    //! Setter for the direction
    void SetDirection( const Vector2f& direction = VEC2_RIGHT );

    //! Update the entity. This function should be overridden in derived classes since no update happens here.
    virtual void Update();

    //! Render the entity. This function should be overridden in derived classes since no render happens here.
    virtual void Render();
};


#endif