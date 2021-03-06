//
// Created by serdok on 16/03/19.
//

#ifndef GOLDEN_PHOENIX_SCREENSMANAGER_H
#define GOLDEN_PHOENIX_SCREENSMANAGER_H

// Custom headers
#include "IntroScreen.h"
#include "StartScreen.h"
#include "ShopScreen.h"
#include "MainScreen.h"
#include "InventoryScreen.h"
#include "PauseScreen.h"
#include "EndScreen.h"

#include "Translation.h"

#include "AudioManager.h"


//! Class managing all rendering screens and audio
class ScreensManager
{
public:
    //! List of all the possible screens
    enum SCREENS
    {
        intro,  ///< Intro screen, represented by the IntroScreen class
        start,  ///< Start screen, represented by the StartScreen class
        shop,   ///< Shop screen, represented by the ShopScreen class
        main,    ///< Main screen, represented by the MainScreen class
        inventory, ///< Inventory screen, represented by the InventoryScreen class
        pause,    ///< Pause screen, represented by the PauseScreen class
        end    ///< End screen, represented by the EndScreen class
    };

private:
    Castle* _castle;
    
    IntroScreen* _introScreen;

    StartScreen* _startScreen;
    ShopScreen* _shopScreen;
    MainScreen* _mainScreen;
    InventoryScreen* _inventoryScreen;
    PauseScreen* _pauseScreen;
    EndScreen* _endScreen;

    Translation* _translation;

    SCREENS _currentScreen = intro;

    AudioManager* _audio;
    bool _musicPaused = false;
    InputsManager* _inputs;


public:
    // TODO Make this class a singleton to avoid multiple screens managers
    //! Create a screen manager
    ScreensManager();

    //! Free resources, delete all associated screens
    ~ScreensManager();

    //! Process SDL2 events no matter what screen the player is on
    void ProcessEvents( SDL_Event* event );

    //! Update the current screen
    void Update();

    //! Render the current screen
    void Render();

private:
    //! Switch the current screen
    void SwitchCurrentScreen( SDL_Event* event );

    //! Start the current screen. Start the background music of this screen
    void StartCurrentScreen();
};

#endif //GOLDEN_PHOENIX_SCREENSMANAGER_H
