//
// Created by serdok on 05/03/19.
//

#include "Object.h"

Object::Object( Object::ID id, int maxStack, int maxDurability, std::string&& name )
:id( id ), maxStackSize( maxStack ), durability( maxDurability ), name( std::move( name ))
{

}

ObjectID Object::ToObjectID() const
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

std::string Object::ToString() const
{
    switch (id)
    {
        case Egg:return "Egg";
        case Crowbar:return "Crowbar";
        case IronKey:return "Iron Key";
        case GoldKey:return "Gold Key";
        case GrapplingHook:return "Grappling Hook";
        case Torch:return "Torch";
        case LifePotion:return "Life Potion";
        case Hint1:return "Hint 1";
        case Hint2:return "Hint 2";
        case Hint3:return "Hint 3";
        case CursedRing:return "Cursed Ring";
        case Nothing:
        default:return " ";
    }
}

const Object Object::ToObject( ObjectID id )
{
    switch (id)
    {
        case ObjectID::Egg:return EGG();
        case ObjectID::Crowbar:return CROWBAR();
        case ObjectID::IronKey:return IRON_KEY();
        case ObjectID::GoldKey:return GOLD_KEY();
        case ObjectID::GrapplingHook:return GRAPPLING_HOOK();
        case ObjectID::Torch:return TORCH();
        case ObjectID::LifePotion:return LIFE_POTION();
        case ObjectID::Hint1:return HINT1();
        case ObjectID::Hint2:return HINT2();
        case ObjectID::Hint3:return HINT3();
        case ObjectID::CursedRing:return CURSED_RING();
        case ObjectID::Nothing:
        default:return NOTHING();
    }
}

std::string Object::ToString( ObjectID id )
{
    switch (id)
    {
        case ObjectID::Egg:return "Egg";
        case ObjectID::Crowbar:return "Crowbar";
        case ObjectID::IronKey:return "Iron Key";
        case ObjectID::GoldKey:return "Gold Key";
        case ObjectID::GrapplingHook:return "Grappling Hook";
        case ObjectID::Torch:return "Torch";
        case ObjectID::LifePotion:return "Life Potion";
        case ObjectID::Hint1:return "Hint 1";
        case ObjectID::Hint2:return "Hint 2";
        case ObjectID::Hint3:return "Hint 3";
        case ObjectID::CursedRing:return "Cursed Ring";
        case ObjectID::Nothing:
        default:return std::string();
    }
}

const Object& Object::NOTHING()
{
    static const Object o = Object( ID::Nothing, 0, 0, "None" );
    return o;
}

const Object& Object::EGG()
{
    static const Object o = Object( ID::Egg, 1, 0, "Egg" );
    return o;
}

const Object& Object::CROWBAR()
{
    static const Object o = Object( ID::Crowbar, 99, 25, "Crowbar" );
    return o;
}

const Object& Object::IRON_KEY()
{
    static const Object o = Object( ID::IronKey, 99, 1, "Iron key" );
    return o;
}

const Object& Object::GOLD_KEY()
{
    static const Object o = Object( ID::GoldKey, 99, 1, "Gold key" );
    return o;
}

const Object& Object::GRAPPLING_HOOK()
{
    static const Object o = Object( ID::GrapplingHook, 99, 1, "Grappling Hook" );
    return o;
}

const Object& Object::TORCH()
{
    static const Object o = Object( ID::Torch, 99, 5, "Torch" );
    return o;
}

const Object& Object::LIFE_POTION()
{
    static const Object o = Object( ID::LifePotion, 99, 1, "Life Potion" );
    return o;
}

const Object& Object::HINT1()
{
    static const Object o = Object( ID::Hint1, 99, 1, "Hint #1" );
    return o;
}

const Object& Object::HINT2()
{
    static const Object o = Object( ID::Hint2, 99, 1, "Hint #2" );
    return o;
}

const Object& Object::HINT3()
{
    static const Object o = Object( ID::Hint3, 99, 1, "Hint #3" );
    return o;
}

const Object& Object::CURSED_RING()
{
    static const Object o = Object( ID::CursedRing, 99, 1, "Cursed Ring" );
    return o;
}