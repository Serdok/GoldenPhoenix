#ifndef GOLDEN_PHOENIX_BAT_H
#define GOLDEN_PHOENIX_BAT_H

// Custom headers
#include "Entity.h"


//! Class representing a bat
class Bat : public Entity
{
public:
    Bat();

    ~Bat() override;

    //! Attack an entity
    void Attack( Entity* entity );
};

#endif