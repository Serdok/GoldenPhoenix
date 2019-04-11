//
// Created by serdok on 10/04/19.
//

#include "AssetsManager.h"

AssetsManager* AssetsManager::_instance = nullptr;

AssetsManager* AssetsManager::GetInstance()
{
    if (!_instance)
        _instance = new AssetsManager();
    return _instance;
}

void AssetsManager::Free()
{
    delete _instance;
}

AssetsManager::AssetsManager() = default;

AssetsManager::~AssetsManager()
{
    for (auto& texture : _textures)
        Cleanup( texture.second );
    _textures.clear();

    for (auto& font : _fonts)
        Cleanup( font.second );
    _fonts.clear();

    for (auto& message : _messages)
        Cleanup( message.second );
    _messages.clear();
}

SDL_Texture* AssetsManager::GetTexture( const std::string& filename )
{
    std::string path = GetResourcePath( "images/" + filename );
    if (_textures.find( path ) == _textures.end())
    {
        std::cout << "New image found! Saving image ..." << std::endl;
        _textures[ path ] = Graphics::GetInstance()->LoadTexture( path );
    }

    std::cout << "Loaded image '" << filename << "' from cache! (path = " << path << ")" << std::endl;
    return _textures.at( path );
}

TTF_Font* AssetsManager::GetFont( const std::string& fontfile, int size )
{
    std::string path = GetResourcePath( "fonts/" + fontfile );
    std::string key = path + std::to_string( size );
    if (_fonts.find( key ) == _fonts.end())
    {
        std::cout << "New font found! Saving font ..." << std::endl;
        _fonts[ key ] = TTF_OpenFont( path.c_str(), size );
        if (!_fonts.at( key ))
            std::cerr << "Font " + path + " failed to load : " << SDL_GetError() << std::endl;
    }


    std::cout << "Loaded font '" << fontfile << "' from cache!(key = " << key << ")" << std::endl;
    return _fonts.at( key );
}

SDL_Texture* AssetsManager::GetMessage( const std::string& message, const std::string& fontfile, int size, const SDL_Color& color )
{
    TTF_Font* font = GetFont( fontfile, size );
    std::string key = message + fontfile + std::to_string( size ) + std::to_string( color.r ) + std::to_string( color.g ) + std::to_string( color.b ) + std::to_string( color.a );
    if (_messages.find( key ) == _messages.end())
    {
        std::cout << "New message found! Saving message ..." << std::endl;
        _messages[ key ] = Graphics::GetInstance()->CreateTextTexture( font, message, color );
    }

    std::cout << "Loaded '" << message << "' from cache! (key = " << key << ")" << std::endl;
    return _messages.at( key );
}