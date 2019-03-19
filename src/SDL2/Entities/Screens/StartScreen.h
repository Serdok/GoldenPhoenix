//
// Created by serdok on 05/03/19.
//

#ifndef GOLDEN_PHOENIX_STARTSCREEN_H
#define GOLDEN_PHOENIX_STARTSCREEN_H

// Custom headers
#include "Castle.h"

#include "AnimatedTexture.h"
#include "InputsManager.h"


class StartScreen : public Texture
{
private:
    Castle* _castle;

    InputsManager* _inputs;

    Texture* _startText;
    Texture* _shopText;

    AnimatedTexture* _player;


public:
    explicit StartScreen( Castle* castle );
    ~StartScreen() final;

    void ProcessEvents( SDL_Event* event );

    void Update() final;
    void Render() final;
};


#endif //GOLDEN_PHOENIX_STARTSCREEN_H
