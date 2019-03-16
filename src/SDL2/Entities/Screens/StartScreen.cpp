//
// Created by serdok on 05/03/19.
//

#include "StartScreen.h"

StartScreen::StartScreen()
{
    _bgi = new Texture( "Image Accueil.png", true );
    _bgi->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.5f, Graphics::SCREEN_HEIGHT*0.5f ));

    _startText = new Texture( "Castle", "Pasatona.ttf", 20, { 255, 255, 255 } );
    _startText->SetPosition( Vector2f( 660, 220 ));

    _shopText = new Texture( "Shop", "Pasatona.ttf", 20, { 255, 255, 255 } );
    _shopText->SetPosition( Vector2f( 100, 250 ));
}

StartScreen::~StartScreen()
{
    delete _shopText;
    delete _startText;
    delete _bgi;
}

void StartScreen::Update()
{

}

void StartScreen::Render()
{
    _bgi->Render();
    _startText->Render();
    _shopText->Render();
}

void StartScreen::ProcessEvents( SDL_Event* event )
{

}