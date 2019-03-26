#ifndef GOLDEN_PHOENIX_BAT_H
#define GOLDEN_PHOENIX_BAT_H

// Custom headers
#include "Entity.h"


//! Class representing a bat
class Bat : public Entity
{
private:
    bool _active = false;


public:
    //! Spawn a bat
    Bat( const Vector2i& position );

    //! Kill a bat
    ~Bat() override;

    void Activate();
    void Deactivate();
    bool GetActiveState() const;

    //! Make the bat attack an entity
    void Attack( Entity* entity );
};

#endif