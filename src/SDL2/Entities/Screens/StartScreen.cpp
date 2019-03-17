//
// Created by serdok on 05/03/19.
//

#include "StartScreen.h"

StartScreen::StartScreen()
: Texture( "Image Accueil.png", true )
{
    _startText = new Texture( "Castle", "Pasatona.ttf", 20, { 255, 255, 255 } );
    _startText->SetPosition( Vector2f( 660, 220 ));

    _shopText = new Texture( "Shop", "Pasatona.ttf", 20, { 255, 255, 255 } );
    _shopText->SetPosition( Vector2f( 100, 250 ));
}

StartScreen::~StartScreen()
{
    delete _shopText;
    delete _startText;
}

void StartScreen::Update()
{

}

void StartScreen::Render()
{
    Texture::Render();
    _startText->Render();
    _shopText->Render();
}

void StartScreen::ProcessEvents( SDL_Event* event )
{

}