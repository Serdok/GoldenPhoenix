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
    //! List of the supported mouse buttons
    enum MOUSE_BUTTON
    {
        left = 0,     ///< Left click
        right,        ///< Right click
        middle,       ///< Middle click
        back,         ///< Back click (mice with 5+ buttons only)
        forward       ///< Forward click (mice with 5+ buttons only)
    };

private:
    static InputsManager* sInstance;

    const Uint8* _keyboardState;
    Uint8* _previousKeyboardState;
    int _keyboardLength;

    Uint32 _mouseState;
    Uint32 _previousMouseState;

    int _mouseXPosition, _mouseYPosition;


public:
    //! Get the instance of the class
    static InputsManager* GetInstance();
    //! Release the instance of the class
    static void Release();

    /**
     * Return true while the key is pressed. See example code down below
     * @code{.cpp}
     * // Output a message while the space bar is down
     *  Inputs* inputsMgr = Inputs::GetInstance();
     *  if (inputsMgr->KeyDown( SDL_SCANCODE_SPACE )
     *      std::cout << "Space key down!\n";
     * @endcode
     *
     * The list of all keys and their corresponding scancode is available at https://wiki.libsdl.org/SDL_Scancode
     * @param key The SDL2 Scancode of the key
     * @return true while the key is pressed
     */
    bool KeyDown( SDL_Scancode key );

    /**
     * Return true the first frame the key is pressed. See example code down below
     * @code{.cpp}
     * // Output the message ONCE
     *  Inputs* inputsMgr = Inputs::GetInstance();
     *  if (inputsMgr->KeyPressed( SDL_SCANCODE_SPACE )
     *      std::cout << "Space key pressed!\n";
     * @endcode
     *
     * The list of all keys and their corresponding scancode is available at https://wiki.libsdl.org/SDL_Scancode
     * @param key The SDL2 Scancode of the key
     * @return true the first frame the key is pressed
     */
    bool KeyPressed( SDL_Scancode key );

    /**
     * Return true the first frame the key is released. See example code down below
     * @code{.cpp}
     * // Output the message ONCE
     *  Inputs* inputsMgr = Inputs::GetInstance();
     *  if (inputsMgr->KeyReleased( SDL_SCANCODE_SPACE )
     *      std::cout << "Space key released!\n";
     * @endcode
     *
     * The list of all keys and their corresponding scancode is available at https://wiki.libsdl.org/SDL_Scancode
     * @param key The SDL2 Scancode of the key
     * @return true the first frame the key is released
     */
    bool KeyReleased( SDL_Scancode key );

    /**
     * Return true while the mouse button is pressed
     * @param button A mouse button
     * @return true while the mouse button is pressed
     * @see KeyDown
     */
    bool MouseButtonDown( MOUSE_BUTTON button );

    /**
     * Return true the first frame the mouse button is pressed
     * @param button A mouse button
     * @return true the first frame the mouse button is pressed
     * @see KeyPressed
     */
    bool MouseButtonPressed( MOUSE_BUTTON button );

    /**
     * Return true the first frame the mouse button is released
     * @param button A mouse button
     * @return true the first frame the mouse button is released
     * @see KeyReleased
     */
    bool MouseButtonReleased( MOUSE_BUTTON button );

    //! Return the current mouse position in a vector
    Vector2i GetMousePosition();

    //! Update the mouse position
    void Update();

    //! Update the keyboard and mouse states
    void UpdatePreviousInput();

private:
    InputsManager();
    ~InputsManager();

    //! Return the mask from a mouse button
    Uint32 GetMask( MOUSE_BUTTON button );
};

#endif //GOLDEN_PHOENIX_INPUTSMANAGER_H
