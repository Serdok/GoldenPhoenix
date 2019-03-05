//
// Created by serdok on 05/03/19.
//

#include "StartScreen.h"

StartScreen::StartScreen()
{
    _audio = AudioManager::GetInstance();
    _timer = Timer::GetInstance();

    _bgm = _audio->LoadMusic( "The One.mp3" );
    _audio->PlayMusic( _bgm );

    _bgi = Texture::LoadImage( "images/Image Accueil.png" );

    _font = TTF_OpenFont( GetResourcePath( "fonts/Pasatona.ttf" ).c_str(), 20 );
    assert( _font );

    _startText = Texture::LoadText( "Castle", _font, { 255, 255, 255 } );
    _startTextDestination = { 660, 220, 70, 70 };
    SDL_QueryTexture( _startText, nullptr, nullptr, &_startTextDestination.w, &_startTextDestination.h );

    _shopText = Texture::LoadText( "Shop", _font, { 255, 255, 255 } );
    _shopTextDestination = { 100, 250, 70, 70 };
    SDL_QueryTexture( _shopText, nullptr, nullptr, &_shopTextDestination.w, &_shopTextDestination.h );
}

StartScreen::~StartScreen()
{
    Cleanup( _bgi, _startText, _shopText, _font );
    _audio->FreeMusic( _bgm );
    _audio = nullptr;
    _timer = nullptr;
}

void StartScreen::Update()
{

}

void StartScreen::Render()
{
    Texture::Draw( _bgi );
    Texture::Draw( _startText, nullptr, &_startTextDestination );
    Texture::Draw( _shopText, nullptr, &_shopTextDestination );
}

void StartScreen::ProcessEvents( SDL_Event* event )
{

}