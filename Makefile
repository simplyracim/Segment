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
# Pick up .cpp in src/ and in one-level subdirs: src/core, src/view, etc.
SRC := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*/*.cpp)

# Turn src/foo/bar.cpp into obj/foo/bar.o
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Default target
all: $(BIN)

# Link step
$(BIN): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

# Compile step
# Ensure the target directory (e.g. obj/core/) exists before compiling
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
.PHONY: clean
clean:
	-del /Q $(OBJ_DIR)\*.o $(BIN) 2>nul || true
	-rem Remove subdirectories inside obj
	-for /d %%D in ($(OBJ_DIR)\*) do @rmdir /S /Q "%%D" 2>nul || true
	-rmdir $(OBJ_DIR) 2>nul || true
