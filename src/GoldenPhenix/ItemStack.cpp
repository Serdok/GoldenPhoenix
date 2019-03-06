//
// Created by serdok on 05/03/19.
//

#include "ItemStack.h"

ItemStack::ItemStack( const Object& object, int amount ) : _object( &object ), _stack( amount )
{

}

int ItemStack::Add( int amount )
{
    _stack += amount;
    if (_stack > _object->maxStackSize)
    {
        int remaining = _stack - _object->maxStackSize;
        _stack = _object->maxStackSize;
        return remaining;
    }
    else
        return 0;
}

void ItemStack::Remove()
{
    --_stack;
    if (_stack == 0)
        _object = &Object::NOTHING;
}

int ItemStack::GetAmount() const
{
    return _stack;
}

const Object& ItemStack::GetObject() const
{
    return *_object;
}