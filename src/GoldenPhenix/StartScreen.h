//
// Created by serdok on 05/03/19.
//

#ifndef GOLDEN_PHOENIX_STARTSCREEN_H
#define GOLDEN_PHOENIX_STARTSCREEN_H

// Custom headers
#include "AudioManager.h"
#include "Cleanup.h"
#include "Timer.h"
#include "Texture.h"


class StartScreen
{
private:
    AudioManager* _audio;
    Timer* _timer;

    FMOD::Sound* _bgm;

    SDL_Texture* _bgi;

    TTF_Font* _font;
    SDL_Texture* _startText;
    SDL_Rect _startTextDestination;

    SDL_Texture* _shopText;
    SDL_Rect _shopTextDestination;


public:
    StartScreen();
    ~StartScreen();

    void ProcessEvents( SDL_Event* event );
    void Update();
    void Render();
};


#endif //GOLDEN_PHOENIX_STARTSCREEN_H
