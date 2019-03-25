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


//! Graphics handler, singleton class
class Graphics
{
public:
    static const int SCREEN_WIDTH = 800;
    static const int SCREEN_HEIGHT = 600;

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
     * @param imagepath [in] Absolute path of the image to load
     * @return A texture to draw or nullptr if an error occurred
     */
    SDL_Texture* LoadTexture( const std::string& imagepath );

    /**
     * Convert a text to a texture
     * @param font [in] The font to use
     * @param text [in] The text to convert
     * @param color [in] The color to apply to the text
     * @return A texture to draw or nullptr if an error occurred
     */
    SDL_Texture* CreateTextTexture( TTF_Font* font, const std::string& text, const SDL_Color& color );

    /**
     * Draw a texture to the buffer
     * @param texture [in] The texture to draw
     * @param clip [in] A sub-section of the texture to draw
     * @param destination [in] A sub-section of the buffer to draw to
     * @param angle [in] The angle to apply to the texture
     * @param flip [in] The flip to apply to the texture (SDL_FLIP_NONE, SDL_FLIP_VERTICAL, SDL_FLIP_HORIZONTAL)
     */
    void DrawTexture( SDL_Texture* texture, const SDL_Rect* clip = nullptr, const SDL_Rect* destination = nullptr, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE );

private:
    Graphics();
    ~Graphics();

    void Init(); ///< Initialize SDL2 and its subsystems
};


#endif //GOLDEN_PHOENIX_GRAPHICS_H