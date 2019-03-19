//
// Created by serdok on 05/03/19.
//

#include "StartScreen.h"

StartScreen::StartScreen( Castle* const castle )
: Texture( "Image Accueil.png", true ), _castle( castle )
{
    _inputs = InputsManager::GetInstance();

    _startText = new Texture( "Castle", "Pasatona.ttf", 20, { 255, 255, 255 } );
    _startText->SetPosition( Vector2f( 660, 220 ));

    _shopText = new Texture( "Shop", "Pasatona.ttf", 20, { 255, 255, 255 } );
    _shopText->SetPosition( Vector2f( 100, 250 ));

    _player = new AnimatedTexture( "Sprites/SpritePersonnage.png", 11, 186, 80, 82, 8, 0.5f, AnimatedTexture::horizontal );
    _castle->GetPlayer()->SetPosition( Vector2f( Graphics::SCREEN_WIDTH/2.0f - 100.0f, Graphics::SCREEN_HEIGHT - 50.0f ) );
}

StartScreen::~StartScreen()
{
    _castle = nullptr;
    _inputs = nullptr;

    delete _shopText;
    delete _startText;
    delete _player;
}

void StartScreen::Update()
{
    _player->SetPosition( _castle->GetPlayer()->GetPosition() );
    _player->Update();
}

void StartScreen::Render()
{
    Texture::Render();
    _startText->Render();
    _shopText->Render();
    _player->Render();
}

void StartScreen::ProcessEvents( SDL_Event* event )
{
    if (_inputs->KeyDown( SDL_SCANCODE_W ))
        _castle->ProcessActions( "down" );
    if (_inputs->KeyDown( SDL_SCANCODE_A ))
        _castle->ProcessActions( "left" );
    if (_inputs->KeyDown( SDL_SCANCODE_S ))
        _castle->ProcessActions( "up" );
    if (_inputs->KeyDown( SDL_SCANCODE_D ))
        _castle->ProcessActions( "right" );
}