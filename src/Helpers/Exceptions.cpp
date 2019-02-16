//
// Created by serdok on 24/01/19.
//

#include "Exceptions.h"

void Rethrow( const std::string& message, const char* file, unsigned int line )
try
{
    std::rethrow_exception( std::current_exception() );
}
catch( ... )
{
    std::throw_with_nested( Exception( message, file, line ) );
}

void Backtrace( const std::exception& exception )
{
    std::cerr << exception.what() << '\n';
    try
    {
        std::rethrow_if_nested( exception );
    }
    catch( const std::exception& nested_exception )
    {
        Backtrace( nested_exception );
    }
}

void HandleException( const std::exception& exception, const std::string& function )
{
    if (!function.empty())
        std::cerr << "Game API : Exception caught in function \'" << function << "\'. ";
    std::cerr << "Backtrace :\n";
    try
    {
        Backtrace( exception );
    }
    catch( ... )
    {
        std::cerr << "Something went super wrong. Terminating ...\n";
        std::exit( EXIT_FAILURE );
    }
}