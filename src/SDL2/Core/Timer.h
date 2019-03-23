//
// Created by serdok on 03/03/19.
//

#ifndef GOLDEN_PHOENIX_TIMER_H
#define GOLDEN_PHOENIX_TIMER_H

// SDL2 headers
#include "SDL.h"


//! Singleton class handling all timer functions
class Timer
{
private:
    static Timer* sInstance;

    unsigned int _startTicks;
    unsigned int _elapsedTicks = 0;

    float _deltaTime = 0.0f;
    float _timeScale = 1.0f;

public:
    //! Return the instance of the class
    static Timer* GetInstance();

    //! Release the instance of the class
    static void Stop();

    //! Reset the timer
    void Reset();

    //! Update the timer
    void Update();

    //! Get the elapsed milliseconds since the beginning of the frame
    float GetDeltaTime() const;

    //! Get the elapsed ticks since the beginning of the game
    unsigned int GetElapsedTicks() const;

    //! Get the current time scale
    float GetTimeScale() const;

    //! Set the time scale
    void SetTimeScale( float t );

private:
    Timer();
    ~Timer();
};


#endif //SDL2_FRAMEWORK_TIMER_H
