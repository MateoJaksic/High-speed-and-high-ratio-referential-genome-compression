CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall

SRC = main.cpp decompressor.cpp
OBJ = $(SRC:.cpp=.o)
BIN = decompressor

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJ) $(BIN)
