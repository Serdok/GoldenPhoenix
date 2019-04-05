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
    SDL_Texture* _texture = nullptr;
    int _width, _height;

    bool _fullscreen = false;
    SDL_Rect _dest;

    bool _clipped = false;
    SDL_Rect _clip;


public:
    /**
     * Create a textured game entity. The original size of the image will be used
     * @param [in] imagefile Name of the image to use. Images must be located in the folder data/images/
     * @param [in] fullscreen If the entity should be drawn on the whole screen (default : false)
     */
    Texture( const std::string& imagefile, bool fullscreen = false );

    /**
     * Create a textured game entity. A specified size of the image will be used
     * @param [in] imagefile Name of the image to use. Images must be located in the folder data/images/
     * @param [in] x x coordinate of the top-left image to clip
     * @param [in] y y coordinate of the top-left image to clip
     * @param [in] width Width of the clip
     * @param [in] height Height of the clip
     * @param [in] fullscreen If the entity should be drawn on the whole screen (default : false)
     */
    Texture( const std::string& imagefile, int x, int y, int width, int height, bool fullscreen = false );

    /**
     * Create a textured game entity. The texture will be a custom text
     * @param [in] text The text to render
     * @param [in] font Name of the font to use. Fonts must be located in the folder data/fonts/
     * @param [in] size Size of the text
     * @param [in] color Color to apply to the text
     * @param [in] fullscreen If the entity should be drawn on the whole screen (default : false)
     */
    Texture( const std::string& text, const std::string& font, int size, const SDL_Color& color, bool fullscreen = false );

    //! Free resources
    ~Texture() override;

    //! Return the height of the loaded image
    int GetHeight() const;

    //! Return the width of the loaded image
    int GetWidth() const;

    void SetAlpha( unsigned char alpha );
    void SetBlendingMode( SDL_BlendMode mode );

    //! Update the textured entity. This function should be overridden in derived classes since no update happens here.
    void Update() override;

    //! Render the textured entity to the back buffer. The position of the image is the center point
    virtual void Render();

    //! Render the textured entity to the back buffer. The position of the image is the center point
    virtual void Render( SDL_RendererFlip flip );
};


#endif //GOLDEN_PHOENIX_TEXTURE_H
