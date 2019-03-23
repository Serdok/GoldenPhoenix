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
    return _deltaTime;
}

float Timer::GetTimeScale() const
{
    return _timeScale;
}

void Timer::SetTimeScale( float t )
{
    _timeScale = t;
}

void Timer::Reset()
{
    _startTicks = SDL_GetTicks();
    _elapsedTicks = 0;

    _deltaTime = 0.0f;
}

void Timer::Update()
{
    _elapsedTicks = SDL_GetTicks() - _startTicks;
    _deltaTime = _elapsedTicks * 0.001f;
}

unsigned int Timer::GetElapsedTicks() const
{
    return _elapsedTicks;
}