//
// Created by serdok on 09/03/19.
//

#ifndef GOLDEN_PHOENIX_GAMEMANAGER_H
#define GOLDEN_PHOENIX_GAMEMANAGER_H

// Custom headers
#include "ScreensManager.h"


//! Game manager
class GameManager
{
private:
    Graphics* _graphicsMgr;
    SDL_Event _event;
    bool _quit;

    Timer* _timer;
    const int FPS = 60;

    AudioManager* _audio;
    InputsManager* _inputs;


    ScreensManager* _screens;


public:
    /**
     * Build a new game, initialize graphics and objects
     * @exception Exception if any manager failed to be loaded
     */
    GameManager() noexcept( false );

    //! Delete a game, destroy objects and close graphics
    ~GameManager();

    //! Run the game
    void Run();

private:
    void InitObjects(); ///< Initialize objects
    void DeleteObjects(); ///< Delete objects

    void ProcessEvents(); ///< Process events

    void EarlyUpdate(); ///< Early update : Input states, ...
    void Update(); ///< Update : Physics, collisions, ...
    void LateUpdate(); ///< Late update : Timer reset, previous Input states

    void Render(); ///< Render everything
};


#endif //GOLDEN_PHOENIX_GAMEMANAGER_H
