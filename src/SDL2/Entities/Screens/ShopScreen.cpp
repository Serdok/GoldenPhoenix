//
// Created by serdok on 16/03/19.
//

#include "ShopScreen.h"

ShopScreen::ShopScreen()
{
    _castle = new Castle( GetResourcePath( "rooms/testroom.txt" ) );

    _bgi = new Texture( "Marchand.png", true );
}

ShopScreen::~ShopScreen()
{
    delete _castle;
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