//
// Created by serdok on 05/03/19.
//

#include "StartScreen.h"

StartScreen::StartScreen( Castle* const castle )
: Texture( "Image Accueil.png", true ), _castle( castle )
{
    _inputs = InputsManager::GetInstance();

    _shopText = new Texture( "1 : Shop", "Roboto-Regular.ttf", 20, { 255, 255, 255 } );
    _shopText->SetPosition( Vector2f( 100, 250 ));

    _startText = new Texture( "2 : Castle", "Roboto-Regular.ttf", 20, { 255, 255, 255 } );
    _startText->SetPosition( Vector2f( 680, 220 ));
}

StartScreen::~StartScreen()
{
    _inputs = nullptr;

    delete _shopText;
    delete _startText;
}

void StartScreen::Update()
{
    _castle->Update();
}

void StartScreen::Render()
{
    // Render the background image
    Texture::Render();

    // Render text textures
    _startText->Render();
    _shopText->Render();
}

void StartScreen::ProcessEvents( SDL_Event* event )
{
    // No events processing (for the moment)
}