# Compiler
CXX = clang++

# Compiler flags
CXXFLAGS = -std=c++20 -Wall -Iinc -Ialgs -Icheckers -Itictactoe

# Linker flags
LDFLAGS = 

# Source files
SRC = $(wildcard src/*.cpp)

# Object files
OBJ = $(SRC:.cpp=.o)

# Executable name
EXEC = gamehub

# Default target
all: $(EXEC)

# Linking
$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

# Compilation
src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f src/*.o $(EXEC)

# Phony targets
.PHONY: all clean
