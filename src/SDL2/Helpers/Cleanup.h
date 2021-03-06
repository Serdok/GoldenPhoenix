//
// Created by serdok on 24/01/19.
//

#ifndef GOLDEN_PHOENIX_CLEANUP_H
#define GOLDEN_PHOENIX_CLEANUP_H

// SDL2 headers
#include "SDL.h"
#include "SDL_ttf.h"

// C++ headers
#include <utility>


//! Recurse through the list of arguments to clean up, cleaning up the first one in the list each iteration.
template<typename T, typename... Args>
void Cleanup( T* t, Args&& ... args ){
    Cleanup( t );
    Cleanup( std::forward< Args >(args)... );
}

// The declarations below are used to end the recursion.
// We make it safe to pass nullptr to save the hassle of checking which variable failed to load.

template<>
inline void Cleanup< SDL_Window >( SDL_Window* window )
{
    if (!window)
        return;
    SDL_DestroyWindow( window );
}

template<>
inline void Cleanup< SDL_Renderer >( SDL_Renderer* renderer )
{
    if (!renderer)
        return;
    SDL_DestroyRenderer( renderer );
}

template<>
inline void Cleanup< SDL_Texture >( SDL_Texture* texture )
{
    if (!texture)
        return;
    SDL_DestroyTexture( texture );
}

template<>
inline void Cleanup< SDL_Surface >( SDL_Surface* surface )
{
    if (!surface)
        return;
    SDL_FreeSurface( surface );
}

template<>
inline void Cleanup< TTF_Font >( TTF_Font* font )
{
    if (!font)
        return;
    TTF_CloseFont( font );
}

#endif //GOLDEN_PHOENIX_CLEANUP_H
