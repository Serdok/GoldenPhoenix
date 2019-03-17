//
// Created by serdok on 05/03/19.
//

#include "Object.h"

const Object Object::NOTHING( ID::Nothing, 0, 0, "None" );
const Object Object::EGG( ID::Egg, 1, 0, "Egg" );
const Object Object::CROWBAR( ID::Crowbar, 99, 25, "Crowbar" );
const Object Object::IRON_KEY( ID::IronKey, 99, 1, "Iron key" );
const Object Object::GOLDEN_KEY( ID::GoldenKey, 99, 1, "Gold key" );
const Object Object::GRAPPLING_HOOK( ID::GrapplingHook, 99, 1, "Grappling hook" );
const Object Object::TORCH( ID::Torch, 99, 5, "Torch" );
const Object Object::LIFE_POTION( ID::LifePotion, 99, 1, "Life potion" );
const Object Object::HINT1( ID::Hint1, 99, 1, "Hint #1" );
const Object Object::HINT2( ID::Hint2, 99, 1, "Hint #2" );
const Object Object::HINT3( ID::Hint3, 99, 1, "Hint #3" );
const Object Object::CURSED_RING( ID::CursedRing, 99, 1, "Cursed ring" );


Object::Object( Object::ID id, int maxStack, int maxDurability, std::string&& name ) : id( id ),
                                                                                       maxStackSize( maxStack ),
                                                                                       durability( maxDurability ),
                                                                                       name( std::move( name ))
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
        case GoldenKey:return ObjectID::GoldenKey;
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
        case ObjectID::Nothing:return NOTHING;
        case ObjectID::Egg:return EGG;
        case ObjectID::Crowbar:return CROWBAR;
        case ObjectID::IronKey:return IRON_KEY;
        case ObjectID::GoldenKey:return GOLDEN_KEY;
        case ObjectID::GrapplingHook:return GRAPPLING_HOOK;
        case ObjectID::Torch:return TORCH;
        case ObjectID::LifePotion:return LIFE_POTION;
        case ObjectID::Hint1:return HINT1;
        case ObjectID::Hint2:return HINT2;
        case ObjectID::Hint3:return HINT3;
        case ObjectID::CursedRing:return CURSED_RING;
        default:return NOTHING;
    }
}