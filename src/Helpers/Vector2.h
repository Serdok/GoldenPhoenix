//
// Created by serdok on 14/02/19.
//

#ifndef GOLDEN_PHOENIX_VECTOR2_H
#define GOLDEN_PHOENIX_VECTOR2_H

// C++ headers
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>


//! Generic 2-dimensional vector representation.
template< typename T >
struct Vector2
{
    T x; ///< x coordinate of the vector.
    T y; ///< y coordinate of the vector.

    //! Set both x and y to 0.
    Vector2() noexcept
    {
        x = y = 0;
    }

    //! Set both x and y to the given parameter n.
    Vector2( T n ) noexcept
    : x( n ), y( n )
    {

    }

    //! Set the vector with the given parameters.
    Vector2( T _x, T _y ) noexcept
    : x( _x ), y( _y )
    {

    }

    //! Set both x and y to the given parameter n. Converts the type of n to match the type of the vector.
    template< typename T2 >
    Vector2( T2 n ) noexcept
    : x( static_cast< T >( n ) ), y( static_cast< T >( n ) )
    {

    }

    //! Set the vector with the given parameters. Converts the type of the parameters to match the type of the vector.
    template< typename T2 >
    Vector2( T2 _x, T2 _y ) noexcept
    : x( static_cast< T >( _x ) ), y( static_cast< T >( _y ) )
    {

    }

    //! Copy constuctor.
    Vector2( const Vector2< T >& v )
    : x( v.x ), y( v.y )
    {

    }

    //! Copy constructor. Converts the type of the parameter to match the type of the vector.
    template< typename T2 >
    Vector2( const Vector2< T2 >& v )
    : x( static_cast< T >( v.x ) ), y( static_cast< T >( v.y ) )
    {

    }

    //! Assigment operator from a vector with the same type.
    Vector2< T >& operator =( const Vector2< T >& rhs )
    {
        x = rhs.x;
        y = rhs.y;
        return *this;
    }

    //! Assigment operator from a vector with a different type.
    template< typename T2 >
    Vector2< T >& operator =( const Vector2< T2 >& rhs )
    {
        x = static_cast< T >( rhs.x );
        y = static_cast< T >( rhs.y );
        return *this;
    }

    //! Equality operator between two vectors.
    bool operator ==( const Vector2< T >& rhs ) const
    {
        return x == rhs.x && y == rhs.y;
    }

    //! Difference operator between two vectors.
    bool operator !=( const Vector2< T >& rhs ) const
    {
        return !( rhs == *this );
    }

    //! Unary operator. Negates all the coordinates.
    void operator -()
    {
        x *= -1;
        y *= -1;
    }

    //! Return the length squared of the vector. Can be used to compare vectors faster.
    T MagnitudeSq() const
    {
        return x*x + y*y;
    }

    //! Return the length of the vector.
    T Magnitude() const
    {
        return std::sqrt( MagnitudeSq() );
    }

    //! Normalize the vector. A normalized vector is a vector which magnitude is equal to 1.
    void Normalize()
    {
        T mag = Magnitude();
        x /= mag;
        y /= mag;
    }

    //! Return the normalized vector without modifying it.
    Vector2< T > Normalized() const
    {
        T mag = Magnitude();
        return { x/mag, y/mag };
    }

    //! Return the direction (angle) of the vector.
    T Direction() const
    {
        return std::atan( y / x );
    }

    //! Relational operator between two vectors. Compares their squared magnitudes.
    bool operator <( const Vector2< T >& rhs ) const
    {
        return MagnitudeSq() < rhs.MagnitudeSq();
    }

    //! Relational operator between two vectors. Compares their squared magnitudes.
    bool operator >( const Vector2< T >& rhs ) const
    {
        return !(*this < rhs);
    }

    //! Relational operator between two vectors. Compares their squared magnitudes.
    bool operator <=( const Vector2< T >& rhs ) const
    {
        return *this < rhs || *this == rhs;
    }

    //! Relational operator between two vectors. Compares their squared magnitudes.
    bool operator >=( const Vector2< T >& rhs ) const
    {
        return !(*this <= rhs);
    }

    //! Addition between two vectors.
    Vector2< T > operator +( const Vector2< T >& rhs ) const
    {
        return { x + rhs.x, y + rhs.y };
    }

    //! Difference between two vectors
    Vector2< T > operator -( const Vector2< T >& rhs ) const
    {
        return { x - rhs.x, y - rhs.y };
    }

    //! Stream output operator. Output format : ( x, y ).
    friend std::ostream& operator <<( std::ostream& out, const Vector2< T >& v )
    {
        out << "( " << v.x << ", " << v.y << " )";
        return out;
    }

    //! String conversion.
    std::string ToString() const
    {
        std::ostringstream oss;
        oss << *this;
        return oss.str();
    }
};

//! Return the dot (or scalar) product between two given vectors.
template< typename T >
T Dot( const Vector2< T >& lhs, const Vector2< T >& rhs )
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

//! Multiplication of a vector and a scalar.
template< typename T >
inline Vector2< T > operator *( const Vector2< T >& lhs, const T& rhs )
{
    return { lhs.x * rhs, lhs.y * rhs };
}

//! Multiplication of a vector and a scalar.
template< typename T >
inline Vector2< T > operator *( const T& lhs, const Vector2< T >& rhs )
{
    return rhs * lhs;
}

//! Division of a vector by a scalar.
template< typename T >
inline Vector2< T > operator /( const Vector2< T >& lhs, const T& rhs )
{
    return { lhs.x / rhs, lhs.y / rhs };
}

//                                              SHORTCUTS
typedef Vector2< int > Vector2i;
typedef Vector2< float > Vector2f;
typedef Vector2< double > Vector2d;

//                                              UNITY CONSTANTS
const Vector2f VEC2_ZERO = Vector2f();
const Vector2f VEC2_ONE = Vector2f( 1.0f, 1.0f );

const Vector2f VEC2_UP = Vector2f( 0.0f, -1.0f ); // Using negative y for SDL2 coordinate system
const Vector2f VEC2_DOWN = Vector2f( 0.0f, 1.0f ); // Using positive y for SDL2 coordinate system
const Vector2f VEC2_RIGHT = Vector2f( 1.0f, 0.0f );
const Vector2f VEC2_LEFT = Vector2f( -1.0f, 0.0f );

#endif //GAME_VECTOR2_H
