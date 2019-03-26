//
// Created by serdok on 07/03/19.
//

#ifndef GOLDEN_PHOENIX_GRAPHICS_H
#define GOLDEN_PHOENIX_GRAPHICS_H

// Custom headers
#include "Cleanup.h"
#include "Exceptions.h"

// SDL2 headers
#include "SDL_image.h"


//! SDL2 graphics handler
class Graphics
{
public:
    static const int SCREEN_WIDTH = 800;    ///< Width of the SDL2 window
    static const int SCREEN_HEIGHT = 600;   ///< Height of the SDL2 window

private:
    static Graphics* sInstance;
    SDL_Window* _window;
    SDL_Renderer* _renderer;


public:
    //! Return the instance of the class
    static Graphics* GetInstance();

    //! Release the instance of the class
    static void Quit();

    //! Clear the window
    void Clear();

    //! Render the buffer
    void Render();

    /**
     * Load a texture from an absolute path
     * @param [in] imagepath Absolute path of the image to load
     * @return A texture to draw or nullptr if an error occurred
     */
    SDL_Texture* LoadTexture( const std::string& imagepath );

    /**
     * Convert a text to a texture
     * @param [in] font The font to use
     * @param [in] text The text to convert
     * @param [in] color The color to apply to the text
     * @return A texture to draw or nullptr if an error occurred
     */
    SDL_Texture* CreateTextTexture( TTF_Font* font, const std::string& text, const SDL_Color& color );

    /**
     * Draw a texture to the buffer
     * @param [in] texture The texture to draw
     * @param [in] clip A sub-section of the texture to draw
     * @param [in] destination A sub-section of the buffer to draw to
     * @param [in] angle The angle to apply to the texture
     * @param [in] flip The flip to apply to the texture (SDL_FLIP_NONE, SDL_FLIP_VERTICAL, SDL_FLIP_HORIZONTAL)
     */
    void DrawTexture( SDL_Texture* texture, const SDL_Rect* clip = nullptr, const SDL_Rect* destination = nullptr, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE );


    void SetBackgroundColor(unsigned char r, unsigned char g, unsigned char b);

private:
    Graphics() noexcept( false );
    ~Graphics();

    void Init() noexcept( false ); ///< Initialize SDL2 and its subsystems
};


#endif //GOLDEN_PHOENIX_GRAPHICS_H