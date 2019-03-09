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

// C++ headers



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
    static Graphics* GetInstance();

    static void Quit();

    void Clear();

    void Render();

    SDL_Texture* LoadTexture( const std::string& imagepath );

    SDL_Texture* CreateTextTexture( TTF_Font* font, const std::string& text, const SDL_Color& color );

    void DrawTexture( SDL_Texture* texture, const SDL_Rect* clip = nullptr, const SDL_Rect* destination = nullptr, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE );

private:
    Graphics();

    ~Graphics();

    void Init();
};


#endif //GOLDEN_PHOENIX_GRAPHICS_H