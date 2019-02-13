//
// Created by serdok on 24/01/19.
//

#include "Game.hpp"

SDL_Window* Game::_window = nullptr;
SDL_Renderer* Game::_renderer = nullptr;
SDL_WindowInfo Game::_windowInfo;
SDL_RendererInfo Game::_rendererInfo;
SDL_Event Game::_event;
SDL_Rect Game::_camera;



void Game::InitObjects()
{
    try
    {
        image = Texture::LoadImage( "images/grass.png" );
        dirt = Texture::LoadImage( "images/dirt.png" );
        stone = Texture::LoadImage( "images/stone.png" );
    }
    catch( Exception& e )
    {
        Rethrow( "Failed to load image assets!", __FILE__, __LINE__ );
    }

    tileSize = 10;
}

void Game::ProcessEvents()
{
    while (SDL_PollEvent( &_event ))
    {
        if (_event.type == SDL_QUIT)
            _running = false;

        // Other events processors

    }
}

void Game::Update()
{

}

void Game::Render()
{
    SDL_RenderClear( _renderer );

    for (int x=0 ; x<_windowInfo.width ; x+=tileSize)
        for (int y=0 ; y<_windowInfo.height ; y+=tileSize)
        {
            SDL_Rect destination = { x, y, tileSize, tileSize };
            if (y < 100)
                Texture::Draw( image, nullptr, &destination );
            else if (y < 300)
                Texture::Draw( dirt, nullptr, &destination );
            else
                Texture::Draw( stone, nullptr, &destination );
        }

    SDL_RenderPresent( _renderer );
}

void Game::Clean()
{
    Cleanup( image, dirt, stone );
    Cleanup( _renderer, _window );
}

Game::Game()
: _running( false )
{
    atexit( Quit );

    try
    {
        InitSDL2();
        InitSDL2_image();
        InitSDL2_ttf();
        InitSDL2_mixer();
    }
    catch( Exception& e )
    {
        Rethrow( "Game graphics engine failed to initialize!", __FILE__, __LINE__ );
    }
}

void Game::InitSDL2()
{
    if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_TIMER ) < 0)
        throw Exception( "Failed to initialize SDL2!" + std::string( SDL_GetError() ), __FILE__, __LINE__ );
}

void Game::InitSDL2_image()
{
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!( IMG_Init( imgFlags ) & imgFlags ))
        throw Exception( "Failed to initialize SDL2_image!" + std::string( SDL_GetError() ), __FILE__, __LINE__ );
}

void Game::InitSDL2_ttf()
{
    if( TTF_Init() < 0 )
        throw Exception( "Failed to initialize SDL2_ttf!" + std::string( SDL_GetError() ), __FILE__, __LINE__ );
}

void Game::InitSDL2_mixer()
{
    if (Mix_OpenAudio( 44800, MIX_DEFAULT_FORMAT, 2, 4096 ) < 0)
        throw Exception( "Failed to initialize SDL2_mixer!" + std::string( SDL_GetError() ), __FILE__, __LINE__ );
}

Game::~Game()
{
    Clean();
}

void Game::Init( const std::string& title, int width, int height, bool fullscreen )
{
    Uint32 flags = (fullscreen ? SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN );

    _window = SDL_CreateWindow(
            title.c_str(),
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            width, height,
            flags
            );
    assert( _window );

    _renderer = SDL_CreateRenderer( _window, -1, SDL_RENDERER_ACCELERATED );
    assert( _renderer );

    _running = true;
    GetWindowInfo();
    GetRendererInfo();
}

void Game::Run() 
{
    if (!_running)
        throw Exception( "Game graphics engine not initialized! Have you called Init() before Run()?", __FILE__, __LINE__ );

    InitObjects();

    const int FPS = 60;
    const int FRAME_DELAY = 1000 / FPS;
    Uint32 frameStart;
    Uint32 deltaTime;

    while (_running)
    {
        frameStart = SDL_GetTicks();

        ProcessEvents();
        Update();
        Render();

        deltaTime = SDL_GetTicks() - frameStart;
        if (deltaTime < FRAME_DELAY)
            SDL_Delay( FRAME_DELAY - deltaTime );
    }

    Clean();
}

bool Game::Running() const
{
    return _running;
}

SDL_Rect Game::GetCamera()
{
    return Game::_camera;
}

SDL_Renderer* Game::GetRenderer()
{
    return Game::_renderer;
}

SDL_RendererInfo Game::GetRendererInfo()
{
    if (SDL_GetRendererInfo( Game::_renderer, &Game::_rendererInfo ) < 0)
        std::cerr << "GAME::RendererInfo() - SDL_GetRendererInfo() : " << SDL_GetError() << '\n';

    return Game::_rendererInfo;
}

SDL_Event Game::GetEvents()
{
    return Game::_event;
}

SDL_WindowInfo Game::GetWindowInfo()
{
    Game::_windowInfo.title = std::string( SDL_GetWindowTitle( Game::_window ) );
    SDL_GetWindowPosition( Game::_window, &Game::_windowInfo.x, &Game::_windowInfo.y );
    SDL_GetWindowSize( Game::_window, &Game::_windowInfo.width, &Game::_windowInfo.height );
    Game::_windowInfo.flags = SDL_GetWindowFlags( Game::_window );

    return Game::_windowInfo;
}

void Quit()
{
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}