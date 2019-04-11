//
// Created by serdok on 09/03/19.
//

#include "GameManager.h"

void GameManager::InitObjects()
{
    // Game objects initialization goes here
    _screens = new ScreensManager();
}

void GameManager::DeleteObjects()
{
    // Game objects destruction goes here
    delete _screens;
}

void GameManager::ProcessEvents()
{
    while (SDL_PollEvent( &_event ))
    {
        if (_event.type == SDL_QUIT)
            _quit = true;

        _inputs->Update( &_event );

        // Other event processing goes here
        _screens->ProcessEvents( &_event );
    }
}

void GameManager::EarlyUpdate()
{
    AudioManager::Update();
}

void GameManager::Update()
{
    // Physics update, collision, ...
    _screens->Update();
}

void GameManager::LateUpdate()
{
    // Updates to do after rendering
    _timer->Reset();
}

void GameManager::Render()
{
    _graphics->Clear();

    // Render everything here
    _screens->Render();

    _graphics->Render();
}

GameManager::GameManager()
: _graphics( nullptr ), _event(), _quit( false ), _timer( nullptr ), _screens( nullptr )
{
    // Initialize core functionality

     try
    {
        _graphics = Graphics::GetInstance();
        _timer = Timer::GetInstance();
        _assets = AssetsManager::GetInstance();
        _audio = AudioManager::GetInstance();
        _inputs = InputsManager::GetInstance();
    }
    catch (Exception& e)
    {
        Rethrow( "Game failed to start", __FILE__, __LINE__ );
    }

 /*   pidf=fork();

    if(pidf == 0)
    {

        _intro = new IntroScreen ;
    }
    else if(pidf> 0)
    {   */

        // Initialize objects
        InitObjects();
 //   }
}

GameManager::~GameManager()
{
    // Delete game objects
    DeleteObjects();

    // Release singletons
    AssetsManager::Free();
    AudioManager::Shutdown();
    InputsManager::Release();
    Timer::Stop();
    Graphics::Quit();
}

void GameManager::Run()
{
  /*  if(pidf==0){
        std::cout<< "coucou" << std::endl;
        while (!_intro->GetQuit())
        {
            _timer->Update();
             while (SDL_PollEvent( &_event ))
            {
                if (_event.type == SDL_QUIT)
                    _quit = true;

                _inputs->Update( &_event );

                // Other event processing goes here
                _intro->ProcessEvents( &_event );
            }

            if (_timer->GetDeltaTime() >= 2.0f/FPS)
            {

                _intro->Update();

                _graphicsMgr->Clear();

                // Render everything here
                _intro->Render();

                _graphicsMgr->Render();

                _timer->Reset();
            }
        }
        delete _intro;
        InputsManager::Release();
        Timer::Stop();
        Graphics::Quit();
    }
    if(pidf>0){
        waitpid(pidf , NULL, 0);*/
        while (!_quit)
        {
            _timer->Update();

            ProcessEvents();

            if (_timer->GetDeltaTime() >= 1.0f/FPS)
            {
                EarlyUpdate();
                Update();

                Render();

                LateUpdate();
            }
        }
   // }
}