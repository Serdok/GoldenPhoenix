//
// Created by serdok on 05/03/19.
//

#ifndef GOLDEN_PHOENIX_OBJECT_H
#define GOLDEN_PHOENIX_OBJECT_H

// C++ headers
#include <cstdint>
#include <string>


//! Enumeration holding all objects and their corresponding ID
enum ObjectID : uint8_t
{
    Nothing = 0,
    Egg = 1,
    Crowbar = 2,
    IronKey = 3,
    GoldKey = 4,
    GrapplingHook = 5,
    Torch = 6,
    LifePotion = 7,
    Hint1 = 8,
    Hint2 = 9,
    Hint3 = 10,
    CursedRing = 11,

    TOTAL
};

//! Structure representing a game object. Used to store "constants" describing the properties of each object
struct Object
{
    //! Enumeration holding all object names
    enum ID
    {
        Nothing, Egg, Crowbar, IronKey, GoldKey, GrapplingHook, Torch, LifePotion, Hint1, Hint2, Hint3, CursedRing
    };

    const Object::ID id;
    const int maxStackSize;
    const int durability;
    const std::string name;

    //! Create an object with an ID, a maximum stack property, a durability property and a name
    Object( Object::ID id, int maxStack, int maxDurability, std::string&& name );

    //! Converts the name to the ID
    ObjectID ToObjectID() const;

    //! Converts the current object to a string
    std::string ToString() const;

    //! Converts the given ID to a string
    static std::string ToString( ObjectID id );

    //! Converts the given ID to an object
    static const Object ToObject( ObjectID id );

    //! List of all objects
    static const Object& NOTHING();
    static const Object& EGG();
    static const Object& CROWBAR();
    static const Object& IRON_KEY();
    static const Object& GOLD_KEY();
    static const Object& GRAPPLING_HOOK();
    static const Object& TORCH();
    static const Object& LIFE_POTION();
    static const Object& HINT1();
    static const Object& HINT2();
    static const Object& HINT3();
    static const Object& CURSED_RING();
};

#endif //GOLDEN_PHOENIX_OBJECT_H
