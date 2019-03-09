//
// Created by serdok on 05/03/19.
//

#ifndef GOLDEN_PHOENIX_PLAYER_H
#define GOLDEN_PHOENIX_PLAYER_H

// Custom headers
#include "ItemStack.h"
#include "Entity.h"

// SDL2 headers
#include "SDL.h"

// C++ headers
#include <vector>


class Room;

class Player : public Entity
{
private:
    Room* _currentRoom;

    std::vector< ItemStack > _items;
    int _heldItem;
    bool _isOnGround;


public:
    Player( Room* currentRoom );

    void ProcessEvents( SDL_Event* event );

    void Update();

    void Render();

    void AddItem( const Object& object );

    ItemStack& GetHeldItems();

private:
    void Jump();

    void LongJump();
};


#endif //GOLDEN_PHOENIX_PLAYER_H
