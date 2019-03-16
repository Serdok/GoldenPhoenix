//
// Created by serdok on 09/03/19.
//

#ifndef GOLDEN_PHOENIX_TEXTURE_H
#define GOLDEN_PHOENIX_TEXTURE_H

// Custom headers
#include "GameEntity.h"
#include "GetResourcePath.h"
#include "Graphics.h"

// C++ headers
#include <cassert>


//! Textured game entity that will be drawn.
class Texture : public GameEntity
{
protected:
    SDL_Texture* _texture;
    int _width, _height;

    bool _fullscreen;
    SDL_Rect _dest;

    bool _clipped;
    SDL_Rect _clip;


public:
    /**
     * Create a textured game entity. The original size of the image will be used
     * @param imagefile [in] Name of the image to use. Images must be located in the folder data/images/
     * @param fullscreen [in] If the entity should be drawn on the whole screen (default : false)
     */
    Texture( const std::string& imagefile, bool fullscreen = false );

    /**
     * Create a textured game entity. A specified size of the image will be used
     * @param imagefile [in] Name of the image to use. Images must be located in the folder data/images/
     * @param x [in] x coordinate of the top-left image to clip
     * @param y [in] y coordinate of the top-left image to clip
     * @param width [in] Width of the clip
     * @param height [in] Height of the clip
     * @param fullscreen [in] If the entity should be drawn on the whole screen (default : false)
     */
    Texture( const std::string& imagefile, int x, int y, int width, int height, bool fullscreen = false );

    /**
     * Create a textured game entity. The texture will be a custom text
     * @param text [in] The text to render
     * @param font [in] Name of the font to use. Fonts must be located in the folder data/fonts/
     * @param size [in] Size of the text
     * @param color [in] Color to apply to the text
     * @param fullscreen [in] If the entity should be drawn on the whole screen (default : false)
     */
    Texture( const std::string& text, const std::string& font, int size, const SDL_Color& color, bool fullscreen = false );

    ~Texture() override;

    //! Update the textured entity. This function should be overridden in derived classes since no update happens here.
    void Update() override;

    //! Render the textured entity to the buffer. Overrides GameEntity::Render() function
    void Render() override;
};


#endif //GOLDEN_PHOENIX_TEXTURE_H
