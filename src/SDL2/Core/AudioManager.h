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
     * Sounds must be located in data/sounds.
     * @param [in] soundfile Name of the sound to load
     * @param [in] spatial If the souns will support 3D (default : false)
     * @param [in] loops The number of times the sound should play (default : once). Use any number <= 0 for infinite loops
     * @return A pointer to the sound loaded
     * @exception Exception if the file cannot be located in the directory.
     */
    FMOD::Sound* LoadSound( const std::string& soundfile, bool spatial = false, int loops = 1 );

    //! Play a sound previously loaded.
    void PlaySound( FMOD::Sound* sound );

    //! Free a sound previously loaded.
    void FreeSound( FMOD::Sound* sound );


    /**
     * Load a music from a file.
     * Musics must be located in data/musics
     * @param [in] musicfile Name of the music to load
     * @param [in] spatial If the music will support 3D (default : false)
     * @param [in] loops The number of times the music should play (default : infinite).
     * @return A pointer to the music loaded
     * @exception Exception if the file cannot be located in this directory.
     */
    FMOD::Sound* LoadMusic( const std::string& musicfile, bool spatial = false, int loops = 0 );

    //! Play a music previously loaded.
    void PlayMusic( FMOD::Sound* music );

    //! Free a music previously loaded.
    void FreeMusic( FMOD::Sound* music );

    //! Update the sound engine
    void Update();

private:
    //! Initialize FMOD
    AudioManager();
    //! Shutdown FMOD
    ~AudioManager();

    /** FMod error checking.
     * @param status A FMOD library return value
     * @exception Exception if the status is not ok
     */
    static void ErrorCheck( const FMOD_RESULT& status );
};


#endif //GOLDEN_PHOENIX_AUDIOENGINE_H
