CC=g++

BIN=legolization.out
SRCS=LegoStabilityUtil.cpp LegoBlockGraph.cpp LegoBlockUtils.cpp LegoBlock.cpp
INCLUDES=LegoBlock.h LegoBlockUtils.h LegoBlockGraph.h LegoStabilityUtil.h
MAIN=main.cpp $(SRCS)
UNIT=unit_test.cpp $(SRCS)

all: $(BIN)

$(BIN): $(MAIN) $(INCLUDES)
	g++ --std=c++11 $(MAIN) -lnlopt -lm -o $(BIN)

clean:
	rm -f *~ *.o $(BIN)

unit: $(UNIT) $(INCLUDES)
	g++ --std=c++11 $(UNIT) -lnlopt -lm -o $(BIN)
