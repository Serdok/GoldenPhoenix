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

    AnimatedTexture* _player;
    bool _movesLeft;

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
    explicit MainScreen( Castle* castle );
    ~MainScreen() final;

    void ProcessEvents( SDL_Event* event );

    void Update() final;
    void Render() final;
};

#endif //GOLDEN_PHOENIX_MAINSCREEN_H
