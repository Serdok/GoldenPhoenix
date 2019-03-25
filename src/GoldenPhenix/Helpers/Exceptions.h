//
// Created by serdok on 23/01/19.
//

#ifndef GOLDEN_PHOENIX_EXCEPTIONS_H
#define GOLDEN_PHOENIX_EXCEPTIONS_H

// C++ headers
#include <iostream>
#include <stdexcept>


//! Custom Exception class. Can be nested to have an error backtrace.
class Exception : public std::runtime_error
{
private:
    std::string _message; ///< The error message
    std::string _file; ///< The file containing the error
    unsigned int _line; ///< The line of the error


public:
    /**
     * Build an Exception.
     * @param [in] message The error message
     * @param [in] file The file containing the error
     * @param [in] line The line containing the error
     */
    Exception( const std::string& message, const char* file, unsigned int line )
    : std::runtime_error( message ), _file( file ), _line( line )
    {
        _message = message + "\n\t@Location : " + _file + " at line " + std::to_string( _line );
    }

    Exception( const Exception& e ) noexcept
    : Exception( e.what(), e.whatFile(), e.whatLine() )
    {

    }

    ~Exception() noexcept override = default;

    //! Return a C-style character string describing the general cause of the current error.
    const char* what() const noexcept override
    {
        return _message.c_str();
    }

    //! Return a C-style character string describing the file of the current error
    const char* whatFile() const noexcept
    {
        return _file.c_str();
    }

    //! Return an integer describing the line of the current error
    const unsigned int whatLine() const noexcept
    {
        return _line;
    }
};

/**
 * Rethrow an exception to be caught again in an upper catch() block.
 * @param message [in] The error message
 * @param file [in] The file containing the error
 * @param line [in] The line containing the error
 */
void Rethrow( const std::string& message, const char* file, unsigned int line );

/**
 * Used for nested exceptions, backtrace error messages and output it.
 * @param exception [in] The exception to backtrace
 */
void Backtrace( const std::exception& exception );

/**
 * Handle an exception. Used in last catch() block for the exception.
 * @param exception [in] The exception to handle
 * @param function [in] The function containing the error
 */
void HandleException( const std::exception& exception, const std::string& function = "" );

#endif //GOLDEN_PHOENIX_EXCEPTIONS_H
