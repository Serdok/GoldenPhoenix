//
// Created by serdok on 19/03/19.
//

#include "InputsManager.h"

InputsManager* InputsManager::sInstance = nullptr;

InputsManager* InputsManager::GetInstance()
{
    if (!sInstance)
        sInstance = new InputsManager();
    return sInstance;
}

void InputsManager::Release()
{
    delete sInstance;
}

InputsManager::InputsManager()
{
    mKeyboardState = SDL_GetKeyboardState( &mKeyboardLength );
    mPreviousKeyboardState = new Uint8[ mKeyboardLength ];
    memcpy( mPreviousKeyboardState, mKeyboardState, (size_t) mKeyboardLength );
}

InputsManager::~InputsManager()
{
    delete [] mPreviousKeyboardState;
}

bool InputsManager::KeyDown( SDL_Scancode key )
{
    return mKeyboardState[ key ];
}

bool InputsManager::KeyPressed( SDL_Scancode key )
{
    return mKeyboardState[ key ] && !mPreviousKeyboardState[ key ];
}

bool InputsManager::KeyReleased( SDL_Scancode key )
{
    return !mKeyboardState[ key ] && mPreviousKeyboardState[ key ];
}

Uint32 InputsManager::GetMask( InputsManager::MOUSE_BUTTON button )
{
    switch (button)
    {
        case left:
            return SDL_BUTTON_LMASK;
        case right:
            return SDL_BUTTON_RMASK;
        case middle:
            return SDL_BUTTON_MMASK;
        case back:
            return SDL_BUTTON_X1MASK;
        case forward:
            return SDL_BUTTON_X2MASK;
        default:
            return (Uint32) 0;
    }
}

bool InputsManager::MouseButtonDown( InputsManager::MOUSE_BUTTON button )
{
    return (bool) (mMouseState & GetMask( button ));
}

bool InputsManager::MouseButtonPressed( InputsManager::MOUSE_BUTTON button )
{
    return (bool) (mMouseState & GetMask( button ) && !(mPreviousMouseState & GetMask( button )));
}

bool InputsManager::MouseButtonReleased( InputsManager::MOUSE_BUTTON button )
{
    return (bool) (!(mMouseState & GetMask( button )) && mPreviousMouseState & GetMask( button ));
}

Vector2i InputsManager::GetMousePosition()
{
    return Vector2i( mMouseXPosition, mMouseYPosition );
}

void InputsManager::Update()
{
    mMouseState = SDL_GetMouseState( &mMouseXPosition, &mMouseYPosition );
}

void InputsManager::UpdatePreviousInput()
{
    memcpy( mPreviousKeyboardState, mKeyboardState, (size_t) mKeyboardLength );
    mPreviousMouseState = mMouseState;
}