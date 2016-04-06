CC=g++

BIN=legolization.out
SRCS=main.cpp LegoStabilityUtil.cpp LegoBlockGraph.cpp LegoBlockUtils.cpp LegoBlock.cpp
INCLUDES=LegoBlock.h LegoBlockUtils.h LegoBlockGraph.h LegoStabilityUtil.h

all: $(BIN)

$(BIN): $(SRCS) $(INCLUDES)
	g++ --std=c++11 $(SRCS) -lnlopt -lm -o $(BIN)

clean:
	rm -f *~ *.o $(BIN)
