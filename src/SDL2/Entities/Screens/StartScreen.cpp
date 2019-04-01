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

	_tomb = new Texture("Objects/Tombe.png", true);
	_tomb -> SetScale( Vector2f( 0.3f, 0.3f ) );	
}

StartScreen::~StartScreen()
{
    _inputs = nullptr;

	delete _tomb;
    delete _shopText;
    delete _startText;
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
	for (unsigned int i = 0; i < _castle->GetPlayer()->GetDeaths() && i < 8; i++) {
		_tomb->SetPosition(Vector2f(420+80*(i%4), 500 + 50 * int(i/4)));
		_tomb->Render();
	}
}

void StartScreen::ProcessEvents( SDL_Event* event )
{
    // No events processing (for the moment)
}