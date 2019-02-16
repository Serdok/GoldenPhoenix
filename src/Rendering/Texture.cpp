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

void Texture::Draw( SDL_Texture* texture, const SDL_Rect* clip, const SDL_Rect* destination, const Flip flip )
{
    SDL_RenderCopyEx( Game::GetRenderer(), texture, clip, destination, 0, nullptr, flip );
}