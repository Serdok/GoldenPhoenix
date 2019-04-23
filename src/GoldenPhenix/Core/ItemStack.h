//
// Created by serdok on 05/03/19.
//

#ifndef GOLDEN_PHOENIX_ITEMSTACK_H
#define GOLDEN_PHOENIX_ITEMSTACK_H

// Custom headers
#include "Object.h"


//! Class holding information about an object and its actual properties such as quantity and durability
class ItemStack
{
private:
    const Object* _object;
    int _stack;
    int _durability;


public:
    //! Allocate an object with a given amount and durability. If the durability is < 0, the maximum durability of the object is used
    ItemStack( const Object& object, int amount, int durability = -1 );

    //! Compare two ItemStack. Return true if all values are equal
    bool operator ==( const ItemStack& i ) const;

    //! Compare two ItemStack. Return true if at least one value is different
    bool operator !=( const ItemStack& i ) const;

    //! Add x objects to the stack. Adds nothing if the maximum amount is hit. Return the extra items added if the stack was full
    int Add( unsigned int amount );

    //! Remove x objects from the stack. Replace the object with NOTHING if the amount is null
    void Remove( unsigned int amount );

    //! Use x times the object. Removes the object if the durability is exhausted.
    void Use( unsigned int amount );

    //! Get the current amount of the object
    int GetAmount() const;

    //! Get the object of this stack
    const Object& GetObject() const;

    //! Get the durability of the item
    int GetDurability() const;
};


#endif //GOLDEN_PHOENIX_ITEMSTACK_H
