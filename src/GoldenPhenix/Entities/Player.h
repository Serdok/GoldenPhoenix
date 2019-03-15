//
// Created by serdok on 05/03/19.
//

#ifndef GOLDEN_PHOENIX_PLAYER_H
#define GOLDEN_PHOENIX_PLAYER_H

// Custom headers
#include "ItemStack.h"
#include "Entity.h"

// C++ headers
#include <vector>


class Room;

class Player : public Entity
{
private:
    Room* _currentRoom;

    std::vector< ItemStack > _items;
    int _heldItem;
    bool _grounded;
    bool _crouched;


public:
    explicit Player( Room* currentRoom );

    void Update();

    void AddItem( const Object& object );

    ItemStack& GetHeldItems();

    bool Crouched() const;

    bool Grounded() const;

    void Jump();

    void LongJump();

    Room* GetCurrentRoom() const;
};


#endif //GOLDEN_PHOENIX_PLAYER_H
