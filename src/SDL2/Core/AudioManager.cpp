//
// Created by serdok on 05/03/19.
//

#include "AudioManager.h"

void Implementation::ErrorCheck( FMOD_RESULT result )
{
    if (result != FMOD_OK)
    {
        std::cerr << result << std::endl;
        throw Exception( "FMod Error", __FILE__, __LINE__ );
    }
}

Implementation::Implementation()
{
    Implementation::ErrorCheck( FMOD::Studio::System::create( &mStudioSystem ) );
    Implementation::ErrorCheck( mStudioSystem->initialize( 32, FMOD_STUDIO_INIT_LIVEUPDATE, FMOD_INIT_PROFILE_ENABLE, nullptr ) );

    Implementation::ErrorCheck( mStudioSystem->getLowLevelSystem( &mSystem ) );
}

Implementation::~Implementation()
{
    Implementation::ErrorCheck( mStudioSystem->unloadAll() );
    Implementation::ErrorCheck( mStudioSystem->release() );
}

void Implementation::Update()
{
    std::vector< ChannelCache::iterator > stoppedChannels;
    for (auto channel=mChannels.begin() ; channel != mChannels.end() ; ++channel)
    {
        bool isPlaying = false;
        channel->second->isPlaying( &isPlaying );
        if (!isPlaying)
            stoppedChannels.push_back( channel );
    }

    for (auto& channel : stoppedChannels)
        mChannels.erase( channel );

    Implementation::ErrorCheck( mStudioSystem->update() );
}


Implementation* AudioManager::_implementation = nullptr;
AudioManager* AudioManager::_instance = nullptr;

AudioManager* AudioManager::GetInstance()
{
    if (!_instance)
        _instance = new AudioManager();

    return _instance;
}

void AudioManager::Shutdown()
{
    delete _instance;
}

AudioManager::AudioManager()
{
    if (!_implementation)
        _implementation = new Implementation();
}

AudioManager::~AudioManager()
{
    delete _implementation;
}

void AudioManager::Update()
{
    _implementation->Update();
}

void AudioManager::LoadSound( const std::string& soundFile, bool looping, bool spatial, bool stream )
{
    if (_implementation->mSounds.find( soundFile ) != _implementation->mSounds.end())
        return;

    FMOD_MODE mode = FMOD_DEFAULT;
    mode |= (looping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);
    mode |= (stream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE);
    mode |= (spatial ? FMOD_3D : FMOD_2D);
    FMOD::Sound* sound = nullptr;
    Implementation::ErrorCheck( _implementation->mSystem->createSound( soundFile.c_str(), mode, nullptr, &sound ) );
    if (sound)
        _implementation->mSounds[ soundFile ] = sound;
}

void AudioManager::UnloadSound( const std::string& soundFile )
{
    auto it = _implementation->mSounds.find( soundFile );
    if (it == _implementation->mSounds.end())
        return;

    Implementation::ErrorCheck( it->second->release() );
    _implementation->mSounds.erase( it );
}

int AudioManager::PlaySound( const std::string& soundFile, const Vector3& position, float dB )
{
    int channelID = _implementation->mNextChannelID++;
    auto it = _implementation->mSounds.find( soundFile );
    if (it == _implementation->mSounds.end())
    {
        LoadSound( soundFile );
        it = _implementation->mSounds.find( soundFile );
        if (it == _implementation->mSounds.end())
            return channelID;
    }

    FMOD::Channel* channel = nullptr;
    Implementation::ErrorCheck( _implementation->mSystem->playSound( it->second, nullptr, true, &channel ) );
    if (channel)
    {
        FMOD_MODE mode = FMOD_DEFAULT;
        Implementation::ErrorCheck( it->second->getMode( &mode ) );

        if (mode & FMOD_3D)
        {
            FMOD_VECTOR pos = Vector3ToFmod( position );
            Implementation::ErrorCheck( channel->set3DAttributes( &pos, nullptr ) );
        }

        Implementation::ErrorCheck( channel->setVolume( dBToVolume( dB ) ) );
        Implementation::ErrorCheck( channel->setPaused( false ) );
        _implementation->mChannels[ channelID ] = channel;
    }

    return channelID;
}

void AudioManager::SetChannel3DPosition( int id, const Vector3& position )
{
    auto it = _implementation->mChannels.find( id );
    if (it == _implementation->mChannels.end())
        return;

    FMOD_VECTOR pos = Vector3ToFmod( position );
    Implementation::ErrorCheck( it->second->set3DAttributes( &pos, nullptr ) );
}

void AudioManager::SetChannelVolume( int id, float dB )
{
    auto it = _implementation->mChannels.find( id );
    if (it == _implementation->mChannels.end())
        return;

    Implementation::ErrorCheck( it->second->setVolume( VolumeTodB( dB ) ) );
}

bool AudioManager::IsPlaying( int id ) const
{
    auto it = _implementation->mChannels.find( id );
    if (it == _implementation->mChannels.end())
        return false;

    bool paused;
    Implementation::ErrorCheck( it->second->getPaused( &paused ) );
    return paused;
}

void AudioManager::StopChannel( int id )
{
    auto it = _implementation->mChannels.find( id );
    if (it == _implementation->mChannels.end())
        return;

    Implementation::ErrorCheck( it->second->setPaused( true ) );
}

void AudioManager::StopAllChannels()
{
    for (auto& channel : _implementation->mChannels)
        Implementation::ErrorCheck( channel.second->setPaused( true ) );
}

void AudioManager::LoadBank( const std::string& bankFile, FMOD_STUDIO_LOAD_BANK_FLAGS flags )
{
    auto it = _implementation->mBanks.find( bankFile );
    if (it != _implementation->mBanks.end())
        return;

    FMOD::Studio::Bank* bank = nullptr;
    Implementation::ErrorCheck( _implementation->mStudioSystem->loadBankFile( bankFile.c_str(), flags, &bank ) );
    if (bank)
        _implementation->mBanks[ bankFile ] = bank;
}

void AudioManager::LoadEvent( const std::string& eventName )
{
    auto it = _implementation->mEvents.find( eventName );
    if (it != _implementation->mEvents.end())
        return;

    FMOD::Studio::EventDescription* event = nullptr;
    Implementation::ErrorCheck( _implementation->mStudioSystem->getEvent( eventName.c_str(), &event ) );
    if (event)
    {
        FMOD::Studio::EventInstance* eventInstance = nullptr;
        Implementation::ErrorCheck( event->createInstance( &eventInstance ) );
        if (eventInstance)
            _implementation->mEvents[ eventName ] = eventInstance;
    }
}

void AudioManager::PlayEvent( const std::string& eventName )
{
    auto it = _implementation->mEvents.find( eventName );
    if (it == _implementation->mEvents.end())
    {
        LoadEvent( eventName );
        it = _implementation->mEvents.find( eventName );
        if (it == _implementation->mEvents.end())
            return;
    }

    Implementation::ErrorCheck( it->second->start() );
}

void AudioManager::StopEvent( const std::string& eventName, bool immediate )
{
    auto it = _implementation->mEvents.find( eventName );
    if (it == _implementation->mEvents.end())
        return;

    FMOD_STUDIO_STOP_MODE mode;
    mode = (immediate ? FMOD_STUDIO_STOP_IMMEDIATE : FMOD_STUDIO_STOP_ALLOWFADEOUT);

    Implementation::ErrorCheck( it->second->stop( mode ) );
}

bool AudioManager::IsEventPlaying( const std::string& eventName ) const
{
    auto it = _implementation->mEvents.find( eventName );
    if (it == _implementation->mEvents.end())
        return false;

    FMOD_STUDIO_PLAYBACK_STATE state;
    Implementation::ErrorCheck( it->second->getPlaybackState( &state ) );
    return state == FMOD_STUDIO_PLAYBACK_PLAYING;
}

void AudioManager::GetEventParameter( const std::string& eventName, const std::string& parameterName, float* value )
{
    auto it = _implementation->mEvents.find( eventName );
    if (it == _implementation->mEvents.end())
        return;

    FMOD::Studio::ParameterInstance* parameter = nullptr;
    Implementation::ErrorCheck( it->second->getParameter( eventName.c_str(), &parameter ) );
    Implementation::ErrorCheck( parameter->getValue( value ) );
}

void AudioManager::SetEventParameter( const std::string& eventName, const std::string& parameterName, float value )
{
    auto it = _implementation->mEvents.find( eventName );
    if (it == _implementation->mEvents.end())
        return;

    FMOD::Studio::ParameterInstance* parameter = nullptr;
    Implementation::ErrorCheck( it->second->getParameter( eventName.c_str(), &parameter ) );
    Implementation::ErrorCheck( parameter->setValue( value ) );
}

FMOD_VECTOR AudioManager::Vector3ToFmod( const Vector3& v )
{
    FMOD_VECTOR f;
    f.x = v.x;
    f.y = v.y;
    f.z = v.z;
    return f;
}

float AudioManager::VolumeTodB( float volume )
{
    return 20.0f*std::log10( volume );
}

float AudioManager::dBToVolume( float dB )
{
    return std::pow( 10.0f, 0.05f*dB );
}
