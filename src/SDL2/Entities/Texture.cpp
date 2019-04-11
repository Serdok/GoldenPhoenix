//
// Created by serdok on 09/03/19.
//

#include "Texture.h"

Texture::Texture( const std::string& imagefile, bool fullscreen )
: _fullscreen( fullscreen )
{
    // Load the image
    _texture = AssetsManager::GetInstance()->GetTexture( imagefile );
    //_texture = Graphics::GetInstance()->LoadTexture( GetResourcePath("images/"+imagefile) );

    // Fetch image size
    SDL_QueryTexture( _texture, nullptr, nullptr, &_width, &_height );
    std::cout << "Size of loaded " << imagefile << " : " << _width << "x" << _height << std::endl;
    _dest.w = _width;
    _dest.h = _height;
}

Texture::Texture( const std::string& imagefile, int x, int y, int width, int height, bool fullscreen )
: _clipped( true ), _fullscreen( fullscreen )
{
    // Load the image
    _texture = AssetsManager::GetInstance()->GetTexture( imagefile );
    //_texture = Graphics::GetInstance()->LoadTexture( GetResourcePath("images/"+imagefile) );

    // Set image sizes
    _dest.w = _width = width;
    _dest.h = _height = height;

    std::cout << "Size of loaded " << imagefile << " : " << _width << "x" << _height << std::endl;

    // Set clip size
    _clip = { x, y, width, height };
}

Texture::Texture( const std::string& text, const std::string& font, int size, const SDL_Color& color, bool fullscreen )
: _fullscreen( fullscreen )
{
    // Convert message to texture
    _texture = AssetsManager::GetInstance()->GetMessage( text, font, size, color );
    //_texture = Graphics::GetInstance()->CreateTextTexture( TTF_OpenFont(GetResourcePath("fonts/" + font).c_str(), size), text, color );

    // Fetch texture size
    SDL_QueryTexture( _texture, nullptr, nullptr, &_width, &_height );
    std::cout << "Size of loaded '" << text << "' : " << _width << "x" << _height << std::endl;
    _dest.w = _width;
    _dest.h = _height;
}

Texture::~Texture()
{
    Cleanup( _texture );
}

int Texture::GetWidth() const
{
    return _width;
}

int Texture::GetHeight() const
{
    return _height;
}

void Texture::SetAlpha( unsigned char alpha )
{
    SDL_SetTextureAlphaMod( _texture, alpha );
}

void Texture::SetBlendingMode( SDL_BlendMode mode )
{
    SDL_SetTextureBlendMode( _texture, mode );
}

void Texture::Update()
{
    // Overridden in derived classes
}

void Texture::Render()
{
    // Calculate destination coordinates. Image will be rendered from its center point
    Vector2f position = GetPosition();
    Vector2f scale = GetScale();

    _dest.x = (int) ( position.x - _width*scale.x*0.5f );
    _dest.y = (int) ( position.y - _height*scale.y*0.5f );
    _dest.w = (int) ( _width*scale.x );
    _dest.h = (int) ( _height*scale.y );

    // Load texture in renderer
    Graphics::GetInstance()->DrawTexture( _texture, ( _clipped ? &_clip : nullptr ), ( _fullscreen ? nullptr : &_dest ),
                                          GetRotation() );
}

void Texture::Render( SDL_RendererFlip flip )
{
    // Calculate destination coordinates. Image will be rendered from its center point
    Vector2f position = GetPosition();
    Vector2f scale = GetScale();

    _dest.x = (int) ( position.x - _width*scale.x*0.5f );
    _dest.y = (int) ( position.y - _height*scale.y*0.5f );
    _dest.w = (int) ( _width*scale.x );
    _dest.h = (int) ( _height*scale.y );

    // Load texture in renderer
    Graphics::GetInstance()->DrawTexture( _texture, ( _clipped ? &_clip : nullptr ), ( _fullscreen ? nullptr : &_dest ),
                                          GetRotation(), flip );
}