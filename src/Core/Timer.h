//
// Created by serdok on 03/03/19.
//

#ifndef GOLDEN_PHOENIX_TIMER_H
#define GOLDEN_PHOENIX_TIMER_H

// Custom headers


// SDL2 headers
#include <SDL2/SDL.h>

// C++ headers



class Timer
{
private:
    static Timer* sInstance;

    unsigned int mStartTicks;
    unsigned int mElapsedTicks;

    float mDeltaTime;
    float mTimeScale;

public:
    static Timer* GetInstance();
    static void Release();

    void Reset();
    void Update();

    float GetDeltaTime() const;
    float GetTimeScale() const;
    unsigned int GetElapsedTicks() const;

    void SetTimeScale( float t );

private:
    Timer();
    ~Timer();
};


#endif //SDL2_FRAMEWORK_TIMER_H
