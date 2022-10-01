

#ifndef INCLUDE_GUARD_VECTOR2D_H
#define INCLUDE_GUARD_VECTOR2D_H


#include <math.h>

class Vector2D {

private:
    float m_x;
    float m_y;

public:
	Vector2D(){};
    Vector2D( int x, int y ):m_x( (float) x ), m_y( (float) y ) {}
	Vector2D( float x, float y ):m_x( x ), m_y( y ) {}

    float getX() { return m_x; }
    float getY() { return m_y; }


    void setX( float x ) { m_x = x; }
    void setY( float y ) { m_y = y; }

    float length(){ return sqrt( m_x * m_x + m_y * m_y ); }


    // OVERLOAD OPERATOR '+' FOR ADDING VECTORS
    // https://www.tutorialspoint.com/cplusplus/cpp_overloading.htm
    //
    // OVERLOADING OPERATOR IS FOR REDEFINE OPERATOR LIKE '+', '-', '*' etc.
    // IF WE DEFINE LIKE
    // Box operator+ ( const Box &);
    // IT OVERLOADS '+' OPERATOR AND MAKE THIS TO ADD MULTIPLE 'Box' TYPED OBJECTS FOR INSTANCE.

    Vector2D operator+ ( const Vector2D & v2 ) const {
        // << POSITION OF "const" >>
        // https://stackoverflow.com/questions/10716769/c-difference-between-const-positioning
        //
        // const int MyClass::showName(string id)
        // ^
        // returns a const int object.
        // So the calling code can not change the returned int.
        // If the calling code is like const int a = m.showName("id"); a = 10; then
        // it will be marked as a compiler error.
        // However, as noted by @David Heffernan below, since the integer is returned by copy
        // the calling code is not obliged to use const int. It can very well declare int as
        // the return type and modify it. Since the object is returned by copy, it doesn't make much sense to declare the return type as const int.

        // int MyClass::showName(string id) const
        //                                  ^
        // tells that the method showName is a const member function.
        // A const member function is the one which does not modify any member variables
        // of the class (unless they are marked as mutable).
        // So if you have member variable int m_a in class MyClass and
        // if you try to do
        // m_a = 10; inside showName you will get a compiler error.

        return Vector2D( m_x + v2.m_x, m_y + v2.m_y );
    }


    // << friend FUNCTION >>
    // https://www.tutorialspoint.com/cplusplus/cpp_friend_functions.htm
    //
    // A friend function of a class is defined outside that class' scope
    // but it has the right to access all private and protected members
    // of the class. Even though the prototypes for friend functions appear
    // in the class definition, friends are not member functions.
    friend Vector2D & operator+= ( Vector2D & v1, const Vector2D & v2 ) {
        v1.m_x += v2.m_x;
        v1.m_y += v2.m_y;

        return v1;
    }


    Vector2D operator* ( float scalar ) {
        return Vector2D( m_x * scalar, m_y * scalar );
    }


    Vector2D & operator*= ( float scalar ){
        m_x *= scalar;
        m_y *= scalar;

        return * this;
    }


    Vector2D operator- ( const Vector2D & v2 ) const {
        return Vector2D ( m_x - v2.m_x, m_y - v2.m_y );
    }

    friend Vector2D & operator-= ( Vector2D & v1, const Vector2D & v2 ) {
        v1.m_x -= v2.m_x;
        v1.m_y -= v2.m_y;

        return v1;
    }


    Vector2D operator/ ( float scalar ){
        return Vector2D( m_x / scalar, m_y / scalar );
    }


    Vector2D & operator /= ( float scalar ){
        m_x /= scalar;
        m_y /= scalar;

        return * this;
    }


    void normalize() {
        float l = length();
        if ( l > 0 ) {
            (* this ) *= 1 / l;
        }
    }





};


#endif
