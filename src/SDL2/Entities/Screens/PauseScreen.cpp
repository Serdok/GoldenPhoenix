#include "PauseScreen.h"

PauseScreen::PauseScreen( Translation* const trans ) : _translation( trans )
{
    _textLang = new Texture( _translation->GetTranslation( 17 ), "Roboto-Regular.ttf", 30, { 255, 255, 255 } );
    _textLang->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.5f, Graphics::SCREEN_HEIGHT*0.6f ));
    _text = new Texture( "PAUSE", "Pasatona.ttf", 60, { 255, 255, 255 } );
    _text->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.5f, Graphics::SCREEN_HEIGHT*0.1f ));
    _textSound = new Texture( "S : " + _translation->GetTranslation( 25 ), "Roboto-Regular.ttf", 30, { 255, 255, 255 } );
    _textSound->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.5f, Graphics::SCREEN_HEIGHT*0.4f ));

}

PauseScreen::~PauseScreen()
{
    delete _text;
    delete _textLang;
    delete _textSound;
}

void PauseScreen::ProcessEvents( SDL_Event* event )
{

}

void PauseScreen::Update()
{
    if (_translationChanged)
    {
        _textLang = new Texture( _translation->GetTranslation( 17 ), "Roboto-Regular.ttf", 30, { 255, 255, 255 } );
        _textLang->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.5f, Graphics::SCREEN_HEIGHT*0.6f ));
        _text = new Texture( "PAUSE", "Pasatona.ttf", 60, { 255, 255, 255 } );
        _text->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.5f, Graphics::SCREEN_HEIGHT*0.1f ));
        _textSound = new Texture( "S : " + _translation->GetTranslation( 25 ), "Roboto-Regular.ttf", 30,
                                  { 255, 255, 255 } );
        _textSound->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.5f, Graphics::SCREEN_HEIGHT*0.4f ));

        _translationChanged = false;
    }
}

void PauseScreen::Render()
{
    _text->Render();
    _textLang->Render();
    _textSound->Render();
}

void PauseScreen::SetTranslation( Translation* const translation )
{
    _translation = translation;
    _translationChanged = true;
}