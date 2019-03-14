//
// Created by serdok on 05/03/19.
//

#ifndef GOLDEN_PHOENIX_DOOR_H
#define GOLDEN_PHOENIX_DOOR_H


//! Class holding all information about a door.
class Door
{
public:
    //! List of the possible doors
    enum DOORS : char
    {
        wall = 'M',
        opening = 'O',
        door = 'D',
        grid = 'G',
        chest = 'C',
        chimney = 'F'
    };

    //! List of the possible actions on a door
    enum OPEN_TYPES : char
    {
        open = 'O',
        open_impossible = 'N',
        crowbar = 'B',
        iron_key = 'I',
        gold_key = 'G'
    };

private:
    DOORS _door;
    OPEN_TYPES _requires;
    bool _hasTorch;
    bool _torchLit;

public:
    //! Assign information about a door
    Door( DOORS door, OPEN_TYPES type, bool hasTorch, bool torchLit );
    ~Door();

    //! Return the type of this door
    DOORS GetDoorType() const;

    //! Return how this door must be opened
    OPEN_TYPES GetOpenType() const;

    //! Return true if the torch is lit, false otherwise
    bool GetTorchState() const;

private:

};


#endif //GOLDEN_PHOENIX_DOOR_H
