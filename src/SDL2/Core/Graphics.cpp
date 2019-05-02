//
// Created by serdok on 07/03/19.
//

#include "Graphics.h"

Graphics* Graphics::sInstance = nullptr;

Graphics* Graphics::GetInstance()
{
    if (!sInstance)
        sInstance = new Graphics();

    return sInstance;
}

void Graphics::Quit()
{
    delete sInstance;
}


Graphics::Graphics() : _window( nullptr ), _renderer( nullptr )
{
    try
    {
        Init();
    }
    catch (Exception& e)
    {
        Rethrow( "Game graphics engine failed to initialize!", __FILE__, __LINE__ );
    }
}

Graphics::~Graphics()
{
    Cleanup( _renderer, _window );

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Graphics::Init()
{
    // SDL2 initialization
    if (SDL_Init( SDL_INIT_VIDEO ) < 0)
        throw Exception( "SDL2 failed to initialize : " + std::string( SDL_GetError()), __FILE__, __LINE__ );

    // Window creation
    _window = SDL_CreateWindow( "L'oeuf du Phénix", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if (!_window)
        throw Exception( "Window failed to create : " + std::string( SDL_GetError()), __FILE__, __LINE__ );
    
    //Icon of windows
    std::string pathicon = "data/images/Objets/Oeuf.png";
    SDL_Surface* icon = IMG_Load( pathicon.c_str());
    SDL_SetWindowIcon(_window, icon);

    // Renderer creation
    _renderer = SDL_CreateRenderer( _window, -1, SDL_RENDERER_ACCELERATED );
    if (!_renderer)
        throw Exception( "Renderer failed to create : " + std::string( SDL_GetError()), __FILE__, __LINE__ );

    // Set default background color
    SDL_SetRenderDrawColor( _renderer, 0x0F, 0x0F, 0xFF, 0xFF );

    // SDL2_image initialization
    int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
    if (!( IMG_Init( imgFlags ) & imgFlags ))
        throw Exception( "SDL2_image failed to initialize : " + std::string( SDL_GetError()), __FILE__, __LINE__ );

    // SDL2_ttf initialization
    if (TTF_Init() < 0)
        throw Exception( "SDL2_ttf failed to initialize : " + std::string( SDL_GetError()), __FILE__, __LINE__ );
}

void Graphics::Render()
{
    SDL_RenderPresent( _renderer );
}

void Graphics::Clear()
{
    SDL_RenderClear( _renderer );
}

SDL_Texture* Graphics::LoadTexture( const std::string& imagepath )
{
    // Load image from file
    SDL_Surface* surface = IMG_Load( imagepath.c_str());
    if (!surface)
    {
        std::cerr << "Failed to load image from " + imagepath + " : " + std::string( SDL_GetError()) << std::endl;
        return nullptr;
    }

    // Convert loaded image to a texture to be drawn
    SDL_Texture* texture = SDL_CreateTextureFromSurface( _renderer, surface );
    SDL_FreeSurface( surface );
    if (!texture)
    {
        std::cerr << "Failed to load image from " + imagepath + " : " << SDL_GetError() << std::endl;
        return nullptr;
    }

    return texture;
}

SDL_Texture* Graphics::CreateTextTexture( TTF_Font* font, const std::string& text, const SDL_Color& color )
{
    // Load text with font and color
    // SDL_Surface* surface = TTF_RenderText_Solid( font, text.c_str(), color );
    SDL_Surface* surface = TTF_RenderUTF8_Blended_Wrapped( font, text.c_str(), color, SCREEN_WIDTH );
    if (!surface)
    {
        std::cerr << "Failed to convert " + text + " to a texture : " << SDL_GetError() << std::endl;
        return nullptr;
    }

    // Convert loaded message to a texture to be drawn
    SDL_Texture* texture = SDL_CreateTextureFromSurface( _renderer, surface );
    SDL_FreeSurface( surface );
    if (!texture)
    {
        std::cerr << "Failed to convert " + text + " to a texture : " << SDL_GetError() << std::endl;
        return nullptr;
    }

    return texture;
}

void Graphics::DrawTexture( SDL_Texture* texture, const SDL_Rect* clip, const SDL_Rect* destination, const float angle, const SDL_RendererFlip flip )
{
    SDL_RenderCopyEx( _renderer, texture, clip, destination, angle, nullptr, flip );
}

void Graphics::SetBackgroundColor( unsigned char r, unsigned char g, unsigned char b )
{
    SDL_SetRenderDrawColor( _renderer, r, g, b, 0xFF );
}