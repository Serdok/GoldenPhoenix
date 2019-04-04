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
    _frameTicks = 0;

    _deltaTime = 0.0f;
}

void Timer::Update()
{
    _frameTicks = SDL_GetTicks() - _startTicks;
    _deltaTime = _frameTicks * 0.001f;
}

unsigned int Timer::GetFrameTime() const
{
    return _frameTicks;
}

unsigned int Timer::GetElapsedTicks() const
{
    return SDL_GetTicks();
}