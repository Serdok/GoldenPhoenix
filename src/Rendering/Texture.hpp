//
// Created by serdok on 26/01/19.
//

#ifndef GAME_TEXTURE_HPP
#define GAME_TEXTURE_HPP

// Custom headers
#include "Game.hpp"
#include "../Helpers/GetResourcePath.hpp"

//! Texture loader and drawer class
class Texture
{
public:
    //! Load an image from a given filename and return a SDL_Texture*
    static SDL_Texture* LoadImage( const std::string& filename );

    /**
     * Draw a texture on the screen. Will actually be displayed at the next Game::Render() call
     * @param texture [in] The texture to draw
     * @param clip [in] A subsection of the texture
     * @param destination [in] A subsection of the screen
     * @param flip [in] The flip of the image (SDL_FLIP_NONE, SDL_FLIP_HORIZONTAL, SDL_FLIP_VERTICAL)
     */
    static void Draw( SDL_Texture* texture, const SDL_Rect* clip = nullptr, const SDL_Rect* destination = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE );
};

#endif //GAME_TEXTURE_HPP
