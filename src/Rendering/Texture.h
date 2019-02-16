//
// Created by serdok on 26/01/19.
//

#ifndef GOLDEN_PHOENIX_TEXTURE_H
#define GOLDEN_PHOENIX_TEXTURE_H

// Custom headers
#include "Game.h"
#include "GetResourcePath.h"


typedef SDL_RendererFlip Flip;
#define none SDL_FLIP_NONE
#define horizontal SDL_FLIP_HORIZONTAL
#define vertical SDL_FLIP_VERTICAL


/**
 * @class Texture
 * Texture loader and drawer class
 */
class Texture
{
public:
    /**
     * Load an image from a given filename
     * @param filename [in]
     * @return A pointer to the texture associated to that image.
     */
    static SDL_Texture* LoadImage( const std::string& filename );

    /**
     * Draw a texture on the screen. Will actually be displayed at the next Render() call
     * @param texture [in] The texture to draw
     * @param clip [in] A subsection of the texture
     * @param destination [in] A subsection of the screen
     * @param flip [in] The flip of the image (none, horizontal, vertical)
     */
    static void Draw( SDL_Texture* texture,const SDL_Rect* clip = nullptr, const SDL_Rect* destination = nullptr, Flip flip = SDL_FLIP_NONE );
};

#endif //GOLDEN_PHOENIX_TEXTURE_H
