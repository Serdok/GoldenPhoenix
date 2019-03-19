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

        // Other event processing goes here
        _screens->ProcessEvents( &_event );
    }
}

void GameManager::EarlyUpdate()
{
    // Input states update

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
    _graphicsMgr->Clear();

    // Render everything here
    _screens->Render();

    _graphicsMgr->Render();
}

GameManager::GameManager()
: _graphicsMgr( nullptr ), _event(), _quit( false ), _timer( nullptr )
{
    // Initialize core functionality
    try
    {
        _graphicsMgr = Graphics::GetInstance();
        _timer = Timer::GetInstance();
        _audio = AudioManager::GetInstance();
        _inputs = InputsManager::GetInstance();
    }
    catch (Exception& e)
    {
        Rethrow( "Game failed to start", __FILE__, __LINE__ );
    }

    // Initialize objects
    InitObjects();
}

GameManager::~GameManager()
{
    DeleteObjects();

    AudioManager::Shutdown();
    InputsManager::Release();
    Timer::Stop();
    Graphics::Quit();
}

void GameManager::Run()
{
    while (!_quit)
    {
        _timer->Update();

        ProcessEvents();

        if (_timer->GetDeltaTime() >= 1.0/FPS)
        {
            EarlyUpdate();
            Update();

            Render();

            LateUpdate();
        }
    }
}