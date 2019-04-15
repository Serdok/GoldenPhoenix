//
// Created by serdok on 15/03/19.
//

#include "Castle.h"
#include "GetResourcePath.h"


int main()
{
    Castle* game = new Castle( GetResourcePath( "rooms/room.room" ), false );
    game->EnterCastle();
    game->GetPlayer()->SetCurrentRoom( game->GetRooms().at( 51 ));
    game->GetPlayer()->SetPosition( Vector2i( 3, 3 ) );
    game->GetPlayer()->AddItem( Object::ToObject( ObjectID::LifePotion ) );
    game->GetPlayer()->AddItem( Object::ToObject( ObjectID::LifePotion ) );
    game->GetPlayer()->AddItem( Object::ToObject( ObjectID::LifePotion ) );
    game->GetPlayer()->AddItem( Object::ToObject( ObjectID::Crowbar ) );

    game->SaveRooms( GetResourcePath( "saves/test.room" ));
    game->LoadCastle( GetResourcePath( "saves/test.room" ) );

    game->GetPlayer()->Save( GetResourcePath( "saves/test.player" ) );
    std::cout << game->GetPlayer()->Load( GetResourcePath( "saves/test.player" ) ) << std::endl;

    delete game;

    for (const auto& entry : fs::directory_iterator( GetResourcePath( "saves/" ) ))
        std::cout << entry.path() << std::endl;

    return 0;
}