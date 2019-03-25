//
// Created by serdok on 05/03/19.
//

#ifndef GOLDEN_PHOENIX_CASTLE_H
#define GOLDEN_PHOENIX_CASTLE_H

// Custom headers
#include "Room.h"
#include "Player.h"
#include "Bat.h"

// C++ headers
#include <fstream>



//! Core game manager. Handles every interaction and update for the game Golden Phoenix
class Castle
{
private:
    std::vector< Room* > _rooms;
    bool _thereIsABat;
    Bat* _bat;
    Player* _player;
    unsigned int _deaths;
    int _score;
    bool _ringIsInInventory;
    bool _exitCastle = false;
    int _iteration;
   
public:
    /** Create a castle from a file containing rooms data. Rooms data files must be located in data/rooms/
     * @param filename The name file containing rooms info
     * @exception Exception if an error occurred in opening the file
     */
    Castle( const std::string& filename ) noexcept( false );

    //! Free resources
    ~Castle();

    //! Update the game
    void Update();

    // TODO List all actions in an enum
    /**
     * Process actions
     * @param [in] action A string containing the action to execute
     */
    void ProcessActions( const std::string& action );

    //! Return the score
    int GetScore();

    //! Set the score
    void SetScore( int s );

    //! Return true if the player should exit the castle
    bool ExitCastle() const;

    //! Set initial player position when re-entering the castle
    void EnterCastle();

    //! Return the player of the game
    const Player* const GetPlayer() const;

    //! Return the player of the game
    Player* const GetPlayer();

    //! Return the bat of the game
    const Bat* const GetBat() const;

    //! Return the bat of the game
    Bat* const GetBat();

    //! Return the array of rooms which have been loaded
    const std::vector< Room* >& GetRooms() const;

private:
    void PickUp(); ///< Pick an item up
    void Use(); ///< Use an item

    void OpenDoor( Door* door, Room::JoiningDirections direction ); ///< Open a door

    void MoveToLeftRoom(); ///< Move the player to the left room
    void MoveToRightRoom(); ///< Move the player to the right room
    void MoveToUpperRoom(); ///< Move the player to the upper room
};


#endif //GOLDEN_PHOENIX_CASTLE_H
