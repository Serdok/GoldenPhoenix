//
// Created by serdok on 05/03/19.
//

#ifndef GOLDEN_PHOENIX_CASTLE_H
#define GOLDEN_PHOENIX_CASTLE_H

// Custom headers
#include "Room.h"
#include "Player.h"
#include "Bat.h"
#include "Rat.h"

// C++ headers
#include <fstream>
#include <random>



//! Core game manager. Handles every interaction and update for the game Golden Phoenix
class Castle
{
private:
    std::vector< Room* > _rooms;
    Bat* _bat = nullptr;
    Rat* _rat = nullptr;
    bool _attacked = false;
    Player* _player;
    bool _movedToNextRoom = false;
    int _score = 0;
    bool _ringIsInInventory = false;
    bool _exitCastle = false;

    unsigned int _iteration = 0;
    bool _usingCustomTimer = false;
   
public:
    /** Create a castle from a file containing rooms data. Rooms data files must be located in data/rooms/
     * @param filename The name file containing rooms info
     * @param useCustomTimer [in] Set to true if you want to use a custom timer for events such as bat movement, removing a life and such
     * @exception Exception if an error occurred in opening the file
     */
    Castle( const std::string& filename, bool useCustomTimer = false ) noexcept( false );

    //! Free resources
    ~Castle();

    //! Update the game
    void Update();

    //! Add an integer to the iteration. Only effective if using a custom timer
    void AddIteration( unsigned int it = 1 );

    // TODO List all actions in an enum
    /**
     * Process actions
     * @param [in] action A string containing the action to execute
     */
    void ProcessActions( const std::string& action );

    //! Return the score
    int GetScore();

    //! Add in the score
    void AddScore( int s );

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

    //! Return the rat of the game
    const Rat* const GetRat() const;

    //! Return the rat of the game
    Rat* const GetRat();

    //! Return the array of rooms which have been loaded
    const std::vector< Room* >& GetRooms() const;


private:
    void PickUp(); ///< Pick an item up
    void Use(); ///< Use an item

    void OpenDoor( Door* door, Room::JoiningDirections direction ); ///< Open a door

    void MoveToLeftRoom(); ///< Move the player to the left room
    void MoveToRightRoom(); ///< Move the player to the right room
    void MoveToUpperRoom(); ///< Move the player to the upper room

    void PlacePlayer( const Room* previousRoom ); ///< Replace the player depending on the last room

    void OpenChest( Room::JoiningDirections direction ); ///< Open a chest

    bool BatInRoom( Vector2i* spawn );
    void SpawnBat();
    void MoveBat();
    bool RatInRoom( Vector2i* spawn );
    void SpawnRat();
    void MoveRat();
    void RemoveALife();
    void KillPlayer();

    float Random( float low = 0.0f, float high = 1.0f );
};


#endif //GOLDEN_PHOENIX_CASTLE_H
