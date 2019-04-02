#ifndef GOLDEN_PHOENIX_INVENTORYSCREEN_H
#define GOLDEN_PHOENIX_INVENTORYSCREEN_H

// Custom headers
#include "Castle.h"
#include "InputsManager.h"
#include "Texture.h"
#include "Translation.h"

// C++ headers
#include <map>


class InventoryScreen : public GameEntity
{
private:
    Castle* _castle;

    InputsManager* _inputs;

    Translation* _translation;

    // Object textures
    std::map< ObjectID, Texture* > _textures;
    std::map< ObjectID, Texture* > _names;
    std::map< ObjectID, Texture* > _numbers;
    std::map< ObjectID, Texture* > _descriptions;

    Texture* _score;
    Texture* _money;



public:
    //! Load the shop from a Castle
    explicit InventoryScreen( Castle* castle, Translation* trans );

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