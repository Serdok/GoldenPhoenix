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

}

IntroScreen::~IntroScreen()
{
    delete _text1;
    delete _text2;
    delete _text3;
}

void IntroScreen::ProcessEvents( SDL_Event* event )
{
    if (_inputs->KeyPressed( SDL_SCANCODE_Q )) _quit=true;
}

void IntroScreen::Update()
{
    if(_nbCaractereRead1+1<text1.size()){
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
    }
    else if(_nbCaractereRead3+1<text3.size()){
        _caractereRead3.push_back(text3.at(_nbCaractereRead3));
        _nbCaractereRead3++;
        delete _text3;
        _text3 = new Texture( _caractereRead3, "Roboto-Regular.ttf", 25, { 255, 255, 255 } );
        _text3->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.5f, Graphics::SCREEN_HEIGHT*0.6f ));
    }
    //else
      //  _quit=true;
}

void IntroScreen::Render()
{
    _text1->Render();
    _text2->Render();
    _text3->Render();
}


bool IntroScreen::GetQuit() const 
{
    return _quit;
}
