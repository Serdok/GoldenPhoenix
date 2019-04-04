//
// Created by serdok on 15/03/19.
//

#include "Castle.h"
#include "GetResourcePath.h"


int main()
{
    Castle* game = new Castle( GetResourcePath( "rooms/testroom.txt" ), false );
    game->EnterCastle();
    game->GetPlayer()->SetCurrentRoom( game->GetRooms().at( 1 ));
    game->GetPlayer()->SetPosition( Vector2i( 0, 1 ) );

    bool egg_found = false;
    do
    {
        std::cout << "Choose an action : ";
        std::string action;
        std::cin >> action;

        if (action == "quit")
            break;

        game->ProcessActions( action );
        game->Update();
        game->AddIteration();

        for (const auto& item : game->GetPlayer()->GetItems())
            if (item == ItemStack( Object::ToObject( ObjectID::Egg ), 1 ))
                egg_found = true;
    } while (!egg_found);

    delete game;
    return 0;
}