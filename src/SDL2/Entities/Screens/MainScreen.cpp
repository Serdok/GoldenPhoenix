//
// Created by serdok on 16/03/19.
//

#include "MainScreen.h"

MainScreen::MainScreen( Castle* const castle ) : _castle( castle ), Texture( "Piece.png", true )
{
    _inputs = InputsManager::GetInstance();

    _player = new AnimatedTexture( "Sprites/SpritePersonnage.png", 11, 186, 80, 82, 8, 0.5f, AnimatedTexture::horizontal );
    _player->SetScale( Vector2f( 2.0f, 2.5f ) );
    _movesLeft = false;

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

    _ironKey = new Texture( "Objets/Clé en Fer.png" );
    _ironKey->SetScale( Vector2f( 0.5f, 0.5f ) );
    _goldKey = new Texture( "Objets/Clé en Or.png" );
    _goldKey->SetScale( Vector2f( 0.5f, 0.5f ) );
    _lifePotion = new Texture( "Objets/Fiole.png" );
    _lifePotion->SetScale( Vector2f( 0.3f, 0.3f ) );
    _grapplingHook = new Texture( "Objets/Grapin.png" );
    _grapplingHook->SetScale( Vector2f( 0.5f, 0.5f ) );
    _hint = new Texture( "Objets/Parchemin.png" );
    _hint->SetScale( Vector2f( 0.5f, 0.5f ) );
}

MainScreen::~MainScreen()
{
    _castle = nullptr;
    _inputs = nullptr;

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

    delete _ironKey;
    delete _goldKey;
    delete _lifePotion;
    delete _grapplingHook;
    delete _hint;
}

void MainScreen::ProcessEvents( SDL_Event* event )
{
    if (_inputs->KeyDown( SDL_SCANCODE_W ))
        _castle->ProcessActions( "down" );
    if (_inputs->KeyDown( SDL_SCANCODE_A ))
    {
        _castle->ProcessActions( "left" );
        _movesLeft = true;
    }
    if (_inputs->KeyDown( SDL_SCANCODE_S ))
        _castle->ProcessActions( "up" );
    if (_inputs->KeyDown( SDL_SCANCODE_D ))
    {
        _castle->ProcessActions( "right" );
        _movesLeft = false;
    }
}

void MainScreen::Update()
{
    _player->SetPosition( _castle->GetPlayer()->GetPosition());
    _player->Update();
}

void MainScreen::Render()
{
    Texture::Render( SDL_FLIP_NONE );


    const Room* const currentRoom = _castle->GetPlayer()->GetCurrentRoom();

    if (currentRoom->IsCorridor())
        _corridor->Render( SDL_FLIP_NONE );

    // Right door
    const Door* const rightDoor = currentRoom->GetDoor( Room::East );

    switch (rightDoor->GetDoorType())
    {
        case Door::DOORS::grid:_rightGate->Render();
            break;
        case Door::DOORS::door:_rightDoor->Render();
            break;
        case Door::DOORS::opening:_rightOpening->Render();
            break;
        default:break;
    }

    if (rightDoor->HasTorch())
    {
        _rightTorch->Render();
    }


    // Upper door
    const Door* const upDoor = currentRoom->GetDoor( Room::North );

    switch (upDoor->GetDoorType())
    {
        case Door::DOORS::chimney:_chimney->Render();
            break;
        case Door::DOORS::grid:_upGate->Render();
            break;
        case Door::DOORS::door:_upDoor->Render();
            break;
        case Door::DOORS::opening:_upOpening->Render();
            break;
        default:break;
    }

    if (upDoor->HasTorch())
    {
        _upTorch->Render();
    }

    // Left door
    const Door* const leftDoor = currentRoom->GetDoor( Room::West );

    switch (leftDoor->GetDoorType())
    {
        case Door::DOORS::chest:_chest->Render();
            break;
        case Door::DOORS::grid:_leftGate->Render();
            break;
        case Door::DOORS::door:_leftDoor->Render();
            break;
        case Door::DOORS::opening:_leftOpening->Render();
            break;
        default:break;
    }

    if (leftDoor->HasTorch())
    {
        _leftTorch->Render();
    }


    // Ground objects
    for (int x=0 ; x<ROOM_WIDTH; ++x)
        for (int y=0 ; y<ROOM_HEIGHT; ++y)
        {
            switch (currentRoom->GetSquare( Vector2i( x, y ) ))
            {
                case (uint8_t) ObjectID::IronKey:
                    _ironKey->SetPosition( Vector2i( 200 + 20*x, 200 + 20*y ) );
                    _ironKey->Render();
                    break;
                case (uint8_t) ObjectID::GoldenKey:
                    _goldKey->SetPosition( Vector2i( 200 + 20*x, 200 + 20*y ) );
                    _goldKey->Render();
                    break;
                case (uint8_t) ObjectID::LifePotion:
                    _lifePotion->SetPosition( Vector2i( 200 + 20*x, 200 + 20*y ) );
                    _lifePotion->Render();
                    break;
                case (uint8_t) ObjectID::GrapplingHook:
                    _grapplingHook->SetPosition( Vector2i( 200 + 20*x, 200 + 20*y ) );
                    _grapplingHook->Render();
                    break;
                case (uint8_t) ObjectID::Hint1:
                case (uint8_t) ObjectID::Hint2:
                case (uint8_t) ObjectID::Hint3:
                    _hint->SetPosition( Vector2i( 200 + 20*x, 200 + 20*y ) );
                    _hint->Render();
                    break;
                default:
                    break;
            }
        }


    if (_movesLeft)
        _player->Render( SDL_FLIP_HORIZONTAL );
    else
        _player->Render();
}