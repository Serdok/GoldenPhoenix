//
// Created by serdok on 09/03/19.
//

#include "AnimatedTexture.h"

AnimatedTexture::AnimatedTexture( const std::string& spritefile, int x, int y, int width, int height, int nombreImages, float vitesseAnimation, ANIMATION_DIRECTIONS direction, bool fullscreen )
: Texture( spritefile, x, y, width, height, fullscreen ), _startX( x ), _startY( y ), _frameCount( nombreImages ), _animationSpeed( vitesseAnimation ), _animDirection( direction )
{
    _timer = Timer::GetInstance();

    _animationTimer = 0.0f;
    _animationDone = false;
    _timePerFrame = _animationSpeed / _frameCount;

    _wrap = loop;
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

    _animationTimer += _timer->GetDeltaTime();
    if (_animationTimer >= _animationSpeed)
    {
        if (_wrap == once)
        {
            _animationDone = true;
            _animationTimer = _animationSpeed - _timePerFrame;
        }
        else
            _animationTimer -= _animationSpeed;
    }

    if (_animDirection == ANIMATION_DIRECTIONS::horizontal)
        _clip.x = _startX + (int) (_animationTimer/_timePerFrame) * _width;
    else
        _clip.y = _startY + (int) (_animationTimer/_timePerFrame) * _height;
}