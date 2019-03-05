//
// Created by serdok on 05/03/19.
//

#ifndef GOLDEN_PHOENIX_AUDIOENGINE_H
#define GOLDEN_PHOENIX_AUDIOENGINE_H

// Custom headers
#include "GetResourcePath.h"
#include "Exceptions.h"

// FMod headers
#include "fmod.hpp"
#include "fmod_errors.h"

// C++ headers



//! Singleton class managing all audio in the game
class AudioManager
{
private:
    static AudioManager* sInstance; ///< Holder for the singleton

    FMOD::System* _system; ///< Variable holding FMod system information


public:
    //! Return the instance of the class
    static AudioManager* GetInstance();
    //! Release the instance of the class
    static void Shutdown();

    /**
     * Load a sound from a file.
     * Sounds must be located in data/sounds. Throws an Exception if the file cannot be located in this directory.
     * @param soundfile [in] Name of the sound to load
     * @param spatial [in] If the souns will support 3D (default : false)
     * @return A pointer to the sound loaded
     */
    FMOD::Sound* LoadSound( const std::string& soundfile, bool spatial = false );

    //! Play a sound previously loaded.
    void PlaySound( FMOD::Sound* sound );

    //! Free a sound previously loaded.
    void FreeSound( FMOD::Sound* sound );


    /**
     * Load a music from a file.
     * Musics must be located in data/musics. Throws an Exception if the file cannot be located in this directory.
     * @param musicfile [in] Name of the music to load
     * @param spatial [in] If the music will support 3D (default : false)
     * @return A pointer to the music loaded
     */
    FMOD::Sound* LoadMusic( const std::string& musicfile, bool spatial = false );

    //! Play a music previously loaded.
    void PlayMusic( FMOD::Sound* music );

    //! Free a music previously loaded.
    void FreeMusic( FMOD::Sound* music );

private:
    //! Constructor made private since the class is a singleton
    AudioManager();
    //! Destructor made private since the class is a singleton
    ~AudioManager();

    //! FMod error checking. Throws an Exception on error
    static void ErrorCheck( const FMOD_RESULT& status );
};


#endif //GOLDEN_PHOENIX_AUDIOENGINE_H
