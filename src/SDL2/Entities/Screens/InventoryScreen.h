#ifndef GOLDEN_PHOENIX_INVENTORYSCREEN_H
#define GOLDEN_PHOENIX_INVENTORYSCREEN_H

// Custom headers
#include "Castle.h"
#include "InputsManager.h"
#include "Texture.h"


class InventoryScreen : public GameEntity
{
private:
    Castle* _castle;

    InputsManager* _inputs;

    // Object textures
    Texture* _ironKey;
    Texture* _goldKey;
    Texture* _lifePotion;
    Texture* _grapplingHook;
    Texture* _egg;
    Texture* _hint;
    Texture* _crowbar;
    Texture* _torch;

    Texture* _select;
    Vector2i _position;

    int _items;
    int* _itemIDs;


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