//
// Created by serdok on 16/03/19.
//

#ifndef GOLDEN_PHOENIX_SHOPSCREEN_H
#define GOLDEN_PHOENIX_SHOPSCREEN_H

// Custom headers
#include "Castle.h"

#include "Texture.h"



class ShopScreen : public GameEntity
{
private:
    Castle* _castle;

    Texture* _bgi;


public:
    explicit ShopScreen( Castle* castle );
    ~ShopScreen() final;

    void ProcessEvents( SDL_Event* event );

    void Update() final;
    void Render() final;
};

#endif //GOLDEN_PHOENIX_SHOPSCREEN_H
