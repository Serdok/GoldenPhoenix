//
// Created by serdok on 15/03/19.
//

#include "Castle.h"
#include "GetResourcePath.h"


int main()
{
    Castle* game = new Castle( GetResourcePath( "rooms/room.room" ), false );
    game->EnterCastle();
    game->GetPlayer()->SetCurrentRoom( game->GetRooms().at( 0 ));
    game->GetPlayer()->SetPosition( Vector2i( 0, 1 ) );

    game->SaveCastle( GetResourcePath( "saves/test.room" ) );
    game->LoadCastle( GetResourcePath( "saves/test.room" ) );

    delete game;
    return 0;
}