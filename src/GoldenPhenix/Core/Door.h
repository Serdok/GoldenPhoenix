//
// Created by serdok on 05/03/19.
//

#ifndef GOLDEN_PHOENIX_DOOR_H
#define GOLDEN_PHOENIX_DOOR_H

// Custom headers
#include "Object.h"


//! Class holding all information about a door.
class Door
{
public:
    //! List of the possible doors
    enum DOORS : char
    {
        wall = 'M',     ///< The door is a wall, not possible to pass through
        opening = 'O',  ///< The door is an opening, can pass through freely
        door = 'D',     ///< The door is a door, may require a key or a crowbar to open
        grid = 'G',     ///< The door is a grid, may require a key or a crowbar to open
        chest = 'C',    ///< The door is a chest, may require a key or a crowbar to open
        chimney = 'F'   ///< The door is a chimney, may require a key or a crowbar to open
    };

    //! List of the possible actions on a door
    enum OPEN_TYPES : char
    {
        open = 'O',             ///< Nothing is required (door already open)
        open_impossible = 'N',  ///< Door impossible to open
        crowbar = 'B',          ///< A crowbar is required
        iron_key = 'I',         ///< An iron key is required
        gold_key = 'G'          ///< A gold key is required
    };

private:
    DOORS _door;
    OPEN_TYPES _requires;
    bool _hasTorch;
    bool _torchLit;
    int _objectID = 0;

public:
    //! Assign information about a door
    Door( DOORS door, OPEN_TYPES type, bool hasTorch, bool torchLit );

    //! Free resources
    ~Door();

    //! Return the type of this door
    DOORS GetDoorType() const;

    //! Return how this door must be opened
    OPEN_TYPES GetOpenType() const;

    //! Return true if the torch is lit, false otherwise
    bool GetTorchState() const;

    //! Return true if the door has a torch on top, false otherwise
    bool HasTorch() const;

    //! Add an object to the door (a chest for example)
    void AddObject( int objectID );

    //! Remove an object from the door (a chest for example)
    void RemoveObject();

    //! Return the object ID contained by the door, if it contains any (a chest for example)
    int GetObject() const;

    //! Set the door type
    void SetDoorType( DOORS door );

    //! Set what's required to open the door
    void SetOpenType( OPEN_TYPES requirement );

private:

};


#endif //GOLDEN_PHOENIX_DOOR_H
