//
// Created by serdok on 09/03/19.
//

#ifndef GOLDEN_PHOENIX_GAMEMANAGER_H
#define GOLDEN_PHOENIX_GAMEMANAGER_H

// Custom headers
#include "Graphics.h"
#include "Timer.h"

#include "StartScreen.h"

// C++ headers
#include <cassert>
#include <iostream>
#include <vector>


class GameManager
{
private:
    Graphics* _graphicsMgr;
    SDL_Event _event;
    bool _quit;

    Timer* _timer;
    const int FPS = 60;


    // Test variables
    StartScreen* _startScreen;


public:
    GameManager();

    ~GameManager();

    void Run();

private:
    void InitObjects();

    void DeleteObjects();

    void ProcessEvents();

    void EarlyUpdate();

    void Update();

    void LateUpdate();

    void Render();
};


#endif //GOLDEN_PHOENIX_GAMEMANAGER_H
