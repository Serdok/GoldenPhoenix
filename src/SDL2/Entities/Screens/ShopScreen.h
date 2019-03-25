//
// Created by serdok on 16/03/19.
//

#ifndef GOLDEN_PHOENIX_SHOPSCREEN_H
#define GOLDEN_PHOENIX_SHOPSCREEN_H

// Custom headers
#include "Castle.h"

#include "Texture.h"


//! Class rendering the shop
class ShopScreen : public Texture
{
private:
    Castle* _castle;


public:
    //! Load the shop from a Castle
    explicit ShopScreen( Castle* castle );

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
