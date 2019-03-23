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
        left = 0,
        right,
        middle,
        back,
        forward
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
    static InputsManager* GetInstance();
    static void Release();

    /**
     * Return true while the key is pressed
     * @param key The SDL2 Scancode of the key
     * @return
     */
    bool KeyDown( SDL_Scancode key );

    /**
     * Return true the first frame the key is pressed
     * @param key The SDL2 Scancode of the key
     * @return
     */
    bool KeyPressed( SDL_Scancode key );

    /**
     * Return true if the key was not pressed
     * @param key The SDL2 Scancode of the key
     * @return
     */
    bool KeyReleased( SDL_Scancode key );

    /**
     * Return true while the mouse button is pressed
     * @param button A mouse button
     * @return
     */
    bool MouseButtonDown( MOUSE_BUTTON button );

    /**
     * Return true the first frame the mouse button is pressed
     * @param button A mouse button
     * @return
     */
    bool MouseButtonPressed( MOUSE_BUTTON button );

    /**
     * Return true if the mouse button was not pressed
     * @param button A mouse button
     * @return
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
