//
// Created by serdok on 16/03/19.
//

#ifndef GOLDEN_PHOENIX_MAINSCREEN_H
#define GOLDEN_PHOENIX_MAINSCREEN_H

// Custom headers
#include "Castle.h"

#include "AnimatedTexture.h"
#include "InputsManager.h"



class MainScreen : public Texture
{
private:
    Castle* _castle;

    InputsManager* _inputs;

#ifdef DEBUG
    Texture* _player;
#else
    AnimatedTexture* _player;
#endif // DEBUG
    bool _movesLeft;

    // Text textures
    Texture* _score;
    Texture* _life;
    Texture* _money;
    Texture* _item;

    // Room features
    Texture* _chimney;
    Texture* _chest;
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

    // Objects
    Texture* _ironKey;
    Texture* _goldKey;
    Texture* _lifePotion;
    Texture* _grapplingHook;
    Texture* _hint;


public:
    //! Load the main screen from a Castle
    explicit MainScreen( Castle* castle );
    ~MainScreen() final;


    //! Process inputs and SDL2 events
    void ProcessEvents( SDL_Event* event );

    //! Update textures and game
    void Update() final;

    //! Render the buffer
    void Render() final;

private:
    //! Convert grid coordinates from the castle to SDL2 coordinates
    void CastleToScreen( Texture* texture, int row, int col );
};

#endif //GOLDEN_PHOENIX_MAINSCREEN_H
