//
// Created by serdok on 05/03/19.
//

#ifndef GOLDEN_PHOENIX_STARTSCREEN_H
#define GOLDEN_PHOENIX_STARTSCREEN_H

// Custom headers
#include "AudioManager.h"
#include "Texture.h"
#include "Timer.h"

#include "Player.h"
#include "Castle.h"


class StartScreen : public GameEntity
{
private:
    AudioManager* _audio;
    Timer* _timer;

    FMOD::Sound* _bgm;

    Texture* _bgi;
    Texture* _startText;
    Texture* _shopText;

    Player* player;
    Castle* castle;


public:
    StartScreen();
    ~StartScreen();

    void ProcessEvents( SDL_Event* event );

    void Update() override;

    void Render() override;
};


#endif //GOLDEN_PHOENIX_STARTSCREEN_H
