//
// Created by serdok on 09/03/19.
//

#include "AnimatedTexture.h"

AnimatedTexture::AnimatedTexture( const std::string& spritefile, int x, int y, int width, int height, int frameCount, float animationSpeed, ANIMATION_DIRECTIONS direction, bool fullscreen )
: Texture( spritefile, x, y, width, height, fullscreen ), _startX( x ), _startY( y ), _frameCount( frameCount ), _animationSpeed( animationSpeed ), _animDirection( direction )
{
    _timer = Timer::GetInstance();

    _timePerFrame = _animationSpeed / _frameCount;
}

AnimatedTexture::~AnimatedTexture()
{
    _timer = nullptr;
}

void AnimatedTexture::SetWrapMode( AnimatedTexture::WRAP_MODE wrap )
{
    _wrap = wrap;
}

void AnimatedTexture::Update()
{
    if (_animationDone)
        return;

    // Add a frame time to the animation timer
    _animationTimer += _timer->GetDeltaTime();
    if (_animationTimer >= _animationSpeed)
    {
        if (_wrap == once) // End the animation, set the texture to the last sprite
        {
            _animationDone = true;
            _animationTimer = _animationSpeed - _timePerFrame;
        }
        else if (_wrap == loop){ // Restart the timer
            _animationTimer -= _animationSpeed;
        }
    }

    if (_animDirection == ANIMATION_DIRECTIONS::horizontal) // Clip goes right
        _clip.x = _startX + (int) (_animationTimer/_timePerFrame) * _width;
    else if(_animDirection == ANIMATION_DIRECTIONS::vertical)// Clip goes down
        _clip.y = _startY + (int) (_animationTimer/_timePerFrame) * _height;
    else
        _clip.x = _startX - (int) (_animationTimer/_timePerFrame) * _width;
    
}

bool AnimatedTexture::GetanimationDone()
{
    return _animationDone;
}

void AnimatedTexture::resetAnimation()
{
    _animationDone = false;
    _animationTimer = 0;
}