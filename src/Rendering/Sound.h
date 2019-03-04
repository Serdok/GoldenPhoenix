//
// Created by serdok on 04/03/19.
//

#ifndef GOLDEN_PHOENIX_SOUND_H
#define GOLDEN_PHOENIX_SOUND_H

// Custom headers
#include "Cleanup.h"
#include "Exceptions.h"
#include "GetResourcePath.h"

// SDL2 headers
#include "SDL_mixer.h"
#include "fmod.h"


// C++ headers
#include <string>


//! Sound loader and player class
class Sound
{
private:
    Mix_Chunk* _sound;

public:
    Sound( const std::string& soundpath );
    ~Sound();

    void Play( int loops = 1, int channel = 0 );
};


#endif //GOLDEN_PHOENIX_SOUND_H
