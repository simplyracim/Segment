# Compiler and flags
CXX      = g++
CXXFLAGS = -std=c++20 -I"C:/SFML-3.0.2/include" -I"include"

# SFML libraries
LDFLAGS  = -L"C:/SFML-3.0.2/lib" -lsfml-graphics -lsfml-window -lsfml-system

# Directories
SRC_DIR  = src
OBJ_DIR  = obj
BIN      = app.exe

# Sources / objects
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Default target
all: $(BIN)

# Link step
$(BIN): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

# Compile step (ensure obj/ exists first)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create obj directory if it doesn't exist
$(OBJ_DIR):
	mkdir $(OBJ_DIR)

# Clean up
.PHONY: clean
clean:
	-del /Q $(OBJ_DIR)\*.o $(BIN) 2>nul || true
	-rmdir $(OBJ_DIR) 2>nul || true
