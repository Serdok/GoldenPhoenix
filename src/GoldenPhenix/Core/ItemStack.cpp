//
// Created by serdok on 05/03/19.
//

#include "ItemStack.h"

ItemStack::ItemStack( const Object& object, int amount, int durability ) : _object( &object ), _stack( amount )
{
    if (durability < 0)
        _durability = _object->maxDurability;
    else
        _durability = durability;
}

bool ItemStack::operator ==( const ItemStack& i ) const
{
    return ( this->_object->GetID() == i.GetObject().GetID()) && ( this->_stack == i.GetAmount()) &&
           ( this->_durability == i.GetDurability());
}

bool ItemStack::operator !=( const ItemStack& i ) const
{
    return !(*this == i);
}

int ItemStack::Add( unsigned int amount )
{
    _stack += amount;
    if (_stack > _object->maxStackSize)
    {
        int extra = _stack - _object->maxStackSize;
        _stack = _object->maxStackSize;
        return extra;
    }
    else
        return 0;
}

void ItemStack::Remove( unsigned int amount )
{
    _stack -= amount;
    if (_stack <= 0)
    {
        _object = &Object::ToObject( ObjectID::Nothing );
        _stack = 0;
    }
}

int ItemStack::GetAmount() const
{
    return _stack;
}

const Object& ItemStack::GetObject() const
{
    return *_object;
}

void ItemStack::Use( unsigned int amount )
{
    _durability -= amount;
    if (_durability <= 0)
        Remove( 1 );
}

int ItemStack::GetDurability() const
{
    return _durability;
}