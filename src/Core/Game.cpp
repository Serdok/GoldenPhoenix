//
// Created by serdok on 24/01/19.
//

#include "Game.h"

SDL_Window* Game::_window = nullptr;
SDL_Renderer* Game::_renderer = nullptr;
SDL_WindowInfo Game::_windowInfo = {};
SDL_RendererInfo Game::_rendererInfo = {};
SDL_Event Game::_event = {};



void Game::InitObjects()
{
    font = TTF_OpenFont( GetResourcePath( "fonts/Pasatona.ttf" ).c_str(), 20 );
    assert( font );

    bg = Texture::LoadImage( "images/ProjectLogo.png" );
    text = Texture::LoadText( "This is a test message", font, { 255, 255, 255 } );

    ah = new Sound( "sounds/ah-peanut-butter-baby.wav" );
    ah->Play( 1 );
}

void Game::ProcessEvents()
{
    while (SDL_PollEvent( &_event ))
    {
        if (_event.type == SDL_QUIT)
            _running = false;

        // Other classes' events processors
        if (_event.type == SDL_KEYDOWN && _event.key.keysym.scancode == SDL_SCANCODE_SPACE)
            ah->Play();
    }
}

void Game::Update()
{

}

void Game::Render()
{
    SDL_RenderClear( _renderer );

    Texture::Draw( bg );
    Texture::Draw( text );

    SDL_RenderPresent( _renderer );
}

void Game::Clean()
{
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
    if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0)
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
    if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 4096 ) < 0)
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