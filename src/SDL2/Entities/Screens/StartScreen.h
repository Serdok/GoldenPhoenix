//
// Created by serdok on 05/03/19.
//

#ifndef GOLDEN_PHOENIX_STARTSCREEN_H
#define GOLDEN_PHOENIX_STARTSCREEN_H

// Custom headers
#include "Texture.h"


class StartScreen : public Texture
{
private:
    Texture* _startText;
    Texture* _shopText;


public:
    StartScreen();
    ~StartScreen() final;

    void ProcessEvents( SDL_Event* event );

    void Update() final;
    void Render() final;
};


#endif //GOLDEN_PHOENIX_STARTSCREEN_H
