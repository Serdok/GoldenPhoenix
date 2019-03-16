//
// Created by serdok on 16/03/19.
//

#include "MainScreen.h"

MainScreen::MainScreen()
{
    _castle = new Castle( GetResourcePath( "rooms/testroom.txt" ) );

    _chimney = new Texture( "Salles/Chemine.png", true );
    _chest = new Texture( "Salles/Coffre.png", true );
    _corridor = new Texture( "Salles/Couloir.png", true );
}

MainScreen::~MainScreen()
{
    delete _castle;
    delete _chimney;
    delete _chest;
    delete _corridor;
    /*_rightGate, _upGate, _leftGate, _rightOpening, _upOpening, _leftOpening,
            _rightDoor, _upDoor, _leftDoor, _rightTorch, _upTorch, _leftTorch*/
}

void MainScreen::ProcessEvents( SDL_Event* event )
{

}

void MainScreen::Update()
{

}

void MainScreen::Render()
{
    _corridor->Render();
    _chimney->Render();
    _chest->Render();
}