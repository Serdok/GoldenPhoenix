//
// Created by serdok on 16/03/19.
//

#include "ScreensManager.h"

ScreensManager::ScreensManager()
{
    _translation = new Translation();

    _castle = new Castle( GetResourcePath( "rooms/room.room" ), true );

    _startScreen = new StartScreen( _castle, _translation );
    _shopScreen = new ShopScreen( _castle, _translation );
    _mainScreen = new MainScreen( _castle, _translation );
    _inventoryScreen = new InventoryScreen( _castle, _translation );
    _pauseScreen = new PauseScreen( _translation );

    _inputs = InputsManager::GetInstance();

    _audio = AudioManager::GetInstance();
    _audio->LoadSound( GetResourcePath( "musics/Overhaul.mp3" ), true, false, true );
    _audio->LoadSound( GetResourcePath( "musics/The One.mp3" ), true, false, true );
    _audio->LoadSound( GetResourcePath( "musics/Reigen.mp3" ), true, false, true );


    _audio->PlaySound( GetResourcePath( "musics/The One.mp3" ) );
}

ScreensManager::~ScreensManager()
{
    delete _startScreen;
    delete _shopScreen;
    delete _mainScreen;
    delete _inventoryScreen;
    delete _pauseScreen;

    delete _translation;
    delete _castle;

    _audio->UnloadSound( GetResourcePath( "musics/Overhaul.mp3" ) );
    _audio->UnloadSound( GetResourcePath( "musics/The One.mp3" ) );
    _audio->UnloadSound( GetResourcePath( "musics/Reigen.mp3" ) );
    _audio = nullptr;

    _inputs = nullptr;
}

void ScreensManager::ProcessEvents( SDL_Event* event )
{
    SwitchCurrentScreen( event );

    switch (_currentScreen)
    {
        case start:_startScreen->ProcessEvents( event );
        if (_inputs->KeyPressed( SDL_SCANCODE_0 ))
        {
            std::cout << fs::remove( GetResourcePath( "saves/save.player" ) ) << std::endl;
            std::cout << fs::remove( GetResourcePath( "saves/save.rooms" ) ) << std::endl;
            _castle->LoadCastle( GetResourcePath( "rooms/room.room" ));
        }
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
            if (_inputs->KeyPressed( SDL_SCANCODE_I ))
            {
                Graphics::GetInstance()->SetBackgroundColor( 217, 207, 141 );
                _currentScreen = inventory;
            }
            if (_inputs->KeyPressed( SDL_SCANCODE_P ))
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
            if (_inputs->KeyPressed( SDL_SCANCODE_P ))
            {
                _currentScreen = main;
            }
            if (_inputs->KeyPressed( SDL_SCANCODE_L ))
            {
                if (_translation->GetCurrentLanguage() == 'F')
                    _translation->SetCurrentLanguage( 'E' );
                
                else if (_translation->GetCurrentLanguage() == 'E')
                    _translation->SetCurrentLanguage( 'F' );
                
                _startScreen->SetTranslation( _translation );
                _shopScreen->SetTranslation( _translation );
                _mainScreen->SetTranslation( _translation );
                _inventoryScreen->SetTranslation( _translation );
                _pauseScreen->SetTranslation( _translation );

            }
            if (_inputs->KeyPressed( SDL_SCANCODE_S ))
            {
                if (!_musicPaused)
                {
                    _audio->StopAllChannels();
                    _musicPaused = true;
                }
                else
                {
                    _audio->PlaySound( GetResourcePath( "musics/Overhaul.mp3" ) );
                    _musicPaused = false;
                }
            }
            break;
        default:break;
    }
}

void ScreensManager::StartCurrentScreen()
{
    switch (_currentScreen)
    {
        case start:
            _audio->StopAllChannels();
            _audio->PlaySound( GetResourcePath( "musics/The One.mp3" ) );
            break;
        case main:
            _audio->StopAllChannels();
            _audio->PlaySound( GetResourcePath( "musics/Overhaul.mp3" ) );
            break;
        case shop:
            _audio->StopAllChannels();
            _audio->PlaySound( GetResourcePath( "musics/Reigen.mp3" ) );
            break;
        default:break;
    }
}


void ScreensManager::Update()
{
    switch (_currentScreen)
    {
        case start:_startScreen->Update();
            break;
        case shop:_shopScreen->Update();
            break;
        case main:_mainScreen->Update();
            if (_castle->ShouldReset())
            {
                _currentScreen = start;
                _castle->LoadRooms( GetResourcePath( "rooms/default.rooms" ));
            }
            if (_castle->ExitCastle())
            {
                _currentScreen = start;
                StartCurrentScreen();
            }
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