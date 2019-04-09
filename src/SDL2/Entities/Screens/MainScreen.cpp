//
// Created by serdok on 16/03/19.
//

#include "MainScreen.h"

MainScreen::MainScreen( Castle* const castle, Translation* const trans ) : _castle( castle ), _translation( trans ),
                                                                           Texture( "Piece.png", true )
{
#ifdef DEBUG
  //   _castle->GetPlayer()->AddItem( Object::ToObject( ObjectID::LifePotion ) );
    // _castle->GetPlayer()->AddItem( Object::ToObject( ObjectID::LifePotion ) );
   // _castle->GetPlayer()->AddItem( Object::ToObject( ObjectID::Crowbar ) );
   // _castle->GetPlayer()->AddItem( Object::ToObject( ObjectID::GrapplingHook ) );
    _castle->GetPlayer()->AddItem( Object::ToObject( ObjectID::Torch ));
    // _castle->GetPlayer()->AddItem( Object::ToObject( ObjectID::Hint1 ) );
    // _castle->GetPlayer()->AddItem( Object::ToObject( ObjectID::Hint2 ) );
    // _castle->GetPlayer()->AddItem( Object::ToObject( ObjectID::Hint3 ) );
    // _castle->GetPlayer()->AddItem( Object::ToObject( ObjectID::Egg ) );
    // _castle->GetPlayer()->SetPosition( Vector2i( 4, 3 ) );
#endif // DEBUG

    _inputs = InputsManager::GetInstance();

    _playerDown = new AnimatedTexture( "Sprites/Personnage.png", 0, 800, 200, 200, 1, 1.0f,
                                       AnimatedTexture::horizontal );
    _playerUp = new AnimatedTexture( "Sprites/Personnage.png", 0, 400, 200, 200, 1, 1.0f, AnimatedTexture::horizontal );
    _playerLeft = new AnimatedTexture( "Sprites/Personnage.png", 0, 600, 200, 200, 1, 1.0f,
                                       AnimatedTexture::horizontal );
    _playerRight = new AnimatedTexture( "Sprites/Personnage.png", 0, 200, 200, 200, 1, 1.0f,
                                        AnimatedTexture::horizontal );
    _bat = new Texture( "Player_minimal.png" );

    _playerAWL = new AnimatedTexture( "Sprites/Personnage.png", 0, 600, 200, 200, 13, 1.0f, AnimatedTexture::horizontal );
    _playerAWR = new AnimatedTexture( "Sprites/Personnage.png", 0, 200, 200, 200, 13, 1.0f, AnimatedTexture::horizontal );
    _playerAWD = new AnimatedTexture( "Sprites/Personnage.png", 0, 800, 200, 200, 13, 1.0f, AnimatedTexture::horizontal );
    _playerAWU = new AnimatedTexture( "Sprites/Personnage.png", 0, 400, 200, 200, 13, 1.0f, AnimatedTexture::horizontal );

    _playerACL = new AnimatedTexture( "Sprites/Personnage.png", 0, 1400, 200, 200, 8, 1.0f, AnimatedTexture::horizontal );
    _playerAUCL = new AnimatedTexture( "Sprites/Personnage.png",1400 , 1400, 200, 200, 8, 1.0f, AnimatedTexture::DvG );
    _playerACD = new AnimatedTexture( "Sprites/Personnage.png", 0, 1200, 200, 200, 8, 1.0f, AnimatedTexture::horizontal );
    _playerAUCD = new AnimatedTexture( "Sprites/Personnage.png",1400 , 1200, 200, 200, 8, 1.0f, AnimatedTexture::DvG );
    _playerACR = new AnimatedTexture( "Sprites/Personnage.png", 0, 1000, 200, 200, 8, 1.0f, AnimatedTexture::horizontal );
    _playerAUCR = new AnimatedTexture( "Sprites/Personnage.png",1400 , 1000, 200, 200, 8, 1.0f, AnimatedTexture::DvG );
    _playerACU = new AnimatedTexture( "Sprites/Personnage.png", 0, 1600, 200, 200, 8, 1.0f, AnimatedTexture::horizontal );
    _playerAUCU = new AnimatedTexture( "Sprites/Personnage.png",1400 , 1600, 200, 200, 8, 1.0f, AnimatedTexture::DvG );
    _playerACTL = new AnimatedTexture( "Sprites/Personnage.png", 1400, 1400, 200, 200, 1, 1.0f, AnimatedTexture::horizontal );
    _playerACTD = new AnimatedTexture( "Sprites/Personnage.png", 1400, 1200, 200, 200, 1, 1.0f, AnimatedTexture::horizontal );
    _playerACTR = new AnimatedTexture( "Sprites/Personnage.png", 1400, 1000, 200, 200, 1, 1.0f, AnimatedTexture::horizontal );
    _playerACTU = new AnimatedTexture( "Sprites/Personnage.png", 1400, 1600, 200, 200, 1, 1.0f, AnimatedTexture::horizontal );
    _playerAJL = new AnimatedTexture( "Sprites/Personnage.png", 0, 2200, 200, 200, 16, 1.0f, AnimatedTexture::horizontal );
    _playerAJD = new AnimatedTexture( "Sprites/Personnage.png", 0, 2000, 200, 200, 16, 1.0f, AnimatedTexture::horizontal );
    _playerAJR = new AnimatedTexture( "Sprites/Personnage.png", 0, 1800, 200, 200, 16, 1.0f, AnimatedTexture::horizontal );
    _playerAJU = new AnimatedTexture( "Sprites/Personnage.png", 0, 2400, 200, 200, 16, 1.0f, AnimatedTexture::horizontal );

    _playerDEATH = new AnimatedTexture( "Sprites/Personnage.png", 0, 3400, 200, 200, 16, 2.0f, AnimatedTexture::horizontal );


    _playerDownH = new AnimatedTexture( "Sprites/Personnage 2.png", 0, 800, 200, 200, 1, 1.0f,
                                       AnimatedTexture::horizontal );
    _playerUpH = new AnimatedTexture( "Sprites/Personnage 2.png", 0, 400, 200, 200, 1, 1.0f, AnimatedTexture::horizontal );
    _playerLeftH = new AnimatedTexture( "Sprites/Personnage 2.png", 0, 600, 200, 200, 1, 1.0f,
                                       AnimatedTexture::horizontal );
    _playerRightH = new AnimatedTexture( "Sprites/Personnage 2.png", 0, 200, 200, 200, 1, 1.0f,
                                        AnimatedTexture::horizontal );


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
    _textNotLit = new Texture( _translation->GetTranslation( 18 ), "Roboto-Regular.ttf", 40, { 255, 255, 255 } );
    _textNotLit->SetPosition( Vector2i( Graphics::SCREEN_WIDTH*0.5f, Graphics::SCREEN_HEIGHT*0.4f ));
    _leftFire = new AnimatedTexture( "Sprites/Fire.png", 0, 0, 500, 500, 4, 1.0f, AnimatedTexture::horizontal );
    _leftFire->SetPosition( Vector2i( Graphics::SCREEN_WIDTH*0.195f, Graphics::SCREEN_HEIGHT*0.025f ));
    _leftFire->SetScale( Vector2f( 0.05f, 0.05f ));
    _upFire = new AnimatedTexture( "Sprites/Fire.png", 0, 0, 500, 500, 4, 1.0f, AnimatedTexture::horizontal );
    _upFire->SetPosition( Vector2i( Graphics::SCREEN_WIDTH*0.5f, Graphics::SCREEN_HEIGHT*0.015f ));
    _upFire->SetScale( Vector2f( 0.05f, 0.05f ));
    _rightFire = new AnimatedTexture( "Sprites/Fire.png", 0, 0, 500, 500, 4, 1.0f, AnimatedTexture::horizontal );
    _rightFire->SetPosition( Vector2i( Graphics::SCREEN_WIDTH*0.805f, Graphics::SCREEN_HEIGHT*0.025f ));
    _rightFire->SetScale( Vector2f( 0.05f, 0.05f ));

    _rat = new Texture( "Objets/Souris.png" );
    _crowbar = new Texture( "Objets/Pied de biche.png" );
    _crowbar->SetRotation(-45.0);
    _crowbar->SetScale( Vector2f( 0.1f, 0.1f ));
    _torch = new Texture( "Objets/Torche.png" );
    _torch->SetScale( Vector2f( 0.1f, 0.1f ));
    _ironKey = new Texture( "Objets/Clé en Fer.png" );
    _ironKey->SetScale( Vector2f( 0.1f, 0.1f ));
    _goldKey = new Texture( "Objets/Clé en Or.png" );
    _goldKey->SetScale( Vector2f( 0.1f, 0.1f ));
    _lifePotion = new Texture( "Objets/Fiole.png" );
    _lifePotion->SetScale( Vector2f( 0.1f, 0.1f ));
    _grapplingHook = new Texture( "Objets/Grapin.png" );
    _grapplingHook->SetScale( Vector2f( 0.1f, 0.1f ));
    _hint = new Texture( "Objets/Parchemin.png" );
    _hint->SetScale( Vector2f( 0.1f, 0.1f ));
    _moneybag = new Texture( "Objets/Bourse.png" );
    _moneybag->SetScale( Vector2f( 0.1f, 0.1f ));
    _egg = new Texture( "Objets/Oeuf.png" );
    _egg->SetScale( Vector2f( 0.1f, 0.1f ));

    temp = new Texture( "Player_minimal.png" );
    _playerHand = _crowbar;
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
    delete _playerAJL;
    delete _playerAJD;
    delete _playerAJR;
    delete _playerAJU;
    delete _playerACTL;
    delete _playerACTD;
    delete _playerACTR;
    delete _playerACTU;

#ifdef DEBUG
    delete _bat;
#endif // DEBUG

    delete _score;
    delete _life;
    delete _item;
    delete _money;
    delete _playerHand;

    delete _chimney;
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

    delete _ironKey;
    delete _goldKey;
    delete _crowbar;
    delete _torch;
    delete _lifePotion;
    delete _grapplingHook;
    delete _hint;
    delete _moneybag;
    delete _egg;

    delete temp;
}

void MainScreen::ProcessEvents( SDL_Event* event )
{
    Vector2i pos = _castle->GetPlayer()->GetPosition();
    if(_anim == false)
    {
        if (_inputs->KeyPressed( SDL_SCANCODE_K ))
        {
            _castle->ProcessActions( "kill" );
        }
        if (_inputs->KeyPressed( SDL_SCANCODE_RETURN ))
        {
            _castle->ProcessActions( "use" );
        }
        if (_inputs->KeyPressed( SDL_SCANCODE_W ) || (_inputs->KeyPressed(SDL_SCANCODE_UP)))
        {
            _castle->ProcessActions( "up" );
            _movesUp = true;
            _movesLeft = false;
        }
        if (_inputs->KeyPressed( SDL_SCANCODE_A ) || (_inputs->KeyPressed(SDL_SCANCODE_LEFT)))
        {
            _castle->ProcessActions( "left" );
            _movesLeft = true;
            _movesUp = false;
        }
        if (_inputs->KeyPressed( SDL_SCANCODE_S ) || (_inputs->KeyPressed(SDL_SCANCODE_DOWN)))
        {
            _castle->ProcessActions( "down" );
            _movesUp = false;
            _movesLeft = false;
        }
        if (_inputs->KeyPressed( SDL_SCANCODE_D ) || (_inputs->KeyPressed(SDL_SCANCODE_RIGHT)))
        {
            _castle->ProcessActions( "right" );
            _movesLeft = false;
            _movesUp = false;
        }
        if (_inputs->Shift())
        {
            _castle->ProcessActions( "duck" );
            _animAC = true;
        }
        if (_inputs->KeyPressed( SDL_SCANCODE_SPACE ))
        {
            _castle->ProcessActions( "jump" );
            _animJ = true;
        }
        if (_inputs->KeyPressed( SDL_SCANCODE_RETURN ))
            _castle->ProcessActions( "pick" );

        if (_inputs->KeyPressed( SDL_SCANCODE_L ))
            _castle->ProcessActions( "long jump" );
    }
    if(pos!=_castle->GetPlayer()->GetPosition())
        _anim = true;
}

void MainScreen::Update()
{
 
    // Update the game
    _castle->AddIteration( Timer::GetInstance()->GetFrameTime());
    _castle->Update();

    // Update the animated textures of player
    float positionObjetHand = 0;
    if(_castle->GetPlayer()->GetHeldItem().GetObject().id !=  Object::ToObject( ObjectID::Nothing ).id)
    {
        switch (_castle->GetPlayer()->GetHeldItem().GetObject().id)
        {
            case 2:
                _playerHand = _crowbar;
                break;
            case 3:
                _playerHand = _ironKey;
                break;
            case 4:
                _playerHand = _goldKey;
                break;
            case 5:
                _playerHand = _grapplingHook;
                break;
            case 6:
                _playerHand = _torch;
                break;
            case 7:
                _playerHand = _lifePotion;
                break;
            default:
                break;
        }
        _playerHand->SetScale( Vector2f( (0.05+float(_castle->GetPlayer()->GetPosition().y)/80), (0.05+float(_castle->GetPlayer()->GetPosition().y)/80) ));
     /*   if (_castle->GetPlayer()->GetDirection() == VEC2_LEFT)
        {
            _player = _playerLeftH;
            positionObjetHand = -19.0-_castle->GetPlayer()->GetPosition().y*3;           
        }
        else if (_castle->GetPlayer()->GetDirection() == VEC2_DOWN)
        {
            _player = _playerDownH;
            positionObjetHand = 12.0+_castle->GetPlayer()->GetPosition().y;      
        }
        else if (_castle->GetPlayer()->GetDirection() == VEC2_RIGHT)
        {
            _player = _playerRightH;
            positionObjetHand = 25.0+_castle->GetPlayer()->GetPosition().y*3;      
        }
        else
        {
            _player = _playerUpH;
            positionObjetHand = -14.0-_castle->GetPlayer()->GetPosition().y*2;      

        }*/
    }
  // else{
        if(_anim == true){
            if (_castle->GetPlayer()->GetDirection() == VEC2_LEFT)
            {
                _playerAWL->SetWrapMode(AnimatedTexture::once);
                _player = _playerAWL;
            }
            else if (_castle->GetPlayer()->GetDirection() == VEC2_DOWN)
            {
                _playerAWD->SetWrapMode(AnimatedTexture::once);
                _player = _playerAWD;
            }
            else if (_castle->GetPlayer()->GetDirection() == VEC2_RIGHT)
            {
                _playerAWR->SetWrapMode(AnimatedTexture::once);
                _player = _playerAWR;
            }
            else
            {
                _playerAWU->SetWrapMode(AnimatedTexture::once);
                _player = _playerAWU;
            }
            _anim = !_player->GetanimationDone();
            if(_anim == false) _player->SetanimationDone(false);
        }
        else if(_animAC == true){
            if(_castle->GetPlayer()->GetDirection() == VEC2_LEFT)
            {
                if(_castle->GetPlayer()->Crouched() == false)
                {
                    _playerAUCL->SetWrapMode(AnimatedTexture::once);
                    _player = _playerAUCL;
                }
                else 
                {
                    _playerACL->SetWrapMode(AnimatedTexture::once);
                    _player = _playerACL;
                }
            }
            else if(_castle->GetPlayer()->GetDirection() == VEC2_DOWN)
            {
                if(_castle->GetPlayer()->Crouched() == false)
                {
                    _playerAUCU->SetWrapMode(AnimatedTexture::once);
                    _player = _playerAUCU;
                }
                else
                {
                    _playerACU->SetWrapMode(AnimatedTexture::once);
                    _player = _playerACU;
                }
            }
            else if(_castle->GetPlayer()->GetDirection() == VEC2_RIGHT)
            {
                if(_castle->GetPlayer()->Crouched() == false)
                {
                    _playerAUCR->SetWrapMode(AnimatedTexture::once);
                    _player = _playerAUCR;
                }
                else
                {
                    _playerACR->SetWrapMode(AnimatedTexture::once);
                    _player = _playerACR;
                }
            }
            else
            {
                if(_castle->GetPlayer()->Crouched() == false)
                {
                    _playerAUCD->SetWrapMode(AnimatedTexture::once);
                    _player = _playerAUCD;
                }
                else
                {
                    _playerACD->SetWrapMode(AnimatedTexture::once);
                    _player = _playerACD;
                }
            }
            _animAC = !_player->GetanimationDone();
            if(_animAC == false) {
                _player->SetanimationDone(false);
            }
        }
        else if(_animJ == true){
            if (_castle->GetPlayer()->GetDirection() == VEC2_LEFT )
            {
                _playerAJL->SetWrapMode(AnimatedTexture::once);   
                _player = _playerAJL;
            }
            else if (_castle->GetPlayer()->GetDirection() == VEC2_DOWN)
            {
                _playerAJU->SetWrapMode(AnimatedTexture::once);   
                _player = _playerAJU;
            }
            else if (_castle->GetPlayer()->GetDirection() == VEC2_RIGHT)
            {
                _playerAJR->SetWrapMode(AnimatedTexture::once);   
                _player = _playerAJR;
            }
            else
            {
                _playerAJD->SetWrapMode(AnimatedTexture::once);   
                _player = _playerAJD;
            }
            _animJ = !_player->GetanimationDone();
            if(_animJ == false) _player->SetanimationDone(false);
        }
        else if(_castle->GetPlayer()->Crouched() == true)
        {
            if(_castle->GetPlayer()->GetDirection() == VEC2_LEFT)
                _player = _playerACTL;
            else if(_castle->GetPlayer()->GetDirection() == VEC2_DOWN)
                _player = _playerACTU;
            else if(_castle->GetPlayer()->GetDirection() == VEC2_RIGHT)
                _player = _playerACTR;
            else
                _player = _playerACTD;
        }
        else{
            if (_castle->GetPlayer()->GetDirection() == VEC2_LEFT )
            {
                _player = _playerLeft;
            }
            else if (_castle->GetPlayer()->GetDirection() == VEC2_DOWN)
            {
                _player = _playerDown;
            }
            else if (_castle->GetPlayer()->GetDirection() == VEC2_RIGHT)
            {
                _player = _playerRight;
            }
            else
            {
                _player = _playerUp;
            }
        }
  //  }
    _player->Update();
    _playerAWL->Update();
    _playerAWR->Update();
    _playerAWU->Update();
    _playerAWD->Update();
    _playerHand->Update();
    _playerLeft->Update();
    _playerRight->Update();
    _playerDown->Update();
    _playerUp->Update();
    const Vector2i& player = _castle->GetPlayer()->GetPosition();
    CastleToScreen( _player, player.x, player.y );


    _player->SetScale( Vector2f( (0.7+float(_castle->GetPlayer()->GetPosition().y)/10), (0.7+float(_castle->GetPlayer()->GetPosition().y)/9) ));
    _player->SetPosition( _player->GetPosition() - Vector2i( 0, _player->GetHeight()*(0.35+float(_castle->GetPlayer()->GetPosition().y)/30)) );
  //_player->SetPosition( _player->GetPosition()+(_castle->GetPlayer()->GetDirection()*)   - Vector2i( 0, _player->GetHeight()*(0.35+float(_castle->GetPlayer()->GetPosition().y)/30)) );
  
  /*  if(positionObjetHand!=0){
        _playerHand->SetPosition(Vector2f(float(_player->GetPosition().x+positionObjetHand), float(_player->GetPosition().y-15)));

    std::cout << float(_player->GetPosition().x) << std::endl;  
    } */


#ifdef DEBUG
    if (_castle->GetBat()->GetActiveState())
    {
        _bat->Update();
        const Vector2i& bat = _castle->GetBat()->GetPosition();
        CastleToScreen( _bat, bat.x, bat.y );
        _bat->SetPosition( _bat->GetPosition() - Vector2i( 0, _bat->GetHeight()*0.5f ));
    }
    if (_castle->GetRat()->GetActiveState())
    {
        _rat->Update();
        const Vector2i& rat = _castle->GetRat()->GetPosition();
        CastleToScreen( _rat, rat.x, rat.y );
        _rat->SetPosition( _rat->GetPosition() - Vector2i( 0, _rat->GetHeight()*0.5f ));
    }
#endif // DEBUG

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
    if (!_castle->GetPlayer()->GetItems().empty())
    {
        SDL_Color color = { 0, 0, 0, 0xFF };
        if (_castle->GetPlayer()->GetHeldItem().GetObject().GetID() == ObjectID::Crowbar)
        {
            auto red = (Uint8) LinearInterp( 0, 255, (float) _castle->GetPlayer()->GetHeldItem().GetDurability()/
                                                     Object::ToObject( ObjectID::Crowbar ).maxDurability );
            auto green = (Uint8) LinearInterp( 255, 0, (float) _castle->GetPlayer()->GetHeldItem().GetDurability()/
                                                       Object::ToObject( ObjectID::Crowbar ).maxDurability );

            color = { red, green, 0, 0xFF };
        }

        delete _item;
        const ItemStack& held = _castle->GetPlayer()->GetHeldItem();
        _item = new Texture( _translation->GetTranslation( 15 ) + " : " +_translation->GetTranslation(_translation->SearchWord(held.GetObject().name, 'E')), "Roboto-Regular.ttf",
                             25, color );
        _item->SetPosition( Vector2f( Graphics::SCREEN_WIDTH*0.75f, Graphics::SCREEN_HEIGHT*0.75f ));
    }
    else
    {
        delete _item;
        _item = new Texture( _translation->GetTranslation( 15 ) + " : ", "Roboto-Regular.ttf",
                             25, { 0, 0, 0 } );
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
        _rightTorch->Render();
    if (rightDoor->GetTorchState())
        _rightFire->Render();


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
        _upTorch->Render();
    if (upDoor->GetTorchState())
        _upFire->Render();

    // Left door
    const Door* const leftDoor = currentRoom->GetDoor( Room::Left );

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

    // Torch of the left door
    if (leftDoor->HasTorch())
        _leftTorch->Render();
    if (leftDoor->GetTorchState())
        _leftFire->Render();


    // Ground objects
    GameEntity hole;
    for (int row = 0 ; row < ROOM_HEIGHT ; ++row)
    {
        for (int col = 0 ; col < ROOM_WIDTH ; ++col)
        {
            switch (currentRoom->GetSquare( Vector2i( row, col )))
            {
                case (uint8_t) ObjectID::IronKey:CastleToScreen( _ironKey, row, col );
                    _ironKey->Render();
                    break;
                case (uint8_t) ObjectID::GoldKey:CastleToScreen( _goldKey, row, col );
                    _goldKey->Render();
                    break;
                case (uint8_t) ObjectID::LifePotion:CastleToScreen( _lifePotion, row, col );
                    _lifePotion->Render();
                    break;
                case (uint8_t) ObjectID::GrapplingHook:CastleToScreen( _grapplingHook, row, col );
                    _grapplingHook->Render();
                    break;
                case (uint8_t) ObjectID::Hint1:
                case (uint8_t) ObjectID::Hint2:
                case (uint8_t) ObjectID::Hint3:CastleToScreen( _hint, row, col );
                    _hint->Render();
                    break;
                case (uint8_t) ObjectID::Egg:CastleToScreen( _egg, row, col );
                    _egg->Render();
                case -1: // Money
                    CastleToScreen( _moneybag, row, col );
                    _moneybag->Render();
                case -3:
                case -4: // Holes
                    // TODO a remplacer par une image
                    CastleToScreen( &hole, row, col );
                    Graphics::GetInstance()->DrawEllipseFill( hole.GetPosition(), 20, 10 );
                    break;
                default:break;
            }
        }

        // Player
        if(row==_castle->GetPlayer()->GetPosition().y){
          //  if(_castle->GetPlayer()->GetHeldItem().GetObject().id !=  Object::ToObject( ObjectID::Nothing ).id)
              //  _playerHand->Render();
            _player->Render();
        }
        #ifdef DEBUG
        if (_castle->GetRat()->GetActiveState() && _castle->GetRat()->GetVisible())
            if(_castle->GetRat()->GetPosition().y==row)
                _rat->Render();
        if (_castle->GetBat()->GetActiveState())
            if(_castle->GetBat()->GetPosition().y==row)
                _bat->Render();
        #endif // DEBUG
    }

    // If not light
    if (!( leftDoor->GetTorchState()) && !( rightDoor->GetTorchState()) && !( upDoor->GetTorchState()))
    {
        _notLit->Render();
        _textNotLit->Render();
    }

    //Render chest
    if(rightDoor->GetDoorType()== Door::DOORS::chest){
        if (rightDoor->GetObject() == 0)
            _chestOpen->Render( SDL_FLIP_HORIZONTAL);
        else
            _chestClosed->Render(SDL_FLIP_HORIZONTAL);
    }
    if(leftDoor->GetDoorType()== Door::DOORS::chest){
        if (leftDoor->GetObject() == 0)
            _chestOpen->Render( );
        else
            _chestClosed->Render();
    }

#ifdef DEBUG
 /*   if (_castle->GetBat()->GetActiveState())
        _bat->Render();
    if (_castle->GetRat()->GetActiveState() && _castle->GetRat()->GetVisible())
        _rat->Render();*/
#endif // DEBUG

    temp->Render();
}

void MainScreen::CastleToScreen( GameEntity* entity, int row, int col )
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

    entity->SetPosition( coordinates[ col ][ row ] );
}

float MainScreen::LinearInterp( int begin, int end, float amount )
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