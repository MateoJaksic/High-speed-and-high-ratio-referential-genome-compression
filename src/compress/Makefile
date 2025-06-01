# automatization of build process
CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall

SRC = main.cpp compressor.cpp
OBJ = $(SRC:.cpp=.o)
BIN = compressor

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJ) $(BIN)

# author: Mateo Jakšić