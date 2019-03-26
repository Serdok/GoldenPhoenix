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

InputsManager::InputsManager() = default;

InputsManager::~InputsManager() = default;

bool InputsManager::KeyPressed( SDL_Scancode key )
{
    if (_locked) return false;

    int k = (int) key;
    if (0 > k || k >= 282) return false;

    return _keyPressed[ k ];
}

bool InputsManager::KeyReleased( SDL_Scancode key )
{
    if (_locked) return false;

    int k = (int) key;
    if (0 > k || k >= 282) return false;

    return _keyReleased[ k ];
}

bool InputsManager::KeyHeld( SDL_Scancode key )
{
    if (_locked) return false;
    if (!_keyboard) return false;

    int k = (int) key;
    if (_keyboard[ k ]) return true;
    return false;
}

void InputsManager::Update( SDL_Event* e )
{
    for (int i = 0 ; i < MAX_KEYS ; ++i)
    {
        _keyPressed[ i ] = false;
        _keyReleased[ i ] = false;
    }

    switch (e->type)
    {
        case SDL_KEYDOWN:_keyboard = SDL_GetKeyboardState( nullptr );
            _keyPressed[ (int) e->key.keysym.scancode ] = true;
            break;
        case SDL_KEYUP:_keyboard = SDL_GetKeyboardState( nullptr );
            _keyReleased[ (int) e->key.keysym.scancode ] = true;
            break;
        default: break;
    }
}

void InputsManager::LockInputs()
{
    _locked = true;
}

void InputsManager::UnlockInputs()
{
    _locked = false;
}

bool InputsManager::Shift()
{
    return sInstance->KeyHeld( SDL_SCANCODE_LSHIFT ) || sInstance->KeyHeld( SDL_SCANCODE_RSHIFT );
}

bool InputsManager::Ctrl()
{
    return sInstance->KeyHeld( SDL_SCANCODE_LCTRL ) || sInstance->KeyHeld( SDL_SCANCODE_RCTRL );
}

bool InputsManager::Alt()
{
    return sInstance->KeyHeld( SDL_SCANCODE_LALT ) || sInstance->KeyHeld( SDL_SCANCODE_RALT );
}