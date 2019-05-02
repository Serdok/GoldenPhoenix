//
// Created by serdok on 16/03/19.
	//

#include "MainScreen.h"

MainScreen::MainScreen( Castle* const castle, Translation* const trans )
        : _castle( castle ), _translation( trans ),
          Texture( "Piece.png", true )
{
    _inputs = InputsManager::GetInstance();
    _audio = AudioManager::GetInstance();
    _audio->LoadSound( GetResourcePath( "musics/bruitpas.mp3" ));

    // _bat = new AnimatedTexture("Sprites/Bat.png", 0, 64, 48, 64, 3, 0.5f, AnimatedTexture::horizontal);
    _batL = new AnimatedTexture( "Sprites/Bat.png", 0, 64, 48, 64, 3, 0.5f, AnimatedTexture::horizontal );
    _batR = new AnimatedTexture( "Sprites/Bat.png", 0, 192, 48, 64, 3, 0.5f, AnimatedTexture::horizontal );
    _batUL = new AnimatedTexture( "Sprites/Bat.png", 144, 64, 48, 64, 3, 0.5f, AnimatedTexture::DvG );
    _batUR = new AnimatedTexture( "Sprites/Bat.png", 144, 192, 48, 64, 3, 0.5f, AnimatedTexture::DvG );

    _playerDown = new AnimatedTexture( "Sprites/Personnage.png", 0, 800, 200, 200, 1, 1.0f,
                                       AnimatedTexture::horizontal );
    _playerUp = new AnimatedTexture( "Sprites/Personnage.png", 0, 400, 200, 200, 1, 1.0f, AnimatedTexture::horizontal );
    _playerLeft = new AnimatedTexture( "Sprites/Personnage.png", 0, 600, 200, 200, 1, 1.0f,
                                       AnimatedTexture::horizontal );
    _playerRight = new AnimatedTexture( "Sprites/Personnage.png", 0, 200, 200, 200, 1, 1.0f,
                                        AnimatedTexture::horizontal );

    _playerAWL = new AnimatedTexture( "Sprites/Personnage.png",
                                      0,
                                      600,
                                      200,
                                      200,
                                      13,
                                      0.7f,
                                      AnimatedTexture::horizontal );
    _playerAWR = new AnimatedTexture( "Sprites/Personnage.png",
                                      0,
                                      200,
                                      200,
                                      200,
                                      13,
                                      0.7f,
                                      AnimatedTexture::horizontal );
    _playerAWD = new AnimatedTexture( "Sprites/Personnage.png",
                                      0,
                                      800,
                                      200,
                                      200,
                                      13,
                                      0.7f,
                                      AnimatedTexture::horizontal );
    _playerAWU = new AnimatedTexture( "Sprites/Personnage.png",
                                      0,
                                      400,
                                      200,
                                      200,
                                      13,
                                      0.7f,
                                      AnimatedTexture::horizontal );

    _playerACL = new AnimatedTexture( "Sprites/Personnage.png", 0, 1400, 200, 200, 8, 1.0f,
                                      AnimatedTexture::horizontal );
    _playerAUCL = new AnimatedTexture( "Sprites/Personnage.png", 1400, 1400, 200, 200, 8, 1.0f, AnimatedTexture::DvG );
    _playerACD = new AnimatedTexture( "Sprites/Personnage.png", 0, 1200, 200, 200, 8, 1.0f,
                                      AnimatedTexture::horizontal );
    _playerAUCD = new AnimatedTexture( "Sprites/Personnage.png", 1400, 1200, 200, 200, 8, 1.0f, AnimatedTexture::DvG );
    _playerACR = new AnimatedTexture( "Sprites/Personnage.png", 0, 1000, 200, 200, 8, 1.0f,
                                      AnimatedTexture::horizontal );
    _playerAUCR = new AnimatedTexture( "Sprites/Personnage.png", 1400, 1000, 200, 200, 8, 1.0f, AnimatedTexture::DvG );
    _playerACU = new AnimatedTexture( "Sprites/Personnage.png", 0, 1600, 200, 200, 8, 1.0f,
                                      AnimatedTexture::horizontal );
    _playerAUCU = new AnimatedTexture( "Sprites/Personnage.png", 1400, 1600, 200, 200, 8, 1.0f, AnimatedTexture::DvG );
    _playerACTL = new AnimatedTexture( "Sprites/Personnage.png", 1400, 1400, 200, 200, 1, 1.0f,
                                       AnimatedTexture::horizontal );
    _playerACTD = new AnimatedTexture( "Sprites/Personnage.png", 1400, 1200, 200, 200, 1, 1.0f,
                                       AnimatedTexture::horizontal );
    _playerACTR = new AnimatedTexture( "Sprites/Personnage.png", 1400, 1000, 200, 200, 1, 1.0f,
                                       AnimatedTexture::horizontal );
    _playerACTU = new AnimatedTexture( "Sprites/Personnage.png", 1400, 1600, 200, 200, 1, 1.0f,
                                       AnimatedTexture::horizontal );
    _playerAJL = new AnimatedTexture( "Sprites/Personnage.png", 0, 2200, 200, 200, 16, 1.0f,
                                      AnimatedTexture::horizontal );
    _playerAJD = new AnimatedTexture( "Sprites/Personnage.png", 0, 2000, 200, 200, 16, 1.0f,
                                      AnimatedTexture::horizontal );
    _playerAJR = new AnimatedTexture( "Sprites/Personnage.png", 0, 1800, 200, 200, 16, 1.0f,
                                      AnimatedTexture::horizontal );
    _playerAJU = new AnimatedTexture( "Sprites/Personnage.png", 0, 2400, 200, 200, 16, 1.0f,
                                      AnimatedTexture::horizontal );

    _playerALJL = new AnimatedTexture( "Sprites/Personnage.png",
                                       0,
                                       3200,
                                       200,
                                       200,
                                       16,
                                       1.5f,
                                       AnimatedTexture::horizontal );
    _playerALJD = new AnimatedTexture( "Sprites/Personnage.png",
                                       0,
                                       2800,
                                       200,
                                       200,
                                       16,
                                       1.5f,
                                       AnimatedTexture::horizontal );
    _playerALJR = new AnimatedTexture( "Sprites/Personnage.png",
                                       0,
                                       2600,
                                       200,
                                       200,
                                       16,
                                       1.5f,
                                       AnimatedTexture::horizontal );
    _playerALJU = new AnimatedTexture( "Sprites/Personnage.png",
                                       0,
                                       3000,
                                       200,
                                       200,
                                       16,
                                       1.5f,
                                       AnimatedTexture::horizontal );


    _playerDEATH = new AnimatedTexture( "Sprites/Personnage.png", 0, 3400, 200, 200, 13, 2.0f,
                                        AnimatedTexture::horizontal );
    _playerDEATH->SetWrapMode( AnimatedTexture::once );


    _playerDownH = new AnimatedTexture( "Sprites/Personnage 2.png", 0, 800, 200, 200, 1, 1.0f,
                                        AnimatedTexture::horizontal );
    _playerUpH = new AnimatedTexture( "Sprites/Personnage 2.png", 0, 400, 200, 200, 1, 1.0f,
                                      AnimatedTexture::horizontal );
    _playerLeftH = new AnimatedTexture( "Sprites/Personnage 2.png", 0, 600, 200, 200, 1, 1.0f,
                                        AnimatedTexture::horizontal );
    _playerRightH = new AnimatedTexture( "Sprites/Personnage 2.png", 0, 200, 200, 200, 1, 1.0f,
                                         AnimatedTexture::horizontal );

    _playerAWLH = new AnimatedTexture( "Sprites/Personnage 2.png",
                                       0,
                                       600,
                                       200,
                                       200,
                                       13,
                                       0.7f,
                                       AnimatedTexture::horizontal );
    _playerAWRH = new AnimatedTexture( "Sprites/Personnage 2.png",
                                       0,
                                       200,
                                       200,
                                       200,
                                       13,
                                       0.7f,
                                       AnimatedTexture::horizontal );
    _playerAWDH = new AnimatedTexture( "Sprites/Personnage 2.png",
                                       0,
                                       800,
                                       200,
                                       200,
                                       13,
                                       0.7f,
                                       AnimatedTexture::horizontal );
    _playerAWUH = new AnimatedTexture( "Sprites/Personnage 2.png",
                                       0,
                                       400,
                                       200,
                                       200,
                                       13,
                                       0.7f,
                                       AnimatedTexture::horizontal );

    _playerACLH = new AnimatedTexture( "Sprites/Personnage 2.png",
                                       0,
                                       1400,
                                       200,
                                       200,
                                       8,
                                       1.0f,
                                       AnimatedTexture::horizontal );
    _playerAUCLH = new AnimatedTexture( "Sprites/Personnage 2.png",
                                        1400,
                                        1400,
                                        200,
                                        200,
                                        8,
                                        1.0f,
                                        AnimatedTexture::DvG );
    _playerACDH = new AnimatedTexture( "Sprites/Personnage 2.png",
                                       0,
                                       1200,
                                       200,
                                       200,
                                       8,
                                       1.0f,
                                       AnimatedTexture::horizontal );
    _playerAUCDH = new AnimatedTexture( "Sprites/Personnage 2.png",
                                        1400,
                                        1200,
                                        200,
                                        200,
                                        8,
                                        1.0f,
                                        AnimatedTexture::DvG );
    _playerACRH = new AnimatedTexture( "Sprites/Personnage 2.png",
                                       0,
                                       1000,
                                       200,
                                       200,
                                       8,
                                       1.0f,
                                       AnimatedTexture::horizontal );
    _playerAUCRH = new AnimatedTexture( "Sprites/Personnage 2.png",
                                        1400,
                                        1000,
                                        200,
                                        200,
                                        8,
                                        1.0f,
                                        AnimatedTexture::DvG );
    _playerACUH = new AnimatedTexture( "Sprites/Personnage 2.png",
                                       0,
                                       1600,
                                       200,
                                       200,
                                       8,
                                       1.0f,
                                       AnimatedTexture::horizontal );
    _playerAUCUH = new AnimatedTexture( "Sprites/Personnage 2.png",
                                        1400,
                                        1600,
                                        200,
                                        200,
                                        8,
                                        1.0f,
                                        AnimatedTexture::DvG );

    _playerACTLH = new AnimatedTexture( "Sprites/Personnage 2.png",
                                        1400,
                                        1400,
                                        200,
                                        200,
                                        1,
                                        1.0f,
                                        AnimatedTexture::horizontal );
    _playerACTDH = new AnimatedTexture( "Sprites/Personnage 2.png",
                                        1400,
                                        1200,
                                        200,
                                        200,
                                        1,
                                        1.0f,
                                        AnimatedTexture::horizontal );
    _playerACTRH = new AnimatedTexture( "Sprites/Personnage 2.png",
                                        1400,
                                        1000,
                                        200,
                                        200,
                                        1,
                                        1.0f,
                                        AnimatedTexture::horizontal );
    _playerACTUH = new AnimatedTexture( "Sprites/Personnage 2.png",
                                        1400,
                                        1600,
                                        200,
                                        200,
                                        1,
                                        1.0f,
                                        AnimatedTexture::horizontal );

    _playerAJLH = new AnimatedTexture( "Sprites/Personnage 2.png",
                                       0,
                                       2200,
                                       200,
                                       200,
                                       16,
                                       1.0f,
                                       AnimatedTexture::horizontal );
    _playerAJDH = new AnimatedTexture( "Sprites/Personnage 2.png",
                                       0,
                                       2000,
                                       200,
                                       200,
                                       16,
                                       1.0f,
                                       AnimatedTexture::horizontal );
    _playerAJRH = new AnimatedTexture( "Sprites/Personnage 2.png",
                                       0,
                                       1800,
                                       200,
                                       200,
                                       16,
                                       1.0f,
                                       AnimatedTexture::horizontal );
    _playerAJUH = new AnimatedTexture( "Sprites/Personnage 2.png",
                                       0,
                                       2400,
                                       200,
                                       200,
                                       16,
                                       1.0f,
                                       AnimatedTexture::horizontal );

    _playerALJLH = new AnimatedTexture( "Sprites/Personnage 2.png",
                                        0,
                                        3000,
                                        200,
                                        200,
                                        16,
                                        1.5f,
                                        AnimatedTexture::horizontal );
    _playerALJDH = new AnimatedTexture( "Sprites/Personnage 2.png",
                                        0,
                                        2800,
                                        200,
                                        200,
                                        16,
                                        1.5f,
                                        AnimatedTexture::horizontal );
    _playerALJRH = new AnimatedTexture( "Sprites/Personnage 2.png",
                                        0,
                                        2600,
                                        200,
                                        200,
                                        16,
                                        1.5f,
                                        AnimatedTexture::horizontal );
    _playerALJUH = new AnimatedTexture( "Sprites/Personnage 2.png",
                                        0,
                                        3200,
                                        200,
                                        200,
                                        16,
                                        1.5f,
                                        AnimatedTexture::horizontal );

    _playerHandFire = new AnimatedTexture( "Sprites/Fire.png", 0, 0, 500, 500, 4, 1.0f, AnimatedTexture::horizontal );
    _playerHandFire->SetScale( Vector2f( 0.06f, 0.06f ));

    _movesLeft = false;

    _score = new Texture( _translation->GetTranslation( 13 ) + " : ", "Roboto-Regular.ttf", 25, { 0, 0, 0 } );
    _score->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.28f, Graphics::SCREEN_HEIGHT*0.8f ));

    _life = new Texture( _translation->GetTranslation( 14 ) + " : ", "Roboto-Regular.ttf", 25, { 0, 0, 0 } );
    _life->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.28f, Graphics::SCREEN_HEIGHT*0.9f ));

    _item = new Texture( _translation->GetTranslation( 15 ) + " : ", "Roboto-Regular.ttf", 25, { 0, 0, 0 } );
    _item->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.75f, Graphics::SCREEN_HEIGHT*0.75f ));

    _money = new Texture( _translation->GetTranslation( 16 ) + " : ", "Roboto-Regular.ttf", 25, { 0, 0, 0 } );
    _money->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.75f, Graphics::SCREEN_HEIGHT*0.85f ));


#ifdef DEBUG
    _leftRoomID = new Texture( "ID : ", "Roboto-Regular.ttf", 15, { 255, 255, 255 } );
    _leftRoomID->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.2f, Graphics::SCREEN_HEIGHT*0.3f ));

    _upperRoomID = new Texture( "ID : ", "Roboto-Regular.ttf", 15, { 255, 255, 255 } );
    _upperRoomID->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.5f, Graphics::SCREEN_HEIGHT*0.1f ));

    _rightRoomID = new Texture( "ID : ", "Roboto-Regular.ttf", 15, { 255, 255, 255 } );
    _rightRoomID->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.8f, Graphics::SCREEN_HEIGHT*0.3f ));
#endif // DEBUG

    _chimney = new Texture( "Salles/Chemine.png", true );
    _chimneyNorm = new Texture( "Salles/Chemine2.png", true );
    _chestClosed = new Texture( "Salles/Coffre_fermer.png", true );
    _chestOpen = new Texture( "Salles/Coffre_ouvert.png", true );
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
    _notLit = new Texture( "Salles/Noir.png", true );
    _column = new Texture( "Salles/Support_oeuf.png", true );
    _table = new Texture( "Salles/Table.png", true );
    _chair = new Texture( "Salles/Chaise.png", true );
    _textNotLit = new Texture( _translation->GetTranslation( 18 ), "Roboto-Regular.ttf", 40, { 255, 255, 255 } );
    _textNotLit->SetPosition( Vector2i( Graphics::SCREEN_WIDTH*0.5f, Graphics::SCREEN_HEIGHT*0.4f ));
    _leftFire = new AnimatedTexture( "Sprites/Fire.png", 0, 0, 500, 500, 4, 1.0f, AnimatedTexture::horizontal );
    _leftFire->SetPosition( Vector2i( Graphics::SCREEN_WIDTH*0.19f, Graphics::SCREEN_HEIGHT*0.035f ));
    _leftFire->SetScale( Vector2f( 0.075f, 0.09f ));
    _upFire = new AnimatedTexture( "Sprites/Fire.png", 0, 0, 500, 500, 4, 1.0f, AnimatedTexture::horizontal );
    _upFire->SetPosition( Vector2i( Graphics::SCREEN_WIDTH*0.5f, Graphics::SCREEN_HEIGHT*0.03f ));
    _upFire->SetScale( Vector2f( 0.04f, 0.05f ));
    _rightFire = new AnimatedTexture( "Sprites/Fire.png", 0, 0, 500, 500, 4, 1.0f, AnimatedTexture::horizontal );
    _rightFire->SetPosition( Vector2i( Graphics::SCREEN_WIDTH*0.815f, Graphics::SCREEN_HEIGHT*0.035f ));
    _rightFire->SetScale( Vector2f( 0.075f, 0.09f ));

    _rat = new Texture( "Objets/Souris.png" );
    _crowbar = new Texture( "Objets/Pied de biche.png" );
    _crowbar->SetRotation( -45.0 );
    _crowbar->SetScale( Vector2f( 0.1f, 0.1f ));
    _torch = new Texture( "Objets/Torche.png" );
    _torch->SetScale( Vector2f( 0.1f, 0.1f ));
    _ironKey = new Texture( "Objets/Clé en Fer.png" );
    _ironKey->SetScale( Vector2f( 0.1f, 0.1f ));
    _goldKey = new Texture( "Objets/Clé en Or.png" );
    _goldKey->SetScale( Vector2f( 0.1f, 0.1f ));
    _lifePotion = new Texture( "Objets/Fiole.png" );
    _lifePotion->SetScale( Vector2f( 0.1f, 0.1f ));
    _grapplingHook = new Texture( "Objets/GrapinMain.png" );
    _grapplingHook->SetScale( Vector2f( 0.1f, 0.1f ));
    _hint = new Texture( "Objets/Parchemin.png" );
    _hint->SetScale( Vector2f( 0.1f, 0.1f ));
    _moneybag = new Texture( "Objets/Bourse.png" );
    _moneybag->SetScale( Vector2f( 0.1f, 0.1f ));
    _egg = new Texture( "Objets/Oeuf.png" );
    _egg->SetScale( Vector2f( 0.2f, 0.2f ));
    _helmet = new Texture( "Objets/Casque.png" );
    _helmet->SetScale( Vector2f( 0.12f, 0.12f ));
    _ring = new Texture("Objets/Bague.png");
    _ring->SetScale(Vector2f(0.08f, 0.08f));
    _hole =  new Texture("Objets/Oubliette.png");
    _stone =  new Texture("Objets/Pierre.png");

    temp = new Texture( "Player_minimal.png" );
}

MainScreen::~MainScreen()
{
    _castle = nullptr;
    _inputs = nullptr;

    _audio->UnloadSound( GetResourcePath( "musics/bruitpas.mp3" ));
    _audio = nullptr;

#ifdef DEBUG
    delete _leftRoomID;
    delete _upperRoomID;
    delete _rightRoomID;
#endif // DEBUG

    _player = nullptr;
    delete _playerLeft;
    delete _playerRight;
    delete _playerUp;
    delete _playerDown;

    delete _playerAWL;
    delete _playerAWR;
    delete _playerAWD;
    delete _playerAWU;

    delete _playerACL;
    delete _playerAUCL;
    delete _playerACD;
    delete _playerAUCD;
    delete _playerACR;
    delete _playerAUCR;
    delete _playerACU;
    delete _playerAUCU;

    delete _playerDEATH;

    delete _playerLeftH;
    delete _playerRightH;
    delete _playerUpH;
    delete _playerDownH;

    delete _playerAWLH;
    delete _playerAWRH;
    delete _playerAWDH;
    delete _playerAWUH;

    delete _playerACLH;
    delete _playerAUCLH;
    delete _playerACDH;
    delete _playerAUCDH;
    delete _playerACRH;
    delete _playerAUCRH;
    delete _playerACUH;
    delete _playerAUCUH;

    delete _playerHandFire;
    _playerHand = nullptr;
    delete _playerAJL;
    delete _playerAJD;
    delete _playerAJR;
    delete _playerAJU;

    delete _playerACTL;
    delete _playerACTD;
    delete _playerACTR;
    delete _playerACTU;

    delete _playerALJL;
    delete _playerALJD;
    delete _playerALJR;
    delete _playerALJU;

    delete _playerAJLH;
    delete _playerAJDH;
    delete _playerAJRH;
    delete _playerAJUH;

    delete _playerACTLH;
    delete _playerACTDH;
    delete _playerACTRH;
    delete _playerACTUH;

    delete _playerALJLH;
    delete _playerALJDH;
    delete _playerALJRH;
    delete _playerALJUH;

    _bat = nullptr;
    delete _batL;
    delete _batR;
    delete _batUL;
    delete _batUR;

    delete _score;
    delete _life;
    delete _item;
    delete _money;
    _playerHand = nullptr;

    delete _requires;

    delete _chimney;
    delete _chimneyNorm;
    delete _chestClosed;
    delete _chestOpen;
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
    delete _leftFire;
    delete _upFire;
    delete _rightFire;
    delete _notLit;
    delete _textNotLit;
    delete _rat;
    delete _column;
    delete _table;

    delete _ironKey;
    delete _goldKey;
    delete _crowbar;
    delete _torch;
    delete _lifePotion;
    delete _grapplingHook;
    delete _hint;
    delete _moneybag;
    delete _egg;
    delete _ring;
    delete _hole;
    delete _helmet;

    delete temp;
}

void MainScreen::ProcessEvents( SDL_Event* event )
{
    Vector2i pos = _castle->GetPlayer()->GetPosition();
    Vector2i dir = _castle->GetPlayer()->GetDirection();
    unsigned int salle = _castle->GetPlayer()->GetCurrentRoom()->GetRoomID();
    int id_obj = _castle->GetPlayer()->GetHeldItem().GetObject().GetID();

    if (!_anim && !_animAC && !_animJ && !_animLJ && !_animDEATH)
    {
        if (_inputs->KeyPressed( SDL_SCANCODE_1 ) || _inputs->KeyPressed( SDL_SCANCODE_KP_1 ))
            _castle->GetPlayer()->SetHeldItem(
                    _castle->GetPlayer()->GetObjectPositionFromInventory( Object::ToObject( ObjectID::Crowbar )));

        if (_inputs->KeyPressed( SDL_SCANCODE_2 ) || _inputs->KeyPressed( SDL_SCANCODE_KP_2 ))
            _castle->GetPlayer()->SetHeldItem(
                    _castle->GetPlayer()->GetObjectPositionFromInventory( Object::ToObject( ObjectID::IronKey )));

        if (_inputs->KeyPressed( SDL_SCANCODE_3 ) || _inputs->KeyPressed( SDL_SCANCODE_KP_3 ))
            _castle->GetPlayer()->SetHeldItem(
                    _castle->GetPlayer()->GetObjectPositionFromInventory( Object::ToObject( ObjectID::GoldKey )));

        if (_inputs->KeyPressed( SDL_SCANCODE_4 ) || _inputs->KeyPressed( SDL_SCANCODE_KP_4 ))
            _castle->GetPlayer()->SetHeldItem(
                    _castle->GetPlayer()->GetObjectPositionFromInventory( Object::ToObject( ObjectID::GrapplingHook )));

        if (_inputs->KeyPressed( SDL_SCANCODE_5 ) || _inputs->KeyPressed( SDL_SCANCODE_KP_5 ))
            _castle->GetPlayer()->SetHeldItem(
                    _castle->GetPlayer()->GetObjectPositionFromInventory( Object::ToObject( ObjectID::Torch )));

        if (_inputs->KeyPressed( SDL_SCANCODE_6 ) || _inputs->KeyPressed( SDL_SCANCODE_KP_6 ))
            _castle->GetPlayer()->SetHeldItem(
                    _castle->GetPlayer()->GetObjectPositionFromInventory( Object::ToObject( ObjectID::LifePotion )));

        if (_inputs->KeyPressed( SDL_SCANCODE_0 ) || _inputs->KeyPressed( SDL_SCANCODE_KP_0 ))
            _castle->GetPlayer()->DeselectItem();
    }
    if (!_anim && !_animAC && !_animJ && !_animLJ && !_animDEATH)
    {
        if (_inputs->KeyPressed( SDL_SCANCODE_K ))
        {
            // _castle->ProcessActions( "kill" );
            _animDEATH = true;
        }
        if (_inputs->KeyPressed( SDL_SCANCODE_RETURN ))
        {
            _castle->ProcessActions( "use" );
        }
        if (_inputs->KeyHeld( SDL_SCANCODE_W ) || ( _inputs->KeyHeld( SDL_SCANCODE_UP )))
        {
            _castle->ProcessActions( "up" );
            _movesUp = true;
            _movesLeft = false;
            if (_castle->FailedToOpenDoor()) _firstPass = true;
        }
        if (_inputs->KeyHeld( SDL_SCANCODE_A ) || ( _inputs->KeyHeld( SDL_SCANCODE_LEFT )))
        {
            _castle->ProcessActions( "left" );
            _movesLeft = true;
            _movesUp = false;
            if (_castle->FailedToOpenDoor()) _firstPass = true;
        }
        if (_inputs->KeyHeld( SDL_SCANCODE_S ) || ( _inputs->KeyHeld( SDL_SCANCODE_DOWN )))
        {
            _castle->ProcessActions( "down" );
            _movesUp = false;
            _movesLeft = false;
            if (_castle->FailedToOpenDoor()) _firstPass = true;
        }
        if (_inputs->KeyHeld( SDL_SCANCODE_D ) || ( _inputs->KeyHeld( SDL_SCANCODE_RIGHT )))
        {
            _castle->ProcessActions( "right" );
            _movesLeft = false;
            _movesUp = false;
            if (_castle->FailedToOpenDoor()) _firstPass = true;
        }
        if (_inputs->Shift())
        {
            _castle->ProcessActions( "duck" );
            _animAC = true;
        }
        if (_inputs->KeyHeld( SDL_SCANCODE_SPACE ))
        {
            _castle->ProcessActions( "jump" );
            _animJ = true;
        }
        if (_inputs->KeyPressed( SDL_SCANCODE_RETURN ))
            _castle->ProcessActions( "pick" );

        if (_inputs->KeyHeld( SDL_SCANCODE_L ))
        {
            _castle->ProcessActions( "long jump" );
            _animLJ = true;
        }
        if(_animAC)
        {
            //Reset les animation ici permet de ne pas voir l'image sauter lors que le perso s'accroupie
            _playerACL -> ResetAnimation();
            _playerAUCL -> ResetAnimation();
            _playerACD -> ResetAnimation();
            _playerAUCD -> ResetAnimation();
            _playerACR -> ResetAnimation();
            _playerAUCR -> ResetAnimation();
            _playerACU -> ResetAnimation();
            _playerAUCU -> ResetAnimation();
            
            _playerACLH -> ResetAnimation();
            _playerAUCLH -> ResetAnimation();
            _playerACDH -> ResetAnimation();
            _playerAUCDH -> ResetAnimation();
            _playerACRH -> ResetAnimation();
            _playerAUCRH -> ResetAnimation();
            _playerACUH -> ResetAnimation();
            _playerAUCUH -> ResetAnimation();
               
            if (_castle->GetPlayer()->Crouched())
                _tmpanim = -8;
            else
                _tmpanim = 0;
        }
        else if(_animLJ || _animJ){
            if( _castle->GetPlayer()->GetPosition() == pos )
                _animLJ = false;
            else if((_castle->GetPlayer()->GetPosition()) == pos + dir){
                _animLJ = false;
                _anim = true;
                _stepChannel = _audio->PlaySound( GetResourcePath( "musics/bruitpas.mp3" ));
            }
            _tmpanim = 0;
        }
        else if((_castle->GetPlayer()->GetPosition() != pos) 
            && (salle == _castle->GetPlayer()->GetCurrentRoom()->GetRoomID()))
        {
            _tmpanim = 0;
            _anim = true;
            _stepChannel = _audio->PlaySound( GetResourcePath( "musics/bruitpas.mp3" ));
            delete _requires;
            _requires = nullptr;
        }
        else
        {
            delete _requires;
            _requires = nullptr;
            if(_firstPass == true){
                _firstPass = false;
                TextDoor();
            }
            else if(salle != _castle->GetPlayer()->GetCurrentRoom()->GetRoomID()){
                delete _requires;
                _requires = nullptr;
            }
        }
    }   
}

void MainScreen::Update()
{
    // Update the game
    _castle->AddIteration( Timer::GetInstance()->GetFrameTime());
    _castle->Update();

    AnimationPlayer();

    _torch->SetAlpha( 255 );
    _crowbar->SetAlpha( 255 );
    _grapplingHook->SetAlpha( 255 );
    _lifePotion->SetAlpha( 255 );


    _torchLit = _castle->GetPlayer()->TorchLit();


    if (_castle->GetBat()->GetActiveState())
    {
        AnimationBat();

        /*const Vector2i& bat = _castle->GetBat()->GetPosition();
        CastleToScreen( _bat, bat.x, bat.y );
        _bat->SetPosition( _bat->GetPosition() - Vector2i( 0, _bat->GetHeight()*0.5f ));*/
    }

    if (_castle->GetRat()->GetActiveState())
    {
        _rat->Update();

        const Vector2i& rat = _castle->GetRat()->GetPosition();
        CastleToScreen( _rat, rat.x, rat.y );
        _rat->SetPosition( _rat->GetPosition() - Vector2i( 0, _rat->GetHeight()*0.5f ));
    }

    _leftFire->Update();
    _upFire->Update();
    _rightFire->Update();

    // Update the score
    delete _score;
    _score = new Texture( _translation->GetTranslation( 13 ) + " : " + std::to_string( _castle->GetScore()),
                          "Roboto-Regular.ttf", 25, { 0, 0, 0 } );
    _score->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.28f, Graphics::SCREEN_HEIGHT*0.8f ));

    // Update the life
    delete _life;
    _life = new Texture( _translation->GetTranslation( 14 ) + " : " + std::to_string( _castle->GetPlayer()->GetLife()),
                         "Roboto-Regular.ttf", 25, { 0, 0, 0 } );
    _life->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.28f, Graphics::SCREEN_HEIGHT*0.9f ));

    // Update the held item
    delete _item;
    if (!_castle->GetPlayer()->GetItems().empty())
    {
        SDL_Color color = { 0, 0, 0, 0xFF };
        if (_castle->GetPlayer()->GetHeldItem().GetObject().GetID() == ObjectID::Crowbar)
        {
            auto red = (Uint8) LinearInterp( 0, 150, (float) _castle->GetPlayer()->GetHeldItem().GetDurability()/
                                                     Object::ToObject( ObjectID::Crowbar ).maxDurability );
            auto green = (Uint8) LinearInterp( 150, 0, (float) _castle->GetPlayer()->GetHeldItem().GetDurability()/
                                                       Object::ToObject( ObjectID::Crowbar ).maxDurability );

            color = { red, green, 0, 0xFF };
        }
        else if (_castle->GetPlayer()->GetHeldItem().GetObject().GetID() == ObjectID::Torch)
        {
            auto red = (Uint8) LinearInterp( 0, 150, (float) _castle->GetPlayer()->GetHeldItem().GetDurability()/
                                                     Object::ToObject( ObjectID::Torch ).maxDurability );
            auto green = (Uint8) LinearInterp( 150, 0, (float) _castle->GetPlayer()->GetHeldItem().GetDurability()/
                                                       Object::ToObject( ObjectID::Torch ).maxDurability );

            color = { red, green, 0, 0xFF };
        }

        const ItemStack& held = _castle->GetPlayer()->GetHeldItem();
        _item = new Texture( _translation->GetTranslation( 15 ) + " : " +
                             _translation->GetTranslation( _translation->SearchWord( held.GetObject().name, 'E' )),
                             "Roboto-Regular.ttf", 25, color );
        _item->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.75f, Graphics::SCREEN_HEIGHT*0.75f ));
    }
    else
    {
        _item = new Texture( _translation->GetTranslation( 15 ) + " : ", "Roboto-Regular.ttf", 25, { 0, 0, 0 } );
        _item->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.75f, Graphics::SCREEN_HEIGHT*0.75f ));
    }

    // Update the money
    delete _money;
    _money = new Texture(
            _translation->GetTranslation( 16 ) + " : " + std::to_string( _castle->GetPlayer()->GetMoney()),
            "Roboto-Regular.ttf", 25, { 0, 0, 0 } );
    _money->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.75f, Graphics::SCREEN_HEIGHT*0.85f ));

#ifdef DEBUG
// Update room ID
    delete _leftRoomID;
    _leftRoomID = new Texture(
            "ID : " + std::to_string( _castle->GetPlayer()->GetCurrentRoom()->GetRoomID( Room::Left )),
            "Roboto-Regular.ttf", 15, { 255, 255, 255 } );
    _leftRoomID->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.04f, Graphics::SCREEN_HEIGHT*0.5f ));

    delete _upperRoomID;
    _upperRoomID = new Texture(
            "ID : " + std::to_string( _castle->GetPlayer()->GetCurrentRoom()->GetRoomID( Room::Up )),
            "Roboto-Regular.ttf", 15, { 255, 255, 255 } );
    _upperRoomID->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.5f, Graphics::SCREEN_HEIGHT*0.05f ));

    delete _rightRoomID;
    _rightRoomID = new Texture(
            "ID : " + std::to_string( _castle->GetPlayer()->GetCurrentRoom()->GetRoomID( Room::Right )),
            "Roboto-Regular.ttf", 15, { 255, 255, 255 } );
    _rightRoomID->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.96f, Graphics::SCREEN_HEIGHT*0.5f ));
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

    // Torch of the right door
    if (rightDoor->GetTorchState())
        _rightFire->Render();
    if (rightDoor->HasTorch())
        _rightTorch->Render();

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


    // Upper door
    const Door* const upDoor = currentRoom->GetDoor( Room::Up );

    // Torch of the upper door
    if (upDoor->GetTorchState())
        _upFire->Render();
    if (upDoor->HasTorch())
        _upTorch->Render();

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

    // Left door
    const Door* const leftDoor = currentRoom->GetDoor( Room::Left );

    // Torch of the left door
    if (leftDoor->GetTorchState())
        _leftFire->Render();
    if (leftDoor->HasTorch())
        _leftTorch->Render();

    switch (leftDoor->GetDoorType())
    {
        case Door::DOORS::grid:_leftGate->Render();
            break;
        case Door::DOORS::door:_leftDoor->Render( SDL_FLIP_HORIZONTAL );
            break;
        case Door::DOORS::opening:_leftOpening->Render();
            break;
        default:break;
    }

    // Ground objects
    for (int row = 0 ; row < ROOM_HEIGHT ; ++row)
    {
        for (int col = 0 ; col < ROOM_WIDTH ; ++col)
        {
            switch (currentRoom->GetSquare( Vector2i( col, row )))
            {
                case (uint8_t) ObjectID::IronKey:CastleToScreen( _ironKey, col, row);
                    _ironKey->SetPosition( Vector2f(_ironKey->GetPosition().x, _ironKey->GetPosition().y - 20.0));
                    _ironKey->SetAlpha( 255 );
                    _ironKey->Render();
                    break;
                case (uint8_t) ObjectID::CursedRing:CastleToScreen( _ring, col, row);
                    _ring->SetPosition( Vector2f(_ring->GetPosition().x, _ring->GetPosition().y - 20.0));
                    _ring->SetAlpha( 255 );
                    _ring->Render();
                    break;
                case (uint8_t) ObjectID::GoldKey:CastleToScreen( _goldKey, col, row);
                    _goldKey->SetPosition( Vector2f(_goldKey->GetPosition().x, _goldKey->GetPosition().y - 20.0));
                    _goldKey->SetAlpha( 255 );
                    _goldKey->Render();
                    break;
                case (uint8_t) ObjectID::LifePotion:
                    if (_castle->GetPlayer()->GetHeldItem().GetObject().id == Object::ToObject( ObjectID::LifePotion ).id)
                    {
                        _playerHand->Render();
                    }
                    _lifePotion->SetScale( Vector2f( 0.1f, 0.1f ));
                    CastleToScreen( _lifePotion, col, row);
                    _lifePotion->SetPosition( Vector2f(_lifePotion->GetPosition().x, _lifePotion->GetPosition().y - 20.0));
                    _lifePotion->Render();
                    break;
                case (uint8_t) ObjectID::Hint1:
                case (uint8_t) ObjectID::Hint2:
                case (uint8_t) ObjectID::Hint3:CastleToScreen( _hint, col, row );
                    _hint->SetAlpha( 255 );
                    _hint->Render();
                    break;
                case (uint8_t) ObjectID::Egg:CastleToScreen( _egg, col, row );
                    _column->Render();
                    _egg->SetPosition( Vector2f( _egg->GetPosition().x + 5, _egg->GetPosition().y - 100 ));
                    _egg->SetAlpha( 255 );
                    _egg->Render();
                    break;
                case (uint8_t) ObjectID::Helmet:CastleToScreen( _helmet, col, row );
                    _column->Render();
                    _helmet->SetPosition( Vector2f( _helmet->GetPosition().x + 10, _helmet->GetPosition().y - 80 ));
                    _helmet->SetAlpha( 255 );
                    _helmet->Render();
                    break;
                case (uint8_t) ObjectID::Column:_column->Render();
                    break;
                case -1: // Money
                    CastleToScreen( _moneybag, col, row );
                    _moneybag->SetPosition( Vector2f(_moneybag->GetPosition().x, _moneybag->GetPosition().y - 20.0));
                    _moneybag->Render();
                    break;
                case -3:
                case -4: // Holes
                    CastleToScreen( _hole, col, row );
                    _hole->SetScale( Vector2f(float(row+4)/10, float(row+4)/10));
                    _hole->Render();
                    break;
                case -2: // Objet suplémentaire
                    if(row == 0)
                    {
                        if(col == 2 && currentRoom->GetSquare( Vector2i( col+1, row )) == -2 && currentRoom->GetSquare( Vector2i( col+2, row )) == -2)
                        {
                            if(currentRoom->GetSquare( Vector2i( col+3, row )) != -2 && upDoor->GetDoorType()!=Door::DOORS::chimney)
                            {
                                _chimneyNorm -> Render();
                                col+=2;
                                break;
                            }
                        }
                        else if(col == 5 && currentRoom->GetSquare( Vector2i( col+1, row )) == -2 && currentRoom->GetSquare( Vector2i( col, row + 1 )) == -2 && currentRoom->GetSquare( Vector2i( col + 1, row + 1 )) == -2)
                        {
                            _table -> Render();
                            col++;
                            break;
                        }
                    }
                    else if(row == 2)
                    {
                        if(col == 0 && currentRoom->GetSquare( Vector2i( col, row + 1 )) != -2)
                        {
                            if(currentRoom->GetSquare( Vector2i( col, row - 1 )) != -2)
                            {
                                _chair -> Render();
                                break;
                            }
                        }
                    }
                    if(col > 0 && col < ROOM_WIDTH - 1)
                    {
                        if(currentRoom->GetSquare( Vector2i( col-1, row )) != -2 && currentRoom->GetSquare( Vector2i( col+1, row )) != -2)
                        {
                            CastleToScreen( _stone, col, row );
                            _stone->SetScale( Vector2f(0.18, 0.18));
                            _stone->SetPosition( Vector2f(_stone->GetPosition().x, _stone->GetPosition().y - 10.0));
                            _stone->Render();
                                break;
                            }
                    }
                    break;
                default:break;
            }
        }
        if(row == ROOM_HEIGHT - 3)
        {
            //Render chest
            if (rightDoor->GetDoorType() == Door::DOORS::chest)
            {
                if (rightDoor->GetObject() == 0)
                    _chestOpen->Render( SDL_FLIP_HORIZONTAL );
                else
                    _chestClosed->Render( SDL_FLIP_HORIZONTAL );
            }
            if (leftDoor->GetDoorType() == Door::DOORS::chest)
            {
                if (leftDoor->GetObject() == 0)
                    _chestOpen->Render();
                else
                    _chestClosed->Render();
            }

        }
        // Player
        if (row == _castle->GetPlayer()->GetPosition().y)
        {
            if (_castle->GetPlayer()->GetHeldItem().GetObject().id != Object::ToObject( ObjectID::Nothing ).id)
            {
                if (_torchLit)
                    _playerHandFire->Render();
                _playerHand->Render();
            }
            _player->Render();
        }

        if (_castle->GetRat()->GetActiveState() && _castle->GetRat()->GetVisible())
            if (_castle->GetRat()->GetPosition().y == row)
                _rat->Render();
        // Bat
        if (_castle->GetBat()->GetActiveState())
            _bat->Render();

    }

    // If not light
    if (!( leftDoor->GetTorchState()) && !( rightDoor->GetTorchState()) && !( upDoor->GetTorchState()) &&
        !_torchLit)
    {
        _notLit->Render();
        _textNotLit->Render();
    }

    if (_requires)
        _requires->Render();
}

void MainScreen::TextDoor()
{
    Vector2i pos = _castle->GetPlayer()->GetPosition();
    Door* door;
    std::string requires;
    requires = _translation->GetTranslation(42);
    if( pos == Vector2i( 0, ROOM_HEIGHT - 2 ) && _castle->GetPlayer()->GetDirection() == VEC2_LEFT )
        door = _castle->GetPlayer()->GetCurrentRoom()->GetDoor( Room::Left );
    else if ( pos == Vector2i( ROOM_WIDTH - 1, ROOM_HEIGHT - 2 ) && _castle->GetPlayer()->GetDirection() == VEC2_RIGHT )
        door = _castle->GetPlayer()->GetCurrentRoom()->GetDoor( Room::Right );
    else if( pos == Vector2i( (ROOM_WIDTH - 1)/2, 0 ) && _castle->GetPlayer()->GetDirection() == VEC2_DOWN )
        door = _castle->GetPlayer()->GetCurrentRoom()->GetDoor( Room::Up );
    else
    {
        if( pos == Vector2i( 1, ROOM_HEIGHT - 2 ) && _castle->GetPlayer()->GetDirection() == VEC2_LEFT 
            && _castle->GetPlayer()->GetCurrentRoom()->GetDoor( Room::Left )->GetDoorType()==Door::chest)
        {
            door = _castle->GetPlayer()->GetCurrentRoom()->GetDoor( Room::Left );
            requires = _translation->GetTranslation(43);
        }
        else if ( pos == Vector2i( ROOM_WIDTH - 2, ROOM_HEIGHT - 2 ) && _castle->GetPlayer()->GetDirection() == VEC2_RIGHT 
            && _castle->GetPlayer()->GetCurrentRoom()->GetDoor( Room::Right )->GetDoorType()==Door::chest)
        {
            door = _castle->GetPlayer()->GetCurrentRoom()->GetDoor( Room::Right );
            requires = _translation->GetTranslation(43);
        }
        else if( pos == Vector2i( (ROOM_WIDTH - 1)/2, 1 ) && _castle->GetPlayer()->GetDirection() == VEC2_DOWN 
            && _castle->GetPlayer()->GetCurrentRoom()->GetDoor( Room::Up )->GetDoorType()==Door::chimney)
        {
            door = _castle->GetPlayer()->GetCurrentRoom()->GetDoor( Room::Up );
            requires = _translation->GetTranslation(44);
        }
        else
            return;
    }

    if(door->GetDoorType()==Door::wall || door->GetOpenType()=='O')
        return;

    if(door->GetOpenType()=='N')
        requires=_translation->GetTranslation(39);
    else
        switch (_castle->GetPlayer()->GetHeldItem().GetObject().GetID())
        {
            case ObjectID::Crowbar:
                if(door->GetOpenType()=='B')
                    requires+=" "+_translation->GetTranslation(41);
                else
                    requires+=" "+_translation->GetTranslation(40);
                break;
            case ObjectID::IronKey:
            case ObjectID::GoldKey:
                requires+=" "+_translation->GetTranslation(40);
                break;
            default:
                requires+=" "+_translation->GetTranslation(38);
                break;
        } 

    delete _requires;
    _requires = new Texture( requires, "Roboto-Regular.ttf", 24, { 255, 0, 0 } );
    _requires->SetPosition( Vector2i( Graphics::SCREEN_WIDTH/2, Graphics::SCREEN_HEIGHT*0.63 )); 

}

void MainScreen::CastleToScreen( GameEntity* entity, int row, int col )
{
    // Storing coordinates for grid to screen conversion
    static const Vector2i coordinates[ROOM_HEIGHT][ROOM_WIDTH] = {
            //        0                     1                     2                     3                     4                     5                     6
            { Vector2i( 268, 215 ), Vector2i( 312, 215 ), Vector2i( 356, 215 ), Vector2i( 400, 215 ), Vector2i( 444,
                                                                                                                215 ), Vector2i(
                    488,
                    215 ), Vector2i( 532, 215 ) }, // 0
            { Vector2i( 254, 234 ), Vector2i( 303, 234 ), Vector2i( 350, 234 ), Vector2i( 400, 234 ), Vector2i( 450,
                                                                                                                234 ), Vector2i(
                    497,
                    234 ), Vector2i( 546, 234 ) }, // 1
            { Vector2i( 236, 258 ), Vector2i( 291, 258 ), Vector2i( 346, 258 ), Vector2i( 400, 258 ), Vector2i( 454,
                                                                                                                258 ), Vector2i(
                    509,
                    258 ), Vector2i( 564, 258 ) }, // 2
            { Vector2i( 216, 288 ), Vector2i( 277, 288 ), Vector2i( 338, 288 ), Vector2i( 400, 288 ), Vector2i( 462,
                                                                                                                288 ), Vector2i(
                    523,
                    288 ), Vector2i( 584, 288 ) }, // 3
            { Vector2i( 188, 325 ), Vector2i( 259, 325 ), Vector2i( 329, 325 ), Vector2i( 400, 325 ), Vector2i( 471,
                                                                                                                325 ), Vector2i(
                    541,
                    325 ), Vector2i( 612, 325 ) }, // 4
            { Vector2i( 152, 377 ), Vector2i( 235, 377 ), Vector2i( 318, 377 ), Vector2i( 400, 377 ), Vector2i( 482,
                                                                                                                377 ), Vector2i(
                    565,
                    377 ), Vector2i( 648, 377 ) }, // 5
    };

    entity->SetPosition( coordinates[ col ][ row ] );
}

Vector2f MainScreen::CastleToScreenTranslation( int x_row, int x_col, int y_row, int y_col, float step, float nb_step )
{
    //For going of the point X in the point y by nb_step step 
    // Storing coordinates for grid to screen conversion
    static const Vector2i coordinates[ROOM_HEIGHT][ROOM_WIDTH] = {
            //        0                     1                     2                     3                     4                     5                     6
            { Vector2i( 268, 215 ), Vector2i( 312, 215 ), Vector2i( 356, 215 ), Vector2i( 400, 215 ), Vector2i( 444,
                                                                                                                215 ), Vector2i(
                    488,
                    215 ), Vector2i( 532, 215 ) }, // 0
            { Vector2i( 254, 234 ), Vector2i( 303, 234 ), Vector2i( 350, 234 ), Vector2i( 400, 234 ), Vector2i( 450,
                                                                                                                234 ), Vector2i(
                    497,
                    234 ), Vector2i( 546, 234 ) }, // 1
            { Vector2i( 236, 258 ), Vector2i( 291, 258 ), Vector2i( 346, 258 ), Vector2i( 400, 258 ), Vector2i( 454,
                                                                                                                258 ), Vector2i(
                    509,
                    258 ), Vector2i( 564, 258 ) }, // 2
            { Vector2i( 216, 288 ), Vector2i( 277, 288 ), Vector2i( 338, 288 ), Vector2i( 400, 288 ), Vector2i( 462,
                                                                                                                288 ), Vector2i(
                    523,
                    288 ), Vector2i( 584, 288 ) }, // 3
            { Vector2i( 188, 325 ), Vector2i( 259, 325 ), Vector2i( 329, 325 ), Vector2i( 400, 325 ), Vector2i( 471,
                                                                                                                325 ), Vector2i(
                    541,
                    325 ), Vector2i( 612, 325 ) }, // 4
            { Vector2i( 152, 377 ), Vector2i( 235, 377 ), Vector2i( 318, 377 ), Vector2i( 400, 377 ), Vector2i( 482,
                                                                                                                377 ), Vector2i(
                    565,
                    377 ), Vector2i( 648, 377 ) }, // 5
    };
    Vector2i pointx = ( coordinates[ x_col ][ x_row ] );
    Vector2i pointy = ( coordinates[ y_col ][ y_row ] );
    float x = float( pointy.x - pointx.x )/nb_step;
    float y = float( pointy.y - pointx.y )/nb_step;
    //std::cout<<step<<std::endl;
    return Vector2f( pointx.x + x*step, pointx.y + y*step );
}

float MainScreen::LinearInterp( float begin, float end, float amount )
{
    return begin*amount + end*( 1 - amount );
}

void MainScreen::SetTranslation( Translation* const translation )
{
    _translation = translation;
}

void MainScreen::SetCastle( Castle* const castle )
{
    _castle = castle;
}

void MainScreen::AnimationPlayer()
{
    // Update the animated textures of player
    Vector2f positionObjetHand = Vector2f( 0, 0 );

    //If the player is dead
    if (_castle->GetPlayer()->GetLife() <= 0 || _animDEATH)
    {
        _player = _playerDEATH;
        _playerHand = nullptr;
        _castle->GetPlayer()->EmptyInventory();

        _playerDEATH->Update();
        if (_playerDEATH->GetAnimationDone())
        {
            _castle->KillPlayer();
            _playerDEATH->ResetAnimation();
            _animDEATH = false;
            _player = _playerDown;
        }
    }

        // If the hand is not nothing
    else if (_castle->GetPlayer()->GetHeldItem().GetObject().GetID() != ObjectID::Nothing )
    {
        switch (_castle->GetPlayer()->GetHeldItem().GetObject().GetID())
        {
            case ObjectID::Crowbar:_playerHand = _crowbar;
                _playerHand->SetScale( Vector2f(( 0.05 + float( _castle->GetPlayer()->GetPosition().y )/80 ),
                                                ( 0.05 + float( _castle->GetPlayer()->GetPosition().y )/80 )));
                break;
            case ObjectID::GrapplingHook:_playerHand = _grapplingHook;
                _playerHand->SetScale( Vector2f(( 0.5 + float( _castle->GetPlayer()->GetPosition().y )/80 ),
                                                ( 0.5 + float( _castle->GetPlayer()->GetPosition().y )/80 )));
                positionObjetHand.y = 28;
                break;
            case ObjectID::Torch:_playerHand = _torch;
                _playerHand->SetScale( Vector2f(( 0.1 + float( _castle->GetPlayer()->GetPosition().y )/80 ),
                                                ( 0.1 + float( _castle->GetPlayer()->GetPosition().y )/80 )));
                break;
            case ObjectID::LifePotion:_playerHand = _lifePotion;
                _playerHand->SetScale( Vector2f(( 0.03 + float( _castle->GetPlayer()->GetPosition().y )/80 ),
                                                ( 0.03 + float( _castle->GetPlayer()->GetPosition().y )/80 )));
                positionObjetHand.y = 12;
                break;
            case ObjectID::IronKey:_playerHand = _ironKey;
                break;
            case ObjectID::GoldKey:_playerHand = _goldKey;
                break;
            default: _castle->GetPlayer()->DeselectItem();
                break;
        }


        if (_anim)
        {
            if (_castle->GetPlayer()->GetDirection() == VEC2_LEFT)
            {
                _playerAWLH->SetWrapMode( AnimatedTexture::once );
                _player = _playerAWLH;
                positionObjetHand.x = -19.0 - _castle->GetPlayer()->GetPosition().y*3;
            }
            else if (_castle->GetPlayer()->GetDirection() == VEC2_DOWN)
            {
                _playerAWDH->SetWrapMode( AnimatedTexture::once );
                _player = _playerAWDH;
                positionObjetHand.x = 12.0 + _castle->GetPlayer()->GetPosition().y;
            }
            else if (_castle->GetPlayer()->GetDirection() == VEC2_RIGHT)
            {
                _playerAWRH->SetWrapMode( AnimatedTexture::once );
                _player = _playerAWRH;
                positionObjetHand.x = 24.0 + _castle->GetPlayer()->GetPosition().y*3;
            }
            else
            {
                _playerAWUH->SetWrapMode( AnimatedTexture::once );
                _player = _playerAWUH;
                positionObjetHand.x = -14.0 - _castle->GetPlayer()->GetPosition().y*2;
            }
            _anim = !_player->GetAnimationDone();
            if (!_anim)
            {
                _player->ResetAnimation();
                _audio->UnloadSound( GetResourcePath( "musics/bruitpas.mp3" ));
            }

        }

        //Animation of crounched
        else if (_animAC)
        {
            if (_castle->GetPlayer()->GetDirection() == VEC2_LEFT)
            {
                if (_castle->GetPlayer()->Crouched())
                {
                    _playerACLH->SetWrapMode( AnimatedTexture::once );
                    _player = _playerACLH;
                }
                else if (!_castle->GetPlayer()->Crouched())
                {
                    _playerAUCLH->SetWrapMode( AnimatedTexture::once );
                    _player = _playerAUCLH;
                }
            }
            else if (_castle->GetPlayer()->GetDirection() == VEC2_DOWN)
            {
                if (_castle->GetPlayer()->Crouched())
                {
                    _playerACUH->SetWrapMode( AnimatedTexture::once );
                    _player = _playerACUH;
                }
                else if (!_castle->GetPlayer()->Crouched())
                {
                    _playerAUCUH->SetWrapMode( AnimatedTexture::once );
                    _player = _playerAUCUH;
                }
            }
            else if (_castle->GetPlayer()->GetDirection() == VEC2_RIGHT)
            {
                if (_castle->GetPlayer()->Crouched())
                {
                    _playerACRH->SetWrapMode( AnimatedTexture::once );
                    _player = _playerACRH;
                }
                else if (!_castle->GetPlayer()->Crouched())
                {
                    _playerAUCRH->SetWrapMode( AnimatedTexture::once );
                    _player = _playerAUCRH;
                }
            }
            else if (_castle->GetPlayer()->GetDirection() == VEC2_UP)
            {
                if (_castle->GetPlayer()->Crouched())
                {
                    _playerACDH->SetWrapMode( AnimatedTexture::once );
                    _player = _playerACDH;
                }
                else if (!_castle->GetPlayer()->Crouched())
                {
                    _playerAUCDH->SetWrapMode( AnimatedTexture::once );
                    _player = _playerAUCDH;
                }
            }
        }
            //Animation of Jump
        else if (_animJ)
        {
            if (_castle->GetPlayer()->GetDirection() == VEC2_LEFT)
            {
                _playerAJLH->SetWrapMode( AnimatedTexture::once );
                _player = _playerAJLH;
                positionObjetHand.x = -19.0 - _castle->GetPlayer()->GetPosition().y*3;
            }
            else if (_castle->GetPlayer()->GetDirection() == VEC2_DOWN)
            {
                _playerAJUH->SetWrapMode( AnimatedTexture::once );
                _player = _playerAJUH;
                positionObjetHand.x = 12.0 + _castle->GetPlayer()->GetPosition().y;
            }
            else if (_castle->GetPlayer()->GetDirection() == VEC2_RIGHT)
            {
                _playerAJRH->SetWrapMode( AnimatedTexture::once );
                _player = _playerAJRH;
                positionObjetHand.x = 24.0 + _castle->GetPlayer()->GetPosition().y*3;
            }
            else
            {
                _playerAJDH->SetWrapMode( AnimatedTexture::once );
                _player = _playerAJDH;
                positionObjetHand.x = -14.0 - _castle->GetPlayer()->GetPosition().y*2;
            }
            _animJ = !_player->GetAnimationDone();
            if (!_animJ)
            {
                _player->ResetAnimation();
                _castle->GetPlayer()->SetGrounded();
                if (_castle->GetPlayer()->Crouched())
                    _castle->GetPlayer()->ProcessActions( "duck" );
            }
        }
            //Animation of long jump
        else if (_animLJ)
        {
            if (_castle->GetPlayer()->GetDirection() == VEC2_LEFT)
            {
                _playerALJLH->SetWrapMode( AnimatedTexture::once );
                _player = _playerALJLH;
                positionObjetHand.x = -19.0 - _castle->GetPlayer()->GetPosition().y*3;
            }
            else if (_castle->GetPlayer()->GetDirection() == VEC2_DOWN)
            {
                _playerALJUH->SetWrapMode( AnimatedTexture::once );
                _player = _playerALJUH;
                positionObjetHand.x = 12.0 + _castle->GetPlayer()->GetPosition().y;
            }
            else if (_castle->GetPlayer()->GetDirection() == VEC2_RIGHT)
            {
                _playerALJRH->SetWrapMode( AnimatedTexture::once );
                _player = _playerALJRH;
                positionObjetHand.x = 24.0 + _castle->GetPlayer()->GetPosition().y*3;
            }
            else
            {
                _playerALJDH->SetWrapMode( AnimatedTexture::once );
                _player = _playerALJDH;
                positionObjetHand.x = -14.0 - _castle->GetPlayer()->GetPosition().y*2;
            }
            _animLJ = !_player->GetAnimationDone();
            if(!_animLJ){
                _player->ResetAnimation();
                _castle->GetPlayer()->SetGrounded();
                if(_castle->GetPlayer()->Crouched())
                    _castle ->GetPlayer()->ProcessActions("duck");
            }
        }
            //Not Animation
            //If the player is crouched
        else if (_castle->GetPlayer()->Crouched())
        {
            if (_castle->GetPlayer()->GetDirection() == VEC2_LEFT)
            {
                _player = _playerACTLH;
                positionObjetHand.x = -34.0 - _castle->GetPlayer()->GetPosition().y*4;
                positionObjetHand.y = 20.0 + _castle->GetPlayer()->GetPosition().y*3;
            }
            else if (_castle->GetPlayer()->GetDirection() == VEC2_DOWN)
            {
                _player = _playerACTUH;
                positionObjetHand.x = 10.0 + _castle->GetPlayer()->GetPosition().y;
                positionObjetHand.y = 10.0 + _castle->GetPlayer()->GetPosition().y;
            }
            else if (_castle->GetPlayer()->GetDirection() == VEC2_RIGHT)
            {
                _player = _playerACTRH;
                positionObjetHand.x = 40.0 + _castle->GetPlayer()->GetPosition().y*6;
                positionObjetHand.y = 20.0 + _castle->GetPlayer()->GetPosition().y*3;
            }
            else
            {
                _player = _playerACTDH;
                positionObjetHand.x = -15.0 - _castle->GetPlayer()->GetPosition().y*2;
                positionObjetHand.y = 25.0 + _castle->GetPlayer()->GetPosition().y*2;
            }
        }
            //if the player is not crouched
        else
        {
            if (_castle->GetPlayer()->GetDirection() == VEC2_LEFT)
            {
                _player = _playerLeftH;
                positionObjetHand.x = -19.0 - _castle->GetPlayer()->GetPosition().y*3;
            }
            else if (_castle->GetPlayer()->GetDirection() == VEC2_DOWN)
            {
                _player = _playerDownH;
                positionObjetHand.x = 12.0 + _castle->GetPlayer()->GetPosition().y;
            }
            else if (_castle->GetPlayer()->GetDirection() == VEC2_RIGHT)
            {
                _player = _playerRightH;
                positionObjetHand.x = 24.0 + _castle->GetPlayer()->GetPosition().y*3;
            }
            else
            {
                _player = _playerUpH;
                positionObjetHand.x = -14.0 - _castle->GetPlayer()->GetPosition().y*2;
            }

        }
    }
    //Si le perso ne tient pas d'objet
    else
    {
        //Animation of walking
        if (_anim)
        {
            if (_castle->GetPlayer()->GetDirection() == VEC2_LEFT)
            {
                _playerAWL->SetWrapMode( AnimatedTexture::once );
                _player = _playerAWL;
            }
            else if (_castle->GetPlayer()->GetDirection() == VEC2_DOWN)
            {
                _playerAWD->SetWrapMode( AnimatedTexture::once );
                _player = _playerAWD;
            }
            else if (_castle->GetPlayer()->GetDirection() == VEC2_RIGHT)
            {
                _playerAWR->SetWrapMode( AnimatedTexture::once );
                _player = _playerAWR;
            }
            else
            {
                _playerAWU->SetWrapMode( AnimatedTexture::once );
                _player = _playerAWU;
            }
            _anim = !_player->GetAnimationDone();
            if (!_anim)
            {
                _player->ResetAnimation();
                _audio->StopChannel( _stepChannel );
            }
        }
            //Animation of crounched
        else if (_animAC)
        {
            if (_castle->GetPlayer()->GetDirection() == VEC2_LEFT)
            {
                if (_castle->GetPlayer()->Crouched())
                {
                    _playerACL->SetWrapMode( AnimatedTexture::once );
                    _player = _playerACL;
                }
                else if (!_castle->GetPlayer()->Crouched())
                {
                    _playerAUCL->SetWrapMode( AnimatedTexture::once );
                    _player = _playerAUCL;
                }
            }
            else if (_castle->GetPlayer()->GetDirection() == VEC2_DOWN)
            {
                if (_castle->GetPlayer()->Crouched())
                {
                    _playerACU->SetWrapMode( AnimatedTexture::once );
                    _player = _playerACU;
                }
                else if (!_castle->GetPlayer()->Crouched())
                {
                    _playerAUCU->SetWrapMode( AnimatedTexture::once );
                }
            }
            else if (_castle->GetPlayer()->GetDirection() == VEC2_RIGHT)
            {
                if (_castle->GetPlayer()->Crouched())
                {
                    _playerACR->SetWrapMode( AnimatedTexture::once );
                    _player = _playerACR;
                }
                else if (!_castle->GetPlayer()->Crouched())
                {
                    _playerAUCR->SetWrapMode( AnimatedTexture::once );
                }
            }
            else if (_castle->GetPlayer()->GetDirection() == VEC2_UP)
            {
                if (_castle->GetPlayer()->Crouched())
                {
                    _playerACD->SetWrapMode( AnimatedTexture::once );
                    _player = _playerACD;
                }
                else if (!_castle->GetPlayer()->Crouched())
                {
                    _playerAUCD->SetWrapMode( AnimatedTexture::once );
                    _player = _playerAUCD;
                }
            }
            _animAC = !_player->GetAnimationDone();
        }
            //Animation of Jump
        else if (_animJ)
        {
            if (_castle->GetPlayer()->GetDirection() == VEC2_LEFT)
            {
                _playerAJL->SetWrapMode( AnimatedTexture::once );
                _player = _playerAJL;
            }
            else if (_castle->GetPlayer()->GetDirection() == VEC2_DOWN)
            {
                _playerAJU->SetWrapMode( AnimatedTexture::once );
                _player = _playerAJU;
            }
            else if (_castle->GetPlayer()->GetDirection() == VEC2_RIGHT)
            {
                _playerAJR->SetWrapMode( AnimatedTexture::once );
                _player = _playerAJR;
            }
            else
            {
                _playerAJD->SetWrapMode( AnimatedTexture::once );
                _player = _playerAJD;
            }
            _animJ = !_player->GetAnimationDone();
            if (!_animJ)
            {
                _player->ResetAnimation();
                _castle->GetPlayer()->SetGrounded();
                if (_castle->GetPlayer()->Crouched())
                    _castle->GetPlayer()->ProcessActions( "duck" );
            }
        }
            //Animation of long jump
        else if (_animLJ)
        {
            if (_castle->GetPlayer()->GetDirection() == VEC2_LEFT)
            {
                _playerALJL->SetWrapMode( AnimatedTexture::once );
                _player = _playerALJL;
            }
            else if (_castle->GetPlayer()->GetDirection() == VEC2_DOWN)
            {
                _playerALJU->SetWrapMode( AnimatedTexture::once );
                _player = _playerALJU;
            }
            else if (_castle->GetPlayer()->GetDirection() == VEC2_RIGHT)
            {
                _playerALJR->SetWrapMode( AnimatedTexture::once );
                _player = _playerALJR;
            }
            else
            {
                _playerALJD->SetWrapMode( AnimatedTexture::once );
                _player = _playerALJD;
            }
            _animLJ = !_player->GetAnimationDone();
            if(!_animLJ){
                _player->ResetAnimation();
                _castle->GetPlayer()->SetGrounded();
                if(_castle->GetPlayer()->Crouched())
                    _castle ->ProcessActions("duck");
            }   
        }
            //Not Animation
            //If the player is crouched
        else if (_castle->GetPlayer()->Crouched())
        {
            if (_castle->GetPlayer()->GetDirection() == VEC2_LEFT)
                _player = _playerACTL;
            else if (_castle->GetPlayer()->GetDirection() == VEC2_DOWN)
                _player = _playerACTU;
            else if (_castle->GetPlayer()->GetDirection() == VEC2_RIGHT)
                _player = _playerACTR;
            else
                _player = _playerACTD;
        }
            //if the player is not crouched
        else
        {
            if (_castle->GetPlayer()->GetDirection() == VEC2_LEFT)
                _player = _playerLeft;
            else if (_castle->GetPlayer()->GetDirection() == VEC2_DOWN)
                _player = _playerDown;
            else if (_castle->GetPlayer()->GetDirection() == VEC2_RIGHT)
                _player = _playerRight;
            else
                _player = _playerUp;
        }

    }

    //Update of animation
    _player->Update();


    const Vector2i& player = _castle->GetPlayer()->GetPosition();
    CastleToScreen( _player, player.x, player.y );
    
    _player->SetScale( Vector2f(( 0.7 + float( _castle->GetPlayer()->GetPosition().y )/10 ),
                                ( 0.7 + float( _castle->GetPlayer()->GetPosition().y )/9 )));

    //std::cout <<_castle->GetPlayer()->GetPosition().x << _castle->GetPlayer()->GetPosition().y << std::endl;

    //Déplacement des texture avec _tmpanim
    if(_anim){
        const Vector2f& player2 = CastleToScreenTranslation(player.x-(_castle->GetPlayer()->GetDirection().x),player.y-(_castle->GetPlayer()->GetDirection().y),
                                                            player.x,player.y, _tmpanim*13/40,13);
        _player->SetPosition( player2 - Vector2i( 0, _player->GetHeight()*( 0.35 +
                                                                                        float( _castle->GetPlayer()->GetPosition().y )/
                                                                                        30 )));

        float scale =LinearInterp(0.7 + float( _castle->GetPlayer()->GetPosition().y )/9, 0.7 + (float( _castle->GetPlayer()->GetPosition().y )/9 - float( _castle->GetPlayer()->GetDirection().y )/9), float(_tmpanim)/41);
        _player->SetScale( Vector2f(( 0.7 + float( _castle->GetPlayer()->GetPosition().y )/10 ),
                                    ( scale )));
        _tmpanim++;
    }
    else if (_animLJ)
    {
        Vector2f player2;
        if (_tmpanim <= 21)
            player2 = CastleToScreenTranslation( player.x - 2*( _castle->GetPlayer()->GetDirection().x ),
                                                 player.y - 2*( _castle->GetPlayer()->GetDirection().y ),
                                                 player.x,
                                                 player.y,
                                                 0,
                                                 1 );

        else if (_tmpanim >= 74)
        {
            player2 = CastleToScreenTranslation( player.x, player.y,
                                                 player.x, player.y, 0, 1 );
        }
    	else{
        	player2 = CastleToScreenTranslation(player.x-2*(_castle->GetPlayer()->GetDirection().x),player.y-2*(_castle->GetPlayer()->GetDirection().y),
                                                            player.x,player.y,( _tmpanim-21)*10/53,10);

            float scale =LinearInterp(0.7 + float( _castle->GetPlayer()->GetPosition().y )/9, 0.7 + (float( _castle->GetPlayer()->GetPosition().y )/9 - 2 *float( _castle->GetPlayer()->GetDirection().y )/9), float( _tmpanim-21)/53);
            _player->SetScale( Vector2f(( 0.7 + float( _castle->GetPlayer()->GetPosition().y )/10 ),
                                        ( scale )));
            if (_castle->GetPlayer()->GetHeldItem( ) != ItemStack( Object::ToObject( ObjectID::Nothing ), 0 ))
            {
                int tmp = _tmpanim - 21 ;
                if (_tmpanim <= 47)
                    positionObjetHand.y = LinearInterp(-40.0 - _castle->GetPlayer()->GetPosition().y*5, _castle->GetPlayer()->GetPosition().y,  float( tmp)/26);
                else
                    positionObjetHand.y = LinearInterp(_castle->GetPlayer()->GetPosition().y,  -40.0 - _castle->GetPlayer()->GetPosition().y*5, float( tmp -26 )/26);
            }
        }


        _player->SetPosition( player2 - Vector2i( 0, _player->GetHeight()*( 0.35 +
                                                                                        float( _castle->GetPlayer()->GetPosition().y )/
                                                                                        30 )));

        _tmpanim++;
    }
    else
    {
        _player->SetPosition( _player->GetPosition() - Vector2i( 0, _player->GetHeight()*( 0.35 +
                                                                                           float( _castle->GetPlayer()
                                                                                                         ->GetPosition()
                                                                                                         .y )/
                                                                                           30 )));
    }


    if (_castle->GetPlayer()->GetHeldItem().GetObject().GetID() != ObjectID::Nothing )
    {

        if (_animAC)
        {
            if(_tmpanim >= 0)
            {
                if (_castle->GetPlayer()->GetDirection() == VEC2_LEFT)
                {
                    if (_castle->GetPlayer()->Crouched())
                    {
                        positionObjetHand.x = LinearInterp(-34.0 - _castle->GetPlayer()->GetPosition().y*4, -19.0 - _castle->GetPlayer()->GetPosition().y*3, float( _tmpanim)/50);
                        positionObjetHand.y = LinearInterp(20.0 + _castle->GetPlayer()->GetPosition().y*3, positionObjetHand.y, float( _tmpanim)/50);
                    }
                    else if (!_castle->GetPlayer()->Crouched())
                    {
                        positionObjetHand.x = LinearInterp(-19.0 - _castle->GetPlayer()->GetPosition().y*3, -34.0 - _castle->GetPlayer()->GetPosition().y*4, float( _tmpanim)/50);
                        positionObjetHand.y = LinearInterp( positionObjetHand.y, 20.0 + _castle->GetPlayer()->GetPosition().y*3,float( _tmpanim)/50);
                    }
                }
                else if (_castle->GetPlayer()->GetDirection() == VEC2_DOWN)
                {
                    if (_castle->GetPlayer()->Crouched())
                    {
                        positionObjetHand.x = LinearInterp(10.0 + _castle->GetPlayer()->GetPosition().y, 12.0 + _castle->GetPlayer()->GetPosition().y, float( _tmpanim)/50);
                        positionObjetHand.y = LinearInterp(10.0 + _castle->GetPlayer()->GetPosition().y, positionObjetHand.y, float( _tmpanim)/50);
                    }
                    else if (!_castle->GetPlayer()->Crouched())
                    {
                        positionObjetHand.x = LinearInterp(12.0 + _castle->GetPlayer()->GetPosition().y, 10.0 + _castle->GetPlayer()->GetPosition().y, float( _tmpanim)/50);
                        positionObjetHand.y = LinearInterp( positionObjetHand.y, 10.0 + _castle->GetPlayer()->GetPosition().y,float( _tmpanim)/50);
                    }
                }
                else if (_castle->GetPlayer()->GetDirection() == VEC2_RIGHT)
                {
                    if (_castle->GetPlayer()->Crouched())
                    {
                        positionObjetHand.x = LinearInterp(40.0 + _castle->GetPlayer()->GetPosition().y*6, 24.0 + _castle->GetPlayer()->GetPosition().y*3, float( _tmpanim)/50);
                        positionObjetHand.y = LinearInterp(20.0 + _castle->GetPlayer()->GetPosition().y*3, positionObjetHand.y, float( _tmpanim)/50);
                    }
                    else if (!_castle->GetPlayer()->Crouched())
                    {
                        positionObjetHand.x = LinearInterp(24.0 + _castle->GetPlayer()->GetPosition().y*3, 40.0 + _castle->GetPlayer()->GetPosition().y*6, float( _tmpanim)/50);
                        positionObjetHand.y = LinearInterp( positionObjetHand.y, 20.0 + _castle->GetPlayer()->GetPosition().y*3,float( _tmpanim)/50);
                    }
                }
                else if (_castle->GetPlayer()->GetDirection() == VEC2_UP)
                {
                    if (_castle->GetPlayer()->Crouched())
                    {
                        positionObjetHand.x = LinearInterp(-15.0 - _castle->GetPlayer()->GetPosition().y*2, -14.0 - _castle->GetPlayer()->GetPosition().y*2, float( _tmpanim)/50);
                        positionObjetHand.y = LinearInterp(25.0 + _castle->GetPlayer()->GetPosition().y*2, positionObjetHand.y, float( _tmpanim)/50);

                    }
                    else if (!_castle->GetPlayer()->Crouched())
                    {
                        positionObjetHand.x = LinearInterp(-14.0 - _castle->GetPlayer()->GetPosition().y*2, -15.0 - _castle->GetPlayer()->GetPosition().y*2, float( _tmpanim)/50);
                        positionObjetHand.y = LinearInterp( positionObjetHand.y, 25.0 + _castle->GetPlayer()->GetPosition().y*2,float( _tmpanim)/50);
                        
                    }
                }
            }
            else if(_castle->GetPlayer()->Crouched()) {
                if (_castle->GetPlayer()->GetDirection() == VEC2_LEFT )
                    positionObjetHand.x = -19.0 - _castle->GetPlayer()->GetPosition().y*3;
                 else if (_castle->GetPlayer()->GetDirection() == VEC2_DOWN)
                    positionObjetHand.x =  10.0 + _castle->GetPlayer()->GetPosition().y;
                else if (_castle->GetPlayer()->GetDirection() == VEC2_RIGHT)
                    positionObjetHand.x =  24.0 + _castle->GetPlayer()->GetPosition().y*3;
                else
                    positionObjetHand.x =  -14.0 - _castle->GetPlayer()->GetPosition().y*2;
            }
            if(_tmpanim!=50)
                _tmpanim++;
            
            //Si placer avant l'image risque de sauter car le programme va pas rentrer dans cette boucle
            //et donc va pas définir sa position (enfin pas sa position complete)
            _animAC = !_player->GetAnimationDone();
        }
        //Animation of Jump
        else if(_animJ)
        {
            int tmp;
            if(_tmpanim<=18){
                tmp = _tmpanim;
                positionObjetHand.y = LinearInterp( 15 +  _castle->GetPlayer()->GetPosition().y*5, positionObjetHand.y, float( tmp)/18);
            }
            else if(_tmpanim<=38) {
                tmp = _tmpanim-18;
                positionObjetHand.y = LinearInterp(-40.0 - _castle->GetPlayer()->GetPosition().y*5,  15 +  _castle->GetPlayer()->GetPosition().y*5, float( tmp)/20);
            }
            else {
                tmp = _tmpanim-38;
                positionObjetHand.y = LinearInterp(positionObjetHand.y, -40.0 - _castle->GetPlayer()->GetPosition().y*5, float( tmp)/20 );
            }
            
            _tmpanim++;
        }
    }
    if (_castle->GetPlayer()->GetHeldItem().GetObject().GetID() != ObjectID::Nothing )
    {
        _playerHand->SetPosition( Vector2f( float( _player->GetPosition().x + positionObjetHand.x ),
                                            float( _player->GetPosition().y - 15 + positionObjetHand.y )));
        _playerHand->SetAlpha( 255 );
        if (_castle->GetPlayer()->GetHeldItem().GetObject().GetID() == ObjectID::Torch )
            _playerHandFire->SetPosition( _playerHand->GetPosition() + VEC2_DOWN*Vector2f( 0, 5 +
                                                                                              _playerHand->GetHeight()*
                                                                                              _playerHand->GetScale().y/
                                                                                              2 ));

    }
}


void MainScreen::AnimationBat()
{
    if (_castle->GetBat()->GetDirection() == VEC2_LEFT)
        _bat = _batR;

    else if (_castle->GetBat()->GetDirection() == VEC2_RIGHT)
        _bat = _batL;

    _bat->SetScale( Vector2f( 2.0, 2.0 ));

    const Vector2i& position = _castle->GetBat()->GetPosition();
    CastleToScreen( _bat, position.x, position.y );
    _bat->Update();
    const Vector2f& bat2 = CastleToScreenTranslation( position.x, position.y,
                                                      position.x, position.y, _tmpanim*3/40, 3 );
    _bat->SetPosition( bat2 - Vector2i( 0, _bat->GetHeight()*( 1.75 +
                                                               float( _castle->GetBat()->GetPosition().y )/
                                                               10 )));
}