//
// Created by serdok on 05/03/19.
//

#ifndef GOLDEN_PHOENIX_ITEMSTACK_H
#define GOLDEN_PHOENIX_ITEMSTACK_H

// Custom headers
#include "Object.h"


//! Class holding information about an object and its amount
class ItemStack
{
private:
    const Object* _object;
    int _stack;

public:
    //! Allocate an object with a given amount
    ItemStack( const Object& object, int amount );

    //! Add x objects to the stack. Adds nothing if the maximum amount is hit
    int Add( unsigned int amount );

    //! Remove x objets from the stack. Replace the object with NOTHING if the amount is null
    void Remove( unsigned int amount );

    //! Get the current amount of the object
    int GetAmount() const;

    //! Get the object of this stack
    const Object& GetObject() const;
};


#endif //GOLDEN_PHOENIX_ITEMSTACK_H