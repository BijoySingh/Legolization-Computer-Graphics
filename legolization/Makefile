CC=g++

BIN=legolization.out
SRCS=unit_test.cpp LegoBlockGraph.cpp LegoBlockUtils.cpp LegoBlock.cpp
INCLUDES=LegoBlock.h LegoBlockUtils.h LegoBlockGraph.h

all: $(BIN)

$(BIN): $(SRCS) $(INCLUDES)
	g++ --std=c++11 $(SRCS) -o $(BIN)

clean:
	rm -f *~ *.o $(BIN)
