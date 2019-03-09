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
    Texture( const std::string& imagefile, bool fullscreen = false );

    Texture( const std::string& imagefile, int x, int y, int width, int height, bool fullscreen = false );

    Texture( const std::string& text, const std::string& font, int size, const SDL_Color& color, bool fullscreen = false );

    ~Texture();

    void Update() override;

    void Render() override;
};


#endif //GOLDEN_PHOENIX_TEXTURE_H
