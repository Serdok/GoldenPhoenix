//
// Created by serdok on 26/01/19.
//

#ifndef GOLDEN_PHOENIX_TEXTURE_H
#define GOLDEN_PHOENIX_TEXTURE_H

// Custom headers
#include "Game.h"
#include "GetResourcePath.h"


enum Flips
{
    NONE = SDL_FLIP_NONE,
    HORIZONTAL = SDL_FLIP_HORIZONTAL,
    VERTICAL = SDL_FLIP_VERTICAL
};


//! Texture loader and drawer class
class Texture
{
public:
    /**
     * Load an image from a given filename
     * @param filename [in] The relative path to the image
     * @return A pointer to the texture associated to that image.
     */
    static SDL_Texture* LoadImage( const std::string& filename );

    /**
     * Load a text message from a previously loaded font
     * @param message [in] The message to load
     * @param font [in] A pointer to a loaded font
     * @return A pointer to the texture associated to that message
     */
    static SDL_Texture* LoadText( const std::string& message, TTF_Font* const font, const SDL_Color& color );

    /**
     * Draw a texture on the screen. Will actually be displayed at the next Render() call
     * @param texture [in] The texture to draw
     * @param clip [in] A subsection of the texture
     * @param destination [in] A subsection of the screen
     * @param flip [in] The flip of the image (NONE, HORIZONTAL, VERTICAL)
     */
    static void Draw( SDL_Texture* texture, const SDL_Rect* clip = nullptr, const SDL_Rect* destination = nullptr, Flips flip = Flips::NONE );
};

#endif //GOLDEN_PHOENIX_TEXTURE_H
