//
// Created by serdok on 16/03/19.
//

#include "MainScreen.h"

MainScreen::MainScreen( Castle* const castle )
: _castle( castle )
{
    _player = new Texture( "Sprites/SpritePersonnage.png", 15, 181, 71, 88 );

    _chimney = new Texture( "Salles/Chemine.png", true );
    _chest = new Texture( "Salles/Coffre.png", true );
    _corridor = new Texture( "Salles/Couloir.png", true );
    _leftGate = new Texture( "Salles/GrilleG.png", true );
    _upGate = new Texture( "Salles/GrilleH.png", true );
    _rightGate = new Texture( "Salles/GrilleD.png", true );
    _leftOpening = new Texture( "Salles/OuvertureG.png", true );
    _upOpening = new Texture( "Salles/OuvertureH.png", true );
    _rightOpening = new Texture( "Salles/OuvertureD.png", true );
    _leftDoor = new Texture( "Salles/PorteG.png", true );
    _upDoor = new Texture( "Salles/PorteH.png", true );
    _rightDoor = new Texture( "Salles/PorteD.png", true );
    _leftTorch = new Texture( "Salles/TorcheG.png", true );
    _upTorch = new Texture( "Salles/TorcheH.png", true );
    _rightTorch = new Texture( "Salles/TorcheD.png", true );
}

MainScreen::~MainScreen()
{
    _castle = nullptr;

    delete _chimney;
    delete _chest;
    delete _corridor;
    delete _rightGate;
    delete _upGate;
    delete _leftGate;
    delete _rightOpening;
    delete _upOpening;
    delete _leftOpening;
    delete _rightDoor;
    delete _upDoor;
    delete _leftDoor;
    delete _rightTorch;
    delete _upTorch;
    delete _leftTorch;
}

void MainScreen::ProcessEvents( SDL_Event* event )
{
    if (event->type == SDL_KEYDOWN)
    {
        switch (event->key.keysym.scancode)
        {
            case SDL_SCANCODE_Z:
                _castle->ProcessActions( "up" );
                break;
            case SDL_SCANCODE_Q:
                _castle->ProcessActions( "left" );
                break;
            case SDL_SCANCODE_S:
                _castle->ProcessActions( "down" );
                break;
            case SDL_SCANCODE_D:
                _castle->ProcessActions( "right" );
                break;
            default:
                break;
        }
    }
}

void MainScreen::Update()
{
    _player->SetPosition( _castle->GetPlayer()->GetPosition() );
    std::cout << _player->GetPosition() << std::endl;
}

void MainScreen::Render()
{
    _corridor->Render();
    _chimney->Render();
    _chest->Render();

    _player->Render();
}