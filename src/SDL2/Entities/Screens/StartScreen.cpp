//
// Created by serdok on 05/03/19.
//

#include "StartScreen.h"

StartScreen::StartScreen( Castle* const castle, Translation* const trans ) : Texture( "Image Accueil.png", true ), _castle( castle ), _translation( trans)
{
    _inputs = InputsManager::GetInstance();

    _shopText = new Texture( "1 :  " + _translation->GetTranslation(2), "Roboto-Regular.ttf", 20, { 255, 255, 255 } );
    _shopText->SetPosition( Vector2f( 100, 250 ));

    _startText = new Texture( "2 :  " + _translation->GetTranslation(3), "Roboto-Regular.ttf", 20, { 255, 255, 255 } );
    _startText->SetPosition( Vector2f( 680, 220 ));

    _tomb = new Texture( "Objets/Tombe.png" );
    _tomb->SetScale( Vector2f( 0.1f, 0.1f ));

    _reset = new Texture( "0 : " + _translation->GetTranslation( 34 ), "Roboto-Regular.ttf", 10, { 255, 255, 255 } );
    _reset->SetPosition( Vector2f( Graphics::SCREEN_WIDTH - _reset->GetWidth()/2.0f, Graphics::SCREEN_HEIGHT - _reset->GetHeight()/2.0f ) );
}

StartScreen::~StartScreen()
{
    _inputs = nullptr;

    delete _tomb;
    delete _shopText;
    delete _startText;
    delete _reset;
}

void StartScreen::Update()
{

}

void StartScreen::Render()
{
    // Render the background image
    Texture::Render();

    // Render text textures
    _startText->Render();
    _shopText->Render();

    // Render the Tombs
    for (unsigned int i = 0 ; i < _castle->GetPlayer()->GetDeaths() && i < 10 ; i++)
    {
        _tomb->SetPosition( Vector2f( 450 + 70*( i%5 )-(50*int( i/5 )), 500 + 50*int( i/5 )));
        _tomb->Render();
    }

    _reset->Render();
}

void StartScreen::ProcessEvents( SDL_Event* event )
{
    // No events processing (for the moment)
}

void StartScreen::SetTranslation( Translation* const translation )
{
    _translation = translation;

    delete _shopText;
    delete _startText;
    delete _reset;

    _shopText = new Texture( "1 :  " + _translation->GetTranslation(2), "Roboto-Regular.ttf", 20, { 255, 255, 255 } );
    _shopText->SetPosition( Vector2f( 100, 250 ));

    _startText = new Texture( "2 :  " + _translation->GetTranslation(3), "Roboto-Regular.ttf", 20, { 255, 255, 255 } );
    _startText->SetPosition( Vector2f( 680, 220 ));

    _reset = new Texture( "3 : " + _translation->GetTranslation( 34 ), "Roboto-Regular.ttf", 10, { 255, 255, 255 } );
    _reset->SetPosition( Vector2f( Graphics::SCREEN_WIDTH - _reset->GetWidth()/2.0f, Graphics::SCREEN_HEIGHT - _reset->GetHeight()/2.0f ) );
}

void StartScreen::SetCastle( Castle* castle )
{
    _castle = castle;
}