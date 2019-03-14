#ifndef GOLDEN_PHOENIX_ENTITY_H
#define GOLDEN_PHOENIX_ENTITY_H

#include "Vector2.h"


//! Class representing a game entity.
class Entity
{
protected:
    int _life; ///< Life of the entity
    Vector2i _position; ///< Position of the entity
    Vector2i _direction; ///< Direction of the eyes of the entity

public:
    //! Default constructor : set life to 1, position and direction to 0
    Entity();

    //! Set life, position and direction to specific values.
    Entity( int life, const Vector2i& position, const Vector2i& direction );

    //! Getter for the life
    int getLife() const;

    //! Setter for the life
    void setLife( int a );

    //! Adds the current life by a given amount
    void AddLife( int a );

    //! Getter for the position
    Vector2i getPosition() const;

    //! Setter for the position
    void setPosition( const Vector2i& position );

    // Getter for the direction
    Vector2i getDirection() const;

    //! Setter for the direction
    void setDirection( const Vector2i& direction );

    void Move(Vector2i p);
};


#endif