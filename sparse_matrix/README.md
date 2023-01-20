# Mini-project: Sparse Matrix implementation in C

## Overview

This is an ADT implementation of sparse matrix in C. This ADT performs basic matrix arithmetic operation. This version supports the following operation:
addition, substraction, multiplication, scalar multiplication, and transpose. This implementation is for sparse matrix therefore it can achieve good runtime
if there are limited non-zero entry.   

## How to use

This ADT requires List.c and List.h to work. use "#include Matrix.h" to implement sparse matrix ADT into any program. 

### compiling

make sure you have gcc installed.

to compile all component:
List: gcc -std=c17 -Wall -c List.c
Matrix: gcc -std=c17 -Wall -c Matrix.c

then link all the components. gcc -std=c17 -Wall -o (program name) (program object) List.o Matrix.o

## Extra Note
None

