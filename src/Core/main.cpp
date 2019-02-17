//
// Created by serdok on 12/02/19.
//

#include "Game.h"

int main( int argc, char* argv[] )
{
#ifdef DEBUG
    std::cout << "Debug mode on ...\n";
#endif
    try
    {
        Game myGame;
        myGame.Init( "Game" );

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