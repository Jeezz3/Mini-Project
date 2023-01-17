# Mini Project: Big Integer ADT implementation in C++

## Overview

This is a Big Integer ADT implementation in C++. It allows the client to compute arithmetic operation with integer
that can not be represented in any integer datatype. Currently, the ADT only supports, addition, subtraction, and multiplication operation.

The value of Big Integer can only be initialize by number that is represent in string datatype. After the Big Integer had been defined, it can be
used similar to normal integer datatype. 

## How To Use

Big Integer ADT requires List.cpp and List.h, without it, the ADT will not work. Use "#include'BigInteger.h'" to implement Big Integer into the program

### Compiling 

make sure you have g++ complier installed

to compile all components:
- BigInteger: g++ -std=c++17 -Wall -c BigInteger.cpp
- List: g++ -std=c++17 -Wall -c List.cpp

then link the BigInteger and List object to desire object:
g++ -std=c++17 -Wall -o (program) (desire object) BigInteger.o List.o

## Extra Note

still thinking about divsion operation

