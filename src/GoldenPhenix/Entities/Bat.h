#ifndef GOLDEN_PHOENIX_BAT_H
#define GOLDEN_PHOENIX_BAT_H

// Custom headers
#include "Entity.h"


//! Class representing a bat
class Bat : public Entity
{
public:
    //! Spawn a bat
    Bat();

    //! Kill a bat
    ~Bat() override;

    //! Make the bat attack an entity
    void Attack( Entity* entity );
};

#endif