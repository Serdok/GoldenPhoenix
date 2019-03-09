//
// Created by serdok on 05/03/19.
//

#include "Player.h"

Player::Player( Room* currentRoom ) : Entity(), _currentRoom( currentRoom )
{
    for (int i = 0 ; i < 4 ; ++i)
        _items.emplace_back( Object::NOTHING, 0 );
}

void Player::AddItem( const Object& object )
{
    Object::ID id = object.id;
    for (auto& obj : _items)
        if (obj.GetObject().id == id)
        {
            obj.Add( 1 );
            return;
        }
        else if (obj.GetObject().id == Object::ID::Nothing)
        {
            obj = { object, 1 };
            return;
        }
}

ItemStack& Player::GetHeldItems()
{
    return _items.at((unsigned long) _heldItem );
}

void Player::ProcessEvents( SDL_Event* event )
{
    if (event->type == SDL_KEYDOWN)
        switch (event->key.keysym.scancode)
        {
            case SDL_SCANCODE_W:_position += VEC2_UP;
                break;
            case SDL_SCANCODE_S:_position += VEC2_DOWN;
                break;
            case SDL_SCANCODE_D:_position += VEC2_RIGHT;
                break;
            case SDL_SCANCODE_A:_position += VEC2_LEFT;
                break;
            case SDL_SCANCODE_0:_heldItem = 0;
                break;
            case SDL_SCANCODE_1:_heldItem = 1;
                break;
            case SDL_SCANCODE_2:_heldItem = 2;
                break;
            case SDL_SCANCODE_3:_heldItem = 3;
                break;
            case SDL_SCANCODE_4:_heldItem = 4;
                break;
            default:break;
        }
}

void Player::Update()
{
    std::cout << _position << std::endl;

    if (_position.x < 0)
        _position.x = 0;
    if (_position.y < 0)
        _position.y = 0;
    if (_position.x > 6)
        _position.x = 6;
    if (_position.y > 5)
        _position.y = 5;

}

void Player::Render()
{

}

void Player::Jump()
{
    if (_isOnGround)
    {
        _isOnGround = false;
        _position += VEC2_UP;
    }
}

void Player::LongJump()
{

}