//
// Created by serdok on 05/03/19.
//

#include "AudioManager.h"

AudioManager* AudioManager::sInstance = nullptr;

AudioManager* AudioManager::GetInstance()
{
    if (!sInstance)
        sInstance = new AudioManager();
    return sInstance;
}

void AudioManager::Shutdown()
{
    delete sInstance;
}

void AudioManager::ErrorCheck( const FMOD_RESULT& status )
{
    if (status != FMOD_OK)
        throw Exception( "FMOD Error : " + std::string( FMOD_ErrorString( status ) ), __FILE__, __LINE__ );
}

AudioManager::AudioManager()
{
    // Initialize FMod
    AudioManager::ErrorCheck( FMOD::System_Create( &_system ) );
    AudioManager::ErrorCheck( _system->init( 512, FMOD_INIT_NORMAL, nullptr ) );
}

AudioManager::~AudioManager()
{
    // Close system, release FMod
    AudioManager::ErrorCheck( _system->close() );
    AudioManager::ErrorCheck( _system->release() );
}

FMOD::Sound* AudioManager::LoadSound( const std::string& soundfile, bool spatial )
{
    FMOD::Sound* sound;
    FMOD_MODE modes = FMOD_CREATESAMPLE;
    modes |= (spatial ? FMOD_3D : FMOD_2D);
    AudioManager::ErrorCheck( _system->createSound( GetResourcePath( "sounds/" + soundfile ).c_str(), modes, nullptr, &sound ) );

    return sound;
}

void AudioManager::PlaySound( FMOD::Sound* sound )
{
    AudioManager::ErrorCheck( _system->playSound( sound, nullptr, false, nullptr ) );
}

void AudioManager::FreeSound( FMOD::Sound* sound )
{
    AudioManager::ErrorCheck( sound->release() );
}

FMOD::Sound* AudioManager::LoadMusic( const std::string& musicfile, bool spatial )
{
    FMOD::Sound* music;
    FMOD_MODE modes = FMOD_CREATESTREAM;
    modes |= (spatial ? FMOD_3D : FMOD_2D);
    AudioManager::ErrorCheck( _system->createSound( GetResourcePath( "musics/" + musicfile ).c_str(), modes, nullptr, &music ) );

    return music;
}

void AudioManager::PlayMusic( FMOD::Sound* music )
{
    AudioManager::ErrorCheck( _system->playSound( music, nullptr, false, nullptr ) );
}

void AudioManager::FreeMusic( FMOD::Sound* music )
{
    AudioManager::ErrorCheck( music->release() );
}
