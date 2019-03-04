//
// Created by serdok on 04/03/19.
//

#include "Sound.h"

Sound::Sound( const std::string& soundpath )
{
    _sound = Mix_LoadWAV( GetResourcePath( soundpath ).c_str() );
    if (!_sound)
        throw Exception( "Sound " + soundpath + " failed to load : " + std::string( SDL_GetError() ), __FILE__, __LINE__ );
}

Sound::~Sound()
{
    Cleanup( _sound );
}

void Sound::Play( int loops, int channel )
{
    Mix_PlayChannel( channel, _sound, --loops );
}