MAIN           = Arithmetic
ADT1           = BigInteger
ADT2           = List
SOURCE         = $(MAIN).cpp
OBJECT         = $(MAIN).o
ADT1_TEST      = $(ADT1)Client
ADT1_SOURCE    = $(ADT1).cpp
ADT1_OBJECT    = $(ADT1).o
ADT1_HEADER    = $(ADT1).h
ADT2_TEST      = $(ADT2)Client
ADT2_SOURCE    = $(ADT2).cpp
ADT2_OBJECT    = $(ADT2).o
ADT2_HEADER    = $(ADT2).h
COMPILE        = g++ -std=c++17 -Wall -c
LINK           = g++ -std=c++17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

$(MAIN): $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(MAIN) $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)

$(OBJECT): $(SOURCE) $(ADT1_HEADER) $(ADT2_HEADER)
	$(COMPILE) $(SOURCE)

$(ADT1_OBJECT): $(ADT1_SOURCE) $(ADT1_HEADER)
	$(COMPILE) $(ADT1_SOURCE)

$(ADT2_OBJECT): $(ADT2_SOURCE) $(ADT2_HEADER)
	$(COMPILE) $(ADT2_SOURCE)

clean:
	$(REMOVE) $(MAIN) $(ADT1_TEST) $(ADT2_TEST)
	$(REMOVE) $(OBJECT) $(ADT1_TEST).o $(ADT2_TEST).o $(ADT1_OBJECT) $(ADT2_OBJECT)
