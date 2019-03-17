//
// Created by serdok on 15/03/19.
//

#include "Castle.h"
#include "GetResourcePath.h"


int main()
{
    try
    {
        try
        {
            Castle* castle = new Castle( GetResourcePath( "rooms/room.room" ));
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