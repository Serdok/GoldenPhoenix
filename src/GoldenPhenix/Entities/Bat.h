#ifndef GOLDEN_PHOENIX_BAT_H
#define GOLDEN_PHOENIX_BAT_H

#include "Entity.h"
#include "Vector2.h"

class Bat : public Entity
{
public:
    Bat();

    void Attack( Entity* entity );

};

#endif