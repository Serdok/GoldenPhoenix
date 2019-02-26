//
// Created by serdok on 26/01/19.
//

#include "Texture.h"

SDL_Texture* Texture::LoadImage( const std::string& filename )
{
    SDL_Surface* surface = IMG_Load( GetResourcePath( filename ).c_str() );
    if (!surface)
        throw Exception( "Failed to load image from " + filename + " : " + std::string( SDL_GetError() ), __FILE__, __LINE__ );

    SDL_Texture* texture = SDL_CreateTextureFromSurface( Game::GetRenderer(), surface );
    Cleanup( surface );
    if (!texture)
        throw Exception( "Failed to load image from " + filename + " : " + std::string( SDL_GetError()), __FILE__, __LINE__ );

    return texture;
}

SDL_Texture* Texture::LoadText( const std::string& message, TTF_Font* const font, const SDL_Color& color )
{
    SDL_Surface* surface = TTF_RenderText_Solid( font, message.c_str(), color );
    if (!surface)
        throw Exception( "Failed to load text message \'" + message + "\' : " + std::string( SDL_GetError() ), __FILE__, __LINE__ );

    SDL_Texture* texture = SDL_CreateTextureFromSurface( Game::GetRenderer(), surface );
    Cleanup( surface );
    if (!texture)
        throw Exception( "Failed to load text message \'" + message + "\' : " + std::string( SDL_GetError() ), __FILE__, __LINE__ );

    return texture;
}

void Texture::Draw( SDL_Texture* texture, const SDL_Rect* clip, const SDL_Rect* destination, const Flips flip )
{
    SDL_RenderCopyEx( Game::GetRenderer(), texture, clip, destination, 0, nullptr, (SDL_RendererFlip) flip );
}