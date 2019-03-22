//
// Created by serdok on 03/03/19.
//

#include "Timer.h"

Timer* Timer::sInstance = nullptr;

Timer* Timer::GetInstance()
{
    if (!sInstance)
        sInstance = new Timer();
    return sInstance;
}

void Timer::Stop()
{
    delete sInstance;
}

Timer::Timer()
{
    Reset();
}

Timer::~Timer() = default;

float Timer::GetDeltaTime() const
{
    return mDeltaTime;
}

float Timer::GetTimeScale() const
{
    return mTimeScale;
}

void Timer::SetTimeScale( float t )
{
    mTimeScale = t;
}

void Timer::Reset()
{
    mStartTicks = SDL_GetTicks();
    mElapsedTicks = 0;

    mDeltaTime = 0.0f;
}

void Timer::Update()
{
    mElapsedTicks = SDL_GetTicks() - mStartTicks;
    mDeltaTime = mElapsedTicks * 0.001f;
}

unsigned int Timer::GetElapsedTicks() const
{
    return mElapsedTicks;
}