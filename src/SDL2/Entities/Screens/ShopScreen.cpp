//
// Created by serdok on 16/03/19.
//

#include "ShopScreen.h"

ShopScreen::ShopScreen( Castle* const castle )
: _castle( castle )
{
    _bgi = new Texture( "Marchand.png", true );
}

ShopScreen::~ShopScreen()
{
    _castle = nullptr;

    delete _bgi;
}

void ShopScreen::ProcessEvents( SDL_Event* event )
{

}

void ShopScreen::Update()
{

}

void ShopScreen::Render()
{
    _bgi->Render();
}