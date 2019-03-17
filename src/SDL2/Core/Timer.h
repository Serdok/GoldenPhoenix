//
// Created by serdok on 03/03/19.
//

#ifndef GOLDEN_PHOENIX_TIMER_H
#define GOLDEN_PHOENIX_TIMER_H

// Custom headers


// SDL2 headers
#include "SDL.h"

// C++ headers


//! Singleton class handling all timer functions
class Timer
{
private:
    static Timer* sInstance;

    unsigned int mStartTicks;
    unsigned int mElapsedTicks;

    float mDeltaTime;
    float mTimeScale;

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

    //! Get the elapsed ticks since the beginning of the frame
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
