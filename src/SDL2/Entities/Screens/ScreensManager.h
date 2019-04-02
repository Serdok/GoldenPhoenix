//
// Created by serdok on 16/03/19.
//

#ifndef GOLDEN_PHOENIX_SCREENSMANAGER_H
#define GOLDEN_PHOENIX_SCREENSMANAGER_H

// Custom headers
#include "StartScreen.h"
#include "ShopScreen.h"
#include "MainScreen.h"
#include "InventoryScreen.h"
#include "PauseScreen.h"

#include "AudioManager.h"


//! Class managing all rendering screens and audio
class ScreensManager
{
public:
    //! List of all the possible screens
    enum SCREENS
    {
        start,  ///< Start screen, represented by the StartScreen class
        shop,   ///< Shop screen, represented by the ShopScreen class
        main,    ///< Main screen, represented by the MainScreen class
        inventory, ///< Inventory screen, represented by the InventoryScreen class
        pause   
    };

private:
    Castle* _castle;

    StartScreen* _startScreen;
    ShopScreen* _shopScreen;
    MainScreen* _mainScreen;
    InventoryScreen* _inventoryScreen;
    PauseScreen* _pauseScreen;

    SCREENS _currentScreen = start;

    AudioManager* _audio;
    FMOD::Sound* _bgm;

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
