//
// Created by serdok on 16/03/19.
//

#include "ScreensManager.h"

ScreensManager::ScreensManager()
{
    _translation= new Translation('F');

    _castle = new Castle( GetResourcePath( "rooms/room.room" ));

    _startScreen = new StartScreen( _castle, _translation );
    _shopScreen = new ShopScreen( _castle, _translation);
    _mainScreen = new MainScreen( _castle, _translation );
    _inventoryScreen = new InventoryScreen( _castle, _translation );
    _pauseScreen = new PauseScreen(_translation);

    _soundActivate = true;
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
    delete _inventoryScreen;
    delete _pauseScreen;

    delete _castle;

    if(_soundActivate){
        _audio->FreeMusic( _bgm );
    }
   
    _audio = nullptr;

    _inputs = nullptr;
}

void ScreensManager::ProcessEvents( SDL_Event* event )
{
    SwitchCurrentScreen( event );

    switch (_currentScreen)
    {
        case start:_startScreen->ProcessEvents( event );
            break;
        case shop:_shopScreen->ProcessEvents( event );
            break;
        case main:_mainScreen->ProcessEvents( event );
            break;
        case inventory:_inventoryScreen->ProcessEvents( event );
            break;
        case pause:_pauseScreen->ProcessEvents( event );
            break;
    }
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
                _castle->EnterCastle();
            }
            if (_inputs->KeyPressed( SDL_SCANCODE_1 ))
            {
                _currentScreen = shop;
                StartCurrentScreen();
                _inputs->LockInputs();
            }
            break;  
        case main:
            if (_castle->ExitCastle())
            {
                _currentScreen = start;
                StartCurrentScreen();
            }
            if (_inputs->KeyPressed( SDL_SCANCODE_I ))
            {
                Graphics::GetInstance()->SetBackgroundColor( 217, 207, 141 );
                _currentScreen = inventory;
            }
            if(_inputs->KeyPressed(SDL_SCANCODE_P))
            {
                Graphics::GetInstance()->SetBackgroundColor( 0, 0, 0 );
                _currentScreen = pause;
            }
            break;
        case shop:
            if (_inputs->KeyPressed( SDL_SCANCODE_ESCAPE ))
            {
                _currentScreen = start;
                StartCurrentScreen();
            }
            if (_inputs->KeyPressed( SDL_SCANCODE_A ))
            {
                _currentScreen = start;
                StartCurrentScreen();
            }
            break;
        case inventory:
            if (_inputs->KeyPressed( SDL_SCANCODE_I ))
            {
                _currentScreen = main;
            }
            break;
        case pause:
            if(_inputs->KeyPressed(SDL_SCANCODE_P))
            {
                _currentScreen = main;
            }
            if (_inputs->KeyPressed( SDL_SCANCODE_L ))
            {
                if(_translation->GetCurrentLanguage()=='F')
                    _translation->SetCurrentLanguage( 'E' );
                else if(_translation->GetCurrentLanguage()=='E')
                    _translation->SetCurrentLanguage( 'F' );

                delete _startScreen;
                delete _shopScreen;
                delete _mainScreen;
                delete _inventoryScreen;
                delete _pauseScreen;
                _startScreen = new StartScreen( _castle, _translation );
                _shopScreen = new ShopScreen( _castle, _translation);
                _mainScreen = new MainScreen( _castle, _translation );
                _inventoryScreen = new InventoryScreen( _castle, _translation );
                _pauseScreen = new PauseScreen(_translation);
                _currentScreen = pause;
            }
            if(_inputs->KeyPressed(SDL_SCANCODE_S))
            {
                if(_soundActivate)
                    _audio->FreeSound(_bgm);
                if(!_soundActivate){
                    _bgm = _audio->LoadMusic( "Overhaul.mp3" );
                    _audio->PlayMusic( _bgm );
                }
                _soundActivate=!_soundActivate;
            }
            break;
        default:break;
    }
}

void ScreensManager::StartCurrentScreen()
{  
    if(_soundActivate)
        switch (_currentScreen)
        {
            case start:_audio->FreeMusic( _bgm );
                _bgm = _audio->LoadMusic( "The One.mp3" );
                _audio->PlayMusic( _bgm );
                break;
            case main:_audio->FreeMusic( _bgm );
                _bgm = _audio->LoadMusic( "Overhaul.mp3" );
                _audio->PlayMusic( _bgm );
                break;
            case shop:_audio->FreeMusic( _bgm );
                _bgm = _audio->LoadMusic( "Reigen.mp3" );
                _audio->PlayMusic( _bgm );
                break;
            default:break;
        }
}


void ScreensManager::Update()
{
    _audio->Update();

    switch (_currentScreen)
    {
        case start:_startScreen->Update();
            break;
        case shop:_shopScreen->Update();
            break;
        case main:_mainScreen->Update();
            break;
        case inventory:_inventoryScreen->Update();
            break;
        case pause:_pauseScreen->Update();
            break;
        default:break;
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
        case inventory:_inventoryScreen->Render();
            break;
        case pause:_pauseScreen->Render();
            break;
        default:break;
    }
}