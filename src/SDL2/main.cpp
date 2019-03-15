//
// Created by serdok on 12/02/19.
//

#include "Core/GameManager.h"

int main( int argc, char* argv[] )
{
#ifdef DEBUG
    std::cout << "Debug mode on ...\n";
#endif
    try
    {
        GameManager myGame;

        try
        {
            myGame.Run();
        }
        catch( Exception& e )
        {
            Rethrow( "Game stopped running. An error occurred!", __FILE__, __LINE__ );
        }
    }
    catch( Exception& e )
    {
        HandleException( e, __func__ );
    }

    return 0;
}