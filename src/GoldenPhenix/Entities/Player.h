//
// Created by serdok on 05/03/19.
//

#ifndef GOLDEN_PHOENIX_PLAYER_H
#define GOLDEN_PHOENIX_PLAYER_H

// Custom headers
#include "ItemStack.h"
#include "Entity.h"
#include "Room.h"

// C++ headers
#include <algorithm>
#include <vector>


//! Class representing a player in the game
class Player : public Entity
{
private:
    Room* _currentRoom;

    std::vector< ItemStack > _items;
    int _heldItem = 0;

    int _money = 400;

    bool _grounded = true;
    bool _crouched = false;

    unsigned int _deaths = 0;

    bool _isTorchLit = false;

public:
    //! Create a player and attach a room to it. (The room here is equivalent to the terrain)
    explicit Player( Room* currentRoom );

    //! Free resources
    ~Player() override;

    //! Process actions
    void ProcessActions( const std::string& action );

    //! Update the player.
    void Update() final;

    //! Add an item to the player's inventory.
    void AddItem( const Object& object );

    //! Remove an item from the player's inventory
    void RemoveItem( const Object& object );

    /**
     * Get the currently held item
     * @return A constant ItemStack
     * @exception std::out_of_range if the index is out of bounds
     */
    const ItemStack& GetHeldItem() const;

    /**
     * Get the currently held item
     * @return A reference to ItemStack
     * @exception std::out_of_range if the index is out of bounds
     */
    ItemStack& GetHeldItem();

    void SetHeldItem( int index );

    void DeselectItem();

    bool HasObject( const Object& o ) const;

    int GetObjectPositionFromInventory( const Object& o ) const;

    //! Return the list of items
    const std::vector< ItemStack >& GetItems() const;

    //! Return true if the player is crouched, false otherwise
    bool Crouched() const;

    //! Return true if the player is on the ground, false otherwise
    bool Grounded() const;

    bool TorchLit() const;

    //! Return the current room the player is in
    const Room* const GetCurrentRoom() const;

    //! Return the current room the player is in
    Room* const GetCurrentRoom();

    //! Set the player in a specific room
    void SetCurrentRoom( Room* room );

    //! Return the money of the player
    int GetMoney();

    //! Add money to the player
    void AddMoney( int m );

    //! Set the money of the player
    void SetMoney( int m );

    //! Clear inventory
    void EmptyInventory();

    //! Kill the player
    void Kill();

    //! Get the number of time the player died
    unsigned int GetDeaths() const;

private:
    void ActivateTorch();
};


#endif //GOLDEN_PHOENIX_PLAYER_H
