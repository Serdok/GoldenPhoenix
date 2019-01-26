//
// Created by serdok on 23/01/19.
//

#ifndef MYPROJECT_EXCEPTIONS_HPP
#define MYPROJECT_EXCEPTIONS_HPP

// C++ headers
#include <iostream>
#include <stdexcept>

//! Custom Exception class. Can be nested to have an error backtrace.
class Exception : public std::runtime_error
{
private:
    std::string _message; ///< The error message


public:
    /**
     * Builds an Exception.
     * @param message [in] The error message
     * @param file [in] The file containing the error
     * @param line [in] The line containing the error
     */
    Exception( const std::string& message, const char* file, unsigned int line )
    : std::runtime_error( message )
    {
        _message = message + "\n\t@Location : " + std::string( file ) + " at line " + std::to_string( line );
    }

    ~Exception() noexcept override = default;

    //! Return a C-style string containing information about the error
    const char* what() const noexcept override
    {
        return _message.c_str();
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
 * Used for nested exceptions, backtrace error messages.
 * @param exception [in] The exception to backtrace
 */
void Backtrace( const std::exception& exception );

/**
 * Handle an exception. Used in last catch() block for the exception.
 * @param exception [in] The exception to handle
 * @param function [in] The function containing the error
 */
void HandleException( const std::exception& exception, const std::string& function = "" );

#endif //MYPROJECT_EXCEPTIONS_HPP
