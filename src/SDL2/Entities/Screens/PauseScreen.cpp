#include "PauseScreen.h"

PauseScreen::PauseScreen( Translation* const trans ) : _translation( trans )
{
    _textLang = new Texture( _translation->GetTranslation( 17 ), "Roboto-Regular.ttf", 30, { 255, 255, 255 } );
    _textLang->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.5f, Graphics::SCREEN_HEIGHT*0.5f ));
    _text = new Texture( "PAUSE", "Pasatona.ttf", 60, { 255, 255, 255 } );
    _text->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.5f, Graphics::SCREEN_HEIGHT*0.1f ));

}

PauseScreen::~PauseScreen()
{
    delete _text;
    delete _textLang;
}

void PauseScreen::ProcessEvents( SDL_Event* event )
{

}

void PauseScreen::Update()
{

}

void PauseScreen::Render()
{
    _text->Render();
    _textLang->Render();
}