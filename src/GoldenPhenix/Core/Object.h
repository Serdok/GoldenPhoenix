//
// Created by serdok on 05/03/19.
//

#ifndef GOLDEN_PHOENIX_OBJECT_H
#define GOLDEN_PHOENIX_OBJECT_H

// C++ headers
#include <string>


//! Enumeration holding all objects and their corresponding ID
enum ObjectID
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

//! Class representing a game object. Used to store "constants" describing the properties of each object
struct Object
{
    enum ID
    {
        Nothing, Egg, Crowbar, IronKey, GoldKey, GrapplingHook, Torch, LifePotion, Hint1, Hint2, Hint3, CursedRing
    };

    const Object::ID id;
    const unsigned int maxStackSize;
    const unsigned int maxDurability;
    const std::string name;

    //! Create an object with an ID, a maximum stack property, a durability property and a name
    Object( Object::ID _id, unsigned int _maxStack, unsigned int _maxDurability, std::string&& _name );

    Object( const Object& o );

    bool operator ==( const Object& o )
    {
        return this->id == o.id;
    }

    //! Converts the name to the ID
    const ObjectID GetID() const;

    //! Converts the given ID to an object
    static const Object& ToObject( ObjectID id );
};

#endif //GOLDEN_PHOENIX_OBJECT_H