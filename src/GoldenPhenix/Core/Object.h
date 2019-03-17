//
// Created by serdok on 05/03/19.
//

#ifndef GOLDEN_PHOENIX_OBJECT_H
#define GOLDEN_PHOENIX_OBJECT_H

// Custom headers


// C++ headers
#include <cstdint>
#include <string>


//! Enumeration holding all objects and their corresponding ID
enum class ObjectID : uint8_t
{
    Nothing = 0,
    Egg = 1,
    Crowbar = 2,
    IronKey = 3,
    GoldenKey = 4,
    GrapplingHook = 5,
    Torch = 6,
    LifePotion = 7,
    Hint1 = 8,
    Hint2 = 9,
    Hint3 = 10,
    CursedRing = 11,

    TOTAL
};


//! Structure representing a game object
struct Object
{
    //! Enumeration holding all object names
    enum ID
    {
        Nothing, Egg, Crowbar, IronKey, GoldenKey, GrapplingHook, Torch, LifePotion, Hint1, Hint2, Hint3, CursedRing
    };

    const Object::ID id;
    const int maxStackSize;
    const int durability;
    const std::string name;

    //! Create an object with an ID, a maximum stack property, a durability property and a name
    Object( Object::ID id, int maxStack, int maxDurability, std::string&& name );

    //! Converts the name to the ID
    ObjectID ToObjectID() const;

    //! Converts the given ID to an object
    static const Object& ToObject( ObjectID id );

    //! List of all objects
    const static Object NOTHING, EGG, CROWBAR, IRON_KEY, GOLDEN_KEY, GRAPPLING_HOOK, TORCH, LIFE_POTION, HINT1, HINT2, HINT3, CURSED_RING;
};


#endif //GOLDEN_PHOENIX_OBJECT_H
