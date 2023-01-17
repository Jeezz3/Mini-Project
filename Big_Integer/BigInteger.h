//-----------------------------------------------------------------------------
// BigInteger.h
// Header file for the BigInteger ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include"List.h"

#ifndef BIG_INTEGER_H_INCLUDE_
#define BIG_INTEGER_H_INCLUDE_

#define BASE 1000000000
#define POWER 9

// Exported type  -------------------------------------------------------------
class BigInteger{

private:

   // BigInteger Fields 
   int signum;    // +1 (positive), -1 (negative), 0 (zero)
   List digits;   // List of digits in this BigInteger

public:

   // Class Constructors & Destructors ----------------------------------------

   // BigInteger()
   // Constructor that creates a new BigInteger in the zero state: 
   // signum=0, digits=().
   BigInteger();

   // BigInteger()
   // Constructor that creates a new BigInteger from the string s.
   // Pre: s is a non-empty string consisting of (at least one) base 10 digit
   // {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
   BigInteger(std::string s);

   // BigInteger()
   // Constructor that creates a copy of N.
   BigInteger(const BigInteger& N);

   // Optional Destuctor
   // ~BigInteger()
   // ~BigInteger();


   // Access functions --------------------------------------------------------

   // sign()
   // param: None
   // return: Int- -1, 1 or 0 according to whether this BigInteger is positive, negative or 0, respectively.
   int sign() const;

   // compare()
   // param: None
   // return: Int- -1, 1 or 0 according to whether this BigInteger is less than N, greater than N or equal to N, respectively.
   int compare(const BigInteger& N) const;


   // Manipulation procedures -------------------------------------------------

   // makeZero()
   // param: None
   // return: None
   // func: Re-sets BigInteger to the zero state.
   void makeZero();

   // negate()
   // param: None
   // return: None
   // func: If BigInteger is zero, does nothing, otherwise reverses the sign of BigInteger positive <--> negative. 
   void negate();


   // BigInteger Arithmetic operations ----------------------------------------

   // add()
   // param: BigInteger- another Big Integer number N
   // return: BigInteger- sum of this and N.
   BigInteger add(const BigInteger& N) const;

   // sub()
   // param: BigInteger- another Big Integer number N
   // return: BigInteger- difference of this and N.
   BigInteger sub(const BigInteger& N) const;

   // mult()
   // param: BigInteger- another Big Integeer number N
   // return: BigInteger- product of this and N. 
   BigInteger mult(const BigInteger& N) const;


   // Other Functions ---------------------------------------------------------

   // to_string()
   // param: None
   // return: a string representation of this BigInteger
   std::string to_string();


   // Overriden Operators -----------------------------------------------------
   
   // operator<<()
   // func: inserts string representation of N into stream.
   friend std::ostream& operator<<( std::ostream& stream, BigInteger N );

   // operator==()
   // return: Bool- true if and only if A equals B. 
   friend bool operator==( const BigInteger& A, const BigInteger& B );

   // operator<()
   // return: Bool- true if and only if A is less than B. 
   friend bool operator<( const BigInteger& A, const BigInteger& B );

   // operator<=()
   // return: Bool- true if and only if A is less than or equal to B. 
   friend bool operator<=( const BigInteger& A, const BigInteger& B );

   // operator>()
   // return: Bool- true if and only if A is greater than B. 
   friend bool operator>( const BigInteger& A, const BigInteger& B );

   // operator>=()
   // return: Bool- true if and only if A is greater than or equal to B. 
   friend bool operator>=( const BigInteger& A, const BigInteger& B );

   // operator+()
   // return: BigInteger- the sum A+B. 
   friend BigInteger operator+( const BigInteger& A, const BigInteger& B );

   // operator+=()
   // func: Overwrites A with the sum A+B. 
   friend BigInteger operator+=( BigInteger& A, const BigInteger& B );

   // operator-()
   // return: BigInteger- the difference A-B. 
   friend BigInteger operator-( const BigInteger& A, const BigInteger& B );

   // operator-=()
   // func: Overwrites A with the difference A-B. 
   friend BigInteger operator-=( BigInteger& A, const BigInteger& B );

   // operator*()
   // return: BigInteger- the product A*B. 
   friend BigInteger operator*( const BigInteger& A, const BigInteger& B );

   // operator*=()
   // func: Overwrites A with the product A*B. 
   friend BigInteger operator*=( BigInteger& A, const BigInteger& B );

};


#endif