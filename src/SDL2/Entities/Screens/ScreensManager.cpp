//
// Created by serdok on 16/03/19.
//

#include "ScreensManager.h"

ScreensManager::ScreensManager()
{
    _castle = new Castle( GetResourcePath( "rooms/room.room" ));

    _startScreen = new StartScreen( _castle );
    _shopScreen = new ShopScreen( _castle );
    _mainScreen = new MainScreen( _castle );

    _currentScreen = SCREENS::start;

    _audio = AudioManager::GetInstance();
    _bgm = _audio->LoadMusic( "The One.mp3" );
    _audio->PlayMusic( _bgm );

    _inputs = InputsManager::GetInstance();
}

ScreensManager::~ScreensManager()
{
    delete _startScreen;
    delete _shopScreen;
    delete _mainScreen;

    delete _castle;

    _audio->FreeMusic( _bgm );
    _audio = nullptr;

    _inputs = nullptr;
}

void ScreensManager::ProcessEvents( SDL_Event* event )
{
    switch (_currentScreen)
    {
        case start:
            _startScreen->ProcessEvents( event );
            break;
        case shop:
            _shopScreen->ProcessEvents( event );
            break;
        case main:
            _mainScreen->ProcessEvents( event );
            break;
    }

    SwitchCurrentScreen( event );
}

void ScreensManager::SwitchCurrentScreen( SDL_Event* event )
{
    switch (_currentScreen)
    {
        case start:
            if (_inputs->KeyPressed( SDL_SCANCODE_2 ))
            {
                _currentScreen = main;
                StartCurrentScreen();
            }
            if (_inputs->KeyPressed( SDL_SCANCODE_1 ))
            {
                _currentScreen = shop;
                StartCurrentScreen();
            }
            break;
        case shop:
        case main:
            if (_inputs->KeyPressed( SDL_SCANCODE_ESCAPE ))
                {
                    _currentScreen = start;
                    StartCurrentScreen();
                }
            break;
    }
}

void ScreensManager::StartCurrentScreen()
{
    switch (_currentScreen)
    {
        case start:
            _audio->FreeMusic( _bgm );
            _bgm = _audio->LoadMusic( "The One.mp3" );
            _audio->PlayMusic( _bgm );

            _castle->GetPlayer()->SetPosition( Vector2f( Graphics::SCREEN_WIDTH/2.0f - 100.0f, Graphics::SCREEN_HEIGHT - 50.0f ) );
            break;
        case main:
            _audio->FreeMusic( _bgm );
            _bgm = _audio->LoadMusic( "Overhaul.mp3" );
            _audio->PlayMusic( _bgm );

            _castle->GetPlayer()->SetPosition( Vector2f( Graphics::SCREEN_WIDTH/2.0f, Graphics::SCREEN_HEIGHT/2.0f ) );
            break;
        case shop:
            _audio->FreeMusic( _bgm );
            _bgm = _audio->LoadMusic( "Reigen.mp3" );
            _audio->PlayMusic( _bgm );
            break;
        default:
            break;
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
        case start:_startScreen->Render();
            break;
        case shop:_shopScreen->Render();
            break;
        case main:_mainScreen->Render();
            break;
        default:
            break;
    }
}