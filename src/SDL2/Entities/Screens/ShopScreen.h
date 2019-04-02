//
// Created by serdok on 16/03/19.
//

#ifndef GOLDEN_PHOENIX_SHOPSCREEN_H
#define GOLDEN_PHOENIX_SHOPSCREEN_H

// Custom headers
#include "Castle.h"
#include "Trader.h"
#include "Translation.h"

#include "Texture.h"
#include "InputsManager.h"


//! Class rendering the shop
class ShopScreen : public Texture
{
private:

    Castle* _castle;

    Translation* _translation;

    Trader* _trader;

    InputsManager* _inputs;

    Texture* _crowbar;
    Texture* _grapplingHook;
    Texture* _torch;
    Texture* _lifePotion;

    Texture* _price_Crowbar;
    Texture* _price_GrapplingHook;
    Texture* _price_Torch;
    Texture* _price_LifePotion;
    Texture* _money;


public:
    //! Load the shop from a Castle
    explicit ShopScreen( Castle* castle, Translation* trans );

    //! Free resources without deleting the Castle
    ~ShopScreen() final;

    //! Process inputs and SDL2 events
    void ProcessEvents( SDL_Event* event );

    //! Update textures and game
    void Update() final;

    //! Render the buffer
    void Render() final;
};

#endif //GOLDEN_PHOENIX_SHOPSCREEN_H
