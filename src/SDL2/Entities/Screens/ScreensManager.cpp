//
// Created by serdok on 16/03/19.
//

#include "ScreensManager.h"

ScreensManager::ScreensManager()
{
    _castle = new Castle( GetResourcePath( "rooms/room.room" ));

    _startScreen = new StartScreen();
    _shopScreen = new ShopScreen( _castle );
    _mainScreen = new MainScreen( _castle );

    _currentScreen = SCREENS::start;

    _audio = AudioManager::GetInstance();
    _bgm = _audio->LoadMusic( "The One.mp3" );
    _audio->PlayMusic( _bgm );
}

ScreensManager::~ScreensManager()
{
    delete _startScreen;
    delete _shopScreen;
    delete _mainScreen;

    delete _castle;

    _audio->FreeMusic( _bgm );
    _audio = nullptr;
}

void ScreensManager::ProcessEvents( SDL_Event* event )
{
    if (event->type == SDL_KEYDOWN)
    {
        switch (event->key.keysym.scancode)
        {
            case SDL_SCANCODE_D:
                if (_currentScreen == main)
                {
                    _mainScreen->ProcessEvents( event );
                    break;
                }
                _currentScreen = main;

                _audio->FreeMusic( _bgm );
                _bgm = _audio->LoadMusic( "Overhaul.mp3" );
                _audio->PlayMusic( _bgm );
                break;
            case SDL_SCANCODE_A:
                if (_currentScreen == shop)
                {
                    _shopScreen->ProcessEvents( event );
                    break;
                }
                _currentScreen = shop;

                _audio->FreeMusic( _bgm );
                _bgm = _audio->LoadMusic( "Reigen.mp3" );
                _audio->PlayMusic( _bgm );
                break;
            case SDL_SCANCODE_ESCAPE:
                if (_currentScreen == start)
                {
                    _startScreen->ProcessEvents( event );
                    break;
                }
                _currentScreen = start;

                _audio->FreeMusic( _bgm );
                _bgm = _audio->LoadMusic( "The One.mp3" );
                _audio->PlayMusic( _bgm );
                break;
            default:
                break;
        }
    }
}

void ScreensManager::Update()
{
    _audio->Update();

    switch (_currentScreen)
    {
        case start:
            _startScreen->Update();
            break;
        case shop:
            _shopScreen->Update();
            break;
        case main:
            _mainScreen->Update();
            break;
        default:
            break;
    }
}

void ScreensManager::Render()
{
    switch (_currentScreen)
    {
        case start:
            _startScreen->Render();
            break;
        case shop:
            _shopScreen->Render();
            break;
        case main:
            _mainScreen->Render();
            break;
        default:
            break;
    }
}