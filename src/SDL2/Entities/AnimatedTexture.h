//
// Created by serdok on 09/03/19.
//

#ifndef GOLDEN_PHOENIX_ANIMATEDTEXTURE_H
#define GOLDEN_PHOENIX_ANIMATEDTEXTURE_H

// Custom headers
#include "Texture.h"
#include "Timer.h"


//! Animated game entity that will be drawn
class AnimatedTexture : public Texture
{
public:
    //! List of the alignment types of the sprites in the sprite sheet
    enum ANIMATION_DIRECTIONS
    {
        horizontal = 0, ///< Sprites are aligned horizontally in the image file
        vertical,
        DvG        ///< Sprites are aligned vertically in the image file
    };

    //! Mode of wrapping.
    enum WRAP_MODE
    {
        once = 0, ///< Will loop the texture once
        loop      ///< Will loop the texture indefinitely
    };

private:

    Timer* _timer;

    int _startX, _startY;
    ANIMATION_DIRECTIONS _animDirection;
    WRAP_MODE _wrap = loop;
    int _frameCount;
    float _animationSpeed;
    float _timePerFrame;
    bool _animationDone = false;
    float _animationTimer = 0.0f;

public:
    /**
     * Load an animated texure. Images must be located in the folder data/images
     * @param [in] spritefile File name of the sprite sheet
     * @param [in] x Top left x coordinate of the first sprite
     * @param [in] y Top left y coordinate of the first sprite
     * @param [in] width Width of one sprite
     * @param [in] height Height of one sprite
     * @param [in] frameCount Number of frames in one cycle
     * @param [in] animationSpeed Speed (in seconds) of one cycle
     * @param [in] direction The alignment of the sprites in the sheet (horizontal, vertical)
     * @param [in] fullscreen If the texture should be rendered on the whole screen (default : false)
     */
    AnimatedTexture( const std::string& spritefile, int x, int y, int width, int height, int frameCount, float animationSpeed, ANIMATION_DIRECTIONS direction, bool fullscreen = false );
    ~AnimatedTexture() override;

    //! Set the loop mode of the animation
    void SetWrapMode( WRAP_MODE wrap );

    //! Update the texture and select the next sprite in line
    void Update() override;

    bool GetanimationDone();
    void SetanimationDone(bool anim);
};


#endif //GOLDEN_PHOENIX_ANIMATEDTEXTURE_H
