//
// Created by serdok on 10/04/19.
//

#ifndef GOLDEN_PHOENIX_ASSETSMANAGER_H
#define GOLDEN_PHOENIX_ASSETSMANAGER_H

// Custom headers
#include "GetResourcePath.h"
#include "Graphics.h"

// C++ headers
#include <map>


class AssetsManager
{
private:
    static AssetsManager* _instance;

    std::map< std::string, SDL_Texture* > _textures;
    std::map< std::string, SDL_Texture* > _messages;
    std::map< std::string, TTF_Font* > _fonts;


public:
    static AssetsManager* GetInstance();
    static void Free();

    SDL_Texture* GetTexture( const std::string& filename );
    SDL_Texture* GetMessage( const std::string& message, const std::string& fontfile, int size, const SDL_Color& color );

private:
    AssetsManager();
    ~AssetsManager();

    TTF_Font* GetFont( const std::string& fontfile, int size );
};

#endif //GOLDEN_PHOENIX_ASSETSMANAGER_H
