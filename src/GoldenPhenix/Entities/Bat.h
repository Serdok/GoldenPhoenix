#ifndef GOLDEN_PHOENIX_BAT_H
#define GOLDEN_PHOENIX_BAT_H

// Custom headers
#include "Entity.h"


class Bat : public Entity
{
public:
    Bat();

    ~Bat() override;

    void Attack( Entity* entity );
};

#endif