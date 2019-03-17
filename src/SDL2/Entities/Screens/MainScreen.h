//
// Created by serdok on 16/03/19.
//

#ifndef GOLDEN_PHOENIX_MAINSCREEN_H
#define GOLDEN_PHOENIX_MAINSCREEN_H

// Custom headers
#include "Castle.h"

#include "Texture.h"


class MainScreen : public GameEntity
{
private:
    Castle* _castle;
    Texture* _player;

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


public:
    explicit MainScreen( Castle* castle );
    ~MainScreen() final;

    void ProcessEvents( SDL_Event* event );

    void Update() final;
    void Render() final;
};

#endif //GOLDEN_PHOENIX_MAINSCREEN_H
