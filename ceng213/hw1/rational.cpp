#include <iostream>
#include "rational.hpp"

// Default (zero-argument) constructor
Rational::Rational()
{
    numer = denom = 0;
}

// Two argument constructor
Rational::Rational(int num, int den)
{
    /* TO-DO: fill the constructor */
}


void Rational::setNumerator(int num)
{
    numer = num;
}
/*****************************************/
/*  TO-DO: add the remaining             */
/*         getX setX functions           */
/*****************************************/


/*****************************************/



/*****************************************/
/*  TO-DO: add print                     */
/*****************************************/


/*****************************************/



// Returns a + b
Rational Rational::add(Rational rhs)
{
    Rational result;

    int num = numer * rhs.denom + rhs.numer * denom;
    int den = denom * rhs.denom;

    result.numer = num;
    result.denom = den;

    // Simplify the result if possible. Note that we
    // are not passing "result" as an argument to 
    // "simplify". Instead we are calling the "simplify"
    // function of the "result" object.

    // result.simplify();

    return result;
}

// Returns a * b
Rational Rational::multiply(Rational rhs)
{
    /* TO-DO: fill multiply */
}


/*****************************************/
/*  TO-DO: add simplify funtion          */
/*  then call it in appropriate places   */
/*****************************************/


/*****************************************/

int Rational::gcd(int a, int b)
{
    int c;

    if(a<0)
        a = a * -1;
    if(b<0)
        b = b * -1;

    while (a != 0)
    {
        c = a;
        a = b % a;
        b = c;
    }

    return b;
}

