#include "IntroScreen.h"

IntroScreen::IntroScreen()
{
    _nbCaractereRead1 = 15;
    for(unsigned int b = 0; b < 15; b++)
    {
        _caractereRead1.push_back(text1.at(b));
    }

    _text1 = new Texture( _caractereRead1, "Roboto-Regular.ttf", 15, { 255, 255, 255 } );
    _text2 = new Texture( " ", "Roboto-Regular.ttf", 15, { 255, 255, 255 } );
    _text3 = new Texture( " ", "Roboto-Regular.ttf", 15, { 255, 255, 255 } );
    _textQuit = new Texture( "Q pour passer...", "Roboto-Regular.ttf", 15, { 255, 255, 255 } );
    
    _text1->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.5f, Graphics::SCREEN_HEIGHT*0.4f ));
    
    _textQuit->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.5f, Graphics::SCREEN_HEIGHT*0.8f ));
    _textQuit->SetActive( false );


}

IntroScreen::~IntroScreen()
{
    delete _text1;
    delete _text2;
    delete _text3;
    delete _textQuit;
}

void IntroScreen::ProcessEvents( SDL_Event* event )
{
   
}

void IntroScreen::Update()
{
    if (_temps % FPS == 0)
    {
        if(_nbCaractereRead1+1<text1.size()){
            _caractereRead1.push_back(text1.at(_nbCaractereRead1));
            _nbCaractereRead1++;
            _caractereRead1.push_back(text1.at(_nbCaractereRead1));
            _nbCaractereRead1++;
            delete _text1;
            _text1 = new Texture( _caractereRead1, "Roboto-Regular.ttf", 25, { 255, 255, 255 } );
            _text1->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.5f, Graphics::SCREEN_HEIGHT*0.4f ));
        }
        else if(_nbCaractereRead2+1<text2.size()){
            _caractereRead2.push_back(text2.at(_nbCaractereRead2));
            _nbCaractereRead2++;
            delete _text2;
            _text2 = new Texture( _caractereRead2, "Roboto-Regular.ttf", 25, { 255, 255, 255 } );
            _text2->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.5f, Graphics::SCREEN_HEIGHT*0.5f ));
            _caractereRead2.push_back(text2.at(_nbCaractereRead2));
            _nbCaractereRead2++;
            delete _text2;
            _text2 = new Texture( _caractereRead2, "Roboto-Regular.ttf", 25, { 255, 255, 255 } );
            _text2->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.5f, Graphics::SCREEN_HEIGHT*0.5f ));
        }
        else if(_nbCaractereRead3+1<text3.size()){
            _caractereRead3.push_back(text3.at(_nbCaractereRead3));
            _nbCaractereRead3++;
            _caractereRead3.push_back(text3.at(_nbCaractereRead3));
            _nbCaractereRead3++;
            delete _text3;
            _text3 = new Texture( _caractereRead3, "Roboto-Regular.ttf", 25, { 255, 255, 255 } );
            _text3->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.5f, Graphics::SCREEN_HEIGHT*0.6f ));
        }
        else
        {
            _quitPossible = true;
            _textQuit->SetActive( !_textQuit->GetActive() );
        }
    }

    _temps++;
}

void IntroScreen::Render()
{
    _text1->Render();
    _text2->Render();
    _text3->Render();
    if (_textQuit->GetActive())
        _textQuit->Render();
}

bool IntroScreen::GetQuitPossible() const
{
    return _quitPossible;
}