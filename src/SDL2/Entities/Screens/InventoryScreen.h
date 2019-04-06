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

    int _selected = ObjectID::Egg;

    Texture* _score = nullptr;
    Texture* _money = nullptr;

    const int offset = 50; // in pixels
    const int WIDTH = Graphics::SCREEN_WIDTH - 2*offset; // in pixels
    const Vector2i coordinates[ ObjectID::TOTAL - 1 ] = {
            Vector2i( WIDTH/7, 2.0f*offset ), Vector2i( 2*WIDTH/7, 2.0f*offset ), Vector2i( 3*WIDTH/7, 2.0f*offset ), Vector2i( 4*WIDTH/7, 2.0f*offset ), Vector2i( 5*WIDTH/7, 2.0f*offset ), Vector2i( 6*WIDTH/7, 2.0f*offset ),
            Vector2i( WIDTH/6, 5.5f*offset ), Vector2i( 2*WIDTH/6, 5.5f*offset ), Vector2i( 3*WIDTH/6, 5.5f*offset ), Vector2i( 4*WIDTH/6, 5.5f*offset ), Vector2i( 5*WIDTH/6, 5.5f*offset )
    };



public:
    //! Load the shop from a Castle
    explicit InventoryScreen( Castle* castle, Translation* trans );

    //! Free resources without deleting the Castle
    ~InventoryScreen() final;

    void SetTranslation( Translation* translation );

    //! Process inputs and SDL2 events
    void ProcessEvents( SDL_Event* event );

    //! Update textures and game
    void Update() final;

    //! Render the buffer
    void Render();

private:
    void ActivateItems();
    void SelectItem();
    void UpdateNumbers( const ItemStack& item );

    void UpdateLanguage();
};

#endif