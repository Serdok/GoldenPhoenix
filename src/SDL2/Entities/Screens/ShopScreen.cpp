//
// Created by serdok on 16/03/19.
//

#include "ShopScreen.h"

ShopScreen::ShopScreen( Castle* const castle )
: _castle( castle ), Texture( "Marchand.png", true )
{

}

ShopScreen::~ShopScreen()
{
    _castle = nullptr;
}

void ShopScreen::ProcessEvents( SDL_Event* event )
{

}

void ShopScreen::Update()
{

}

void ShopScreen::Render()
{
    Texture::Render();
}