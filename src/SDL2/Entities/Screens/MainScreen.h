//
// Created by serdok on 16/03/19.
//

#ifndef GOLDEN_PHOENIX_MAINSCREEN_H
#define GOLDEN_PHOENIX_MAINSCREEN_H

// Custom headers
#include "Castle.h"
#include "Translation.h"

#include "AnimatedTexture.h"
#include "InputsManager.h"
#include "AudioManager.h"


//! Class rendering the main game
class MainScreen : public Texture
{
private:
    Castle* _castle;

    Translation* _translation;

    InputsManager* _inputs;

    Texture* temp;
    const Vector2f vel = Vector2i( 10, 10 );
    Vector2i speed;

    AudioManager* _audio;
    AnimatedTexture* _player = nullptr;
    AnimatedTexture* _playerLeft;
    AnimatedTexture* _playerRight;
    AnimatedTexture* _playerUp;
    AnimatedTexture* _playerDown;
    AnimatedTexture* _playerAWL;
    AnimatedTexture* _playerAWR;
    AnimatedTexture* _playerAWU;
    AnimatedTexture* _playerAWD;
    AnimatedTexture* _playerACL;
    AnimatedTexture* _playerAUCL;
    AnimatedTexture* _playerACD;
    AnimatedTexture* _playerAUCD;
    AnimatedTexture* _playerACR;
    AnimatedTexture* _playerAUCR;
    AnimatedTexture* _playerACU;
    AnimatedTexture* _playerAUCU;
    AnimatedTexture* _playerAJL;
    AnimatedTexture* _playerAJD;
    AnimatedTexture* _playerAJR;
    AnimatedTexture* _playerAJU;
    AnimatedTexture* _playerACTL;
    AnimatedTexture* _playerACTD;
    AnimatedTexture* _playerACTR;
    AnimatedTexture* _playerACTU;
    AnimatedTexture* _playerDEATH;
    Texture* _playerHand;
    AnimatedTexture* _playerLeftH;
    AnimatedTexture* _playerRightH;
    AnimatedTexture* _playerUpH;
    AnimatedTexture* _playerDownH;

    bool _movesLeft = false;
    bool _movesUp = false;
    bool _anim = false;
    bool _animAC = false;
    bool _animJ = false;

    // Text textures
    Texture* _score;
    Texture* _life;
    Texture* _money;
    Texture* _item;
#ifdef DEBUG
    Texture* _leftRoomID;
    Texture* _upperRoomID;
    Texture* _rightRoomID;
#endif // DEBUG

    // Room features
    Texture* _chimney;
    Texture* _chestClosed;
    Texture* _chestOpen;
    Texture* _corridor;
    Texture* _rightGate;
    Texture* _upGate;
    Texture* _leftGate;
    Texture* _rightOpening;
    Texture* _upOpening;
    Texture* _leftOpening;
    Texture* _rightDoor;
    Texture* _upDoor;
    Texture* _leftDoor;
    Texture* _rightTorch;
    Texture* _upTorch;
    Texture* _leftTorch;
    Texture* _notLit;
    Texture* _textNotLit;
    Texture* _rat;
    Texture* _bat;
    AnimatedTexture* _leftFire;
    AnimatedTexture* _upFire;
    AnimatedTexture* _rightFire;

    // Objects
    Texture* _torch;
    Texture* _crowbar;
    Texture* _ironKey;
    Texture* _goldKey;
    Texture* _lifePotion;
    Texture* _grapplingHook;
    Texture* _hint;
    Texture* _moneybag;
    Texture* _egg;

public:
    //! Load the main screen from a Castle
    explicit MainScreen( Castle* castle, Translation* trans );

    //! Free resources without deleting the Castle
    ~MainScreen() final;

    void SetCastle( Castle* const castle );
    void SetTranslation( Translation* const translation );

    //! Process inputs and SDL2 events
    void ProcessEvents( SDL_Event* event );

    //! Update textures and game
    void Update() final;

    //! Render the buffer
    void Render() final;

private:
    //! Convert grid coordinates from the castle to SDL2 coordinates on the screen
    void CastleToScreen( GameEntity* entity, int row, int col );

    //! Linear interpolation
    float LinearInterp( int begin, int end, float amount );
};

#endif //GOLDEN_PHOENIX_MAINSCREEN_H
