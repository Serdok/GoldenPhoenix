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


//! Class managing all rendering screens and audio
class ScreensManager
{
public:
    //! List of all the possible screens
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

    SCREENS _currentScreen = start;

    AudioManager* _audio;
    FMOD::Sound* _bgm;

    InputsManager* _inputs;


public:
    // TODO Make this class a singleton to avoid multiple screens managers
    //! Create a screen manager
    ScreensManager();
    ~ScreensManager();

    //! Process SDL2 events no matter what screen the player is on
    void ProcessEvents( SDL_Event* event );

    //! Switch the current screen
    void SwitchCurrentScreen( SDL_Event* event );

    //! Start the current screen. Start the background music of this screen
    void StartCurrentScreen();

    //! Update the current screen
    void Update();

    //! Render the current screen
    void Render();
};

#endif //GOLDEN_PHOENIX_SCREENSMANAGER_H
