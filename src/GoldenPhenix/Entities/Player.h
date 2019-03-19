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
    uint8_t _heldItem;
    int _money;


    bool _grounded;
    bool _crouched;


public:
    //! Create a player and attach a room to it. (The room here is equivalent to the terrain)
    explicit Player( Room* currentRoom );

    ~Player() override;

    //! Process actions
    void ProcessActions( const std::string& action );

    //! Update the player.
    void Update() final;

    //! Add an item to the player's inventory.
    void AddItem( const Object& object );

    //! Remove an item from the player's inventory
    void RemoveItem( const Object& object );

    //! Return the currently held item
    const ItemStack& GetHeldItem() const;

    //! Return the currently held item
    ItemStack& GetHeldItem();

    //! Return true if the player is crouched, false otherwise
    bool Crouched() const;

    //! Return true if the player is on the ground, false otherwise
    bool Grounded() const;

    //! Return the current room the player is in
    Room* GetCurrentRoom() const;

    void setCurrentRoom(Room * room);

    int getMoney();

    void setMoney( int m );

    void clearItems();
};


#endif //GOLDEN_PHOENIX_PLAYER_H
