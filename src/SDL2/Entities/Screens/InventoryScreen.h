#ifndef GOLDEN_PHOENIX_INVENTORYSCREEN_H
#define GOLDEN_PHOENIX_INVENTORYSCREEN_H

#include "Castle.h"
#include "Texture.h"

class InventoryScreen : public GameEntity
{
private:
    Castle* _castle;


public:
    //! Load the shop from a Castle
    explicit InventoryScreen( Castle* castle );

    //! Free resources without deleting the Castle
    ~InventoryScreen() final;

    //! Process inputs and SDL2 events
    void ProcessEvents( SDL_Event* event );

    //! Update textures and game
    void Update() final;

    //! Render the buffer
    void Render();
};

#endif