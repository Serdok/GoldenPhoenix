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
    _keyboardState = SDL_GetKeyboardState( &_keyboardLength );
    _previousKeyboardState = new Uint8[ _keyboardLength ];
    memcpy( _previousKeyboardState, _keyboardState, (size_t) _keyboardLength );
}

InputsManager::~InputsManager()
{
    delete [] _previousKeyboardState;
}

bool InputsManager::KeyDown( SDL_Scancode key )
{
    return _keyboardState[ key ];
}

bool InputsManager::KeyPressed( SDL_Scancode key )
{
    return _keyboardState[ key ] && !_previousKeyboardState[ key ];
}

bool InputsManager::KeyReleased( SDL_Scancode key )
{
    return !_keyboardState[ key ] && _previousKeyboardState[ key ];
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
    return (bool) (_mouseState & GetMask( button ));
}

bool InputsManager::MouseButtonPressed( InputsManager::MOUSE_BUTTON button )
{
    return (bool) (_mouseState & GetMask( button ) && !(_previousMouseState & GetMask( button )));
}

bool InputsManager::MouseButtonReleased( InputsManager::MOUSE_BUTTON button )
{
    return (bool) (!(_mouseState & GetMask( button )) && _previousMouseState & GetMask( button ));
}

Vector2i InputsManager::GetMousePosition()
{
    return Vector2i( _mouseXPosition, _mouseYPosition );
}

void InputsManager::Update()
{
    _mouseState = SDL_GetMouseState( &_mouseXPosition, &_mouseYPosition );
}

void InputsManager::UpdatePreviousInput()
{
    memcpy( _previousKeyboardState, _keyboardState, (size_t) _keyboardLength );
    _previousMouseState = _mouseState;
}