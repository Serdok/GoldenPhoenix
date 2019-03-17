//
// Created by serdok on 16/03/19.
//

#ifndef GOLDEN_PHOENIX_SCREENSMANAGER_H
#define GOLDEN_PHOENIX_SCREENSMANAGER_H

// Custom headers
#include "StartScreen.h"
#include "ShopScreen.h"
#include "MainScreen.h"

#include "AudioManager.h"


class ScreensManager
{
public:
    enum SCREENS
    {
        start,
        shop,
        main
    };

private:
    Castle* _castle;

    StartScreen* _startScreen;
    ShopScreen* _shopScreen;
    MainScreen* _mainScreen;

    SCREENS _currentScreen;

    AudioManager* _audio;
    FMOD::Sound* _bgm;


public:
    ScreensManager();
    ~ScreensManager();

    void ProcessEvents( SDL_Event* event );
    void Update();
    void Render();
};

#endif //GOLDEN_PHOENIX_SCREENSMANAGER_H
