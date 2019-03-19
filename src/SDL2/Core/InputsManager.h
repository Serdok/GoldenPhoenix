//
// Created by serdok on 19/03/19.
//

#ifndef GOLDEN_PHOENIX_INPUTSMANAGER_H
#define GOLDEN_PHOENIX_INPUTSMANAGER_H

// Custom headers
#include "Vector2.h"

// SDL2 headers
#include <SDL2/SDL.h>


// C++ headers



class InputsManager
{
public:
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

    const Uint8* mKeyboardState;
    Uint8* mPreviousKeyboardState;
    int mKeyboardLength;

    Uint32 mMouseState;
    Uint32 mPreviousMouseState;

    int mMouseXPosition, mMouseYPosition;


public:
    static InputsManager* GetInstance();
    static void Release();

    bool KeyDown( SDL_Scancode key );
    bool KeyPressed( SDL_Scancode key );
    bool KeyReleased( SDL_Scancode key );

    bool MouseButtonDown( MOUSE_BUTTON button );
    bool MouseButtonPressed( MOUSE_BUTTON button );
    bool MouseButtonReleased( MOUSE_BUTTON button );

    Vector2i GetMousePosition();

    void Update();
    void UpdatePreviousInput();

private:
    InputsManager();
    ~InputsManager();

    Uint32 GetMask( MOUSE_BUTTON button );
};

#endif //GOLDEN_PHOENIX_INPUTSMANAGER_H
