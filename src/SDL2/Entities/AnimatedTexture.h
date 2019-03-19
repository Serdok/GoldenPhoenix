//
// Created by serdok on 09/03/19.
//

#ifndef GOLDEN_PHOENIX_ANIMATEDTEXTURE_H
#define GOLDEN_PHOENIX_ANIMATEDTEXTURE_H

// Custom headers
#include "Texture.h"
#include "Timer.h"


// TODO Julia je te laisse le faire ça :p
//! Animated game entity that will be drawn
class AnimatedTexture : public Texture
{
public:
    enum ANIMATION_DIRECTIONS
    {
        horizontal = 0,
        vertical
    };

    enum WRAP_MODE
    {
        once = 0,
        loop
    };

private:

    Timer* _timer;

    int _startX, _startY;
    ANIMATION_DIRECTIONS _animDirection;
    WRAP_MODE _wrap;
    int _frameCount;
    float _animationSpeed;
    float _timePerFrame;
    bool _animationDone;

    float _animationTimer;

public:
    AnimatedTexture( const std::string& spritefile, int x, int y, int width, int height, int nombreImages, float vitesseAnimation, ANIMATION_DIRECTIONS direction, bool fullscreen = false );
    ~AnimatedTexture() override;

    void SetWrapMode( WRAP_MODE wrap );

    void Update() override;
};


#endif //GOLDEN_PHOENIX_ANIMATEDTEXTURE_H
