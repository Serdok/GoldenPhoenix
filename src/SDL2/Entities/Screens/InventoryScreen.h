#ifndef GOLDEN_PHOENIX_INVENTORYSCREEN_H
#define GOLDEN_PHOENIX_INVENTORYSCREEN_H

// Custom headers
#include "Castle.h"
#include "InputsManager.h"
#include "Texture.h"

// C++ headers
#include <map>


class InventoryScreen : public GameEntity
{
private:
    Castle* _castle;

    InputsManager* _inputs;

    // Object textures
    std::map< ObjectID, Texture* > _textures;

    int _cursor = 0;


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