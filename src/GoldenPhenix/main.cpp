//
// Created by serdok on 15/03/19.
//

#include "Castle.h"
#include "GetResourcePath.h"


int main( int argc, char* argv[], char* env[] )
{
    try
    {
        try
        {
            Castle* castle = new Castle( GetResourcePath( "rooms/room.room" ));

            std::cout << castle->GetRooms().at( 0 )->GetRoomID() << std::endl;
#ifdef DEBUG
            std::cout << "Choose a beginning room : ";
            unsigned int id;
            std::cin >> id;
            castle->GetPlayer()->SetCurrentRoom( castle->GetRooms().at( id - 1 ));
#endif // DEBUG

            while (castle->GetPlayer()->GetHeldItem().GetObject().ToObjectID() != ObjectID::Egg)
            {
                std::cout << "Choose an action : ";
                std::string action;
                std::cin >> action;

                if (action == "quit")
                    break;

                castle->ProcessActions( action );
                castle->Update();
            }

            delete castle;
        }
        catch (Exception& e)
        {
            Rethrow( "An error occured!", __FILE__, __LINE__ );
        }
    }
    catch (Exception& e)
    {
        HandleException( e, __func__ );
    }

    return 0;
}