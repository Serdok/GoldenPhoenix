//
// Created by serdok on 05/03/19.
//

#ifndef GOLDEN_PHOENIX_AUDIOENGINE_H
#define GOLDEN_PHOENIX_AUDIOENGINE_H

// Custom headers
#include "Exceptions.h"

// FMod headers
#include "fmod.hpp"
#include "fmod_studio.hpp"
#include "fmod_errors.h"

// C++ headers
#include <math.h>
#include <map>
#include <string>
#include <vector>


//! Structure holding position. Useful for sound positionning
struct Vector3
{
    int x, y, z;
};

//! Structure holding information about FMod library, also serves as a cache
struct Implementation
{
    FMOD::Studio::System* mStudioSystem = nullptr;
    FMOD::System* mSystem = nullptr;

    typedef std::map< std::string, FMOD::Sound* > SoundCache;
    SoundCache mSounds;

    typedef std::map< int, FMOD::Channel* > ChannelCache;
    ChannelCache mChannels;
    int mNextChannelID = 0;

    typedef std::map< std::string, FMOD::Studio::EventInstance* > EventCache;
    EventCache mEvents;

    typedef std::map< std::string, FMOD::Studio::Bank* > BankCache;
    BankCache mBanks;

    Implementation();
    ~Implementation();

    void Update();

    static void ErrorCheck( FMOD_RESULT result );
};

//! Singleton class managing all audio in the game
class AudioManager
{
private:
    static Implementation* _implementation;
    static AudioManager* _instance;


public:
    //! Get the singleton
    static AudioManager* GetInstance();
    //! Release the singleton
    static void Shutdown();

    //! Update audio
    static void Update();

    /**
     * Load a bank file.
     * @warning File paths must be absolute
     * @param [in] bankFile Name of the bank file
     * @param [in] flags Flags used for loading the bank
     */
    void LoadBank( const std::string& bankFile, FMOD_STUDIO_LOAD_BANK_FLAGS flags );

    /**
     * Load a sound / music file.
     * @warning File paths must be absolute
     * @param [in] soundFile Name of the sound / music file
     * @param [in] looping If the sound / music should loop
     * @param [in] spatial If the sound / music should support 3D
     * @param [in] stream If the sound / music should be streamed
     */
    void LoadSound( const std::string& soundFile, bool looping = false, bool spatial = false, bool stream = false );

    /**
     * Play a sound / music from a file. Loads it first if not previously loaded
     * @warning File paths must be absolute
     * @param [in] soundFile Name of the sound / music file
     * @param [in] position Position of the sound in space. Only has effect if the sound / music was loaded supporting 3D
     * @param [in] dB Initial volume in decibels
     * @return The channel of the sound / music
     */
    int PlaySound( const std::string& soundFile, const Vector3& position = { 0, 0, 0 }, float dB = 0.0f );

    /**
     * Unload a sound / music
     * @warning File paths must be absolute
     */
    void UnloadSound( const std::string& soundFile );

    /**
     * Load an event
     * @warning File paths must be absolute
     * @param [in] eventName Name of the event
     */
    void LoadEvent( const std::string& eventName );

    /**
     * Play an event. Loads it first if not previously loaded
     * @warning File paths must be absolute
     * @param [in] eventName Name of the event
     */
    void PlayEvent( const std::string& eventName );

    /**
     * Stop an event
     * @param [in] eventName Name of the event
     * @param [in] immediate If the event should stop now
     */
    void StopEvent( const std::string& eventName, bool immediate = false );

    /**
     * Get a parameter value from an event
     * @param [in] eventName Name of the event
     * @param [in] parameterName Name of the parameter
     * @param [out] value Value of the parameter
     */
    void GetEventParameter( const std::string& eventName, const std::string& parameterName, float* value );

    /**
     * Set a parameter value to an event
     * @param [in] eventName Name of the event
     * @param [in] parameterName Name of the parameter
     * @param [in] value Value of the parameter
     */
    void SetEventParameter( const std::string& eventName, const std::string& parameterName, float value );

    //! Stop all playing sounds / musics
    void StopAllChannels();

    //! Stop a specific sound / music
    void StopChannel( int id );

    //! Set a position for a specific sound / music
    void SetChannel3DPosition( int id, const Vector3& position );

    //! Set a volume for a specific sound / music
    void SetChannelVolume( int id, float dB );

    //! Return true if the channel is playing
    bool IsPlaying( int id ) const;

    //! Return true if the event is playing
    bool IsEventPlaying( const std::string& eventName ) const;

    //! Convert decibel to volume
    float dBToVolume( float dB );

    //! Convert volume to decibel
    float VolumeTodB( float volume );

    //! Convert Vector3 to FMOD_VECTOR
    FMOD_VECTOR Vector3ToFmod( const Vector3& v );

private:
    AudioManager();
    ~AudioManager();
};


#endif //GOLDEN_PHOENIX_AUDIOENGINE_H
