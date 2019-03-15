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
            Castle* castle = new Castle( GetResourcePath( "pieces/testroom.txt" ));
            delete castle;
        }
        catch (Exception& e)
        {
            Rethrow( "An error occured!", __FILE__, __LINE__ );
        }
    }
    catch (Exception& e)
    {
        Backtrace( e );
    }

    return 0;
}