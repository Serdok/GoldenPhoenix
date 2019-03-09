//
// Created by serdok on 09/03/19.
//

#include "Texture.h"

Texture::Texture( const std::string& imagefile, bool fullscreen ) : _texture( nullptr ), _clipped( false ),
                                                                    _fullscreen( fullscreen )
{
    // TODO Will be loaded with the assets manager later
    _texture = Graphics::GetInstance()->LoadTexture( GetResourcePath( "images/" + imagefile ));

    SDL_QueryTexture( _texture, nullptr, nullptr, &_width, &_height );
    _dest.w = _width;
    _dest.h = _height;
}

Texture::Texture( const std::string& imagefile, int x, int y, int width, int height, bool fullscreen ) : _texture(
        nullptr ), _clipped( true ), _fullscreen( fullscreen )
{
    // TODO Will be loaded with the assets manager later
    _texture = Graphics::GetInstance()->LoadTexture( GetResourcePath( "images/" + imagefile ));

    _dest.w = _width = width;
    _dest.h = _height = height;

    _clip = { x, y, height, width };
}

Texture::Texture( const std::string& text, const std::string& font, int size, const SDL_Color& color, bool fullscreen )
        : _texture( nullptr ), _clipped( false ), _fullscreen( fullscreen )
{
    // TODO Will be loaded with the assets manager later
    TTF_Font* tempFont = TTF_OpenFont( GetResourcePath( "fonts/" + font ).c_str(), size );
    assert( tempFont );

    _texture = Graphics::GetInstance()->CreateTextTexture( tempFont, text, color );
    Cleanup( tempFont );

    SDL_QueryTexture( _texture, nullptr, nullptr, &_width, &_height );
    _dest.w = _width;
    _dest.h = _height;
}

Texture::~Texture()
{
    Cleanup( _texture );
}

void Texture::Update()
{
    // Overridden in derived classes
}

void Texture::Render()
{
    Vector2f position = GetPosition();
    Vector2f scale = GetScale();

    _dest.x = (int) ( position.x - _width*scale.x*0.5f );
    _dest.y = (int) ( position.y - _height*scale.y*0.5f );
    _dest.w = (int) ( _width*scale.x );
    _dest.h = (int) ( _height*scale.y );

    Graphics::GetInstance()->DrawTexture( _texture, ( _clipped ? &_clip : nullptr ), ( _fullscreen ? nullptr : &_dest ),
                                          GetRotation());
}