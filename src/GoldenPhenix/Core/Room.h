//
// Created by serdok on 05/03/19.
//

#ifndef GOLDEN_PHOENIX_ROOM_H
#define GOLDEN_PHOENIX_ROOM_H

// Custom headers
#include "Door.h"
#include "Exceptions.h"
#include "Vector2.h"

// C++ headers
#include <array>
#include <queue>

// Constants
const int ROOM_WIDTH = 7;
const int ROOM_HEIGHT = 6;


//! Class holding all information about a room in the castle
class Room
{
public:
    //! List of all possible joining directions
    enum JoiningDirections
    {
        Left = 0, ///< Left door
        Up,       ///< Upper door
        Right,    ///< Right door

        TOTAL     ///< Total number of joining directions
    };

private:
    unsigned int _id;
    bool _isCorridor;

    int _ground[ ROOM_HEIGHT ][ ROOM_WIDTH ];

    std::array< unsigned int, Room::TOTAL > _joiningRooms;
    std::array< Door*, Room::TOTAL > _joiningDoors;


public:
    /** Load a room from file data stored in a queue
     * @param [in,out] data A queue containing the rooms data (FIFO)
     * @exception Exception if a room does not have 10 lines descibing it
     */
    explicit Room( std::queue< std::string >& data ) noexcept( false );

    //! Free resources
    ~Room();

    //! Get the ID of the current room
    unsigned int GetRoomID() const;

    //! Get the ID of a joining room
    unsigned int GetRoomID( JoiningDirections direction ) const;

    //! Get the door from a joining room
    Door* GetDoor( JoiningDirections direction );

    //! Get the door from a joining room
    const Door* const GetDoor( JoiningDirections direction ) const;

    //! Return true if the current room is a corridor, false otherwise
    bool IsCorridor() const;

    /**
     * Return what's on the ground.
     * If the number is positive, then the corresponding object ID is returned.
     * If the number is negative then the number corresponds to : <br>
     *      * -1 : Money<br>
     *      * -2 : Wall<br>
     *      * -3 : Oblivion passage<br>
     *      * -4 : Oblivion room<br>
     *      * -5 : Bat spawning location<br>
     *      * -6 : Use grappling hook
     * @param [in] position The square to fetchc info from
     * @return A number ranging from -6 to ObjectID::Total
     */
    int GetSquare( const Vector2i& position ) const;

    /**
     * Return what's on the ground.
     * If the number is positive, then the corresponding object ID is returned.
     * If the number is negative then the number corresponds to : <br>
     *      * -1 : Money<br>
     *      * -2 : Wall<br>
     *      * -3 : Oblivion passage<br>
     *      * -4 : Oblivion room<br>
     *      * -5 : Bat spawning location<br>
     *      * -6 : Use grappling hook
     * @param [in] position The square to fetchc info from
     * @return A number ranging from -6 to ObjectID::Total
     */
    int& GetSquare( const Vector2i& position );

    //! Return a string version of what's on the ground
    std::string ToString( const Vector2i& position ) const;

private:
    void LoadID( std::queue< std::string >& data ); ///< Load the ID of the room from the queue
    void LoadJoiningData( std::queue< std::string >& data ); ///< Load joining room data from the queue
    void LoadGround( std::queue< std::string >& data ); ///< Load ground info from the queue

};


#endif //GOLDEN_PHOENIX_ROOM_H
