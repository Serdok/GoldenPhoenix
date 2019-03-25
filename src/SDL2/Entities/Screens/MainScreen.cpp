//
// Created by serdok on 16/03/19.
//

#include "MainScreen.h"

MainScreen::MainScreen( Castle* const castle ) : _castle( castle ), Texture( "Piece.png", true )
{
#ifdef DEBUG
    _castle->GetPlayer()->AddItem( Object::CROWBAR );
    _castle->GetPlayer()->AddItem( Object::IRON_KEY );
    _castle->GetPlayer()->AddItem( Object::GOLDEN_KEY );
    _castle->GetPlayer()->SetCurrentRoom( _castle->GetRooms().at( 6 - 1 ));
#endif // DEBUG

    _inputs = InputsManager::GetInstance();

#ifdef DEBUG
    _player = new Texture( "Player_minimal.png" );
#else
    _player = new AnimatedTexture( "Sprites/SpritePersonnage.png", 11, 186, 80, 82, 8, 0.5f, AnimatedTexture::horizontal );
    _player->SetScale( Vector2f( 2.0f, 2.5f ) );
#endif // DEBUG

    _movesLeft = false;

    _score = new Texture( "Score : ", "Roboto-Regular.ttf", 25, { 255, 255, 255 } );
    _score->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.2f, Graphics::SCREEN_HEIGHT*0.9f ) );

    _life = new Texture( "Life : ", "Roboto-Regular.ttf", 25, { 255, 255, 255 } );
    _life->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.2f, Graphics::SCREEN_HEIGHT*0.8f ) );

    _item = new Texture( "Hand : ", "Roboto-Regular.ttf", 25, { 255, 255, 255 } );
    _item->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.8f, Graphics::SCREEN_HEIGHT*0.8f ) );

    _money = new Texture( "Money : ", "Roboto-Regular.ttf", 25, { 255, 255, 255 } );
    _money->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.8f, Graphics::SCREEN_HEIGHT*0.9f ) );

#ifdef DEBUG
    _leftRoomID = new Texture( "ID : ", "Roboto-Regular.ttf", 15, { 255, 255, 255 } );
    _leftRoomID->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.2f, Graphics::SCREEN_HEIGHT*0.3f ) );

    _upperRoomID = new Texture( "ID : ", "Roboto-Regular.ttf", 15, { 255, 255, 255 } );
    _upperRoomID->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.5f, Graphics::SCREEN_HEIGHT*0.1f ) );

    _rightRoomID = new Texture( "ID : ", "Roboto-Regular.ttf", 15, { 255, 255, 255 } );
    _rightRoomID->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.8f, Graphics::SCREEN_HEIGHT*0.3f ) );
#endif // DEBUG

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

#ifdef DEBUG
    delete _leftRoomID;
    delete _upperRoomID;
    delete _rightRoomID;
#endif // DEBUG

    delete _player;
    delete _score;
    delete _life;
    delete _item;
    delete _money;

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
        _castle->ProcessActions( "up" );
    if (_inputs->KeyDown( SDL_SCANCODE_A ))
    {
        _castle->ProcessActions( "left" );
        _movesLeft = true;
    }
    if (_inputs->KeyDown( SDL_SCANCODE_S ))
        _castle->ProcessActions( "down" );
    if (_inputs->KeyDown( SDL_SCANCODE_D ))
    {
        _castle->ProcessActions( "right" );
        _movesLeft = false;
    }
    if (_inputs->KeyPressed( SDL_SCANCODE_LSHIFT ))
        _castle->ProcessActions( "duck" );
    if (_inputs->KeyPressed( SDL_SCANCODE_SPACE ))
        _castle->ProcessActions( "jump" );

    if (_inputs->KeyPressed( SDL_SCANCODE_1 ))
        _castle->ProcessActions( "inv 0" );
    if (_inputs->KeyPressed( SDL_SCANCODE_2 ))
        _castle->ProcessActions( "inv 1" );
    if (_inputs->KeyPressed( SDL_SCANCODE_3 ))
        _castle->ProcessActions( "inv 2" );
    if (_inputs->KeyPressed( SDL_SCANCODE_4 ))
        _castle->ProcessActions( "inv 3" );
    if (_inputs->KeyPressed( SDL_SCANCODE_5 ))
        _castle->ProcessActions( "inv 4" );
    if (_inputs->KeyPressed( SDL_SCANCODE_6 ))
        _castle->ProcessActions( "inv 5" );
    if (_inputs->KeyPressed( SDL_SCANCODE_7 ))
        _castle->ProcessActions( "inv 6" );
    if (_inputs->KeyPressed( SDL_SCANCODE_8 ))
        _castle->ProcessActions( "inv 7" );
    if (_inputs->KeyPressed( SDL_SCANCODE_9 ))
        _castle->ProcessActions( "inv 8" );
    if (_inputs->KeyPressed( SDL_SCANCODE_0 ))
        _castle->ProcessActions( "inv 9" );

    if (_inputs->KeyPressed( SDL_SCANCODE_RETURN ))
        _castle->ProcessActions( "pick" );

}

void MainScreen::Update()
{
    // Update the game
    _castle->Update();

    // Update the animated texture
    _player->Update();

    // Update the score
    delete _score;
    _score = new Texture( "Score : " + std::to_string( _castle->GetScore() ), "Roboto-Regular.ttf", 25, { 255, 255, 255 } );
    _score->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.2f, Graphics::SCREEN_HEIGHT*0.9f ) );

    // Update the life
    delete _life;
    _life = new Texture( "Life : " + std::to_string( _castle->GetPlayer()->GetLife() ), "Roboto-Regular.ttf", 25, { 255, 255, 255 } );
    _life->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.2f, Graphics::SCREEN_HEIGHT*0.8f ) );

    // Update the held item
    delete _item;
    const ItemStack& held = _castle->GetPlayer()->GetHeldItem();
    SDL_Color color = { 255, 255, 255 };
    if (held.GetObject().ToObjectID() == ObjectID::Crowbar)
    {
        auto red = (Uint8) LinearInterp( 0, 255, (float) held.GetDurability()/Object::CROWBAR.durability );
        auto green = (Uint8) LinearInterp( 255, 0, (float) held.GetDurability()/Object::CROWBAR.durability );

        color = { red, green, 0, 0xFF };
    }


    _item = new Texture( "Hand : " + held.GetObject().ToString(), "Roboto-Regular.ttf", 25, color );
    _item->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.8f, Graphics::SCREEN_HEIGHT*0.8f ) );

    // Update the money
    delete _money;
    _money = new Texture( "Money : " + std::to_string( _castle->GetPlayer()->GetMoney() ), "Roboto-Regular.ttf", 25, { 255, 255, 255 } );
    _money->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.8f, Graphics::SCREEN_HEIGHT*0.9f ) );

#ifdef DEBUG
    // Update room ID
    delete _leftRoomID;
    _leftRoomID = new Texture( "ID : " + std::to_string( _castle->GetPlayer()->GetCurrentRoom()->GetRoomID( Room::Left ) ), "Roboto-Regular.ttf", 15, { 255, 255, 255 } );
    _leftRoomID->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.04f, Graphics::SCREEN_HEIGHT*0.5f ) );

    delete _upperRoomID;
    _upperRoomID = new Texture( "ID : " + std::to_string( _castle->GetPlayer()->GetCurrentRoom()->GetRoomID( Room::Up ) ), "Roboto-Regular.ttf", 15, { 255, 255, 255 } );
    _upperRoomID->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.5f, Graphics::SCREEN_HEIGHT*0.05f ) );

    delete _rightRoomID;
    _rightRoomID = new Texture( "ID : " + std::to_string( _castle->GetPlayer()->GetCurrentRoom()->GetRoomID( Room::Right ) ), "Roboto-Regular.ttf", 15, { 255, 255, 255 } );
    _rightRoomID->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.96f, Graphics::SCREEN_HEIGHT*0.5f ) );
#endif // DEBUG
}

void MainScreen::Render()
{
    // Background image
    Texture::Render();

    // Lower texts & info
    _score->Render();
    _life->Render();
    _item->Render();
    _money->Render();

#ifdef DEBUG
    _leftRoomID->Render();
    _upperRoomID->Render();
    _rightRoomID->Render();
#endif // DEBUG


    // Room info
    const Room* const currentRoom = _castle->GetPlayer()->GetCurrentRoom();

    if (currentRoom->IsCorridor())
        _corridor->Render();

    // Right door
    const Door* const rightDoor = currentRoom->GetDoor( Room::Right );

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

    // Torch of the right door
    if (rightDoor->HasTorch())
    {
        _rightTorch->Render();
    }


    // Upper door
    const Door* const upDoor = currentRoom->GetDoor( Room::Up );

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

    // Torch of the upper door
    if (upDoor->HasTorch())
    {
        _upTorch->Render();
    }

    // Left door
    const Door* const leftDoor = currentRoom->GetDoor( Room::Left );

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

    // Torch of the left door
    if (leftDoor->HasTorch())
    {
        _leftTorch->Render();
    }


    // Ground objects
    for (int row=0 ; row<ROOM_HEIGHT; ++row)
        for (int col=0 ; col<ROOM_WIDTH; ++col)
        {
            switch (currentRoom->GetSquare( Vector2i( row, col ) ))
            {
                case (uint8_t) ObjectID::IronKey:
                    CastleToScreen( _ironKey, row, col );
                    _ironKey->Render();
                    break;
                case (uint8_t) ObjectID::GoldenKey:
                    CastleToScreen( _goldKey, row, col );
                    _goldKey->Render();
                    break;
                case (uint8_t) ObjectID::LifePotion:
                    CastleToScreen( _lifePotion, row, col );
                    _lifePotion->Render();
                    break;
                case (uint8_t) ObjectID::GrapplingHook:
                    CastleToScreen( _grapplingHook, row, col );
                    _grapplingHook->Render();
                    break;
                case (uint8_t) ObjectID::Hint1:
                case (uint8_t) ObjectID::Hint2:
                case (uint8_t) ObjectID::Hint3:
                    CastleToScreen( _hint, row, col );
                    _hint->Render();
                    break;
                default:
                    break;
            }
        }


    // Player
    const Vector2i& position = _castle->GetPlayer()->GetPosition();
    CastleToScreen( _player, position.x, position.y );
    _player->SetPosition( _player->GetPosition() - Vector2i( 0, _player->GetHeight()*0.5f ) );
    if (_movesLeft)
        _player->Render( SDL_FLIP_HORIZONTAL );
    else
        _player->Render();
}

void MainScreen::CastleToScreen( Texture* texture, int row, int col )
{
    // Storing coordinates for grid to screen conversion
    static const Vector2i coordinates[ ROOM_HEIGHT ][ ROOM_WIDTH ] = {
            //        0                     1                     2                     3                     4                     5                     6
            { Vector2i( 268, 215 ), Vector2i( 312, 215 ), Vector2i( 356, 215 ), Vector2i( 400, 215 ), Vector2i( 444, 215 ), Vector2i( 488, 215 ), Vector2i( 532, 215 ) }, // 0
            { Vector2i( 254, 234 ), Vector2i( 303, 234 ), Vector2i( 350, 234 ), Vector2i( 400, 234 ), Vector2i( 450, 234 ), Vector2i( 497, 234 ), Vector2i( 546, 234 ) }, // 1
            { Vector2i( 236, 258 ), Vector2i( 291, 258 ), Vector2i( 346, 258 ), Vector2i( 400, 258 ), Vector2i( 454, 258 ), Vector2i( 509, 258 ), Vector2i( 564, 258 ) }, // 2
            { Vector2i( 216, 288 ), Vector2i( 277, 288 ), Vector2i( 338, 288 ), Vector2i( 400, 288 ), Vector2i( 462, 288 ), Vector2i( 523, 288 ), Vector2i( 584, 288 ) }, // 3
            { Vector2i( 188, 325 ), Vector2i( 259, 325 ), Vector2i( 329, 325 ), Vector2i( 400, 325 ), Vector2i( 471, 325 ), Vector2i( 541, 325 ), Vector2i( 612, 325 ) }, // 4
            { Vector2i( 152, 377 ), Vector2i( 235, 377 ), Vector2i( 318, 377 ), Vector2i( 400, 377 ), Vector2i( 482, 377 ), Vector2i( 565, 377 ), Vector2i( 648, 377 ) }, // 5
    };

    texture->SetPosition( coordinates[ row ][ col ] );
}

float MainScreen::LinearInterp( int begin, int end, float amount )
{
    return begin*amount + end*(1 - amount);
}