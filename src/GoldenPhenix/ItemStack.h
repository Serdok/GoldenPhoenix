//
// Created by serdok on 05/03/19.
//

#ifndef GOLDEN_PHOENIX_ITEMSTACK_H
#define GOLDEN_PHOENIX_ITEMSTACK_H

// Custom headers
#include "Object.h"


class ItemStack
{
private:
    const Object* _object;
    int _stack;

public:
    ItemStack( const Object& object, int amount );

    int Add( int amount );

    void Remove();

    int GetAmount() const;

    const Object& GetObject() const;
};


#endif //GOLDEN_PHOENIX_ITEMSTACK_H
