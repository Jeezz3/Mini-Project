BASE_SOURCES   = List.c Matrix.c
BASE_OBJECTS   = List.o Matrix.o
HEADERS        = List.h Matrix.h
COMPILE        = gcc -std=c17 -Wall -c
LINK           = gcc -std=c17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

Sparse : Sparse.o $(BASE_OBJECTS)
	$(LINK) Sparse Sparse.o $(BASE_OBJECTS)

Sparse.o : Sparse.c $(HEADERS)
	$(COMPILE) Sparse.c

$(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

clean :
	$(REMOVE) Sparse Sparse.o $(BASE_OBJECTS)

checkSparse : FindSparse
	$(MEMCHECK) FindPath in out

checkLClient : ListClient
	$(MEMCHECK) ./ListClient

checkMClient: MatrixClient
	$(MEMCHECK) ./MatrixClient

checkTest: MatrixTest
	$(MEMCHECK) ./MatrixTest

