#ifndef GOLDEN_PHOENIX_RAT_H
#define GOLDEN_PHOENIX_RAT_H

// Custom headers
#include "Entity.h"


//! Class representing a rat
class Rat : public Entity
{
private:
    bool _active = false;
    bool _visible = false;


public:
    //! Spawn a rat
    Rat( const Vector2i& position );

    //! Kill a rat
    ~Rat() override;

    void Activate();
    void Deactivate();
    bool GetActiveState() const;
    void SetVisible(bool visible);
    bool GetVisible() const;

    //! Make the rat attack an entity
    void Attack( Entity* entity );
};

#endif