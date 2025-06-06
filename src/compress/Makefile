# author: Mateo Jakšić
# automatization of build process
CXX = g++
INCLUDES = -I../utils
CXXFLAGS = -std=c++17 -O2 -Wall $(INCLUDES)

SRC = main.cpp compressor.cpp ../utils/utils.cpp
OBJ = $(SRC:.cpp=.o)
BIN = compressor

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BIN)
