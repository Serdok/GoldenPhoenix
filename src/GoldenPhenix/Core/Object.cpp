//
// Created by serdok on 05/03/19.
//

#include "Object.h"

Object::Object( Object::ID _id, unsigned int _maxStack, unsigned int _maxDurability, std::string&& _name )
: id( _id ), maxStackSize( _maxStack ), maxDurability( _maxDurability ), name( std::move( _name ) )
{

}

Object::Object( const Object& o )
: id( o.id ), maxStackSize( o.maxStackSize ), maxDurability( o.maxDurability ), name( o.name )
{

}

const ObjectID Object::GetID() const
{
    switch (id)
    {
        case Nothing:return ObjectID::Nothing;
        case Egg:return ObjectID::Egg;
        case Crowbar:return ObjectID::Crowbar;
        case IronKey:return ObjectID::IronKey;
        case GoldKey:return ObjectID::GoldKey;
        case GrapplingHook:return ObjectID::GrapplingHook;
        case Torch:return ObjectID::Torch;
        case LifePotion:return ObjectID::LifePotion;
        case Hint1:return ObjectID::Hint1;
        case Hint2:return ObjectID::Hint2;
        case Hint3:return ObjectID::Hint3;
        case CursedRing:return ObjectID::CursedRing;
        default:return ObjectID::TOTAL;
    }
}

const Object& Object::ToObject( ObjectID id )
{
    switch (id)
    {
        case ObjectID::Egg:
            static const Object egg( ID::Egg, 1, 0, "Egg" );
            return egg;
        case ObjectID::Crowbar:
            static const Object crowbar( ID::Crowbar, 99, 25, "Crowbar" );
            return crowbar;
        case ObjectID::IronKey:
            static const Object ironKey( ID::IronKey, 1, 999, "Iron Key" );
            return ironKey;
        case ObjectID::GoldKey:
            static const Object goldKey( ID::GoldKey, 1, 999, "Gold Key" );
            return goldKey;
        case ObjectID::GrapplingHook:
            static const Object grapplingHook( ID::GrapplingHook, 99, 1, "Grappling Hook" );
            return grapplingHook;
        case ObjectID::Torch:
            static const Object torch( ID::Torch, 99, 5, "Torch" );
            return torch;
        case ObjectID::LifePotion:
            static const Object lifePotion( ID::LifePotion, 99, 1, "Life Potion" );
            return lifePotion;
        case ObjectID::Hint1:
            static const Object hint1( ID::Hint1, 99, 1, "Hint #1" );
            return hint1;
        case ObjectID::Hint2:
            static const Object hint2( ID::Hint2, 99, 1, "Hint #2" );
            return hint2;
        case ObjectID::Hint3:
            static const Object hint3( ID::Hint3, 99, 1, "Hint #3" );
            return hint3;
        case ObjectID::CursedRing:
            static const Object cursedRing( ID::CursedRing, 99, 1, "Cursed Ring" );
            return cursedRing;
        case ObjectID::Nothing:
        default:
            static const Object nothing( ID::Nothing, 1, 1, " " );
            return nothing;
    }
}