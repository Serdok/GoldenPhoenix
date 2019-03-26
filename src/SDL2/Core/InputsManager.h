//
// Created by serdok on 19/03/19.
//

#ifndef GOLDEN_PHOENIX_INPUTSMANAGER_H
#define GOLDEN_PHOENIX_INPUTSMANAGER_H

// Custom headers
#include "Vector2.h"

// SDL2 headers
#include "SDL.h"


//! Class storing keyboard and mouse events for simpler processing
class InputsManager
{
public:


private:
    static InputsManager* sInstance;
    static const int MAX_KEYS = 282;

    const Uint8* _keyboard = nullptr;
    bool _keyPressed[ MAX_KEYS ];
    bool _keyReleased[ MAX_KEYS ];

    bool _locked = false;


public:
    //! Get the instance of the class
    static InputsManager* GetInstance();
    //! Release the instance of the class
    static void Release();

    /**
     * Updates the game inputs state
     *
     * @note This function should be called every frame to properly update inputs. Except undefined behaviour otherwise
     */
    void Update( SDL_Event* e );

    //! Return true if the key was pressed right now
    bool KeyPressed( SDL_Scancode key );

    //! Return true if the key was released right now
    bool KeyReleased( SDL_Scancode key );

    //! Return true if the key is currently being held
    bool KeyHeld( SDL_Scancode key );

    //! Helper function - Return true if any shift key is held
    bool Shift();

    //! Helper function - Return true if any control key is held
    bool Ctrl();

    //! Helper function - Return true if any alt key is held
    bool Alt();

    /**
     * Lock the inputs manager, preventing it to update inputs. Useful for cutscenes, dialog, ...
     *
     * @note Make sure that for every LockInputs() call there is a UnlockInputs() call. Except undefined behaviour otherwise
     */
    void LockInputs();

    //! Unlock the inputs manager, allowing it to update inputs again
    void UnlockInputs();

    //! Removing copy constructor
    InputsManager( const InputsManager& ) = delete;

    //! Removing assignment operator
    InputsManager& operator =( const InputsManager& ) = delete;
private:
    InputsManager();
    ~InputsManager();
};

#endif //GOLDEN_PHOENIX_INPUTSMANAGER_H
